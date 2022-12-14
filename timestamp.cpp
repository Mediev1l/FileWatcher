#include "timestamp.h"
#include "qdebug.h"

Timestamp::Timestamp(QObject *parent)
    : QObject{parent}
{
}

QVector<Event> Timestamp::items()
{
    return m_items;
}

void Timestamp::appendItem(const Event& event)
{
    emit preItemAppended();

    m_items.append(std::move(event));

    emit postItemAppended();
}

void Timestamp::clearItems()
{
    emit preItemsClear();

    m_items.clear();

    emit postItemsClear();
}
