#ifndef DOWNFILEINFO_H
#define DOWNFILEINFO_H
#include<QString>

//存放文件断点信息
class DownFileInfo{
public:
    int id;
    QString path;
    int beginPos;
    int totalNum;
    void init(int id,QString path,int beginPos,int totalNum);
    double getProportion();
};

#endif // DOWNFILEINFO_H
