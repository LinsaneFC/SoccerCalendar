#include "database.h"

Database::Database(QObject * parent)
    : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    qDebug() << db.open();

    QSqlQuery dropMatch("DROP TABLE match");
    QSqlQuery match("CREATE TABLE match (id INT PRIMARY KEY, utcDate TEXT, status TEXT, matchday INT, winner TEXT, homeScore INT, awayScore INT, homeTeam INT, awayTeam INT)");

    QSqlQuery dropTeam("DROP TABLE team");
    QSqlQuery team("CREATE TABLE team (id INT PRIMARY KEY, areaID INT, baseLocation TEXT, name TEXT, shortName TEXT, tla TEXT, crestUrl TEXT, venue TEXT)");

    qDebug() << "Create match table error: " << match.lastError();

}

QVariantList Database::query(const QString &query){

    QVariantList records;
    QSqlQuery results(query);

    while(results.next()){
        QVariantMap map;
        QSqlRecord record = results.record();

        for(int i = 0; i < record.count(); i++){
            qDebug() << "Printing record.field(i).name for query:" << record.field(i).name();
            map.insert(record.field(i).name(), record.field(i).value());
        }
        records.append(map);
    }

    return records;
}
