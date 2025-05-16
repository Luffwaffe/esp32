#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include <QObject>
#include <cmdAndStatus.h>
#include <QTimer>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QDebug>
#include <QThread>

class cardController;

class cardReader : public QObject
{
    Q_OBJECT
public:

    QSerialPort serial;
    QTimer* heartbeat;

    cardReader(QObject* parent);
public slots:
    void initializeCardConnection();
    // void tryToConnect();
    QString readCardID();
    // void heartBeat();
public:
    cardController* mParent = nullptr;
};

//////////////////////////////////////////////////
class cardController : public QObject
{
    Q_OBJECT
public:
    QString currentCardID;
    QThread* thread;
    cardReader* mCardReader = nullptr;

    cardController();
};

#endif // CARDCONTROLLER_H
