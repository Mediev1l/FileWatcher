#include "filetracker.h"

FileTracker::FileTracker(QObject *parent)
    : QObject{parent}
{
}

QVector<FileTrackerItem> FileTracker::items()
{
    return m_items;
}

bool FileTracker::containsPath(const QString &path)
{
    for(auto& value : m_items) {
        if(value.path == path) {
            return true;
        }
    }

    return false;
}

void FileTracker::appendItem(QString path)
{
    if(path.isEmpty() || containsPath(path)) {
        return;
    }

    emit preItemAppended();

    FileTrackerItem item;
    item.path = path;
    m_items.append(item);

    emit postItemAppended();
}

void FileTracker::removeItemAt(int index)
{
    if (index < 0 || index >= m_items.size()){
        return;
    }

    emit preItemRemoved(index);

    m_items.removeAt(index);

    emit postItemRemoved();
}
