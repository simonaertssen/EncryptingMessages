// g++ -std=c++11 -o client.o simplesocket.cpp client.cpp && ./client.o
#include <iostream>
#include "client.h"
#include <arpa/inet.h>


Client::Client() : SimpleSocket(){
  std::cout << "Creating Client..." << std::endl;
  // inet_pton(AF_UNIX, "127.0.0.1", &Address.sin_addr);
  connect(FD, (struct sockaddr*)&Address, AddressLength);
  std::cout << "Made connection..." << std::endl;
  char const *message = "Hello from client";
  send(FD, message, strlen(message), 0);
  message = "This is a good message service...";
  send(FD, message, strlen(message), 0);
  std::cout << "Message sent..." << std::endl;
}

Client::~Client(){
  std::cout << "Destroying Client..." << std::endl;
}

int main(int argc, char *argv[]){
  Client* client = new Client();
  delete client;
}
