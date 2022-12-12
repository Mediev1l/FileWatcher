#include "event.h"

Event::Event(QObject *parent)
    : QObject{parent}
{

}

Event::Event(Type type, QString path, bool isFolder, QString timestamp, QObject *parent)
    : QObject{parent}
    , m_eventType{type}
    , m_path{path}
    , m_isFolder{isFolder}
    , m_timestamp{timestamp}
{

}

Event::Event(const Event &ev, QObject *parent)
    : QObject{parent}
{
    this->m_eventType = ev.m_eventType;
    this->m_path = ev.m_path;
    this->m_isFolder = ev.m_isFolder;
    this->m_timestamp = ev.m_timestamp;
}

Event &Event::operator=(const Event &ev)
{
    this->m_eventType = ev.m_eventType;
    this->m_path = ev.m_path;
    this->m_isFolder = ev.m_isFolder;
    this->m_timestamp = ev.m_timestamp;

    return *this;
}

QString Event::typeToString(Type type)
{
    QString ret = "Unknown";
    switch (type) {
    case Created:
        ret = "Created";
        break;
    case Moved:
        ret = "Moved";
        break;
    case Renamed:
        ret = "Renamed";
        break;
    case Deleted:
        ret = "Deleted";
        break;
    }

    return ret;
}
