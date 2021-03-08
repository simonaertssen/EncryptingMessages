#include <iostream>  // printing
#include <unistd.h>  // close()

#include "simplesocket.h"


SimpleSocket::SimpleSocket(){
  try {
    FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (FileDescriptor < 0) throw "ERROR opening socket...";

    if (setsockopt(FileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &OptionValue, sizeof(OptionValue)) < 0) throw "ERROR setting socket options...";

  } catch (const char* e) {
    std::cerr << e << std::endl;
  }
  Address.sin_family = AF_INET;
  Address.sin_port = htons(PORT);
  AddressLength = sizeof(Address);
}

SimpleSocket::~SimpleSocket(){
  close(FileDescriptor);
}
