#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>

#include "event.h"

//struct file {
//    bool directory;
//    QString path;
//};

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = nullptr);

signals:
    void NewEvent(const Event& ev);

public slots:
    void addPathToWatch(QString path);
    void fileChanged(const QString& path);
    void directoryHandler(const QString& path);

private:
    // helpers
    void scanFiles(const QString& root);
    QVector<QFileInfo> getFilesByDir(const QString& path);
    int getIndexByPath(const QString& p);
    QVector<QFileInfo> searchInSaved(QString p);
    QString getAbsPath(const QString& path);

private:
    QFileSystemWatcher m_watcher;
    QFileSystemWatcher* m_watcher2;
    QVector<QFileInfo> m_files;

};

#endif // WATCHER_H
