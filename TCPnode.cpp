#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

#include "TCPnode.hpp"


int communicate_error(int error_code, const char *file, int line){
  int SUCCESS = 0;
	if (error_code != SUCCESS){
    std::cout << "ERROR: code " << error_code << " in file " << file << ", line " << line << "." << std::endl;
    exit(1);
  }
  return error_code;
}


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
    ADL = (socklen_t *) sizeof(Address);

    // connectSafely();
    // pthread_t startup_thread;
    // e = pthread_create(&startup_thread, NULL, TCPClient::connectSafely, NULL);
}


const char *TCPnode::myName() {
    return typeid(this).name();
}


// void TCPClient::connect_or_bind() {
//     throw std::runtime_error("connect_or_bind is not implemented.");
// }


// void TCPClient::connectSafely() {
//     int connected = 0;
//     try {
//         connect_or_bind();
//         connected = 1;
//         std::cout << name << " is safely connected" << std::endl;
//     } catch (const std::runtime_error& e) {
//       std::cout << e.what() << std::endl;
//     }
//
//     if (connected == 0) {
//         shutdownSafely();
//     }
// }


void TCPnode::shutdownSafely() {
    std::cout << myName() << " shutting down safely" << std::endl;
    releaseDependencies();
    shutdown(myFD, SHUT_RDWR);
    close(myFD);
}

TCPnode::~TCPnode(){
}
