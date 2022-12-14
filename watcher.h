#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QUrl>
#include <QMutexLocker>

#include "event.h"

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = nullptr);

signals:
    void NewEvent(const Event& ev);

public slots:
    void addPathToWatch(QUrl path);
    void removePathFromWatcher(QUrl path);
    void fileHandler(const QString& path);
    void directoryHandler(const QString& path);
    void trackFiles(bool value);

private:
    // helpers
    void scanFiles(const QString& root);
    QStringList getFilesByDir(const QString& path);
    QStringList searchInSaved(QString p);
    QString getAbsPath(const QString& path);
    void sendEvent(Event::Type type, const QString& path, bool isFolder);
    QStringList pathIntersect(const QStringList& left, const QStringList& right);

private:
    QFileSystemWatcher m_watcher;
    QStringList m_files;
    QMutex m_mutex;
    bool m_track;

};

#endif // WATCHER_H
