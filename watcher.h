#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QUrl>
#include <QMutex>

#include "event.h"

class Watcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool m_track MEMBER m_track NOTIFY trackChanged)
public:
    explicit Watcher(QObject *parent = nullptr);

signals:
    void newEvent(const Event& ev);
    void fileRemoved(const QString& path);
    void trackChanged();

public slots:
    void addPathToWatch(QUrl path);
    void removePathFromWatcher(QUrl path);
    void fileHandler(const QString& path);
    void directoryHandler(const QString& path);
    void trackFiles(bool value);

private:
    // helpers
    void scanFiles(const QString& root);
    void sendEvent(Event::Type type, const QString& path, bool isFolder);

    QStringList getFilesByDir(const QString& path);
    QStringList searchInSaved(QString p);
    QStringList pathIntersect(const QStringList& left, const QStringList& right);

    QString getAbsPath(const QString& path);
    QString getRoot(QString filePath);

private:
    QFileSystemWatcher m_watcher;
    QStringList m_files;
    QStringList m_roots;
    QMutex m_mutex;
    bool m_track;
};

#endif // WATCHER_H
