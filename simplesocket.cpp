#include <iostream>  // printing
#include <unistd.h>  // close()

#include "simplesocket.h"


int communicate_error(int error_code, const char *file, int line){
  int SUCCESS = 0;
	if (error_code != SUCCESS){
    std::cout << "ERROR: code " << error_code << " in file " << file << ", line " << line << "." << std::endl;
    exit(1);
  }
  return error_code;
}


SimpleSocket::SimpleSocket(){
  FD = socket(AF_UNIX, SOCK_STREAM, 0);
  CHECK(FD < 0);
  CHECK(setsockopt(FD, SOL_SOCKET, SO_REUSEADDR || SO_REUSEPORT, &OptionValue, sizeof(OptionValue)));

  // Address.sin_family = AF_UNIX;
  // Address.sin_port = htons(PORT);
  // AddressLength = sizeof(Address);
  Address.sun_family = AF_UNIX;
  strncpy(Address.sun_path, "socket", sizeof(Address.sun_path)-1);
  AddressLength = sizeof(Address);
}


SimpleSocket::~SimpleSocket(){
  close(FD);
}
