#ifndef ESP32CONNECTOR_H
#define ESP32CONNECTOR_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <cmdAndStatus.h>
#include<QTimer>
#include<QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>

class esp32Connector;
class connector : public QObject
{
    Q_OBJECT
public:
    QTcpSocket *mainSocket;
public:

    connector(QObject* parent);
    QTimer* heartbeat;
public slots:
    void initializeSocket();
    bool connectToRoom();
    void tryToConnect();
    bool writeDataToRoom(QString data);
    QString readDataFromRoom();
    QString sendCmd(QString cmd);
    void handleResponseFromRoom(QString rep);
    void heartBeat();
public:
    esp32Connector* mParent = nullptr;
};

////////////////////////////////////////////////////////////////////
class esp32Connector : public QObject
{
    Q_OBJECT

public:
    QTime remainingTime;
    QString name;
    QString address;
    quint16 port;
    QThread* thread;
    QTimer* countdownTimer;
    connector* mConnector = nullptr;

    Q_PROPERTY(QString runningStatus READ runningStatus WRITE setRunningStatus NOTIFY runningStatusChanged FINAL)
    Q_PROPERTY(quint16 timeOrder READ timeOrder WRITE setTimeOrder NOTIFY timeOrderChanged FINAL)

    Q_PROPERTY(QString timeStart READ timeStart WRITE setTimeStart NOTIFY timeStartChanged FINAL)
    Q_PROPERTY(QString timeEnd READ timeEnd WRITE setTimeEnd NOTIFY timeEndChanged FINAL)
    Q_PROPERTY(QString timeRemainning READ timeRemainning WRITE setTimeRemainning NOTIFY timeRemainningChanged FINAL)

    esp32Connector(QString name, QString address, quint16 port);

    Q_INVOKABLE void roomBtnClick();
    Q_INVOKABLE void startEnd();
    Q_INVOKABLE void refreshBtnClick();
    Q_INVOKABLE void setTimeBtnClick(quint16 time);
    Q_INVOKABLE QString getRoomInfor(QString infor);
    void timeHandle();
    void createJsonFile(QFile* file);
    void readAndUpdateJsonFile(QFile* file);
    void updatTimeToJson();
    void loadTimeFromJson();
    void jsonTimeHandle();

    QString runningStatus() const;
    void setRunningStatus(const QString &newRunningStatus);
    quint16 timeOrder() const;
    void setTimeOrder(const quint16 &newTimeOrder);
    QString timeStart() const;
    void setTimeStart(QString newTimeStart);
    QString timeEnd() const;
    void setTimeEnd(const QString &newTimeEnd);
    QString timeRemainning() const;
    void setTimeRemainning(const QString &newTimeRemainning);

signals:
    void sendCmd(QString cmd);

    void runningStatusChanged();
    void timeOrderChanged();
    void timeStartChanged();
    void timeEndChanged();
    void timeRemainningChanged();

private:
    QString m_runningStatus;
    quint16 m_timeOrder;
    QString m_timeStart;
    QString m_timeEnd;
    QString m_timeRemainning;
};

#endif
