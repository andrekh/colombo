#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc != 4){
        std::cout << "Usage: ./colombo <target ip> <start port> <end port>" << std::endl;
        return -1;
    }

    char *targetIP = argv[1];
    int startPort = atoi(argv[2]);
    int endPort = atoi(argv[3]);

    struct sockaddr_in target_addr = {0};
    int sock = 0;

    target_addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, targetIP, &target_addr.sin_addr) <= 0) {
        std::cout << "Error converting target ip address to binary form." << std::endl;
        return -1;
    }

    for (int i = startPort; i < endPort; i++){
        target_addr.sin_port = htons(i);
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <0) {
            std::cout << "Error creating socket: ";
            std::cout << std::strerror(errno) << std::endl;
            return -1;
        }
        if (connect(sock, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0){
            std::cout << "Port " << i << " closed: ";
            std::cout << std::strerror(errno) << std::endl;
        }
        else{
            std::cout << "Port " << i << " open " << std::endl;
        }
        close(sock);
    }

    return 0;
}