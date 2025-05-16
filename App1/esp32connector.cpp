#include "esp32connector.h"

connector::connector(QObject* parent)
{
    this->mParent = (esp32Connector*)parent;
}

void connector::initializeSocket()
{
    mainSocket = new QTcpSocket(this);
    discoverSocket = new QUdpSocket(this);
    this->discoverSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    discoverSocket->bind(0);

    connect(mainSocket, &QTcpSocket::connected, this, [&]() {
        qDebug() << mParent->name + ": Connected to server!";
        this->sendCmd(getRunningStatusCmd);
    });
    connect(mainSocket, &QTcpSocket::disconnected, this, [&]() {
        qDebug() << mParent->name + ": Disconnected to server!";
        this->handleResponseFromRoom(notConnectStatus);
        tryToConnect();
    });

    while (connectToRoom() != true) {
         qDebug() << mParent->name+ ": Try to connect to server!";
    }
    heartBeat();
}

bool connector::connectToRoom()
{
    bool retval = false;
    //UDP
    discoverSocket->writeDatagram(this->mParent->getRoomInfor("name").toUtf8().data(), QHostAddress::Broadcast, 9999);
    while (discoverSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(discoverSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        discoverSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << this->mParent->getRoomInfor("name") +": Received datagram: " << datagram;

        if (datagram == this->mParent->getRoomInfor("name")) {
            qDebug() << this->mParent->getRoomInfor("name") + ": discovered at: " << sender.toString();
            this->mParent->address = sender.toString();
            // this->mParent->port = 12345;
        }
    }

    //TCP
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
        qDebug() << this->mParent->getRoomInfor("name") + ": Successfully wrote: " + data;
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
        this->readDataFromRoom();
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
        qDebug()<<this->mParent->name+": "+"Heartbeat";
        this->sendCmd(getRunningStatusCmd);
        if(this->mParent->runningStatus() == startedStatus){ // log the current using time to a json, handle for power down
            qDebug()<<this->mParent->name+": "+"update used time";
            QTime current = QTime::currentTime();
            QTime startTime = QTime::fromString(this->mParent->timeStart(), "HH:mm:ss");

            int secondsUsing = startTime.secsTo(current);
            if (secondsUsing < 0) {
                qDebug() << "current time is before start time (maybe it's for the next day).";
                secondsUsing += 24 * 60 * 60;
            }
            QString usingTime = QTime(0, 0).addSecs(secondsUsing).toString();
        }
    });
    heartbeat->start(60000); // Tick every second
}

////////////////////////////////////////////////////////////////////////////////
esp32Connector::esp32Connector(QString name, QString address, quint16 port) {
    this->name = name;
    this->address = address;
    this->port = port;
    this->setRunningStatus(notConnectStatus);
    this->mConnector = new connector(this);
    this->thread = new QThread;
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
    if(this->runningStatus() == startedStatus){
        emit this->sendCmd(endCmd);
        // handleUsedTimeAndUpdateStartStopTime(endCmd); //stop used time timer and update end time (keep start time)
    }
    else if(this->runningStatus() == endStatus){
        emit this->sendCmd(startCmd);
        // handleUsedTimeAndUpdateStartStopTime(startCmd); //start used time timer and update start time as current time (keep end time)
    }
    else if(this->runningStatus() == notConnectStatus){
        qDebug()<<this->name+ ": "+"No connection";
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
