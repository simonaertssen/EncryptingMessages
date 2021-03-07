// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include "server.h"
#include <unistd.h>
#include <ctime>


Server::Server() : SimpleSocket(){
  std::cout << "Creating Server..." << std::endl;
  Address.sin_addr.s_addr = INADDR_ANY;
  bind(FileDescriptor, (struct sockaddr*)&Address, AddressLength);
  listen(FileDescriptor, MAX_CONNECTIONS);
  ListenToID = accept(FileDescriptor, (struct sockaddr*)&Address, (socklen_t*)&AddressLength);
  std::cout << "Connection accepted..." << std::endl;

  ReadContinuously();
}

void Server::ReadContinuously(){
  std::cout << "Reading continuously .. " << std::endl;
  std::clock_t start_time = std::clock(), now = std::clock();
  double MAX_TIME = 10.0;
  // std::cout << "start_time = " << start_time << std::endl;
  read(ListenToID, MessageBuffer, BUFFER_SIZE);
  std::cout << "Message received: " << MessageBuffer << std::endl;
  // while(((now - start_time)/(double)CLOCKS_PER_SEC) < MAX_TIME) {
  //   read(ListenToID, MessageBuffer, BUFFER_SIZE);
  //   now = std::clock();
  // }
}

Server::~Server(){
  std::cout << "Destroying Server..." << std::endl;
}


int main(int argc, char *argv[]){
  Server* server = new Server();
  delete server;
}
