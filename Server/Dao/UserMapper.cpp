//
// Created by 泪程 on 2023/6/7.
//

#include "UserMapper.h"

using namespace std;
sql::Connection* con;

void mysqlInit(){
  // 设置MySQL连接信息
  sql::Driver* driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "123456");

  // 选择要使用的数据库
  con->setSchema("zyuser");
}

string  getUserPassword(string userName){
  try {
    mysqlInit();
    string Sql = "select password from user where username = '" + userName + "'";
    sql::Statement* stmt = con->createStatement();
//    cout << "User_password" << Sql << endl;
    sql::ResultSet* res = stmt->executeQuery(Sql);
    res->next();
    string password = res->getString("password");
    delete res;
    delete stmt;
    return password;
  }
  catch (sql::SQLException &e) {
//    cout << "SQL Exception: " << e.what() << endl;
    return e.what();
  }
  catch (std::exception &e) {
//    cout << "Exception: " << e.what() << endl;
    return e.what();
  }
}
int getUserPriority(std::string userName){
  try {
    mysqlInit();
    string Sql = "select priority from user where username = '" + userName + "'";
    sql::Statement* stmt = con->createStatement();
    //    cout << "User_password" << Sql << endl;
    sql::ResultSet* res = stmt->executeQuery(Sql);
    res->next();
    int priority = res->getInt("priority");
    delete res;
    delete stmt;
    return priority;
  }
  catch (sql::SQLException &e) {
        cout << "SQL Exception: " << e.what() << endl;
    return -1;
  }
  catch (std::exception &e) {
        cout << "Exception: " << e.what() << endl;
    return -1;
  }
}
bool registerUser(string username,string password,string email){
  try {
    mysqlInit();
    string sql = "insert into user(username, password, email) values ('"+username + "','"+password+"','"+email+"');";
    sql::Statement* stmt = con->createStatement();
    stmt->execute(sql);
    delete stmt;
    return true;
  }
  catch (sql::SQLException &e) {
    cout << "SQL Exception: " << e.what() << endl;
    return false;
  }
  catch (std::exception &e) {
    cout << "Exception: " << e.what() << endl;
    return false;
  }

}
void savePrivateAesKey(std::string username,std::string key){
  try {
    mysqlInit();
    string Sql = "insert into aeskey (username, aeskey) values ('"+username+"','"+key+"');";
    sql::Statement* stmt = con->createStatement();
    stmt->execute(Sql);
    delete stmt;
  }
  catch (sql::SQLException &e) {
    cout << "SQL Exception: " << e.what() << endl;
  }
  catch (std::exception &e) {
    cout << "Exception: " << e.what() << endl;
  }
}
std::string getAesKey(std::string username){
  try {
    mysqlInit();
    string Sql = "select aeskey from aeskey where username = '" + username + "'";
    sql::Statement* stmt = con->createStatement();
    //    cout << "User_password" << Sql << endl;
    sql::ResultSet* res = stmt->executeQuery(Sql);
    res->next();
    std::string aeskey = res->getString("aeskey");
    delete res;
    delete stmt;
    return aeskey;
  }
  catch (sql::SQLException &e) {
    cout << "SQL Exception: " << e.what() << endl;
    return "error";
  }
  catch (std::exception &e) {
    cout << "Exception: " << e.what() << endl;
    return "error";
  }
}