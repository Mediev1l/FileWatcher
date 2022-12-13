#include "timestampmodel.h"

TimestampModel::TimestampModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_list(nullptr)
{
    m_headerInfo[0] = {"Event type", 0.15};
    m_headerInfo[1] = {"Path", 0.5};
    m_headerInfo[2] = {"Is Folder", 0.1};
    m_headerInfo[3] = {"Timestamp", 0.25};
}

int TimestampModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_list)
        return 0;

    return m_list->items().size();
}

int TimestampModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_headerInfo.size();
}

int TimestampModel::columnWidth(int index, int maxWidth) const
{
    return m_headerInfo[index].width * maxWidth;
}

QVariant TimestampModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal) {
        return m_headerInfo[section].name;
    } else {
        return QString();
    }

}

QVariant TimestampModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == displayRole) {
        const auto& items = m_list->items().at(index.row());
        switch (index.column()) {
        case 0:
            return QVariant(Event::typeToString(items.m_eventType));
        case 1:
            return QVariant(items.m_path);
        case 2:
            return QVariant(items.m_isFolder ? "Yes" : "No");
        case 3:
            return QVariant(items.m_timestamp);
        }
    }

    return QVariant();
}

QHash<int, QByteArray> TimestampModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[displayRole] = "display";

    return names;
}

Timestamp *TimestampModel::list() const
{
    return m_list;
}

void TimestampModel::setList(Timestamp *list)
{
    beginResetModel();

    if(list && m_list) {
        m_list->disconnect(this);
    }

    m_list = list;

    if(m_list) {
        connect(m_list, &Timestamp::preItemAppended, this, [=](){
            const int index = m_list->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(m_list, &Timestamp::postItemAppended, this, [=](){
            endInsertRows();
        });

    }

    endResetModel();
}

void TimestampModel::addEvent(const Event &event)
{
    if(m_list) {
        m_list->appendItem(std::move(event));
    }
}
