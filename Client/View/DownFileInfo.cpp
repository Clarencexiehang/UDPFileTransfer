#include"DownFileInfo.h"

void DownFileInfo::init(int id, QString path, int beginPos, int totalNum)
{
    this->id=id;
    this->path=path;
    this->beginPos=beginPos;
    this->totalNum=totalNum;
}

double DownFileInfo::getProportion()
{
    return (this->beginPos-1)*1.0/this->totalNum;
}
