#include "filetrackermodel.h"

FileTrackerModel::FileTrackerModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_list(nullptr)
{
}

FileTrackerModel::~FileTrackerModel()
{
}

int FileTrackerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_list)
        return 0;

    return m_list->items().size();
}

QVariant FileTrackerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_list)
        return QVariant();

    const FileTrackerItem item = m_list->items().at(index.row());
    switch (role) {
    case pathRole:
        return QVariant(item.path);
    }

    return QVariant();
}

Qt::ItemFlags FileTrackerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> FileTrackerModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[pathRole] = "path";
    return names;
}

FileTracker *FileTrackerModel::list() const
{
    return m_list;
}

void FileTrackerModel::setList(FileTracker *list)
{
    beginResetModel();

    if(list && m_list) {
        m_list->disconnect(this);
    }

    m_list = list;

    if(m_list) {
        connect(m_list, &FileTracker::preItemAppended, this, [=](){
            const int index = m_list->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(m_list, &FileTracker::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(m_list, &FileTracker::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        })  ;

        connect(m_list, &FileTracker::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
