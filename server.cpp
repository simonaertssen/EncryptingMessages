// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <cerrno>

#include "server.hpp"


Server::Server(char *IP, int PORT) : TCPnode(IP, PORT){
  Address.sin_addr.s_addr = INADDR_ANY;
  connectSafely();
}


Server::~Server(){
}


void Server::connectSafely() {
    int connected = 0;
    try {
        if (bind(myFD, (struct sockaddr*)&Address, ADL) != 0) {
            throw std::runtime_error("Unable to bind socket...");
        }

        if (listen(myFD, MAX_CONNECTIONS) != 0) {
            throw std::runtime_error("Unable to listen...");
        }

        yoFD = accept(myFD, (struct sockaddr*)&Address, (socklen_t *)&ADL);
        if (yoFD < 0) {
            if (errno == ETIMEDOUT || errno == EAGAIN || errno == EWOULDBLOCK) {
                throw std::runtime_error("Connection timed out...");
            } else {
                throw std::runtime_error("Connection was not accepted...");
            }
        }

        connected = 1;
        std::cout << myName() << " is safely connected" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << myName() << ": error code " << errno << ". ";
        std::cout << e.what() << std::endl;
        exit(errno);
    }

    if (connected == 0) {
        shutdownSafely();
    }
}


const char *Server::myName() {
    return typeid(this).name();
}


void Server::readContinuously(){
    while (recv(yoFD, MessageBuffer, BUFFER_SIZE, 0) > 0) {
        // MessageBuffer[bytes_read] = '\0';
        std::cout << "Message received: " << MessageBuffer << std::endl;
        // MessageBuffer[0] = '\0';
    }
}
