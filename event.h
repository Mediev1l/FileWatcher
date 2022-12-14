#ifndef EVENT_H
#define EVENT_H

#include <QObject>

class Event : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Created,
        Renamed,
        Modified,
        Deleted
    };

    explicit Event(QObject *parent = nullptr);

    Event(Type type, QString path, bool isFolder, QString timestamp, QObject *parent = nullptr);

    explicit Event(const Event& ev, QObject *parent = nullptr);

    Event& operator=(const Event& ev);

    static QString typeToString(Type type);
public:
    Type m_eventType;
    QString m_path;
    bool m_isFolder;
    QString m_timestamp;

};

#endif // EVENT_H
