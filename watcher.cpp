#include "watcher.h"
#include "qdebug.h"
#include <QDir>
#include <QDirIterator>
#include <QSet>

Watcher::Watcher(QObject *parent)
    : QObject{parent}
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &Watcher::fileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &Watcher::directoryHandler);
}

void Watcher::addPathToWatch(QUrl path)
{
    m_watcher.addPath(path.toLocalFile());
    m_files.emplaceBack(path.toLocalFile());

    scanFiles(path.toLocalFile());
}

void Watcher::fileChanged(const QString& path)
{
    qDebug() << "File Changed Event" << path;

    auto absPath = getAbsPath(path);
    auto files = getFilesByDir(absPath);
    auto saved = searchInSaved(absPath);

    // file has been modified
    if (files.size() == saved.size() && QFileInfo::exists(path)){
        qDebug() << "Modified\n";
        sendEvent({Event::Type::Modified, path, false, "now"});
    }
}

void Watcher::directoryHandler(const QString& path)
{
    qDebug() << "Directory Changed Event" << path;

    auto hasExtension = [&](const QString& p) -> bool {
        return QFileInfo(p).suffix().size() > 0;
    };

    auto absPath = getAbsPath(path);
    auto files = getFilesByDir(absPath);
    auto saved = searchInSaved(absPath);

    // file has been created
    if(files.size() > saved.size()) {
        qDebug() << "Created";
        auto intersect = pathIntersect(files, saved);

        for(const auto& p : intersect) {
            sendEvent({Event::Type::Created, p, !hasExtension(p), "now"});
            m_watcher.addPath(p);
            if(!m_files.contains(p)){
                m_files.emplaceBack(p);
            }
        }
    }
    // file has been removed
    else if(files.size() < saved.size()) {
        qDebug() << "Deleted";

        auto intersect = pathIntersect(saved, files);

        for(const auto& p : intersect) {
            auto index = getIndexByPath(p);
            if(index != -1) {
                m_files.removeAt(index);
            }

            sendEvent({Event::Type::Deleted, p, !hasExtension(p), "now"});
            m_watcher.removePath(p);
        }
    }
    // file is renamed
    else if(files.size() == saved.size()) {
        qDebug() << "renamed";

        auto oldFile = pathIntersect(saved, files);
        auto newFile = pathIntersect(files, saved);

        for(const auto& p : oldFile) {
            auto index = getIndexByPath(p);
            if(index != -1) {
                m_files.removeAt(index);
            }

            sendEvent({Event::Type::Renamed, p, !hasExtension(p), "now"});
            m_watcher.removePath(p);
        }
        scanFiles(absPath);
    }
}

void Watcher::scanFiles(const QString& root)
{
    QDir dir(root);
    dir.setFilter( QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    QDirIterator it = QDirIterator(dir, QDirIterator::Subdirectories);

    while(it.hasNext()) {
        auto path = it.next();
        m_watcher.addPath(path);
        if(!m_files.contains(path)) {
            m_files.emplaceBack(path);
        }
    }
}

QStringList Watcher::getFilesByDir(const QString& path)
{
    QDir dir(path);
    dir.setFilter( QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    QDirIterator it = QDirIterator(dir);

    QStringList ret;
    while(it.hasNext()) {
        ret.emplaceBack(it.next());
    }

    return ret;
}

int Watcher::getIndexByPath(const QString &p)
{
    for(int i = 0; i<m_files.size(); i++) {
        if(QFileInfo(m_files.at(i)).filePath() == p){
            return i;
        }
    }
    return -1;
}

QStringList Watcher::searchInSaved(QString p)
{
    QStringList ret;
    for(const auto& val : m_files) {
        if(QFileInfo(val).absolutePath() == p){
            ret.push_back(val);
        }
    }
    return ret;
}

QString Watcher::getAbsPath(const QString &path)
{
    auto info = QFileInfo(path);
    return (info.isFile() || !info.exists()) ? info.absolutePath() : path;
}

void Watcher::sendEvent(const Event &event)
{
    if(m_track) {
        emit NewEvent(event);
    }
}

QStringList Watcher::pathIntersect(const QStringList &left, const QStringList &right)
{
    QStringList ret;
    for(const auto& value : left){
        if(!right.contains(value)) {
            ret.append(value);
        }
    }

    return ret;
}
