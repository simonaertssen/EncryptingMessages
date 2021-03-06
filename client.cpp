#include <iostream>
#include "client.h"

Client::Client(int socketId) : SimpleSocket(0){
  std::cout << "Creating Client..." << std::endl;
}

Client::~Client(){
  std::cout << "Destroying Client..." << std::endl;
}
