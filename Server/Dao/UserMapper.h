//
// Created by 泪程 on 2023/6/7.
//
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>// 这里必须包含此文件

#ifndef SERVER_USERMAPPER_H
#define SERVER_USERMAPPER_H

std::string  getUserPassword(std::string userName);
int getUserPriority(std::string userName);
bool registerUser(std::string username,std::string password,std::string email);
void savePrivateAesKey(std::string username,std::string key);
std::string getAesKey(std::string username);
#endif // SERVER_USERMAPPER_H
