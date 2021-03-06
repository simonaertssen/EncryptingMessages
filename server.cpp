#include <iostream>
#include "server.h"

Server::Server(int socketId) : SimpleSocket(0){
  std::cout << "Creating Server..." << std::endl;
}

Server::~Server(){
  std::cout << "Destroying Server..." << std::endl;
}
