#include "watcher.h"
#include <QDir>
#include <QDirIterator>
#include <QDateTime>

Watcher::Watcher(QObject *parent)
    : QObject{parent}
    , m_track{true}
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &Watcher::fileHandler);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &Watcher::directoryHandler);
}

void Watcher::addPathToWatch(QUrl path)
{
    auto localFile = path.toLocalFile();
    m_watcher.addPath(localFile);
    m_files.emplaceBack(localFile);
    m_roots.emplaceBack(localFile);

    scanFiles(path.toLocalFile());
}

void Watcher::fileHandler(const QString& path)
{
    auto absPath = getAbsPath(path);
    auto files = getFilesByDir(absPath);
    auto saved = searchInSaved(absPath);

    // file has been modified
    if (files.size() == saved.size() && QFileInfo::exists(path)){
        sendEvent(Event::Type::Modified, path, false);
    }
}

void Watcher::directoryHandler(const QString& path)
{
    auto hasExtension = [&](const QString& p) -> bool {
        return QFileInfo(p).suffix().size() > 0;
    };

    auto absPath = getAbsPath(path);
    auto files = getFilesByDir(absPath);
    auto saved = searchInSaved(absPath);

    // file has been created
    if(files.size() > saved.size()) {
        auto intersect = pathIntersect(files, saved);

        for(const auto& p : intersect) {
            sendEvent(Event::Type::Created, p, !hasExtension(p));
            m_watcher.addPath(p);
            if(!m_files.contains(p)){
                m_files.emplaceBack(p);
            }
        }
    }
    // file has been removed
    else if(files.size() < saved.size()) {
        auto intersect = pathIntersect(saved, files);

        for(const auto& p : intersect) {
            m_files.removeAll(p);
            m_watcher.removePath(p);
            sendEvent(Event::Type::Deleted, p, !hasExtension(p));
        }
    }
    // file is renamed
    else if(files.size() == saved.size()) {
        auto oldFile = pathIntersect(saved, files);
        auto newFile = pathIntersect(files, saved);

        for(const auto& p : oldFile) {
            m_files.removeAll(p);
            m_watcher.removePath(p);
            sendEvent(Event::Type::Renamed, p, !hasExtension(p));
        }
        scanFiles(absPath);
    }
}

void Watcher::trackFiles(bool value)
{
    m_track = value;
}

void Watcher::removePathFromWatcher(QUrl path)
{
    const auto localFile = path.toLocalFile();
    auto paths = searchInSaved(localFile);
    paths.append(localFile);

    m_watcher.removePaths(paths);
    m_roots.removeAll(localFile);
    for(const auto& p : paths) {
        m_files.removeAll(p);
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

void Watcher::sendEvent(Event::Type type, const QString& path, bool isFolder)
{
    if(m_track) {
        qDebug() << "|New event| Type " << Event::typeToString(type) << " Path " << path << " Is Folder "
                 << isFolder << " Timestamp " << QDateTime::currentDateTime().time().toString();
        emit NewEvent({type, path, isFolder, QDateTime::currentDateTime().time().toString()});

        if(type == Event::Type::Deleted) {
            emit FileRemoved(getRoot(path));
        }
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

QString Watcher::getRoot(QString filePath)
{
    QString ret{};
    for(const auto& root : m_roots) {
        if(filePath.contains(root)){
            ret = root;
            break;
        }
    }
    return ret;
}
