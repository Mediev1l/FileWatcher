#include "catdownloader.h"

#include <QNetworkReply>
#include <QFile>

CatDownloader::CatDownloader(QObject *parent)
    : QThread{parent}
{
}

CatDownloader::~CatDownloader()
{
    requestInterruption();
    wait();
}

void CatDownloader::downloadCat(const QString& path)
{
    m_mutex.lock();
    m_queue.enqueue(path);
    m_mutex.unlock();

    if(!isRunning()) {
        start();
    }
}

void CatDownloader::onDownloadFileComplete(QNetworkReply *reply)
{
    auto dst = dequeueSafe();

    QFile file(dst + m_name + QString::number(m_counter++) + m_extension);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();

    m_downloading = false;

    exit();
}

void CatDownloader::run()
{
    m_networkManager = std::make_unique<QNetworkAccessManager>();
    connect(m_networkManager.get(), &QNetworkAccessManager::finished, this, &CatDownloader::onDownloadFileComplete);

    while(!isInterruptionRequested()){
        while(queueSize() == 0 || m_downloading) {
            QThread::sleep(1);
        }

        m_downloading = true;

        m_networkManager->get(QNetworkRequest(m_src));

        exec();
    }
}

int CatDownloader::queueSize()
{
    m_mutex.lock();
    int size = m_queue.size();
    m_mutex.unlock();

    return size;
}

QString CatDownloader::dequeueSafe()
{
    m_mutex.lock();
    QString path = m_queue.dequeue();
    m_mutex.unlock();

    return path;
}
