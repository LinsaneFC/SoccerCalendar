#include "database.h"

Database::Database(QObject * parent)
    : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    qDebug() << db.open();

    QSqlQuery drop("DROP TABLE match");
    QSqlQuery match("CREATE TABLE match (id INT PRIMARY KEY, winner TEXT, homeScore INT, awayScore INT, homeTeam TEXT, awayTeam TEXT, homeTeamId INT, awayTeamId INT)");

    qDebug() << "Create match table error: " << match.lastError();

}
