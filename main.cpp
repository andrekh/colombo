#include <iostream>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "utils.h"
#include "vanillaTCP.h"

int main(int argc, char *argv[]) {

    if (argc != 4){
        std::cout << "Usage: ./colombo <target ip> <start port> <end port>" << std::endl;
        return -1;
    }

    char *target = get_IP_from_hostname(argv[1]);
    int startPort = atoi(argv[2]);
    int endPort = atoi(argv[3]);

    struct sockaddr_in targetAddr = {0};

    // targetAddr setup.
    if (inet_pton(AF_INET, target, &targetAddr.sin_addr) <= 0) {   //inet_pton copies the target ip to targetAddr.sin_addr
        std::cout << "Error converting target ip address to binary form." << std::endl;
        return -1;
    }
    targetAddr.sin_family = AF_INET;   //IPv4

    // spawn a thread for each socket
    std::vector<std::thread> threads;
    for (int i = startPort; i < endPort; i++){
        //create threads and wait for each of them to return
        TCPScanner tcpscanner = TCPScanner(&targetAddr);
        threads.emplace_back(std::thread(&TCPScanner::scan, tcpscanner, i));
    }
    for (std::thread &th : threads){
        th.join();
    }

    return 0;
}
