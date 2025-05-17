#include "databasecontroller.h"

databaseConnector::databaseConnector(QObject *parent)
{
    this->mParent = dynamic_cast<dataBaseController*>(parent);
}

void databaseConnector::initializeDatabaseConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("roomStartEndDb.db");
    if (!db.open()) {
        qDebug() << "DB: Failed to open database:" << db.lastError().text();
    } else {
        qDebug() << "DB: Database opened successfully.";
    }

    QSqlQuery query(db);
    QString createTable =
        "CREATE TABLE IF NOT EXISTS roomStartEndDb ("
        "room TEXT, "
        "startTime TEXT, "
        "endTime TEXT, "
        "usedTime TEXT"
        ");";

    if (!query.exec(createTable)) {
        qDebug() << "DB: Failed to create table:" << query.lastError().text();
    } else {
        qDebug() << "DB: Table 'roomStartEndDb' created OK.";
    }
}

void databaseConnector::insertDataToDb(QString roomName, QString timeStart, QString timeEnd, QString usedTime)
{
    QSqlQuery insertQuery(this->db);
    insertQuery.prepare("INSERT INTO roomStartEndDb (room, startTime, endTime, usedTime) "
                        "VALUES (?, ?, ?, ?)");
    insertQuery.addBindValue(roomName);
    insertQuery.addBindValue(timeStart);
    insertQuery.addBindValue(timeEnd);
    insertQuery.addBindValue(usedTime);
    if (!insertQuery.exec()) {
        qDebug() << "DB: Insert failed:" << insertQuery.lastError().text();
    }
    else{
        qDebug() << "DB: Successfully update start and end time to DB";
    }
}


///////////////////////////////////////////////////////////////
dataBaseController::dataBaseController(QObject *parent)
    : QObject{parent}
{
    this->mDatabaseConnector = new databaseConnector(this);
    this->thread = new QThread();
    this->mDatabaseConnector->moveToThread(this->thread);
    QObject::connect(thread, &QThread::started, mDatabaseConnector, &databaseConnector::initializeDatabaseConnection);
    QObject::connect(this, &dataBaseController::insertDataToDb, mDatabaseConnector, &databaseConnector::insertDataToDb,Qt::QueuedConnection);
    this->thread->start();
}

