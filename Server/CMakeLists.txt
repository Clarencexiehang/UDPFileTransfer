cmake_minimum_required(VERSION 3.21)

project(Server)

set(CMAKE_CXX_STANDARD 14)


include_directories(Util
                    Service
                    Entity
                    ${OPENSSL_INCLUDE_DIR}
        )

add_executable(Server
        main.cpp
        Entity/SockInfo.h
        Service/ServerService.h
        Service/ServerService.cpp
        Util/MD5Util.h
        Util/MD5Util.cpp
        Controller/WebServer.cpp
        Controller/WebServer.h
        Dao/UserMapper.cpp
        Dao/UserMapper.h
        Service/DynamicallyAdjustNetwork.cpp Service/DynamicallyAdjustNetwork.h
        Service/NetControl.cpp Service/NetControl.h Entity/StatusInfo.h

        Controller/WebServer.cpp Controller/WebServer.cpp Util/crsa.h Util/crsa.cpp Util/Rsa.h)


# 指定b库的头文件路径和链接库
#包含外部库
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_library(WFREST_LIB NAMES wfrest HINTS /usr/local/lib)
find_library(WORKFLOW_LIB NAMES workflow HINTS /usr/local/lib)

target_link_libraries(Server ${WORKFLOW_LIB} ${WFREST_LIB})

target_link_libraries(Server mysqlcppconn)
target_link_libraries(Server ZLIB::ZLIB)
target_link_libraries(Server OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(Server crypto)

#文件系统库
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(Server Boost::filesystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

