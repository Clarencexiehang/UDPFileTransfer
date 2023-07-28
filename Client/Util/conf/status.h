#ifndef SERVER_STATUSINFO_H
#define SERVER_STATUSINFO_H

class StatusInfo{
public:
    static enum info{
        MD5TRUE = 1,               //MD5验证正确
        MD5FALSE = 2,              //MD5验证失败
        SUCCESS = 3,            //传输完成
        PAUSE = 4               //传输暂停，断点
    };
};

#endif //SERVER_STATUSINFO_H
