#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject * parent = nullptr);

//    Q_INVOKABLE QVariantList query(const QString &query);

signals:

public slots:
};

#endif // DATABASE_H
