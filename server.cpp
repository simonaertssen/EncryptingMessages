// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include <unistd.h>
#include <ctime>

#include "server.hpp"


Server::Server() : SimpleSocket(){
  // Address.sin_addr.s_addr = INADDR_ANY;
  CHECK(bind(FD, (struct sockaddr*)&Address, AddressLength));
  CHECK(listen(FD, MAX_CONNECTIONS));
  ListenToFD = accept(FD, (struct sockaddr*)&Address, (socklen_t*)&AddressLength);
  CHECK(ListenToFD);

  ReadContinuously();
}

void Server::ReadContinuously(){
  std::cout << "Reading continuously .. " << std::endl;
  std::clock_t start_time = std::clock(), now = std::clock();
  double MAX_TIME = 10.0;
  // std::cout << "start_time = " << start_time << std::endl;
  read(FD, MessageBuffer, BUFFER_SIZE);
  std::cout << "Message received: " << MessageBuffer << std::endl;
  // while(((now - start_time)/(double)CLOCKS_PER_SEC) < MAX_TIME) {
  //   read(ListenToID, MessageBuffer, BUFFER_SIZE);
  //   now = std::clock();
  // }
}

Server::~Server(){
}


int main(int argc, char *argv[]){
  Server* server = new Server();
  delete server;
}
