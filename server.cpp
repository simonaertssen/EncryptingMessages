// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include <unistd.h>
#include <time.h>

#include "server.hpp"


Server::Server(char *IP, int PORT) : TCPClient(char *IP, int PORT){
  Address.sin_addr.s_addr = INADDR_ANY;
  connectSafely()
  readContinuously();
}

void TCPClient::connectSafely() {
    int connected = 0;
    try {
        CHECK(bind(FD, (struct sockaddr*)&Address, AddressLength));
        CHECK(listen(FD, MAX_CONNECTIONS));
        try {
          if ((ListenToFD = accept(FD, (struct sockaddr*)&Address, (socklen_t*)&AddressLength)) < 0)
            throw std::runtime_error("Connection was not accepted.");
        } catch (const std::runtime_error& e) {
          std::cout << e.what() << std::endl;
        }
        connected = 1;
        std::cout << name << " is safely connected" << std::endl;
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }

    if (connected == 0) {
        shutdownSafely();
    }
}

void Server::readContinuously(){
  int bytes_read;
  try {
      while ((bytes_read = read(ListenToFD, MessageBuffer, BUFFER_SIZE)) > 0) {
      MessageBuffer[bytes_read] = '\0';
      std::cout << "Message received: " << MessageBuffer << std::endl;
      MessageBuffer[0] = '\0';
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}

Server::~Server(){
}


int main(int argc, char *argv[]){
  Server* server = new Server();
  delete server;
}
