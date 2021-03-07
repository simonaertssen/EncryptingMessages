#include <iostream>
#include "simplesocket.h"


SimpleSocket::SimpleSocket(){
  std::cout << "Creating SimpleSocket..." << std::endl;
  FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(FileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &OptionValue, sizeof(OptionValue));
  Address.sin_family = AF_INET;
  Address.sin_port = htons(PORT);
  AddressLength = sizeof(Address);
}

SimpleSocket::~SimpleSocket(){
  std::cout << "Destroying SimpleSocket..." << std::endl;
}
