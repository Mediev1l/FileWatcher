#include "watcher.h"
#include "qdebug.h"
#include <QDir>
#include <QDirIterator>

Watcher::Watcher(QObject *parent)
    : QObject{parent}
{
    m_watcher.disconnect(SIGNAL(directoryChanged(QString)));
    //    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, [&](QString val){ directoryHandler(val);});
    connect(&m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
    m_watcher2 = new QFileSystemWatcher(this);
    connect(m_watcher2, SIGNAL(directoryChanged(const QString&)), this, SLOT(directoryHandler(const QString&)));

}

void Watcher::addPathToWatch(QString path)
{
    // remove windows prefix
    if(path.contains("file:///")) {
        path = path.remove(0,8);
    }

    //    qDebug() << "path added " << path;
    m_watcher.addPath(std::move(path));
    m_watcher2->addPath("D:/Test/Nowy folder");

    if(!m_files.contains(QFileInfo(path))) {
        m_files.emplaceBack(path);
    }

    m_files.emplaceBack(path);

    scanFiles(path);

    //    qDebug() << "files " << m_watcher.files();
    //    qDebug() << "dirs " << m_watcher.directories();
    //    qDebug() << "contai files " << m_watcher.files().contains("C:/Users/Asus/OneDrive");
    //    qDebug() << "contai dirs " << m_watcher.directories().contains("C:/Users/Asus/OneDrive");
    //    qDebug() << QFile::exists("C:/Users/Asus/OneDrive/Desktop/111x/ee.txt");
}

void Watcher::fileChanged(const QString& path)
{
    qDebug() << "File Changed Event" << path;

    auto absPath = getAbsPath(path);
    auto files = getFilesByDir(absPath);
    auto saved = searchInSaved(absPath);

    // file is missing
    if(files.size() < saved.size()) {
        qDebug() << "Deleted\n";

        m_files.remove(getIndexByPath(path));
        m_watcher.removePath(path);

        //        //TODO remove all subdirectories from watcher
        //        for(const auto& file : m_files) {
        //            if(file.path() == )
        //        }

        // emit deleted
    }
    // file has been modified
    else {
        qDebug() << "Modified\n";
    }
}

void Watcher::directoryHandler(const QString& path)
{
    qDebug() << "Directory Changed Event" << path;


    auto absPath = getAbsPath(path);
    auto files = getFilesByDir(absPath);
    auto saved = searchInSaved(absPath);

    //    qDebug() << files.size()  << " " << saved.size();
    qDebug() << "files " << m_watcher.files();
    qDebug() << "directories " << m_watcher.directories();

    // file has been created
    if(files.size() > saved.size()) {
        qDebug() << "Created\n";

        m_watcher.addPath(path);
        if(!m_files.contains(QFileInfo(path))){
            qDebug() << "working";
            m_files.emplaceBack(path);
            qDebug() << "size "<< m_files.size();

        }
        scanFiles(path);

        // emit created
    } else if (!QFileInfo(path).exists()  && m_files.size() > 0) {
        qDebug() << "Deleted\n";

        m_files.remove(getIndexByPath(path));
        m_watcher.removePath(path);

    } else {
        return;
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
        if(!m_files.contains(QFileInfo(path))) {
            m_files.emplaceBack(path);
        }
    }
}

QVector<QFileInfo> Watcher::getFilesByDir(const QString& path)
{
    QDir dir(path);
    dir.setFilter( QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    QDirIterator it = QDirIterator(dir);

    QVector<QFileInfo> ret;
    while(it.hasNext()) {
        ret.emplaceBack(it.next());
    }

    return ret;
}

int Watcher::getIndexByPath(const QString &p)
{
    for(int i = 0; i<m_files.size(); i++) {
        if(m_files.at(i).filePath() == p){
            return i;
        }
    }
    return -1;
}

QVector<QFileInfo> Watcher::searchInSaved(QString p)
{
    QVector<QFileInfo> ret;
    for(const auto& val : m_files) {
        if(val.absolutePath() == p){
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
