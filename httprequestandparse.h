#ifndef HTTPREQUESTANDPARSE_H
#define HTTPREQUESTANDPARSE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>

class HTTPRequestAndParse : public QObject
{
    Q_OBJECT

public:
    explicit HTTPRequestAndParse(QObject *parent = nullptr);
    Q_INVOKABLE void getPremierLeagueResults();



private:
    QNetworkAccessManager * m_manager;
    QNetworkRequest m_request;
    QByteArray m_buffer;
};

#endif // HTTPREQUESTANDPARSE_H
