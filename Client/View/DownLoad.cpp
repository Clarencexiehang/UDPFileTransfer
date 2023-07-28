#include"DownLoad.h"
#include"mainwindow.h"

extern MainWindow *w;

QList<DownThread*> DownLoad::downThreadList;

void DownLoad::showThread()
{
    qDebug()<<"下载队列待处理 ....."<<endl;
    for(DownThread *th:downThreadList){
        qDebug()<<"线程 id:"<<th->getID()<<"isWait:"<<th->isWaited()<<" percent:"<<th->getPercent()<<endl;
    }
}

void DownLoad::startDown(QString username,QString downPath,QList<int> downList){
    for(int id:downList){
        DownThread *downThread = new DownThread;
        downThread->init(id);
        downThreadList.append(downThread);
        downThread->start();
    }
}

void DownLoad::instantDown(QList<DownFileInfo> fileList)
{
    for(DownFileInfo file:fileList){
        //文件继续下载
        DownThread *downThread = new DownThread;
        downThread->init(file.id);
        downThread->setDefalutPercent(qRound(file.getProportion()*100));
        downThreadList.append(downThread);
        downThread->start();

        ClientService::instantDown(file.id,file.path);
    }
}

void DownLoad::pauseDown(QList<int> pauseList)
{
    for(int id:pauseList){
        qDebug()<<"暂停下载文件 "<<id<<endl;
        for(DownThread* th:downThreadList){
            if(th->getID()==id&&th->isWaited()!=true){
                qDebug()<<"暂停下载文件的线程已找到! "<<id<<endl;
                th->setIsWait(true);
                break;
            }
        }
    }
    qDebug()<<"===================== "<<endl;
    showThread();
}

void DownLoad::stopDown(QString username,QList<int> stopList){
    for(int id:stopList){
        for(DownThread* th:downThreadList){
            if(th->getID()==id){
                th->setIsWait(true);
                downThreadList.removeOne(th);
                th->requestInterruption();
                break;
            }
        }
    }
}

void DownLoad::updatePercent(int id,int percent){
    qDebug()<<"更新文件  "<<id<<"  的进度为 : "<<percent<<endl;
}

void DownLoad::removeThread(int id)
{
    for(DownThread* th:downThreadList){
        if(th->getID()==id){
            downThreadList.removeOne(th);
        }
    }
}
