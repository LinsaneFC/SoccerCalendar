#include "event.h"

Event::Event(QObject *parent) :
    QObject(parent)
{

}

QString Event::getName() const
{
    return m_name;
}

void Event::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

QDateTime Event::getStartDate() const
{
    return m_start_date;
}

void Event::setStartDate(const QDateTime &startDate)
{
    if (startDate != m_start_date) {
        m_start_date = startDate;
        emit startDateChanged(m_start_date);
    }
}

QDateTime Event::getEndDate() const
{
    return m_end_date;
}

void Event::setEndDate(const QDateTime &endDate)
{
    if (endDate != m_end_date) {
        m_end_date = endDate;
        emit endDateChanged(m_end_date);
    }
}
