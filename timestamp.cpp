#include "timestamp.h"

Timestamp::Timestamp(QObject *parent)
    : QObject{parent}
{
    m_items.append({Event::Type::Created, "p1", true, "41243"});
    m_items.append({Event::Type::Deleted, "p2", true, "44"});
    m_items.append({Event::Type::Created, "", true, "4"});
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
