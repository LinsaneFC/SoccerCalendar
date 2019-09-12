#include "httprequestandparse.h"

HTTPRequestAndParse::HTTPRequestAndParse(QObject * parent)
    : QObject(parent),
    m_manager(new QNetworkAccessManager()){

    getMatches();

}

void HTTPRequestAndParse::getMatches(){
    qDebug() << "HTTP:RequestAndParse::getPremierLeagueResults() - Setting URL for Premier League";

    QUrl url("http://api.football-data.org/v2/competitions/PL/matches");
    QUrlQuery query;
//    query.addQueryItem("status", "FINISHED");
//    query.addQueryItem("matchday", "3");

//    qDebug() << "Query: " << query.query();

    url.setQuery(query.query());
    m_request.setUrl(url);
    qDebug() << url;
    m_request.setRawHeader("X-Auth-Token", "bb9d6838fb1c435bbde0a1759f8dae19");

    QNetworkReply * reply = m_manager->get(m_request);

    connect(reply, &QNetworkReply::readyRead, this, [=](){
        while(reply->bytesAvailable())
            m_buffer.append(reply->readAll());
    });

    connect(reply, &QNetworkReply::finished, this, [&]{
        QElapsedTimer timer;
        timer.start();

        QJsonDocument jsonDoc;
        QJsonParseError jsonErr;

        jsonDoc = QJsonDocument::fromJson(m_buffer, &jsonErr);

        QJsonObject jsonObj = jsonDoc.object();
        QVariantMap map = jsonObj.toVariantMap();

        QVariantList matchList = map["matches"].toList();

        QSqlQuery insert;
        insert.prepare("REPLACE INTO match VALUES (?,?,?,?,?,?,?,?,?)");

        QVariantList matchIds;
        QVariantList dates;
        QVariantList statuses;
        QVariantList matchdays;
        QVariantList winners;
        QVariantList homeScores;
        QVariantList awayScores;
        QVariantList homeTeamIds;
        QVariantList awayTeamIds;

        for(auto match : matchList){
            QVariantMap matchMap = match.toMap();
            QVariantMap scoreMap = matchMap["score"].toMap();
            QVariantMap fullTimeMap = scoreMap["fullTime"].toMap();
            QVariantMap homeTeamMap = matchMap["homeTeam"].toMap();
            QVariantMap awayTeamMap = matchMap["awayTeam"].toMap();

            matchIds << matchMap["id"];
            dates << matchMap["utcDate"];
            statuses << matchMap["status"];
            matchdays << matchMap["matchday"];
            winners << scoreMap["winner"];
            homeScores << fullTimeMap["homeTeam"];
            awayScores << fullTimeMap["awayTeam"];
            homeTeamIds << homeTeamMap["id"];
            awayTeamIds << awayTeamMap["id"];
        }

        insert.addBindValue(matchIds);
        insert.addBindValue(dates);
        insert.addBindValue(statuses);
        insert.addBindValue(matchdays);
        insert.addBindValue(winners);
        insert.addBindValue(homeScores);
        insert.addBindValue(awayScores);
        insert.addBindValue(homeTeamIds);
        insert.addBindValue(awayTeamIds);


        QSqlDatabase::database().transaction();
        qDebug() << insert.execBatch();
        QSqlDatabase::database().commit();
        qDebug() << "HTTPRequestAndParse::getMatches() - Error:" << insert.lastError().text();
        qDebug() << "HTTPRequestAndParse::getMatches() - Insertion took" << timer.elapsed() << "milliseconds";

        /******************** Sample Gameday **********************/
        //    matchIds << 264341;
        //    dates << "2019-08-09T19:00:00Z";
        //    statuses << "FINISHED";
        //    matchdays << 1;
        //    winners << "HOME_TEAM";
        //    homeScores << 4;
        //    awayScores << 1;
        //    homeTeamIds << 64;
        //    awayTeamIds << 68;


    });
}


/*
 ********************* QUERIES ******************************
 *
 * Selecting Winning Team Name
 * SELECT CASE winner
 *       WHEN 'HOME_TEAM'
 *           THEN homeTeam
 *       ELSE awayTeam
 *       END 'Winner'
 *   FROM match
 *
 *
*/


