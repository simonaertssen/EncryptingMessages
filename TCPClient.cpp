#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>

#include "TCPClient.hpp"


int communicate_error(int error_code, const char *file, int line){
  int SUCCESS = 0;
	if (error_code != SUCCESS){
    std::cout << "ERROR: code " << error_code << " in file " << file << ", line " << line << "." << std::endl;
    exit(1);
  }
  return error_code;
}


TCPClient::TCPClient(char *IP, int PORT) {
    if ((FD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::perror("Unable to create socket...");
        exit(-1);
    }

    const int opt = 1;
    e = setsockopt(FD, SOL_SOCKET, SO_REUSEADDR || SO_REUSEPORT, &opt, 4))
    if (e < 0) {
        std::perror("Unable to set socket options...");
        exit(-1);
    }

    Address.sin_family = AF_INET;
    Address.sin_port = htons(PORT);
    AddressLength = sizeof(Address);

    pthread_t startup_thread;
    e = pthread_create(&startup_thread, NULL, connectSafely, NULL);
}

void* TCPClient::connectSafely() {
}


TCPClient::~TCPClient(){
    releaseDependencies();
    shutdown(FD, SHUT_RDWR);
    close(FD);
}
