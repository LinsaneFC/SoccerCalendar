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

#include <QString>
#include <QStringRef>

class HTTPRequestAndParse : public QObject
{
    Q_OBJECT

public:
    explicit HTTPRequestAndParse(QObject *parent = nullptr);


private:
    void getAll();
    void getMatches();
    void getTeams();


private:
    QNetworkAccessManager * m_manager;
    QNetworkRequest m_request;
    QByteArray m_buffer;
};

#endif // HTTPREQUESTANDPARSE_H
