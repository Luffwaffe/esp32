#include "cardcontroller.h"

cardReader::cardReader(QObject *parent)
{
    this ->mParent = dynamic_cast<cardController*>(parent);
    this->initializeCardConnection();
}

void cardReader::initializeCardConnection()
{
    serial.setPortName("COM5");
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

QString cardReader::readCardID()
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
    QObject::connect(thread, &QThread::started, mCardReader, &cardReader::readCardID);
    this->thread->start();
}
