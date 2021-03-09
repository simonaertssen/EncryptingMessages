// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include <unistd.h>
#include <time.h>

#include "server.hpp"


Server::Server() : SimpleSocket(){
  Address.sin_addr.s_addr = INADDR_ANY;
  CHECK(bind(FD, (struct sockaddr*)&Address, AddressLength));
  CHECK(listen(FD, MAX_CONNECTIONS));
  try {
    if ((ListenToFD = accept(FD, (struct sockaddr*)&Address, (socklen_t*)&AddressLength)) < 0)
      throw std::runtime_error("Connection was not accepted.");
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
  ReadContinuously();
}

void Server::ReadContinuously(){
  clock_t start_time = clock(), now = clock();
  double MAX_TIME = 10.0;
  int bytes_read;
  try {
    // while(((now - start_time)/(double)CLOCKS_PER_SEC) < MAX_TIME) {
    while((bytes_read = read(ListenToFD, MessageBuffer, BUFFER_SIZE)) > 0) {
      now = clock();
      MessageBuffer[bytes_read] = '\0';
      std::cout << (now - start_time)/(double)CLOCKS_PER_SEC << " Message received: " << MessageBuffer << std::endl;
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
