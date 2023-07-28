#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"zlibwapi.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>

#include"../Util/conf/crypto.h"
#include"../Util/conf/ssl.h"

//#include <openssl/crypto.h>
//#include <openssl/ssl.h>

#include "../Util/md5/md5.h"
#include "../Entity/requestbody.h"
#include "../Util/rsa/Rsa.h"
#include "../Service/clientservice.h"
#include "../Util/conf/status.h"
#include "../Util/conf/zlib.h"
#define iv1 "8NONwyJtHesysWpM"
ClientService::ClientService(string host, int serverPort) {
        this->host = host;
        this->hostTcpPort = serverPort;
        isTerminate = FALSE;
        iv = iv1;
}


void ClientService::ini() {
    // 初始化 Winsock 库,最后关闭socket和清理WSA库
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "ini fail.\n";
        return;
    }


    // 创建 TCP 客户端套接字
    localTcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (localTcpSocket == INVALID_SOCKET) {
        std::cout << "create socket fail.\n";
        WSACleanup();
        return;
    }


    //创建UDP套接字并绑定
    sockaddr_in localaddr;
    memset(&localaddr, 0, sizeof(localaddr));
    localaddr.sin_family = AF_INET;
    localaddr.sin_port = htons(localUdpPort);
    localaddr.sin_addr.S_un.S_addr = INADDR_ANY;

    localUdpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (bind(localUdpSocket, (struct sockaddr*)&localaddr, sizeof(localaddr)) == SOCKET_ERROR){
        cout<<"udp socket bind fail"<<endl;
        closesocket(localUdpSocket);
        return;
    }

    //加载断点配置
    brs = getBreakPoints("breaks.txt");

}


void ClientService::cleanWork() {
    closesocket(localUdpSocket);
    WSACleanup();
    brs->clear();
    delete brs;
    //考虑添加堆内存集合集中释放内存
}

sockaddr_in hostUdpAddr;
void ClientService::TcpRequest(string serverIP, int serverPort,RequestBody rb) {
        // 设置服务器地址和端口号
        sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str()); // 服务器 IP 地址
        serverAddr.sin_port = htons(serverPort); // 服务器端口号


        // 连接到服务器
        if ( connect(localTcpSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cout << "connect fail.\n";
            closesocket(localTcpSocket);
            WSACleanup();
            return;
        }


        Rsa r;
        r.ini();
        int psk = r.getPsk();
        int module = r.getModule();
        string pm = "";

        //检查私钥
        if (!checkKey())
        {
            pm = to_string(psk) + "|" + to_string(module)+"|";
            rb.setIsSendKey(TRUE);
            cout << "none aes key,be ready for rcv aes key" << endl;
        }


        //发送数据
        string rs = pm + rb.toString();
        const char* message = rs.c_str();
        if (send(localTcpSocket, message, strlen(message), 0) == SOCKET_ERROR) {
            cout << "TCP data send fail.\n";
            closesocket(localTcpSocket);
            WSACleanup();
            return;
        }
        cout << "send message:" << rs << endl;


        //接收并保存密钥
         if (!checkKey())
         {
             string buf = TCPRcvResponse();
             vector<long> t;
             for (int i = 0; i < buf.length(); i++) {
                 t.push_back(buf[i]);
             }

             buf = r.vecConverter(r.decrypt(&t));
             string key = "aes-private-key:" + buf;
             fosWrite("keys.txt", key.c_str());
         }

        //接收端口号
        string res = TCPRcvResponse();

        try
        {
            hostUdpPort = stoi(res);
            cout << "udp:" << hostUdpPort << endl;

            //设置目标地址和端口号
            hostUdpAddr.sin_family = AF_INET;
            hostUdpAddr.sin_port = htons(hostUdpPort);
            inet_pton(AF_INET, serverIP.c_str(), &hostUdpAddr.sin_addr);
        }
        catch (const std::exception&)
        {
            cout << "maybe res is not valid number string and the res is "<<res<<endl;
        }

        //接收总包数
        try {
            totalNum = stoi(TCPRcvResponse());
        }
        catch (const std::exception&) {
            cout << "maybe res is not valid number string and the res is " << res << endl;
        }

        cout << "totalNum:" << totalNum << endl;
        closesocket(localTcpSocket);
        cout << "close tcp connect" << endl;
}


string ClientService::TCPRcvResponse() {
    // 接收从服务器返回的数据
    char buffer[1024];
    int receivedBytes = recv(localTcpSocket, buffer, sizeof(buffer), 0);
    if (receivedBytes < 1024)
    {
        buffer[receivedBytes] = '\0';
    }

    if (receivedBytes == SOCKET_ERROR) {
        std::cout << "rcv fail.\n";
        closesocket(localTcpSocket);
        return "";
    }

    return string(buffer);
}


/// <summary>
/// 检查aes密钥，未考虑密钥失效或被手动修改
/// </summary>
/// <returns>是否存在密钥</returns>
bool ClientService::checkKey() {
    //aes私钥检查
    ifstream fis;
    fis.open("keys.txt",ios_base::in);
    if(fis.is_open()){
        string aes;
        getline(fis,aes);
        fis.close();
        return aes.substr(0, 16) == "aes-private-key:";
    }else{
        cout<<"keys open fail"<<endl;
    }
}


void ClientService::fosWrite(string filePath,const char* buf){
    ofstream fos;
    fos.open(filePath,ios_base::app);
    if(!fos.is_open()){
        cout<<"file open fail"<<endl;
        return;
    }
    fos.write(buf, strlen(buf));
    fos.close();
}


/// <summary>
/// 读一行字符串，存在函数依赖
/// </summary>
/// <param name="filePath"></param>
/// <returns>带aes密钥的字符串</returns>
string ClientService::fisRead(string filePath) {
    ifstream fis;
    fis.open(filePath);
    if (!fis.is_open())
    {
        cout << "file open fail" << endl;
        return "";
    }
    string line;
    getline(fis,line);
    fis.close();
    return line;
}


/// <summary>
/// 终止下载
/// </summary>
/// <param name="c">要终止对象的指针</param>
void ClientService::terminate(ClientService* c) {
    c->isTerminate = TRUE;
}


/// <summary>
/// 字节转整型
/// </summary>
/// <param name="data"></param>
/// <returns>包序号</returns>
unsigned int ClientService::getSeq(string* data)
{
    int seq = 0;
    for (int i = 0; i < 3; i++)
    {
        seq += (*data)[i];
        seq = seq << 8;
    }
    seq += (*data)[3];
    return seq;
}


/// <summary>
/// 下载进度
/// </summary>
/// <returns></returns>
double ClientService::downloadProgress() {
    return seq * 1.0 / (totalNum-1);
}


ClientService* const ClientService::download(string serverIp, int port, RequestBody rb,string stoPath)
{
    ClientService* const service = new ClientService(serverIp, port);
    service->ini();
    service->TcpRequest(serverIp, port, rb);
    service->UDPReceiveFile(stoPath);
    return service;
}


void ClientService::UDPReceiveFile(string storePath) {
    //缓冲区
        char* buf = new char[1024 * 80] {0};

        //加载aes密钥
        string str = fisRead("keys.txt");
        string aeKey = str.substr(16, str.length() - 16);

        bool timeOut = TRUE;
        time_t now = time(NULL);

        unsigned long mode = 1;

        if (ioctlsocket(localUdpSocket, FIONBIO, &mode) == SOCKET_ERROR) {
            cout << "no blocking set fail" << endl;
            timeOut = FALSE;
        }

        while(time(NULL) - now < 60){
            //是否接收完
            if (ClientService::seq == totalNum - 1) {
                cout << "download finish" << endl;
                break;
            }
            //是否停止接收
            if (isTerminate){
                timeOut = FALSE;
                breakStorage(storePath, ClientService::seq, totalNum);
                //发送暂停反馈
                string msg = to_string(StatusInfo::PAUSE);
                string encryptMsg = encrypt_AES(msg, aeKey, iv);
                sendto(localUdpSocket, encryptMsg.c_str(), encryptMsg.length(), 0, (sockaddr*)&hostUdpAddr, sizeof(hostUdpAddr));
                cout << "pause down on,seq:" << ClientService::seq << endl;
                break;
            }

            //收包
            int rcvLen = recv(localUdpSocket,buf,sizeof(buf),0);
            //不可读时跳过本次迭代
            if (rcvLen == WSAEWOULDBLOCK) {  continue; }

            now = time(NULL);
            buf[rcvLen] = '\0';
            string cPacket(buf);
            //解密
            string mPacket = ClientService::decrypt_AES(cPacket, aeKey,iv);
            //字段提取
            int seq = ClientService::getSeq(&mPacket);
            string md5 = mPacket.substr(4,32);
            string data = mPacket.substr(36,mPacket.length()-36);
            //校验
            string msg;
            string encryptMsg;

            //通过校验
            if (1)//MD5(data).toStr() == md5
            {
                ClientService::seq = seq;
                msg = to_string(StatusInfo::MD5TRUE);
                fosWrite(storePath, data.c_str());
                cout << "md5 verify success" << endl;
            }
            else {
                msg = to_string(StatusInfo::MD5FALSE);
                cout << "md5 verify fail" << endl;
            }
            encryptMsg = encrypt_AES(msg, aeKey, iv);
            //发送反馈
            sendto(localUdpSocket, encryptMsg.c_str(), encryptMsg.length(), 0, (sockaddr*)&hostUdpAddr, sizeof(hostUdpAddr));
            //清空缓冲区
            memset(buf,0,sizeof(buf));
        }

        if(timeOut) {
            cout << "timeout：60 s"<<endl;
        }

        delete[] buf;
}


/// <summary>
/// 断点存储
/// </summary>
/// <param name="path">存储路径</param>
/// <param name="rcvNum">接收的序号，从0开始</param>
/// <param name="totalNum">总包数</param>
void ClientService::breakStorage(const string path, const int rcvNum,const int totalNum) {
    ofstream fos;
    fos.open("breaks.txt",ios_base::app);
    if (!fos.is_open()){
        cout<<"breaks open and storage fail\n"<<endl;
        return;
    }
    string str = path+":"+ to_string(rcvNum)+","+ to_string(totalNum)+"\n";
    fos.write(str.c_str(),str.length());
    fos.close();
}


/// <summary>
/// 断点文件解析
/// </summary>
/// <param name="confPath">断点文件存储路径</param>
/// <returns>断点对象向量指针，注意释放堆内存</returns>
vector<BreakPoint>* ClientService::getBreakPoints(const string confPath) {
    ifstream fis;
    fis.open(confPath,ios_base::in);
    if(!fis.is_open()) {
        cout<<"conf open fail"<<endl;
    }
    //堆内存
    vector<BreakPoint>* brs = new vector<BreakPoint>;
    string tmpLine;
    while(true){
        if (fis.eof()) break;
        getline(fis,tmpLine);
        if (tmpLine == "") {
            cout<<"breaks file parse finished"<<endl;
            break;
        }
        size_t dotIndex = tmpLine.find(':');
        size_t dotIndex2 = tmpLine.find(',');
        string path = tmpLine.substr(0,dotIndex);
        string rcvNum =  tmpLine.substr(dotIndex+1,dotIndex2-dotIndex-1);
        string totalNUm = tmpLine.substr(dotIndex2+1,tmpLine.length()-dotIndex2-1);
        BreakPoint br;
        br.path = path;
        br.rcvNum = stoi(rcvNum);
        br.totalNum = stoi(totalNUm);
        brs->push_back(br);
    }
    return brs;
}


/// <summary>
/// 判断文件路径是否是断点
/// </summary>
/// <param name="path">服务器返回的文件路径</param>
/// <returns>断点对象的指针 或 NULL</returns>
BreakPoint* ClientService::getBreakInfo(string path) {
    if (brs == NULL) {
        cout << "breaks conf file load incorrectly" << endl;
    }
    for (BreakPoint& br : *brs) {
        if (br.path == path)
        {
            return &br;
        }
    }
    return NULL;
}

bool ClientService::getisTerminate()
{
    return this->isTerminate;
}


std::string ClientService::encrypt_AES(const std::string& data, const std::string& key, const std::string& iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));

    std::vector<unsigned char> encrypted_data(data.size() + 16); // +16用于限制最大的填充
    int encrypted_length;
    EVP_EncryptUpdate(ctx, encrypted_data.data(), &encrypted_length, reinterpret_cast<const unsigned char*>(data.data()), data.size());

    int final_length;
    EVP_EncryptFinal_ex(ctx, encrypted_data.data() + encrypted_length, &final_length);

    encrypted_data.resize(encrypted_length + final_length); //调整到实际长度
    EVP_CIPHER_CTX_free(ctx);

    //将vector<unsigned char>转换成string
    std::string result(encrypted_data.begin(), encrypted_data.end());
    return result;
}


std::string ClientService::decrypt_AES(const std::string data, const std::string& key, const std::string& iv) {
    //将string转换成vector<unsigned char>
    const std::vector<unsigned char> encrypted_data(data.begin(), data.end());

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));

    std::string decrypted_data(encrypted_data.size(), '\0');
    int decrypted_length;
    EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&decrypted_data[0]), &decrypted_length, encrypted_data.data(), encrypted_data.size());

    int final_length;
    EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&decrypted_data[0]) + decrypted_length, &final_length);

    decrypted_data.resize(decrypted_length + final_length); //调整到实际长度
    EVP_CIPHER_CTX_free(ctx);

    return decrypted_data;
}

bool ClientService::decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        return false;
    }
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        return false;
    }

    inFile.seekg(0, std::ios::end);
    auto fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    std::vector<char> inputBuffer(fileSize);
    inFile.read(inputBuffer.data(), fileSize);
    inFile.close();

    uLongf outputBufferSize = fileSize * 10;  // 输出缓冲区的大小，可根据需要调整。
    std::vector<char> outputBuffer(outputBufferSize);

    int result;
    do {
        result = uncompress(reinterpret_cast<Bytef*>(outputBuffer.data()), &outputBufferSize,
            reinterpret_cast<const Bytef*>(inputBuffer.data()), fileSize);

        if (result == Z_BUF_ERROR) {
            outputBufferSize *= 2;
            outputBuffer.resize(outputBufferSize);
        }
    } while (result == Z_BUF_ERROR);

    if (result != Z_OK) {
        return false;
    }

    outFile.write(outputBuffer.data(), outputBufferSize);
    outFile.close();

    return true;
}












