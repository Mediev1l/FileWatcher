#ifndef CATDOWNLOADER_H
#define CATDOWNLOADER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QNetworkAccessManager>


class CatDownloader : public QThread
{
    Q_OBJECT
public:
    explicit CatDownloader(QObject *parent = nullptr);
    ~CatDownloader();

signals:
    void startDownload();

public slots:
    void downloadCat(const QString& path);

private slots:
    void onDownloadFileComplete(QNetworkReply *reply);

private:
    void run() override;

    int queueSize();
    QString dequeueSafe();

private:
    QQueue<QString> m_queue;
    QMutex m_mutex;
    std::unique_ptr<QNetworkAccessManager> m_networkManager;

    const QString m_src{"https://cataas.com/cat/says/hello%20world!"};
    const QString m_name{"/cat"};
    const QString m_extension{".jpg"};

    bool m_downloading{false};
    int m_counter{1};

};

#endif // CATDOWNLOADER_H
