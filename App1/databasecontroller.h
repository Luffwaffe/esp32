#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <cmdAndStatus.h>
#include <QTimer>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QDebug>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMutex>

class dataBaseController;

class databaseConnector : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase db;
    QMutex mutex;
    databaseConnector(QObject* parent);
    void getPowerDownInformation(QString roomName, QString* timeStart, QString* timeEnd, QString* usedTime, QString* status); // roomName is input, others are output
public slots:
    void initializeDatabaseConnection();
    void insertDataToDb(QString roomName, QString timeStart, QString timeEnd, QString usedTime);
    void updateDataToPowerDownDb(QString roomName, QString timeStart, QString timeEnd, QString usedTime, QString status);
public:
    dataBaseController* mParent = nullptr;
};


////////////////////////////////////////
class dataBaseController : public QObject
{
    Q_OBJECT
public:
    QThread* thread;
    databaseConnector* mDatabaseConnector = nullptr;
    explicit dataBaseController(QObject *parent = nullptr);

signals:
    void insertDataToDb(QString roomName, QString timeStart, QString timeEnd, QString usedTime);
    void updateDataToPowerDownDb(QString roomName, QString timeStart, QString timeEnd, QString usedTime, QString status);
    void getPowerDownInformation(QString roomName, QString* timeStart, QString* timeEnd, QString* usedTime, QString* status);

};

#endif // DATABASECONTROLLER_H
