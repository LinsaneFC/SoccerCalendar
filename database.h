#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>


class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject * parent = nullptr);

    Q_INVOKABLE QVariantList query(const QString &query);

signals:

public slots:
};

#endif // DATABASE_H
