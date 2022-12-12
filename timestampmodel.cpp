#include "timestampmodel.h"

TimestampModel::TimestampModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    qDebug() << "const";
    m_headerInfo[0] = {"Event type", 0.15};
    m_headerInfo[1] = {"Path", 0.5};
    m_headerInfo[2] = {"Is Folder", 0.1};
    m_headerInfo[3] = {"Timestamp", 0.25};
}

int TimestampModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 20;

    // FIXME: Implement me!
}

int TimestampModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_headerInfo.size();
}

int TimestampModel::columnWidth(int index, int maxWidth) const
{
    qDebug() << "index " << index << " max " << maxWidth;
    return m_headerInfo[index].width * maxWidth;
}

QVariant TimestampModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug() << "im here";
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

    // FIXME: Implement me!
    return QVariant();
}

bool TimestampModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

//bool TimestampModel::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//    return true;
//}
