#include "httprequestandparse.h"

HTTPRequestAndParse::HTTPRequestAndParse(QObject * parent)
    : QObject(parent),
    m_manager(new QNetworkAccessManager()){

}

void HTTPRequestAndParse::getPremierLeagueResults(){
    qDebug() << "HTTP:RequestAndParse::getPremierLeagueResults() - Setting URL for Premier League";

    QUrl url("http://api.football-data.org/v2/competitions/PL/matches");
    QUrlQuery query;
    query.addQueryItem("status", "FINISHED");
    query.addQueryItem("matchday", "3");

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
        QJsonDocument jsonDoc;
        QJsonParseError jsonErr;

        jsonDoc = QJsonDocument::fromJson(m_buffer, &jsonErr);

        QString answer =  jsonDoc.toJson(QJsonDocument::Compact);
    });

}


