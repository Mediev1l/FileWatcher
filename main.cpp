#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "filetrackermodel.h"
#include "filetracker.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<FileTrackerModel>("FileWatcher", 1, 0, "FileTrackerModel");
    qmlRegisterUncreatableType<FileTracker>("FileWatcher", 1, 0, "FileTracker", QStringLiteral("Should not create in QML"));

    FileTracker fileTracker;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("fileTracker"),&fileTracker);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
