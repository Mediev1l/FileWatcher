#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QObject>
#include <QVector>

#include "event.h"

class Event;

class Timestamp : public QObject
{
    Q_OBJECT
public:
    explicit Timestamp(QObject *parent = nullptr);

    QVector<Event> items();
signals:
    void preItemAppended();
    void postItemAppended();

    void preItemsClear();
    void postItemsClear();

public slots:
    void appendItem(const Event& event);
    void clearItems();

private:
    QVector<Event> m_items;
};

#endif // TIMESTAMP_H
