//
// Created by Clarence on 2023/6/10.
//

#ifndef SERVER_REQUESTINFO_H
#define SERVER_REQUESTINFO_H

#include "string"
using namespace std;

class RequestInfo{
public:
    int clientID;
    std::string userName;
    std::string filePath;
    int startPos;
    std::string clientIP;
    std::string aesKey;

    RequestInfo(int clientId, const string &userName, const string &filePath, int startPos, const string &clientIp,
                const string &aesKey) : clientID(clientId), userName(userName), filePath(filePath), startPos(startPos),
                                        clientIP(clientIp), aesKey(aesKey) {}

    virtual ~RequestInfo() {

    }
};

#endif //SERVER_REQUESTINFO_H
