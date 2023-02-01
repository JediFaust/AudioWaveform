#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "audioamplitude.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/AudioAmplitude/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<audioamplitude>("AudioAmplitude", 1, 0, "AudioAmplitude");
    engine.load(url);

    return app.exec();
}
