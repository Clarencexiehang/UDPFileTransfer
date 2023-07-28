#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include <string>
#include <winsock2.h>
#include <fstream>
#include <vector>
#include "../Entity/BreakPoint.h"
#include "../Entity/requestbody.h"

using namespace std;
class ClientService
{
private:
    int seq; 
    int totalNum;
    bool isTerminate;

    int hostTcpPort = 9000;
    int hostUdpPort;
    int localUdpPort = 9999;
    
    string host;
    SOCKET localTcpSocket;
    SOCKET localUdpSocket;
    
    vector<BreakPoint>* brs = NULL;
    
    string iv;
public:
    ClientService(string host,int serverPort);
    void ini();
    void cleanWork();
    string TCPRcvResponse();
    void TcpRequest(string serverIP, int serverPort, RequestBody);   
    void UDPReceiveFile(string storePath);
    ClientService* const  download(string serverIp,int port,RequestBody rb,string stopath);
    double downloadProgress();
    BreakPoint* getBreakInfo(string);
    bool getisTerminate();

    static bool decompressFile(const std::string& inputFile, const std::string& outputFile);
    static bool checkKey();
    static void fosWrite(string filePath,const char*);
    static string fisRead(string filePath);
    static void breakStorage(const string,const int,const int);
    static vector<BreakPoint>* getBreakPoints(const string);
    
    static void terminate(ClientService*); //另一个线程调用
    static string encrypt_AES(const std::string& data, const std::string& key, const std::string& iv);
    static string decrypt_AES(const std::string data, const std::string& key, const std::string& iv);
    static unsigned int getSeq(string*);
};

#endif 
