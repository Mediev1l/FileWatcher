#ifndef TIMESTAMPMODEL_H
#define TIMESTAMPMODEL_H

#include <QAbstractTableModel>

#include "timestamp.h"

struct headerInfo {
    QString name;
    float width;
};

class TimestampModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(Timestamp *list READ list WRITE setList)
public:
    enum {
        displayRole,
    };

    explicit TimestampModel(QObject *parent = nullptr);
    ~TimestampModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnWidth(int index, int maxWidth) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Timestamp* list() const;
    void setList(Timestamp* list);

private:
    QMap<int, headerInfo> m_headerInfo;
    Timestamp* m_list;
};

#endif // TIMESTAMPMODEL_H
