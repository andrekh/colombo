//
// Created by smallguy on 2021-07-23.
//
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <mutex>
#include "vanillaTCP.h"

std::mutex TCPScanner::mtx_;

TCPScanner::TCPScanner(sockaddr_in *targetAddr) {
    this->targetAddr= targetAddr;
}

int TCPScanner::scan(int port){
    (*targetAddr).sin_port = htons(port);
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <0) {
        std::cout << "Error creating socket: ";
        std::cout << std::strerror(errno) << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr*)targetAddr, sizeof(*targetAddr)) < 0){
        TCPScanner::mtx_.lock();
        std::cout << "Port " << port << " closed: ";
        std::cout << std::strerror(errno) << std::endl;
        TCPScanner::mtx_.unlock();
    }
    else{
        TCPScanner::mtx_.lock();
        std::cout << "Port " << port << " open " << std::endl;
        TCPScanner::mtx_.unlock();
    }

    close(sock);
}