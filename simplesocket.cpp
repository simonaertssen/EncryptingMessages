#include <iostream>
#include "simplesocket.h"

SimpleSocket::SimpleSocket(){
  std::cout << "Creating SimpleSocket..." << std::endl;
}

SimpleSocket::SimpleSocket(int socketId){
  std::cout << "Creating SimpleSocket..." << std::endl;
}

SimpleSocket::~SimpleSocket(){
  std::cout << "Destroying SimpleSocket..." << std::endl;
}
