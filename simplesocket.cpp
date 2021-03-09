#include <iostream>  // printing
#include <unistd.h>  // close()

#include "simplesocket.h"


int communicate_error(int error_code, const char *file, int line){
  int SUCCESS = 0;
	if (error_code != SUCCESS){
    std::cout << "E: code " << error_code << " in file " << file << ", line " << line << std::endl;
    exit(1);
  }
  return error_code;
}


SimpleSocket::SimpleSocket(){
  try {
    FD = socket(AF_UNIX, SOCK_STREAM, 0);
    if (FD < 0) err("Cannot construct socket", FD);

    e = setsockopt(FD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &OptionValue, sizeof(OptionValue));
    if (e < 0) err("Cannot set socket options", e);
  } catch(const std::system_error& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  }

  // Address.sin_family = AF_UNIX;
  // Address.sin_port = htons(PORT);
  // AddressLength = sizeof(Address);
  Address.sun_family = AF_UNIX;
  strncpy(Address.sun_path, "socket", sizeof(Address.sun_path)-1);
  AddressLength = sizeof(Address);
}


void SimpleSocket::err(const std::string msg, int errcode) {
  throw std::system_error(errcode, std::generic_category(), msg);
}


SimpleSocket::~SimpleSocket(){
  close(FD);
}
