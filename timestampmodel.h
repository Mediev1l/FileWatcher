#ifndef TIMESTAMPMODEL_H
#define TIMESTAMPMODEL_H

#include <QAbstractTableModel>
#include <QMap>

struct headerInfo {
    QString name;
    float width;
};

class TimestampModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TimestampModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnWidth(int index, int maxWidth) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    //    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QMap<int, headerInfo> m_headerInfo;
};

#endif // TIMESTAMPMODEL_H
