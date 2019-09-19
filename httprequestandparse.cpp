#include "httprequestandparse.h"

HTTPRequestAndParse::HTTPRequestAndParse(QObject * parent)
    : QObject(parent),
    m_manager(new QNetworkAccessManager()){

    getAll();

}

void HTTPRequestAndParse::getAll(){
    getTeams();
    getMatches();
}

void HTTPRequestAndParse::getMatches(){
    //    QUrlQuery query;
    //    query.addQueryItem("status", "FINISHED");
    //    query.addQueryItem("matchday", "3");

    //    qDebug() << "Query: " << query.query();

    //    url.setQuery(query.query());

    qDebug() << "HTTP:RequestAndParse::getMatches() - Setting URL for Premier League Matches";

    QUrl url("http://api.football-data.org/v2/competitions/PL/matches");

    qDebug() << url;

    m_request.setUrl(url);
    m_request.setRawHeader("X-Auth-Token", "bb9d6838fb1c435bbde0a1759f8dae19");

    QNetworkReply * reply = m_manager->get(m_request);

    connect(reply, &QNetworkReply::readyRead, this, [=](){
        while(reply->bytesAvailable())
            m_buffer.append(reply->readAll());
    });

    connect(reply, &QNetworkReply::finished, this, [&](){
        QElapsedTimer timer;
        timer.start();

        QJsonDocument jsonDoc;
        QJsonParseError jsonErr;

        jsonDoc = QJsonDocument::fromJson(m_buffer, &jsonErr);
        m_buffer.clear();

        QJsonObject jsonObj = jsonDoc.object();
        QVariantMap map = jsonObj.toVariantMap();

        QVariantList matchList = map["matches"].toList();


        QSqlQuery insert;
        insert.prepare("REPLACE INTO match VALUES (?,?,?,?,?,?,?,?,?,?)");

        QVariantList matchIds;
        QVariantList dates;
        QVariantList times;
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

            QString matchUTC = matchMap["utcDate"].toString();
            QStringRef matchDate(&matchUTC, 0, 10);
            dates << matchDate.toString();

            QStringRef matchTime(&matchUTC, 11, 8);
            times << matchTime.toString();

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
        insert.addBindValue(times);
        insert.addBindValue(statuses);
        insert.addBindValue(matchdays);
        insert.addBindValue(winners);
        insert.addBindValue(homeScores);
        insert.addBindValue(awayScores);
        insert.addBindValue(homeTeamIds);
        insert.addBindValue(awayTeamIds);


        QSqlDatabase::database().transaction();
        insert.execBatch();
        QSqlDatabase::database().commit();
        qDebug() << "HTTPRequestAndParse::getMatches() - Insertion took" << timer.elapsed() << "milliseconds";
        qDebug() << "HTTPRequestAndParse::getMatches() - Error:" << insert.lastError().text();

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


void HTTPRequestAndParse::getTeams(){
    qDebug() << "HTTP:RequestAndParse::getTeams() - Setting URL for Premier League Teams";

    QUrl url("http://api.football-data.org/v2/competitions/PL/teams");

    m_request.setUrl(url);
    m_request.setRawHeader("X-Auth-Token", "bb9d6838fb1c435bbde0a1759f8dae19");

    QNetworkReply * reply = m_manager->get(m_request);

    connect(reply, &QNetworkReply::readyRead, this, [=](){
        while(reply->bytesAvailable())
            m_buffer.append(reply->readAll());
    });

    connect(reply, &QNetworkReply::finished, this, [&](){
        QElapsedTimer timer;
        timer.start();

        QJsonDocument jsonDoc;
        QJsonParseError jsonErr;

        jsonDoc = QJsonDocument::fromJson(m_buffer, &jsonErr);
        m_buffer.clear();

        QJsonObject jsonObj = jsonDoc.object();
        QVariantMap map = jsonObj.toVariantMap();

        QVariantList teamList = map["teams"].toList();

        QSqlQuery insert;
        insert.prepare("REPLACE INTO team VALUES (?,?,?,?,?,?,?,?)");

        QVariantList teamIds;
        QVariantList areaIds;
        QVariantList baseLocations;
        QVariantList teamNames;
        QVariantList teamNamesShorts;
        QVariantList teamNamesThrees;
        QVariantList teamCrests;
        QVariantList teamVenues;

        for(auto team : teamList){
            QVariantMap teamMap = team.toMap();
            QVariantMap areaMap = teamMap["area"].toMap();

            teamIds << teamMap["id"];
            areaIds << areaMap["id"];
            baseLocations << areaMap["name"];
            teamNames << teamMap["name"];
            teamNamesShorts << teamMap["shortName"];
            teamNamesThrees << teamMap["tla"];
            teamCrests << teamMap["crestUrl"];
            teamVenues << teamMap["venue"];
        }

        insert.addBindValue(teamIds);
        insert.addBindValue(areaIds);
        insert.addBindValue(baseLocations);
        insert.addBindValue(teamNames);
        insert.addBindValue(teamNamesShorts);
        insert.addBindValue(teamNamesThrees);
        insert.addBindValue(teamCrests);
        insert.addBindValue(teamVenues);


        QSqlDatabase::database().transaction();
        insert.execBatch();
        QSqlDatabase::database().commit();
        qDebug() << "HTTPRequestAndParse::getTeams() - Insertion took" << timer.elapsed() << "milliseconds";
        qDebug() << "HTTPRequestAndParse::getTeams() - Error:" << insert.lastError().text();

        /******************** Sample Team **********************/
        //    teamIds << 57;
        //    areaIds << 2072;
        //    baseLocations << "England";
        //    teamNames << "Arsenal FC";
        //    teamNamesShorts << "Arsenal";
        //    teamNamesThrees << "ARS";
        //    teamCrests << "http://upload.wikimedia.org/wikipedia/en/5/53/Arsenal_FC.svg";
        //    teamVenues << "Emirates Stadium";

    });
}

/*
 ********************* QUERIES ******************************
 *

SELECT CASE winner
     WHEN 'HOME_TEAM'
         THEN homeTeam
     ELSE awayTeam
     END 'Winner'
 FROM match



SELECT name as "Winning Teams"
FROM team
WHERE id in (SELECT CASE winner
     WHEN 'HOME_TEAM' THEN homeTeam
     WHEN 'AWAY_TEAM' THEN awayTeam
     END 'Winner'
FROM match
WHERE matchday = 1)



SELECT CASE match.winner
        WHEN 'HOME_TEAM' then t1.name
        WHEN 'AWAY_TEAM' then t2.name
        END 'WINNER', t1.name as Home_Team, t2.name as Away_Team
FROM match, team as t1, team as t2
WHERE matchday = 1 and t1.id = homeTeam and t2.id = awayTeam



SELECT CASE match.winner
        WHEN 'HOME_TEAM' then 1
        WHEN 'AWAY_TEAM' then 0
        END 'WINNER', t1.name as Home_Team, t2.name as Away_Team, match.homeScore, match.awayScore, t1.crestUrl as homeTeamCrest, t2.crestUrl as awayTeamCrest
FROM match, team as t1, team as t2
WHERE match.utcDate = "2019-08-10"  and t1.id = homeTeam and t2.id = awayTeam


*/


