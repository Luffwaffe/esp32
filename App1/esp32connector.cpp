#include "esp32connector.h"

connector::connector(QObject* parent)
{
    this->mParent = (esp32Connector*)parent;
}

void connector::initializeSocket()
{
    mainSocket = new QTcpSocket(this);
    discoverSocket = new QUdpSocket(this);
    this->discoverSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 0);
    discoverSocket->bind(0);

    connect(mainSocket, &QTcpSocket::connected, this, [&]() {
        qDebug() << mParent->name + ": Connected to TCP Esp32!";
        this->sendCmd(getRunningStatusCmd);
    });
    connect(mainSocket, &QTcpSocket::disconnected, this, [&]() {
        qDebug() << mParent->name + ": Disconnected to TCP Esp32, re-connect now...!";
        this->handleResponseFromRoom(notConnectStatus);
        tryToConnect();
    },Qt::QueuedConnection);

    tryToConnect();
    heartBeat();
}

bool connector::connectToRoom()
{
    bool retval = false;
    //UDP
    if(discoverSocket->writeDatagram(this->mParent->getRoomInfor("name").toUtf8().data(), QHostAddress::Broadcast, 9999)){
        if (discoverSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(discoverSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            discoverSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            qDebug() << this->mParent->getRoomInfor("name") +": Received UDP message from Esp32: " << datagram;

            if (datagram == this->mParent->getRoomInfor("name")){
                qDebug() << this->mParent->getRoomInfor("name") + ": discovered Esp32 at: " << sender.toString();
                this->mParent->address = sender.toString();
                //TCP
                this->mainSocket->connectToHost(mParent->address, mParent->port);
                if (this->mainSocket->waitForConnected(3000)){
                    retval = true;
                }
                else{
                    qDebug() << mParent->name+ ": Failed to connect to TCP Esp32!";
                }
            }
        }
        else{
            qDebug() << mParent->name+ ": Failed to connect to UDP Esp32!";
            QThread::sleep(1);
        }
    }
    else {
        qDebug() << mParent->name+ ": Failed to write to UDP Esp32!";
        QThread::sleep(1);
    }
    return retval;
}

void connector::tryToConnect()
{
    if (mainSocket) {
        mainSocket->deleteLater();
    }
    if (discoverSocket) {
        discoverSocket->deleteLater();
    }
    mainSocket = new QTcpSocket(this);
    discoverSocket = new QUdpSocket(this);
    this->discoverSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 0);
    discoverSocket->bind(0);

    connect(mainSocket, &QTcpSocket::connected, this, [&]() {
        qDebug() << mParent->name + ": Connected to TCP Esp32!";
        this->sendCmd(getRunningStatusCmd);
    });
    connect(mainSocket, &QTcpSocket::disconnected, this, [&]() {
        qDebug() << mParent->name + ": Disconnected to TCP Esp32 re-connect now...!";
        this->handleResponseFromRoom(notConnectStatus);
        tryToConnect();
    },Qt::QueuedConnection);

    while (true) {
        qDebug() << mParent->name + ": Try to connect to Esp32!";
        if(this->connectToRoom()){
            break;
        }
    }
}

bool connector::writeDataToRoom(QString data)
{
    bool retval = false;
    this->mainSocket->write(data.toUtf8());
    if(mainSocket->waitForBytesWritten(1000)){
        qDebug() << this->mParent->getRoomInfor("name") + ": Successfully wrote to TCP Esp32: " + data;
        retval =  true;
    }
    else {
        qDebug() << mParent->name+"Write failed to TCP Esp32:" << this->mainSocket->errorString();
    }
    return retval;
}

QString connector::readDataFromRoom()
{
    QString data ="";
    if (this->mainSocket->waitForReadyRead(1000)){
        data = QString::fromUtf8(this->mainSocket->readAll());
        if(data != ""){
            qDebug() << mParent->name+": Received data from TCP Esp32"+": "+ data;
            this->handleResponseFromRoom(data);
        }
    }
    else{
        data = "ERROR";
    }
    return data;
}

QString connector::sendCmd(QString cmd)
{
    QString rep;
    if(this->writeDataToRoom(cmd) == true){
        rep = this->readDataFromRoom();
    }

    if(rep == endStatus){
        handleEndedRoom();
    }
    else if(rep == startedStatus){
        handleStartRoom();
    }
    return rep;
}

void connector::handleResponseFromRoom(QString rep)
{
    if(rep == notConnectStatus){
        mParent->setRunningStatus(rep);
    }
    else if(rep == startedStatus){
        mParent->setRunningStatus(rep);
    }
    else if(rep == endStatus){
        mParent->setRunningStatus(rep);
    }
}

void connector::heartBeat(){
    static int tryTime = 0;
    heartbeat = new QTimer(this);
    connect(heartbeat, &QTimer::timeout, this, [=]() mutable {
        static int index = 0;
        index ++;
        ///////////////////////check connection
        if(index%5 == 0){
            qDebug()<<this->mParent->name+": "+"Heartbeat to Esp32";
            if(this->isDisconnectFromPeer()){
                mainSocket->disconnectFromHost();
                if (mainSocket->state() != QAbstractSocket::UnconnectedState) {
                    mainSocket->waitForDisconnected();
                }
            }
        }
        ////////////////////Handle used time counting
        if(this->mParent->runningStatus() == startedStatus){
            qDebug()<<this->mParent->getRoomInfor("name")+": "+"counting used time";
            usedTime = usedTime.addSecs(1);
            this->mParent->setTimeRemainning(usedTime.toString());

            /// write to datdbase each 60s
            if(index == 60){
                index = 0;
                qDebug()<<this->mParent->getRoomInfor("name")+": "+"update to database";
            }
        }
        ////////////////////////////////////////
    });
    heartbeat->start(1000); // Tick every 3 second
}

bool connector::isDisconnectFromPeer()
{
    bool retVal = true;
    if(this->writeDataToRoom(getRunningStatusCmd) == true){
        if (this->mainSocket->waitForReadyRead(2000)){
            auto data = QString::fromUtf8(this->mainSocket->readAll());
            if(data != ""){
                qDebug() << mParent->name+": Received data from TCP Esp32"+": "+ data;
                this->handleResponseFromRoom(data);
                retVal = false;
            }
        }
        else{
            qDebug() <<  mParent->name+": Disconnected from Esp32";
        }
    }
    return retVal;
}

void connector::handleStartRoom()
{
    this->usedTime = QTime(0,0,0);
    QTime currentTime = QTime::currentTime();
    this->mParent->setTimeStart(currentTime.toString());
    emit this->mParent->mDataBaseController->insertDataToDb(this->mParent->getRoomInfor("name"),
                                                            this->mParent->timeStart(),"caculating","caculating");
}
void connector::handleEndedRoom()
{
    if(this->mParent->timeStart() != QTime(0,0,0).toString()){
        QTime currentTime = QTime::currentTime();
        this->mParent->setTimeEnd(currentTime.toString());
        emit this->mParent->mDataBaseController->insertDataToDb(this->mParent->getRoomInfor("name"),
                                                                this->mParent->timeStart(),this->mParent->timeEnd(),
                                                                this->usedTime.toString());
    }
    else{
        qDebug() <<  mParent->name+": First time read status skip set time end";
    }
}

////////////////////////////////////////////////////////////////////////////////
esp32Connector::esp32Connector(QString name, dataBaseController* dataBaseController, quint16 port) {
    this->name = name;
    this->mDataBaseController = dataBaseController;
    this->port = port;
    this->setRunningStatus(notConnectStatus);
    this->setTimeStart(QTime(0,0,0).toString());
    this->setTimeEnd(QTime(0,0,0).toString());
    this->setTimeRemainning(QTime(0,0,0).toString());
    this->mConnector = new connector(this);
    this->thread = new QThread;

    this->mConnector->moveToThread(this->thread);
    QObject::connect(thread, &QThread::started, mConnector, &connector::initializeSocket);
    QObject::connect(this,&esp32Connector::sendCmd, mConnector, &connector::sendCmd);
    this->thread->start();
}

void esp32Connector::startEnd()
{
    if(this->runningStatus() == startedStatus){
        emit this->sendCmd(endCmd);
        // handleUsedTimeAndUpdateStartStopTime(endCmd); //stop used time timer and update end time (keep start time)
    }
    else if(this->runningStatus() == endStatus){
        emit this->sendCmd(startCmd);
        // handleUsedTimeAndUpdateStartStopTime(startCmd); //start used time timer and update start time as current time (keep end time)
    }
    else if(this->runningStatus() == notConnectStatus){
        qDebug()<<this->name+ ": "+"No Esp32 connection";
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
