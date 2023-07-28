#include "ServerService.h"
#include "random"
#include "iostream"
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "thread"

#include "MD5Util.h"
#include "StatusInfo.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "DynamicallyAdjustNetwork.h"
#include "../Dao/UserMapper.h"
#include "Rsa.h"

using namespace std;

vector<int> ServerService::ports;
vector<RequestInfo> ServerService::requestInfos;
const string iv = "8NONwyJtHesysWpM"; // 16字节（128位）初始化向量


int ServerService::allocateUdpPort() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // 设定随机数范围（包括）
    int min_num = 9000;
    int max_num = 9990;

    std::uniform_int_distribution<int> dist(min_num, max_num);

    while (true) {
        // 生成随机端口号
        int tempPort = dist(gen);

        bool flag = false;
        for (int i: ServerService::ports) {
            if (tempPort == i) {
                flag = true;
                break;
            }
        }

        if (flag == false) {
            ServerService::ports.push_back(tempPort);
            return tempPort;
        }
    }
}

void ServerService::releaseUdpPort(int port) {
    for (int i: ServerService::ports) {
        if (port == i) {
            ServerService::ports.erase(ports.begin() + i);
            break;
        }
    }
}

int ServerService::allocateClientID(string account) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // 设定随机数范围（包括）
    int min_num = 0;
    int max_num = 10000;

    std::uniform_int_distribution<int> dist(min_num, max_num);

    while (true) {
        // 生成随机端口号
        int id = dist(gen);

        bool flag = false;
        for (RequestInfo i : ServerService::requestInfos) {
            if (id == i.clientID) {
                flag = true;
                break;
            }
        }

        if (flag == false) {
            return id;
        }
    }
}

void ServerService::releaseClientID(int client_ID) {
    for (auto i: ServerService::requestInfos) {
        if (client_ID == i.clientID) {
            ServerService::requestInfos.erase(requestInfos.begin()+client_ID);
            break;
        }
    }
}


string ServerService::createAESkey(string userName) {
    //生成256bit 的AES密钥
    constexpr int key_length = 32;  // AES 256位密钥长度（以字节为单位）
    unsigned char key[key_length];

    // 生成密钥
    if (!RAND_bytes(key, sizeof(key))) {
        std::cerr << "Error generating random AES key." << std::endl;
        return 0;
    }

    // 输出密钥（以十六进制格式）
    for (int i = 0; i < key_length; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(key[i])<<endl;
    }

    //存入数据库中
    string storeKey(reinterpret_cast<char*>(key), reinterpret_cast<char*>(key) + sizeof(key) - 1);
    savePrivateAesKey(userName,storeKey);

    return storeKey;
}

void ServerService::sentSecretKey(SockInfo *cinfo,string userName) {
    //获取客户端RSA公钥
    string client_RSA_publicKey;
    string aes_key;

    char buff[1024];
    int len = recv(cinfo->fd, buff, sizeof(buff), 0);
    if (len > 0) {
        client_RSA_publicKey.assign(buff);
        vector<string> content = split_string(client_RSA_publicKey);
        Rsa r;
        r.ini();
        r.setPsk(stoi(content[0]));             //设置公钥
        r.setModule(stoi(content[1]));

        //生成AES密钥并存入数据库中
        aes_key = ServerService::createAESkey(userName);

        //用RSA公钥加密，发送加密后的AES密钥
        vector<long> temp = {aes_key.begin(),aes_key.end()};
        string newKey = r.vecConverter(r.encrypt(&temp));
        if (send(cinfo->fd, newKey.data(), newKey.length(), 0) < 0) {
            std::cerr << "AES密钥发送失败!" << std::endl;
            close(cinfo->fd);
            return;
        }
    } else if (len == 0) {
        cout << "接收完毕\n\n";
    } else {
        std::cerr << "读取失败\n";
    }
}


/*
 * @Param
 * */
RequestInfo ServerService::getTCPInfo(SockInfo *cinfo) {
    //打印客户端的IP和端口号
    char clientIP[32];cout<<"account3:";
    cout << "连接的客户端IP:" << inet_ntop(AF_INET, &cinfo->addr.sin_addr.s_addr, clientIP, sizeof(clientIP))
         << "  端口号是:" << ntohs(cinfo->addr.sin_port) << endl;


    //接收数据,获取TCP发送的文件路径
    string account;
    string filePath;
    int startPos = 0;
    int isSendRSAKey = 0;
    while (1) {
        char buff[1024];
        int len = recv(cinfo->fd, buff, sizeof(buff), 0);
        if (len > 0) {
            string tcp_data;
            tcp_data.assign(buff);  cout<<"客户端TCP传递的信息是: "<<tcp_data<<endl;
            vector<string> content = ServerService::split_string(tcp_data);

            account = content[0];
            filePath = content[1];
            startPos = stoi(content[2]);
            isSendRSAKey = stoi(content[3]);

            //判断是否需要发送 服务器RSA公钥 和 AES密钥
            if (isSendRSAKey) {
                sentSecretKey(cinfo, account);
            }

            //添加客户端
            int client_id = allocateClientID(account);         //随机分配一个ID
            DynamicallyAdjustNetwork::addClilent(client_id, account);

            //添加到对象中
            string aesKey = getAesKey(account);

            RequestInfo info(client_id, account, filePath, startPos, clientIP, aesKey);
            ServerService::requestInfos.push_back(info);


            //关闭TCP连接资源
            close(cinfo->fd);

            return info;
        } else if (len == 0) {
            cout << "接收完毕\n\n";
            break;
        } else {
            std::cerr << "读取失败\n";
            break;
        }
    }
}



void ServerService::UDPSendFile(const char *clientIP, int clientPort, int clientID, string filePath , int startPos , string aesKey){
    //绑定服务端UDP接收端口
    int serverPort = allocateUdpPort();
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverPort);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);


    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        std::cerr << "Error: 无法创建UDP socket" << std::endl;
        return;
    }

    //服务端绑定套接字地址
    if (bind(sockfd, (const struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 配置目标地址
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(clientPort);
    if (inet_pton(AF_INET, clientIP, &client_addr.sin_addr) <= 0) {
        std::cerr << "Error: 无效的客户端IP地址" << std::endl;
        close(sockfd);
        return;
    }

    //发送端口号
    sendto(sockfd, to_string(serverPort).data(), sizeof(serverPort), 0,
           (struct sockaddr *) &client_addr, sizeof(client_addr));


    //压缩文件
    string compressFilePath = "/root/CompressDir/"+ServerService::getFileName(filePath);
    if (compressFile(filePath, compressFilePath)) {
        std::cout << "File compressed successfully!\n";
    } else {
        std::cout << "Failed to compress file.\n";
    }

    //给服务端发送数据包总的个数
    int total_packet_num = ServerService::getFilePacketNum(compressFilePath);
    sendto(sockfd, to_string(total_packet_num).data(), sizeof(total_packet_num), 0,
           (struct sockaddr *) &client_addr, sizeof(client_addr));

    //读取文件
    cout << "compress filePath  " << compressFilePath << endl;
    std::ifstream inputFile(compressFilePath, std::ios::in | std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: 无法打开文件!" << std::endl;
        return;
    }

    const size_t chunkSize = 60 * 1024;         //缓冲区设置为60k
    std::vector<char> buffer(chunkSize);


    int packet_num = 0;
    while (inputFile.read(buffer.data(), chunkSize)) {
        std::streamsize bytesRead = inputFile.gcount();

        //数据包序号+1
        if(packet_num < startPos){      //如果是断点续传，前面的直接略过
            packet_num++;
            continue;
        }
        packet_num++;


        //生成数据MD5摘要
        string hashKey = MD5Util(buffer.data()).toStr();

        //连接发送的数据包
        string OriginPacketData = to_string(packet_num) + '|' + hashKey + '|' + buffer.data();

        //加密数据
        string packetData = encrypt_AES(OriginPacketData, aesKey, iv);

        auto start_time = std::chrono::high_resolution_clock::now();        //用于计算发送开始时间

        //将数据包发送到客户端
        ssize_t bytesSent = sendto(sockfd, packetData.data(), bytesRead, 0,
                                   (struct sockaddr *) &client_addr, sizeof(client_addr));

        if (bytesSent != bytesRead) {
            std::cerr << "数据包发送失败" << std::endl;
            break;
        }

        //计算服务器发送速度，并选择是否延迟，控制发送速度
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        auto bindWidth = (60*1024)/duration;
        DynamicallyAdjustNetwork::setClientBindwidth(clientID,bindWidth);
        int sleepTime = DynamicallyAdjustNetwork::get_limit_num(clientID);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

        //等待客户端的重传响应，如果验证失败，重传
        char feedback[1024];
        socklen_t client_addr_len = sizeof(client_addr);
        int recv_len = recvfrom(sockfd, feedback, sizeof(feedback) - 1, 0, (struct sockaddr *) &client_addr,
                                &client_addr_len);
        if (recv_len < 0) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        }
        buffer[recv_len] = '\0';

        //解密反馈信息
        std::string decrypted_data = decrypt_AES(feedback, aesKey, iv);

        std::cout << "Received message: " << decrypted_data << std::endl;


        if (std::stoi(decrypted_data) == StatusInfo::FALSE) {
            int retransmission_num = 0;
            while (true) {
                //开始重传，重传10次就超限
                if (retransmission_num == 10) {
                    string encodeSign = encrypt_AES(to_string(StatusInfo::PAUSE).data(),aesKey,iv);
                    sendto(sockfd, encodeSign.data(), encodeSign.length(), 0,
                           (struct sockaddr *) &client_addr, sizeof(client_addr));
                    cout << "重传超限!\n";

                    //释放资源
                    inputFile.close();
                    releaseUdpPort(serverPort);
                    return;
                } else {
                    sendto(sockfd, packetData.data(), bytesRead, 0,
                           (struct sockaddr *) &client_addr, sizeof(client_addr));

                    //等待回复
                    recvfrom(sockfd, feedback, sizeof(feedback) - 1, 0, (struct sockaddr *) &client_addr,
                             &client_addr_len);
                    decrypted_data = decrypt_AES(feedback, aesKey, iv);
                    if (stoi(decrypted_data) == StatusInfo::TRUE)
                        break;
                    else
                        retransmission_num++;
                }
            }
        }

    }

    //文件传输完成
    string encodeSign = encrypt_AES(to_string(StatusInfo::SUCCESS).data(),aesKey,iv);
    sendto(sockfd, encodeSign.data(), encodeSign.length(), 0,
           (struct sockaddr *) &client_addr, sizeof(client_addr));
    cout << "文件发送完成\n";

    //删除压缩的文件
    if (remove(compressFilePath.c_str()) != 0)
        std::cout << "压缩删除文件失败" << std::endl;


    //释放资源
    inputFile.close();
    releaseUdpPort(serverPort);
    ServerService::releaseClientID(clientID);

}


string ServerService::getFileName(std::string filePath) {
    size_t found = filePath.find_last_of("/");

    if (found != std::string::npos) {
        return filePath.substr(found + 1);
    } else {
        return filePath; // 如果路径不包含'/'，则直接返回原字符串
    }
}


bool ServerService::compressFile(const std::string &inputFile, const std::string &outputFile, int compressionLevel) {
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

    std::vector<char> outputBuffer(compressBound(fileSize));

    uLongf outputBufferSize = outputBuffer.size();
    int result = compress2(reinterpret_cast<Bytef *>(outputBuffer.data()), &outputBufferSize,
                           reinterpret_cast<const Bytef *>(inputBuffer.data()), fileSize, compressionLevel);

    if (result != Z_OK) {
        return false;
    }

    outFile.write(outputBuffer.data(), outputBufferSize);
    outFile.close();

    return true;
}


bool ServerService::decompressFile(const std::string &inputFile, const std::string &outputFile) {
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
        result = uncompress(reinterpret_cast<Bytef *>(outputBuffer.data()), &outputBufferSize,
                            reinterpret_cast<const Bytef *>(inputBuffer.data()), fileSize);

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

// 加密函数
std::string ServerService::encrypt_AES(const std::string &data, const std::string &key, const std::string &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));

    std::vector<unsigned char> encrypted_data(data.size() + 16); // +16用于限制最大的填充
    int encrypted_length;
    EVP_EncryptUpdate(ctx, encrypted_data.data(), &encrypted_length, reinterpret_cast<const unsigned char*>(data.data()), data.size());

    int final_length;
    EVP_EncryptFinal_ex(ctx, encrypted_data.data() + encrypted_length, &final_length);

    encrypted_data.resize(encrypted_length + final_length); //调整到实际长度
    EVP_CIPHER_CTX_free(ctx);

    //将vector<unsigned char>转换成string
    std::string result(encrypted_data.begin(),encrypted_data.end());
    return result;
}

// 解密函数
std::string ServerService::decrypt_AES(const std::string data, const std::string &key, const std::string &iv) {
    //将string转换成vector<unsigned char>
    const std::vector<unsigned char> encrypted_data(data.begin(), data.end());

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
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

vector<string> ServerService::split_string(const std::string& input) {
    char delimiter = '|';
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


int ServerService::getFilePacketNum(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        return -1;
    }

    file.seekg(0, std::ios::end);
    std::streamoff size = file.tellg();
    file.close();

    int fileSizeInt = static_cast<int>(size)/(60*1024);

    return fileSizeInt;
}

