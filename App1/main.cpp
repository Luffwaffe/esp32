#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <esp32connector.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // model
    esp32Connector* room1 = new esp32Connector("Room1","192.168.1.33", 3333);
    engine.rootContext()->setContextProperty("room1model", room1);
    // esp32Connector* room2 = new esp32Connector("Room2","127.0.0.1", 1234);
    // engine.rootContext()->setContextProperty("room2model", room2);

    //

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("App1", "Main");


    return app.exec();
}
