#ifndef HTTPREQUESTANDPARSE_H
#define HTTPREQUESTANDPARSE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QElapsedTimer>


class HTTPRequestAndParse : public QObject
{
    Q_OBJECT

public:
    explicit HTTPRequestAndParse(QObject *parent = nullptr);


private:
    void getMatches();

private:
    QNetworkAccessManager * m_manager;
    QNetworkRequest m_request;
    QByteArray m_buffer;
};

#endif // HTTPREQUESTANDPARSE_H
