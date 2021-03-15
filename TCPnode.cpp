#include <iostream>
#include <unistd.h>

#include "TCPnode.hpp"


TCPnode::TCPnode(char *IP, int PORT) {
    if ((myFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::perror("Unable to create socket...");
        exit(-1);
    }

    const int opt = 1;
    e = setsockopt(myFD, SOL_SOCKET, SO_REUSEADDR, &opt, 4);
    if (e < 0) {
        std::perror("Unable to set socket options...");
        exit(-1);
    }

    Address.sin_family = AF_INET;
    Address.sin_port = htons(PORT);
    ADL = sizeof(Address);
}


TCPnode::~TCPnode(){
}


const char *TCPnode::myName() {
    return typeid(this).name();
}


void TCPnode::shutdownSafely() {
    std::cout << myName() << " shutting down safely" << std::endl;
    shutdown(myFD, SHUT_RDWR);
    close(myFD);
}
