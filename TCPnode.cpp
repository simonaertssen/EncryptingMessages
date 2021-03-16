#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "TCPnode.hpp"


TCPnode::TCPnode(char *IP, int PORT) {
    if ((myFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        std::perror("Unable to create socket...");
        exit(-1);
    }

    // Set socket to reuse addresses:
    const int opt = 1;  // has size of 4 bytes
    if (setsockopt(myFD, SOL_SOCKET, SO_REUSEADDR, &opt, 4) < 0) {
        std::perror("Unable to set socket options...");
        exit(-1);
    }

    // Set connection timeout: set socket to non-blocking
    int flags = fcntl(myFD, F_GETFL, NULL);
    if (flags > 0) {
        flags |= O_NONBLOCK;
        if (fcntl(myFD, F_SETFL, flags) < 0) {
            std::perror("Unable to set socket non-blocking...");
        }
    }

    // // flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    // //
    // // if (fcntl(myFD, F_SETFL, flags) < 0) {
    // //     std::perror("Unable to set connection timeout options...");
    // // }
    //
    struct timeval timeout;  // has size of 16 bytes
    timeout.tv_sec  = 1;
    timeout.tv_usec = 10;
    // fd_set myset;
    // FD_ZERO(&myset);
    // FD_SET(myFD, &myset);
    // if (select(0, &myset, NULL, NULL, &timeout) < 0) {
    //     std::perror("Unable to set connection timeout options...");
    // }

    // fd_set  fdread,fdwrite;
	// int		ret = 0;
	// FD_ZERO( &fdread );
	// FD_ZERO( &fdwrite );
	// FD_SET( myFD, &fdread);
	// FD_SET( myFD, &fdwrite);
    // std::cout << "Time out starts" << std::endl;
    // if (select(myFD, &fdread, &fdwrite, NULL, &timeout) < 0) {
    //     std::perror("Unable to set connection timeout options...");
    // }
    // std::cout << "Time out ends" << std::endl;

    if (setsockopt(myFD, SOL_SOCKET, SO_RCVTIMEO, &timeout, 16) < 0 ||
        setsockopt(myFD, SOL_SOCKET, SO_SNDTIMEO, &timeout, 16) < 0) {
        std::perror("Unable to set recv/send timeout options...");
    }

    memset((char *) &Address, 0, sizeof(Address));
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
