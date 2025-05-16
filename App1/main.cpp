#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <esp32connector.h>
#include <QQmlContext>
#include <cardcontroller.h>
#include "cmdAndStatus.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // model
    esp32Connector* room1 = new esp32Connector("Room1","192.168.1.1", 12345);
    engine.rootContext()->setContextProperty("room1model", room1);
    // esp32Connector* room2 = new esp32Connector("Room2","192.168.1.1", 12345);
    // engine.rootContext()->setContextProperty("room2model", room2);

    //card controller
    cardController* mCardController = new cardController();
    mCardController->insertRoomMap(IDRoom1,room1);
    // mCardController->insertRoomMap(IDRoom2,room2);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("App1", "Main");


    return app.exec();
}
