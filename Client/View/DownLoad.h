#include<QObject>
#include<QWidget>
#include<QDebug>
#include<QTimer>
#include<QThread>

#include"DownThread.h"
#include"DownFileInfo.h"

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

class DownLoad{
    public:
    static QList<DownThread*> downThreadList;

    public slots:
    static void showThread();
    static void startDown(QString username,QString downPath,QList<int> downList);
    static void instantDown(QList<DownFileInfo> fileList);
    static void pauseDown(QList<int> pauseList);
    static void stopDown(QString username,QList<int> stopList);
    static void updatePercent(int id,int percent);
    static void removeThread(int id);
};
#endif // DOWNLOAD_H
