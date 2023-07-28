//
// Created by 泪程 on 2023/6/7.
//

#include "DynamicallyAdjustNetwork.h"
#include "../Dao/UserMapper.h"
double DynamicallyAdjustNetwork::SeverHostBindwidth = 100*1000*1000; //假设服务器的最大带宽是800Mbps 即100MB/s
std::vector<ClientInfo> DynamicallyAdjustNetwork::ClientList;
double DynamicallyAdjustNetwork::SumBindwidth = 0;

void DynamicallyAdjustNetwork::addClilent(int Client_id,std::string userName) {
  int client_priority = getUserPriority(userName);
  ClientInfo client = ClientInfo(Client_id, client_priority);
  ClientList.push_back(client);
}

void DynamicallyAdjustNetwork::setClientBindwidth(int Client_id,double Client_bindwidth){

  for (ClientInfo item : ClientList) {
    if (item.Client_id == Client_id) {
      SumBindwidth -= item.Client_bindwidth;//更新总带宽
      SumBindwidth += Client_bindwidth;
      item.Client_bindwidth = Client_bindwidth;//更新客服端带宽
      if(Client_bindwidth <= 100 * 1000){ //如果某个客服端的发送速率低于100kb每秒，我们认为此时服务器的带宽利用率可能已经达到最大，
                                          // 这时候满足不了所有的客服机，需要进行动态控制发送速度

        DynamicallyAdjustNetwork::AdjustNetwork();
      }
    }
  }
}

void DynamicallyAdjustNetwork::AdjustNetwork() {
  std::cout<<"动态控制算法：已用带宽："<<SumBindwidth<<std::endl;
  if(SumBindwidth < 95 * 1000 * 1000) return;//如果总发送速率低于95MB/s 说明还有足够的带宽资源，不用控制发送速度
  double averageBindwidth = SumBindwidth / ClientList.size();
  for (int i = 0; i < ClientList.size(); i++) {
    if (ClientList[i].Client_bindwidth > averageBindwidth) {
      //如果某客服端的带宽较高，占用的较高的服务端资源，应该适当降低这个客服端的发送速度
      //优先级定义：
      //0:最高优先级，任何时候都以最高速率发送，1：次高优先级，如果客服机的带宽较高，每组加1ms延迟，2：低优先级，每组加1ms延迟，此外如果客服端的带宽较高，再加1ms
      //注意：降低的程度我这里默认每发送一个分组暂停1ms用于体现算法
      //实际上这个值应该根据很多因素来计算

      ClientList[i].limit_num = 1;
    }
    if(ClientList[i].priority == 0) {
      ClientList[i].limit_num == 0;
      continue;
    }
    if(ClientList[i].priority == 3){
      ClientList[i].limit_num ++ ;
    }
  }
}

double DynamicallyAdjustNetwork::get_limit_num(int client_id) {
  for (ClientInfo item : ClientList) {
    if (item.Client_id == client_id) {
      return item.limit_num;
    }
  }
  return -1;
}
