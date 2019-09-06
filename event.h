#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDateTime>
#include <QString>

class Event : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QDateTime startDate READ getStartDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(QDateTime endDate READ getEndDate WRITE setEndDate NOTIFY endDateChanged)

public:
    explicit Event(QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

    QDateTime getStartDate() const;
    void setStartDate(const QDateTime &startDate);

    QDateTime getEndDate() const;
    void setEndDate(const QDateTime &endDate);

signals:
    void nameChanged(const QString &name);
    void startDateChanged(const QDateTime &startDate);
    void endDateChanged(const QDateTime &endDate);

private:
    QString m_name;
    QDateTime m_start_date;
    QDateTime m_end_date;
};

#endif // EVENT_H
