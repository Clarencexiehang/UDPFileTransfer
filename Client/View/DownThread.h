#include<QObject>
#include<QDebug>
#include<QTimer>
#include<QThread>
#ifndef DOWNTHREAD_H
#define DOWNTHREAD_H
#include"Service/clientservice.h"

class DownThread:public QThread{
    public:
        void run() override;
        void init(int id);
        void setIsWait(bool isW);
        bool isWaited();
        int getID();
        int getPercent();

        //模拟继续位置
        void setDefalutPercent(int percent);

    signals:
        void updatePercent(int id,int percent);
        void setErrorSignal(int id);//出错标志
    private:
        int id;
        int percent=0;
        bool isWait=false;
        ClientService *clientService ;
};

#endif // DOWNTHREAD_H
