#ifndef SERVER_STATUSINFO_H
#define SERVER_STATUSINFO_H

class StatusInfo{
public:
    enum info{
        TRUE = 1,               //MD5验证正确
        FALSE = 2,              //MD5验证失败
        SUCCESS = 3,            //传输完成
        PAUSE = 4               //传输暂停，断点
    };
};

#endif //SERVER_STATUSINFO_H
