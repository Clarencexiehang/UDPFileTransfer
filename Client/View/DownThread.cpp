#include"DownThread.h"
#include"mainwindow.h"

extern MainWindow *w;

void DownThread::run()
{
    qDebug() << "新的 下载 线程 running...    下载 id:"<<this->id<<endl;
    while (!isInterruptionRequested()||!this->isWait) {
        qDebug() << "*******下载进度:"<<this->percent<<endl;
        w->getMainPage()->updatePercent(this->id,this->clientService->downloadProgress());
        //模拟下载出错 ------------------
        if(this->clientService->getisTerminate()){
            qDebug() << "*******下载出错 :"<<this->percent<<endl;
            w->getMainPage()->setError(this->id);
            //从下载队列中移除
            DownLoad::removeThread(this->getID());
            this->setIsWait(false);
            requestInterruption();
            break;
        }else if(this->percent>=100){
            //从下载队列中移除
            DownLoad::removeThread(this->getID());
            this->setIsWait(false);
            requestInterruption();
            break;
        }
        this->percent+=10;
        QThread::currentThread()->sleep(1);
    }
    // 执行需要在新线程中执行的操作
}

void DownThread::init(int id){
    this->id=id;
    this->clientService = new ClientService("host",9000);
}

void DownThread::setIsWait(bool isW)
{
    this->isWait=isW;
    qDebug()<<"暂停下载文件的线程暂停标志 : "<<this->isWait<<endl;
}

bool DownThread::isWaited()
{
    return this->isWait;
}


int DownThread::getID()
{
    return this->id;
}

int DownThread::getPercent()
{
    return this->percent;
}

void DownThread::setDefalutPercent(int percent)
{
    qDebug()<<" 默认进度为 ：   "<<this->percent<<"  修改为 ："<<percent<<endl;
    this->percent=percent;
    qDebug()<<" 新进度为 ："<<this->percent<<endl;
}
