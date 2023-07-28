#include "NetControl.h"
#include <iostream>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define TEST_DURATION 1000 // 测试持续时间，单位为毫秒

double Server_Limit_test(char* ip_address,int port) {
  try {
    // 创建UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 设置客户端地址和端口
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(ip_address);

    // 启动计时器
    auto start_time = std::chrono::high_resolution_clock::now();

    // 发送数据包
    char buffer[BUFFER_SIZE] = { 0 };
    long total_bytes_sent = 0;
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count() < TEST_DURATION) {
      sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
      total_bytes_sent += strlen(buffer);
    }

    // 停止计时器
    auto end_time = std::chrono::high_resolution_clock::now();

    // 计算传输速度（单位：字节/秒） 上行带宽
    double bandwidth = (double)total_bytes_sent / (std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()) * 1000;

    // 关闭socket

    close(sockfd);

    // 返回网络带宽
    return bandwidth;
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

