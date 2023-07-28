#include<QObject>

#include<QtCore>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>
#include<QMessageBox>

#include"config.h"

#ifndef REQUEST_H
#define REQUEST_H

class Request{
public:
    static QNetworkReply* GET(QString url);
    static QNetworkReply* POST(QString url,QByteArray data);
};
#endif // REQUEST_H
