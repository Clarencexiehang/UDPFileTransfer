#ifndef SERVER_SERVERSERVICE_H
#define SERVER_SERVERSERVICE_H

#include "string"
#include "vector"

#include "SockInfo.h"
#include <zlib.h>
#include "../Entity/RequestInfo.h"
using namespace std;

class ServerService {
private:
    static vector<int> ports;
public:
    static vector<RequestInfo> requestInfos;

public:

    static int allocateUdpPort();                                                       //给UDP线程分配绑定的端口
    static void releaseUdpPort(int port);                                               //释放UDP绑定端口
    static int allocateClientID(string account);
    static void releaseClientID(int client_ID);

    static string createAESkey(string userName);
    static void sentSecretKey(SockInfo *cinfo , string userName);

    static RequestInfo getTCPInfo(SockInfo *cinfo);                                            //获取客户端TCP请求发送的消息,返回连接的clientID
    static void UDPSendFile(const char *clientIP, int clientPort, int clientID, string filePath , int startPos , string aesKey);     //向服务端发文件

    static string getFileName(string filePath);

    static bool compressFile(const std::string &inputFile, const std::string &outputFile, int compressionLevel = Z_DEFAULT_COMPRESSION);
    static bool decompressFile(const std::string &inputFile, const std::string &outputFile);

    static std::string encrypt_AES(const std::string &data, const std::string &key, const std::string &iv);
    static std::string decrypt_AES(const std::string encrypted_data, const std::string &key, const std::string &iv);

    static vector<string> split_string(const std::string& input);
    static int getFilePacketNum(const std::string& filename);
};


#endif //SERVER_SERVERSERVICE_H
