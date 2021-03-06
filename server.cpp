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
  bind(FileDescriptor, (struct sockaddr*)&Address, AddressLength);
  // listen(FileDescriptor, MAX_CONNECTIONS);
  // ListenToID = accept(FileDescriptor, (struct sockaddr*)&Address, (socklen_t*)&AddressLength);
  ReadContinuously();
}

void Server::ReadContinuously(){
  std::cout << "Reading continuously .. " << std::endl;
  int MAX_TIME = 5;
  std::time_t start_time = std::time(nullptr), now = start_time;
  std::cout << "start_time = " << start_time << std::endl;

  while(now - start_time < MAX_TIME) {
    // read(ListenToID, MessageBuffer, BUFFER_SIZE);
    std::cout << "now = " << now << std::endl;
    now = std::time(nullptr);
  }
}

Server::~Server(){
  std::cout << "Destroying Server..." << std::endl;
}
