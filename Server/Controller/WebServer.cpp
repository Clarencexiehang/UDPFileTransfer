//
// Created by 泪程 on 2023/6/7.
//

#include "WebServer.h"
#include "wfrest/HttpServer.h"
#include "wfrest/json.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
namespace fs = boost::filesystem;
; // 命名空间別名
using namespace wfrest;
using myJson = nlohmann::json;

std::string file_url = "/home/zj666/code/file_resources";
HttpServer svr;

void getAllFiles(const fs::path& path, const std::string& relativePath, myJson& valid_text, int& i)
{
  for (const auto& entry : fs::directory_iterator(path)) {
    if (fs::is_directory(entry.status())) {
      std::string subdir_relative_path = relativePath.empty() ? entry.path().filename().string() : relativePath + "/" + entry.path().filename().string();
      getAllFiles(entry.path(), subdir_relative_path, valid_text, i);
    } else {
      std::string file_relative_path = relativePath.empty() ? entry.path().filename().string() : relativePath + "/" + entry.path().filename().string();
      valid_text["data"][i++] = file_relative_path;
    }
  }
}
void return_file_info() {
  svr.GET("/getFileList", [](const HttpReq *req, HttpResp *resp) {
//    fs::path p(file_url);
//    myJson valid_text;
//    int i = 0;
//    valid_text["data"] = myJson ::array();
//    for (fs::directory_iterator it(p); it != fs::directory_iterator(); ++it) {
//      if (!fs::is_directory(it->status())) { // 只列出文件而忽略目录
//        std::string temp;
//        temp = it->path().filename().string();
//        valid_text["data"][i++] = temp;
//      }
//    }
    fs::path p(file_url);
    myJson valid_text;
    int i = 0;
    valid_text["data"] = myJson::array();
    getAllFiles(p,"", valid_text, i);

    resp->Json(valid_text);
  });
}

void login() {
  svr.GET("/login", [](const HttpReq *req, HttpResp *resp) {
    std::string username = req->query("username");
    std::string password = req->query("password");
    std::string true_password = getUserPassword(username);
    if (true_password == password){
      resp->String(std::move("ok"));
    }
    else{
      resp->String(std::move("error"));
    }
  });
}

void myRegister() {
  svr.POST("/register", [](const HttpReq *req, HttpResp *resp) {
    // reference, no copy here
    std::string &body = req->body();
    nlohmann::json json_data = nlohmann::json::parse(body);
    std::string username = json_data["username"];
    std::string password = json_data["password"];
    std::string email = json_data["email"];
    std::cout<<"register_request"<<std::endl;
    bool isreg = registerUser(username,password,email);
    if(isreg){
      resp->String(std::move("ok"));
    }
    else{
      resp->String(std::move("error"));
    }
  });
}

void runServer() {
  return_file_info();
  login();
  myRegister();
  if (svr.start(8888) == 0) {
    getchar();
    svr.stop();
  } else {
    fprintf(stderr, "Cannot start server");
    exit(1);
  }
}
