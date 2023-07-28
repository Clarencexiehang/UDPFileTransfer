#ifndef REQUESTBODY_H
#define REQUESTBODY_H

#include <string>
using namespace std;
class RequestBody
{
public:
    RequestBody();
    void setAccount(const string account);
    void setPath(const string path);
    void setBeginPos(int beginPos);
    void setIsSendKey(bool isSendKey);
    string toString();
private:
    string account;
    string path;
    int beginPos;
    bool isSendKey;
    
};

#endif
