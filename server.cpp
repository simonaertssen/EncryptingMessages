#include <iostream>
#include "server.h"
#include <unistd.h>
#include <ctime>

Server::Server() : SimpleSocket(){
  std::cout << "Creating Server..." << std::endl;
  Address.sin_family = AF_INET;
  Address.sin_addr.s_addr = INADDR_ANY;
  Address.sin_port = htons(PORT);
  AddressLength = sizeof(Address);
  // bind(FileDescriptor, (struct sockaddr*)&Address, AddressLength);
  // listen(FileDescriptor, MAX_CONNECTIONS);
  // ListenToID = accept(FileDescriptor, (struct sockaddr*)&Address, (socklen_t*)&AddressLength);
  ReadContinuously();
}

void Server::ReadContinuously(){
  std::cout << "Reading continuously .. " << std::endl;
  std::clock_t start_time = std::clock(), now = std::clock();
  double MAX_TIME = 0.01;
  std::cout << "start_time = " << start_time << std::endl;
  while(((now - start_time)/(double)CLOCKS_PER_SEC) < MAX_TIME) {
    // read(ListenToID, MessageBuffer, BUFFER_SIZE);
    std::cout << "diff = " << ((now - start_time)/(double)CLOCKS_PER_SEC) << std::endl;
    now = std::clock();
    // Wait
  }
}

Server::~Server(){
  std::cout << "Destroying Server..." << std::endl;
}
