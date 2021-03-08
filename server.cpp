// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include "server.h"
#include <unistd.h>
#include <ctime>


Server::Server() : SimpleSocket(){
  // Address.sin_addr.s_addr = INADDR_ANY;
  try {
    e = bind(FD, (struct sockaddr*)&Address, AddressLength);
    if (e < 0) throw "E binding server...";

    e = listen(FD, MAX_CONNECTIONS);
    if (e < 0) throw "E listening from server...";

    ListenToFD = accept(FD, (struct sockaddr*)&Address, (socklen_t*)&AddressLength);
    if (ListenToFD < 0) throw "ERROR accepting from server...";

  } catch (const char* e) {
    std::cerr << e << std::endl;
  }
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
