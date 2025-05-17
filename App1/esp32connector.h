#ifndef ESP32CONNECTOR_H
#define ESP32CONNECTOR_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <cmdAndStatus.h>
#include<QTimer>
#include<QTime>
#include <QFile>
#include <QUdpSocket>

class esp32Connector;
class connector : public QObject
{
    Q_OBJECT
public:
    QTcpSocket *mainSocket;
    QUdpSocket *discoverSocket;
    connector(QObject* parent);
    QTimer* heartbeat;
    QTimer* usedTimeTimer;
    QTime usedTime = QTime(0, 0, 0);
public slots:
    void initializeSocket();
    bool connectToRoom();
    void tryToConnect();
    bool writeDataToRoom(QString data);
    QString readDataFromRoom();
    QString sendCmd(QString cmd);
    void handleResponseFromRoom(QString rep);
    void heartBeat();
    bool isDisconnectFromPeer();
    void handleStartRoom();
    void handleEndedRoom();
public:
    esp32Connector* mParent = nullptr;
};

////////////////////////////////////////////////////////////////////
class esp32Connector : public QObject
{
    Q_OBJECT

public:
    QString name;
    QString address;
    quint16 port;
    QThread* thread;
    connector* mConnector = nullptr;

    Q_PROPERTY(QString runningStatus READ runningStatus WRITE setRunningStatus NOTIFY runningStatusChanged FINAL)
    Q_PROPERTY(QString timeStart READ timeStart WRITE setTimeStart NOTIFY timeStartChanged FINAL)
    Q_PROPERTY(QString timeEnd READ timeEnd WRITE setTimeEnd NOTIFY timeEndChanged FINAL)
    Q_PROPERTY(QString timeRemainning READ timeRemainning WRITE setTimeRemainning NOTIFY timeRemainningChanged FINAL)

    esp32Connector(QString name, QString address, quint16 port);

    Q_INVOKABLE void startEnd();
    Q_INVOKABLE QString getRoomInfor(QString infor);

    QString runningStatus() const;
    void setRunningStatus(const QString &newRunningStatus);
    QString timeStart() const;
    void setTimeStart(QString newTimeStart);
    QString timeEnd() const;
    void setTimeEnd(const QString &newTimeEnd);
    QString timeRemainning() const;
    void setTimeRemainning(const QString &newTimeRemainning);

signals:
    void sendCmd(QString cmd);
    void runningStatusChanged();
    void timeStartChanged();
    void timeEndChanged();
    void timeRemainningChanged();

private:
    QString m_runningStatus;
    QString m_timeStart;
    QString m_timeEnd;
    QString m_timeRemainning;
};

#endif
