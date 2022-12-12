#ifndef FILETRACKER_H
#define FILETRACKER_H

#include <QObject>
#include <QVector>

struct FileTrackerItem {
    QString path;
};

class FileTracker : public QObject
{
    Q_OBJECT
public:
    explicit FileTracker(QObject *parent = nullptr);

    QVector<FileTrackerItem> items();

    bool containsPath(const QString& path);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(QString path);
    void removeItemAt(int index);

private:
    QVector<FileTrackerItem> m_items;
};

#endif // FILETRACKER_H
