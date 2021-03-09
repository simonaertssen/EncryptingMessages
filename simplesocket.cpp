#include <iostream>  // printing
#include <unistd.h>  // close()

#include "simplesocket.hpp"


int communicate_error(int error_code, const char *file, int line){
  int SUCCESS = 0;
	if (error_code != SUCCESS){
    std::cout << "ERROR: code " << error_code << " in file " << file << ", line " << line << "." << std::endl;
    exit(1);
  }
  return error_code;
}


SimpleSocket::SimpleSocket(){
  try {
    if ((FD = socket(AF_INET, SOCK_STREAM, 0)) < 0) throw std::runtime_error("Socket could not be created.");
    CHECK(setsockopt(FD, SOL_SOCKET, SO_REUSEADDR || SO_REUSEPORT, &OptionValue, sizeof(OptionValue)));
    Address.sin_family = AF_INET;
    Address.sin_port = htons(PORT);
    AddressLength = sizeof(Address);
    AddressLength = sizeof(Address);
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}


SimpleSocket::~SimpleSocket(){
  close(FD);
}
