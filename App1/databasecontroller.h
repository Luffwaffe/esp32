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

class dataBaseController;

class databaseConnector : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase db;
    databaseConnector(QObject* parent);
public slots:
    void initializeDatabaseConnection();
    void insertDataToDb(QString roomName, QString timeStart, QString timeEnd, QString usedTime);
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
};

#endif // DATABASECONTROLLER_H
