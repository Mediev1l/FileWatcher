#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "filetrackermodel.h"
#include "filetracker.h"
#include "timestampmodel.h"
#include "timestamp.h"
#include "watcher.h"
#include "catdownloader.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<FileTrackerModel>("FileWatcher", 1, 0, "FileTrackerModel");
    qmlRegisterType<TimestampModel>("FileWatcher", 1, 0, "TimestampModel");

    qmlRegisterUncreatableType<FileTracker>("FileWatcher", 1, 0, "FileTracker", QStringLiteral("Should not create in QML"));
    qmlRegisterUncreatableType<Timestamp>("FileWatcher", 1, 0, "Timestamp", QStringLiteral("Should not create in QML"));
    qmlRegisterUncreatableType<Watcher>("FileWatcher", 1, 0, "Watcher", QStringLiteral("Should not create in QML"));
    qmlRegisterUncreatableType<CatDownloader>("FileWatcher", 1, 0, "CatDownloader", QStringLiteral("Should not create in QML"));

    FileTracker fileTracker;
    Timestamp timestamp;
    Watcher watcher;
    CatDownloader catDownloader;

    Event::connect(&watcher, &Watcher::newEvent, &timestamp, &Timestamp::appendItem);
    Event::connect(&watcher, &Watcher::fileRemoved, &catDownloader, &CatDownloader::downloadCat);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("fileTracker"), &fileTracker);
    engine.rootContext()->setContextProperty(QStringLiteral("timestamp"), &timestamp);
    engine.rootContext()->setContextProperty(QStringLiteral("watcher"), &watcher);
    engine.rootContext()->setContextProperty(QStringLiteral("catDownloader"), &catDownloader);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
