#include "cardcontroller.h"
cardReader::cardReader(QObject *parent)
{
    this ->mParent = dynamic_cast<cardController*>(parent);
    this->initializeCardConnection();
}

void cardReader::initializeCardConnection()
{
    qDebug() << "Starting to open CH340 port...";
    QString CH340Port = "";
    serial.setPortName("none");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        QString description = port.description().toLower();
        QString manufacturer = port.manufacturer().toLower();

        if (description.contains("ch340") || manufacturer.contains("wch")) {
            CH340Port = port.portName();
            qDebug() << "CH340 detected on port:" << CH340Port << ",  Description:" << port.description();
            serial.setPortName(CH340Port);
            if (!serial.open(QIODevice::ReadWrite)) {
                qDebug() << "Failed to open port " << serial.portName()
                << ", error: " << serial.errorString() << "\n";
            }
            else{
                qDebug() << "Successfully to open port: " << serial.portName();
            }
        }
    }
}

QString cardReader::handleCard()
{
    QByteArray responseData = "";
    QByteArray atCommand = "AT+ID\r\n";
    while(true){
        if(!serial.isOpen()){
            initializeCardConnection();
            QThread::sleep(3);
        }
        else{
            if(serial.waitForReadyRead(5000)) {
                responseData = serial.readAll();
                if(responseData == "\r\n+TAG:1\r\n\n"){
                    serial.write(atCommand);
                    if (!serial.waitForBytesWritten(1000)) {
                        qDebug() << "Failed to write data to port\n";
                    }
                    else{
                        if (serial.waitForReadyRead(1000)) {
                            responseData = serial.readAll().mid(5,8);
                            this->mParent->currentCardID = responseData;
                            qDebug() << "Card ID: " << responseData;
                            if (this->mParent->roomMap.contains(this->mParent->currentCardID)) {
                                esp32Connector* mEsp32Connector = this->mParent->roomMap.value(this->mParent->currentCardID);
                                mEsp32Connector->startEnd();
                            } else {
                                qDebug() << "Card ID not found in roomMap.";
                            }
                        } else {
                            qDebug() << "No response received within timeout period\n";
                        }
                    }
                }
            }
            else{  //check port connection
                if(checkPortConnection() == false){
                    initializeCardConnection();
                }
            }
        }
    }
}

bool cardReader::checkPortConnection()
{
    bool portAvailable = false;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.portName() == serial.portName()) {
            portAvailable = true;
            break;
        }
    }
    if (!portAvailable) {
        qDebug() << "CH340 Serial port disconnected.";
        serial.close();
    }
    return portAvailable;
}


////////////////////////////////////////////////////////////////////////
cardController::cardController() {
    this->currentCardID = "none";
    this->mCardReader = new cardReader(this);
    this->thread = new QThread;
    this->mCardReader->moveToThread(this->thread);
    QObject::connect(thread, &QThread::started, mCardReader, &cardReader::handleCard);
    this->thread->start();
}

void cardController::insertRoomMap(QString IDRoom, esp32Connector* room)
{
    roomMap.insert(IDRoom,room);
}

