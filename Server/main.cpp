#include <iostream>

#include "Controller/WebServer.h"
#include "Dao/UserMapper.h"
#include "Service/DynamicallyAdjustNetwork.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "thread"

#include "Service/ServerService.h"
#include "Entity/SockInfo.h"


using namespace std;

const int tcp_port = 9000;
int server_fd;
struct sockaddr_in server_addr;    //绑定端口号
std::vector<std::thread> threads;



bool init(){
    //创建子线程运行web后端
    threads.emplace_back(runServer);
    cout<<"成功启动服务器后端...\n";

    //1.创建监听的套接字
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        std::cerr << "创建套接字失败\n"<<endl;
        return false;
    }

    //2.绑定本地的IP port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(tcp_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "绑定失败\n";
        return false;
    }
    return true;
}

/*
 * 创建的子线程
 */
void * working(SockInfo *cinfo){
    //获取客户端TCP请求发送的数据
    RequestInfo info = ServerService::getTCPInfo(cinfo);


    //UDP开始发送数据
    ServerService::UDPSendFile(info.clientIP.c_str(),8000,info.clientID,info.filePath,info.startPos,info.aesKey);

}

int main(int argc, char** argv){
    //初始化服务器
    if(!init()){
        cout<<"服务器初始化错误!"<<endl;
        return 0;
    }else{
        cout<<"服务器已启动..."<<endl;
    }

    //设置监听
    if (listen(server_fd, 128) == -1) {
        std::cerr << "监听失败\n";
        return -1;
    }else{
        cout<<"服务器正在监听\n";
    }

    SockInfo *clientSocketInfo = new SockInfo;
    socklen_t  client_len = sizeof(clientSocketInfo->addr);
    while (1){
        //阻塞并等待客户端的连接
        clientSocketInfo->fd = accept(server_fd, (struct sockaddr*)&clientSocketInfo->addr, &client_len);
        if (clientSocketInfo->fd == -1) {
            std::cerr << "接受连接失败\n";
            continue;   //重试，再次接收
        }

        //连接成功后
        //建立新的线程处理UDP发送数据
        threads.emplace_back(working,clientSocketInfo);

    }

}


