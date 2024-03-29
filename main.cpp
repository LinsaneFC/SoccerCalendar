#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QSslSocket>

#include "httprequestandparse.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterType<HTTPRequestAndParse>("HttpRequestAndParse", 1, 0, "HttpRequestAndParse");
    qmlRegisterType<Database>("Database", 1, 0, "Database");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
