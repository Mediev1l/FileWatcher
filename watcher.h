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
    void fileChanged(const QString& path);
    void directoryHandler(const QString& path);

private:
    // helpers
    void scanFiles(const QString& root);
    QStringList getFilesByDir(const QString& path);
    int getIndexByPath(const QString& p);
    QStringList searchInSaved(QString p);
    QString getAbsPath(const QString& path);
    void sendEvent(const Event& event);
    QStringList pathIntersect(const QStringList& left, const QStringList& right);

private:
    QFileSystemWatcher m_watcher;
    QStringList m_files;
    QMutex m_mutex;
    bool m_track{true};

};

#endif // WATCHER_H
