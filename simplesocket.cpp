#include <iostream>
#include "simplesocket.h"

SimpleSocket::SimpleSocket(){
  std::cout << "Creating SimpleSocket..." << std::endl;
  FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(FileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &OptionValue, sizeof(OptionValue));
}

SimpleSocket::~SimpleSocket(){
  std::cout << "Destroying SimpleSocket..." << std::endl;
}
