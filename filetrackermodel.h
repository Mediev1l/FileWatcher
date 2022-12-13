#ifndef FILETRACKERMODEL_H
#define FILETRACKERMODEL_H

#include <QAbstractListModel>
#include "filetracker.h"
#include "event.h"

class FileTrackerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(FileTracker *list READ list WRITE setList)
public:
    explicit FileTrackerModel(QObject *parent = nullptr);

    enum {
        pathRole = Qt::UserRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    FileTracker* list() const;
    void setList(FileTracker* list);

private:
    FileTracker *m_list;
};

#endif // FILETRACKERMODEL_H
