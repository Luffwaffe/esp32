#include "cardcontroller.h"

cardReader::cardReader(QObject *parent)
{
    this ->mParent = dynamic_cast<cardController*>(parent);
    this->initializeCardConnection();
}

void cardReader::initializeCardConnection()
{
    //Detect CH340 port
    QString CH340Port = "";
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        QString description = port.description().toLower();
        QString manufacturer = port.manufacturer().toLower();

        if (description.contains("ch340") || manufacturer.contains("wch")) {
            CH340Port = port.portName();
            qDebug() << "CH340 detected on port:" << CH340Port << ",  Description:" << port.description();
        }
    }
    ////////////////////////////////
    serial.setPortName(CH340Port);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open port " << serial.portName()
        << ", error: " << serial.errorString() << "\n";
    }
    else{
        qDebug() << "Successfully to open port: " << serial.portName();
    }
}

QString cardReader::handleCard()
{
    QByteArray responseData = "";
    QByteArray atCommand = "AT+ID\r\n";
    while(true){
        if(serial.waitForReadyRead(500)) {
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
                        qDebug() << "Card ID: " << responseData << "\n";
                        this->mParent->roomMap[responseData]->startEnd();
                    } else {
                        qDebug() << "No response received within timeout period\n";
                    }
                }
            }
        }
    }
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

