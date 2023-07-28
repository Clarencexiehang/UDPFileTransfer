//
// Created by 泪程 on 2023/6/7.
//
#include <iostream>
#include <vector>
#ifndef SERVER_DYNAMICALLYADJUSTNETWORK_H
#define SERVER_DYNAMICALLYADJUSTNETWORK_H
class ClientInfo {
public:
  int Client_id;
  double Client_bindwidth;
  double limit_num ;
  int priority;
public:
  ClientInfo(int client_id, int client_priority) {
    Client_id = client_id;
    priority = client_priority;
    Client_bindwidth = 0;
    limit_num = 0;
  }
};

class DynamicallyAdjustNetwork {
public:
  static double SeverHostBindwidth; //假设服务器的最大带宽是800Mbps 即100MB/s
  static std::vector<ClientInfo> ClientList;
  static double SumBindwidth;

public:
  static void addClilent(int Client_id,std::string userName);
  static void AdjustNetwork() ;
  static double get_limit_num(int client_id);
  static void setClientBindwidth(int Client_id,double Client_bindwidth);
};
#endif // SERVER_DYNAMICALLYADJUSTNETWORK_H
