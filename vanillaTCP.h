//
// Created by smallguy on 2021-07-23.
//

#ifndef COLOMBO_VANILLATCP_H
#define COLOMBO_VANILLATCP_H
#include <mutex>

class TCPScanner {
public:
    explicit TCPScanner(sockaddr_in *targetAddr);
    int scan(int port);

private:
    sockaddr_in *targetAddr;
    static std::mutex mtx_;
};


#endif //COLOMBO_VANILLATCP_H
