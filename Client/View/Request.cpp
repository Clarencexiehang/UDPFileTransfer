#include"Request.h"

//GET 请求
QNetworkReply*  Request::GET(QString url){
    QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
    QNetworkRequest requestInfo;
    requestInfo.setUrl(QUrl(url));
    //添加事件循环机制，返回后再运行后面的
    QEventLoop eventLoop;
    QNetworkReply *reply =  m_pHttpMgr->get(requestInfo);

    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    return reply;
}

QNetworkReply* Request::POST(QString url,QByteArray data){
    qDebug()<<" post 请求 ："<<url<<endl;

    QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
    QNetworkRequest requestInfo;
    requestInfo.setUrl(QUrl(url));

    requestInfo.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    requestInfo.setRawHeader("Content-Type","application/json");//服务器要求的数据头部
    requestInfo.setRawHeader("Accept","text/json,*/*;q=0.5");//服务器要求的数据头部

    QNetworkReply *reply =  m_pHttpMgr->post(requestInfo, data);
    //添加事件循环机制，返回后再运行后面的
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    //错误处理
    qDebug()<<" post 请求 "<<url<<"  完成 !"<<endl;
    return reply;
}
