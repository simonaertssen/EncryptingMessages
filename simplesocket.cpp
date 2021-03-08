#include <iostream>  // printing
#include <unistd.h>  // close()

#include "simplesocket.h"


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
