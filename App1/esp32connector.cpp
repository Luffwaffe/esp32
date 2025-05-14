#include "esp32connector.h"

connector::connector(QObject* parent)
{
    this->mParent = (esp32Connector*)parent;
}

void connector::initializeSocket()
{
    mainSocket = new QTcpSocket(this);
    connect(mainSocket, &QTcpSocket::connected, this, [&]() {
        qDebug() << mParent->name + ": Connected to server!";
        this->sendCmd(getRunningStatusCmd);
    });
    connect(mainSocket, &QTcpSocket::disconnected, this, [&]() {
        qDebug() << mParent->name + ": Disconnected to server!";
        this->handleResponseFromRoom(notConnectStatus);
        tryToConnect();
    });
    // connect(mainSocket, &QTcpSocket::readyRead, this, &connector::readDataFromRoom);
    this->sendCmd(notConnectStatus);
    while (connectToRoom() != true) {
         qDebug() << mParent->name+ ": Try to connect to server!";
    }
    heartBeat();
}

bool connector::connectToRoom()
{
    bool retval = false;
    this->mainSocket->connectToHost(mParent->address, mParent->port);
    if (this->mainSocket->waitForConnected(3000)) {
        retval = true;
    }
    else{
        qDebug() << mParent->name+ ": Failed to connect to server!";
    }
    return retval;
}

void connector::tryToConnect()
{
    if (mainSocket) {
        mainSocket->deleteLater();
    }
    mainSocket = new QTcpSocket(this);
    connect(mainSocket, &QTcpSocket::connected, this, [&]() {
        qDebug() << mParent->name + ": Connected to server!";
        this->sendCmd(getRunningStatusCmd);
    });
    connect(mainSocket, &QTcpSocket::disconnected, this, [&]() {
        qDebug() << mParent->name + ": Disconnected to server!";
        this->handleResponseFromRoom(notConnectStatus);
        tryToConnect();
    });
    // connect(mainSocket, &QTcpSocket::readyRead, this, &connector::readDataFromRoom);

    while (true) {
        qDebug() << mParent->name + ": Try to connect to server!";
        if(this->connectToRoom()){
            break;
        }
    }
}

bool connector::writeDataToRoom(QString data)
{
    bool retval = false;
    if(this->mainSocket->write(data.toUtf8()) != -1){
        qDebug() << "Successfully wrote: " + data;
        retval =  true;
    }
    else {
        qDebug() << "Write failed:" << this->mainSocket->errorString();
    }
    return retval;
}

QString connector::readDataFromRoom()
{
    QString data ="";
    if (this->mainSocket->waitForReadyRead(3000)){
        data = QString::fromUtf8(this->mainSocket->readAll());
        if(data != ""){
            qDebug() << "Received data from:"+ mParent->name +": "+ data;
            this->handleResponseFromRoom(data);
        }
    }
    else{
        data = "ERROR";
    }
    return "data";
}

QString connector::sendCmd(QString cmd)
{
    QString rep;
    if(this->writeDataToRoom(cmd) == true){
    }
    this->readDataFromRoom();
    return rep;
}

void connector::handleResponseFromRoom(QString rep)
{
    if(rep == notConnectStatus){
        mParent->setRunningStatus(rep);
    }
    else if(rep == startedStatus){

        auto currentStatus = mParent->runningStatus();
        if(currentStatus == notConnectStatus){

            mParent->loadTimeFromJson();
        }
        else if(currentStatus == endStatus) {
            mParent->updatTimeToJson();
        }
        mParent->setRunningStatus(rep);
    }
    else if(rep == endStatus){
        auto currentStatus = mParent->runningStatus();
        if(currentStatus == startedStatus) {
            mParent->updatTimeToJson();
        }
        mParent->setRunningStatus(rep);
    }
}

void connector::heartBeat(){
    static int tryTime = 0;
    heartbeat = new QTimer(this);
    connect(heartbeat, &QTimer::timeout, this, [=]() mutable {
        qDebug()<<this->mParent->name+": "+"Heartbeat";
        this->sendCmd(getRunningStatusCmd);
        auto reply = readDataFromRoom();
        if(this->mParent->runningStatus() == startedStatus){
            qDebug()<<this->mParent->name+": "+"update remaining time";
            QTime current = QTime::currentTime();
            QTime endTime = QTime::fromString(this->mParent->timeEnd(), "HH:mm:ss");

            int secondsRemaining = current.secsTo(endTime);
            if (secondsRemaining < 0) {
                qDebug() << "End time is before start time (maybe it's for the next day).";
                secondsRemaining += 24 * 60 * 60;
            }
            QString remainingTime = QTime(0, 0).addSecs(secondsRemaining).toString();

            QFile file("roomTimeData.json");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Failed to open file:" << file.errorString();
                return;
            }
            QByteArray data = file.readAll();
            file.close();
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "JSON parse error:" << parseError.errorString();
                return;
            }

            if (!jsonDoc.isArray()) {
                qDebug() << "JSON is not an array.";
                return;
            }

            QJsonArray jsonArray = jsonDoc.array();
            for (int i = 0; i < jsonArray.size(); ++i) {
                QJsonObject obj = jsonArray[i].toObject();
                QString name = obj["name"].toString();
                if(name == this->mParent->name){
                    obj["remainning"] = remainingTime;
                    obj["endTimeReal"] = current.toString();
                    jsonArray[i] = obj;

                    QJsonDocument updatedDoc(jsonArray);
                    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                        qDebug() << "Failed to open file for writing";
                        return;
                    }
                    file.write(updatedDoc.toJson(QJsonDocument::Indented));
                    file.close();
                }
            }
        }
    });
    heartbeat->start(60000); // Tick every second
}

////////////////////////////////////////////////////////////////////////////////
esp32Connector::esp32Connector(QString name, QString address, quint16 port) {
    this->name = name;
    this->address = address;
    this->port = port;
    this->setTimeOrder(0);
    this->setRunningStatus(notConnectStatus);
    this->mConnector = new connector(this);
    this->thread = new QThread;
    this->countdownTimer = new QTimer();
    connect(countdownTimer, &QTimer::timeout, this, [&]() mutable {
        if (remainingTime == QTime(0, 0, 0)) {
            countdownTimer->stop();
            qDebug() << this->name+ ": Countdown finished!";
            emit this->startEnd();
            return;
        }

        remainingTime = remainingTime.addSecs(-1);
        this->setTimeRemainning(remainingTime.toString("hh:mm:ss"));
    });

    this->mConnector->moveToThread(this->thread);
    QObject::connect(thread, &QThread::started, mConnector, &connector::initializeSocket);
    QObject::connect(this,&esp32Connector::sendCmd, mConnector, &connector::sendCmd);
    this->thread->start();
}
void esp32Connector::roomBtnClick()
{

}


void esp32Connector::startEnd()
{
    if(this->runningStatus() == startedStatus
        ){
        emit this->sendCmd(endCmd);
        this->setTimeOrder(0);
        this->countdownTimer->stop();
    }
    else if(this->runningStatus() == endStatus
            && this->timeOrder() != 0){
        emit this->sendCmd(startCmd);
        timeHandle();
    }
    else if(this->runningStatus() == notConnectStatus){
        qDebug()<<this->name+ ": "+"No connection";
    }
    else{
        qDebug()<<this->name+ ": "+"Did not set timer order";
    }
}

void esp32Connector::refreshBtnClick()
{
    this->mConnector->connectToRoom();
}

void esp32Connector::setTimeBtnClick(quint16 time)
{
    //time format is hhmm: 1234 ~ 12h 44m
    quint16 minute = time/100*60 +time%100;
    if(this->runningStatus() == endStatus){
        qDebug()<<this->name+ " set time: "+QString::number(minute);
        this->setTimeOrder(minute);
    }
    else{
         qDebug()<<this->name+ ": "+"Can not set time";
    }
}

QString esp32Connector::getRoomInfor(QString infor)
{
    QString retVal = "";
    if(infor == "name"){
        retVal =  this->name;
    }
    else if(infor == "address"){
        retVal = this->address + ":"+QString::number(this->port);
    }
    return retVal;
}

QString esp32Connector::runningStatus() const
{
    return m_runningStatus;
}

void esp32Connector::setRunningStatus(const QString &newRunningStatus)
{
    if (m_runningStatus == newRunningStatus)
        return;
    m_runningStatus = newRunningStatus;
    emit runningStatusChanged();
}

void esp32Connector::timeHandle()
{

    QTime startTime = QTime::currentTime();
    QTime endTime = startTime.addSecs(this->timeOrder()*60);

    quint16 hh = this->timeOrder()/60;
    quint16 mm = this->timeOrder()%60;
    remainingTime = QTime(hh, mm, 0);
    qDebug() << this->name+ "remainning time: "<<hh<<mm;
    this->setTimeStart(startTime.toString("hh:mm:ss"));
    this->setTimeEnd(endTime.toString("hh:mm:ss"));
    this->setTimeRemainning(remainingTime.toString("hh:mm:ss"));
    countdownTimer->start(1000);
}

void esp32Connector::createJsonFile(QFile* file) {
    //////////////////////////////////////////////////////////////////////
    QTime current = QTime::currentTime();
    QTime endTime = QTime::fromString(this->timeEnd(), "HH:mm:ss");

    int secondsRemaining = current.secsTo(endTime);
    if (secondsRemaining < 0) {
        qDebug() << "End time is before start time (maybe it's for the next day).";
        secondsRemaining += 24 * 60 * 60;
    }
    QString remainingTime = QTime(0, 0).addSecs(secondsRemaining).toString();
    //////////////////////////////////////////////////////////////////
    QString currentTime = current.toString("hh:mm:ss");
    QJsonArray jsonArray;
    for (int i = 1; i <= 8; ++i) {
        QJsonObject obj;
        obj["name"] = QString("Room") + QString::number(i);
        if(obj["name"] == this->name){
            obj["startTime"] = this->timeStart();
            obj["endTime"] =  this->timeEnd();
            obj["endTimeReal"] =  currentTime;
            obj["remainning"] =  remainingTime;
        }
        else{
            obj["startTime"] = "00:00:00";
            obj["endTime"] =  "00:00:00";
            obj["endTimeReal"] =  "00:00:00";
            obj["remainning"] =  "00:00:00";
        }
        jsonArray.append(obj);
    }

    QJsonDocument jsonDoc(jsonArray);

    if (!file->open(QIODevice::ReadWrite)) {
        qDebug() << "Could not open file for writing.";
        return;
    }

    file->write(jsonDoc.toJson());
    file->close();
    qDebug() << "JSON file created successfully.";
}

void esp32Connector::readAndUpdateJsonFile(QFile* file)
{
    QTime current = QTime::currentTime();
    QString currentTime = current.toString("hh:mm:ss");
    QTime endTime = QTime::fromString(this->timeEnd(), "HH:mm:ss");

    int secondsRemaining = current.secsTo(endTime);
    if (secondsRemaining < 0) {
        qDebug() << "End time is before start time (maybe it's for the next day).";
        secondsRemaining += 24 * 60 * 60;
    }
    QString remainingTime = QTime(0, 0).addSecs(secondsRemaining).toString();


    QByteArray data = file->readAll();
    file->close();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return;
    }

    if (!jsonDoc.isArray()) {
        qDebug() << "JSON is not an array.";
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject obj = jsonArray[i].toObject();
        QString name = obj["name"].toString();
        if(name == this->name){
            QString startTime = obj["startTime"].toString();
            QString endTime = obj["endTime"].toString();

            qDebug() << "Name:" << name;
            qDebug() << "oldStartTime:" << startTime;
            qDebug() << "oldEndTime:" << endTime;

            obj["startTime"] = this->timeStart();
            obj["endTime"] = this->timeEnd();
            obj["endTimeReal"] =  currentTime;
            obj["remainning"] = remainingTime;
            jsonArray[i] = obj;

            QJsonDocument updatedDoc(jsonArray);
            if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                qDebug() << "Failed to open file for writing";
                return;
            }
            file->write(updatedDoc.toJson(QJsonDocument::Indented));
            file->close();
            qDebug() << "Name:" << name;
            qDebug() << "newStartTime:" << obj["startTime"];
            qDebug() << "newEndTime:" << obj["endTime"];
            qDebug() << "newEndTimeReal:" << obj["endTimeReal"];

        }
    }
}

void esp32Connector::updatTimeToJson()
{
    qDebug()<<this->name+": "<<"updatTimeToJson";
    QFile file("roomTimeData.json");
    if(!file.exists()){
        this->createJsonFile(&file);
    }
    else if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Could not open file for reading create new one.";
    }
    else{ //case disconnect while room is still running
        this->readAndUpdateJsonFile(&file);
    }
}

void esp32Connector::loadTimeFromJson()
{
    QFile file("roomTimeData.json");
    if(!file.exists()){
        this->createJsonFile(&file);
    }
    else if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Could not open file for reading create new one.";
    }
    else{
        qDebug()<<this->name+": "<<"loadTimeFromJson";
        QByteArray data = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            return;
        }

        if (!jsonDoc.isArray()) {
            qDebug() << "JSON is not an array.";
            return;
        }

        QJsonArray jsonArray = jsonDoc.array();
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject obj = jsonArray[i].toObject();
            QString name = obj["name"].toString();
            if(name == this->name){
                QString startTime = obj["startTime"].toString();
                QString endTime = obj["endTime"].toString();

                qDebug() << "Name:" << name;
                qDebug() << "currentStartTime:" << startTime;
                qDebug() << "currentEndTime:" << endTime;
                this->setTimeStart(startTime);
                this->setTimeEnd(endTime);

                ////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief newStartTime
                ///////////////////////////////////////////////////////////////////////////////////////////
                QTime newStartTime = QTime::currentTime();
                QTime newEndTime = QTime::fromString(this->timeEnd(), "HH:mm:ss");

                int secondsRemaining = newStartTime.secsTo(newEndTime);
                if (secondsRemaining < 0) {
                    qDebug() << "End time is before start time (maybe it's for the next day).";
                    // Optionally handle overnight wrap-around:
                    secondsRemaining += 24 * 60 * 60; // Add 24 hours in seconds
                }
                QTime remainingTime = QTime(0, 0).addSecs(secondsRemaining);
                //counter
                qDebug() << this->name+ remainingTime.toString("HH:mm:ss");
                QTimer* subCountdownTimer = new QTimer(this);
                connect(subCountdownTimer, &QTimer::timeout, this, [=]() mutable {
                    if (remainingTime == QTime(0, 0, 0) || this->runningStatus() == endStatus
                        || this->runningStatus() == notConnectStatus) {
                        subCountdownTimer->stop();
                        qDebug() << this->name+ ": Countdown finished!";
                        emit this->startEnd();
                        return;
                    }

                    remainingTime = remainingTime.addSecs(-1);
                    this->setTimeRemainning(remainingTime.toString("hh:mm:ss"));
                });
                subCountdownTimer->start(1000); // Tick every second

                this->setTimeRemainning(remainingTime.toString("hh:mm:ss"));
            }
        }
    }
}

void esp32Connector::jsonTimeHandle()
{

}


quint16 esp32Connector::timeOrder() const
{
    return m_timeOrder;
}

void esp32Connector::setTimeOrder(const quint16 &newTimeOrder)
{
    if (m_timeOrder == newTimeOrder)
        return;
    m_timeOrder = newTimeOrder;
    emit timeOrderChanged();
}

QString esp32Connector::timeStart() const
{
    return m_timeStart;
}

void esp32Connector::setTimeStart(QString newTimeStart)
{
    if (m_timeStart == newTimeStart)
        return;
    m_timeStart = newTimeStart;
    emit timeStartChanged();
}

QString esp32Connector::timeEnd() const
{
    return m_timeEnd;
}

void esp32Connector::setTimeEnd(const QString &newTimeEnd)
{
    if (m_timeEnd == newTimeEnd)
        return;
    m_timeEnd = newTimeEnd;
    emit timeEndChanged();
}

QString esp32Connector::timeRemainning() const
{
    return m_timeRemainning;
}

void esp32Connector::setTimeRemainning(const QString &newTimeRemainning)
{
    if (m_timeRemainning == newTimeRemainning)
        return;
    m_timeRemainning = newTimeRemainning;
    emit timeRemainningChanged();
}
