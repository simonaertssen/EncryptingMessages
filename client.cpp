// g++ -std=c++11 -o client.o simplesocket.cpp client.cpp && ./client.o
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

#include "client.hpp"


Client::Client() : SimpleSocket(){
  try {
    if (inet_pton(AF_INET, "127.0.0.1", &Address.sin_addr) < 0)
      throw std::runtime_error("Address is not supported.");
    CHECK(connect(FD, (struct sockaddr*)&Address, AddressLength));

    char const *message = "Hello from client";
    send(FD, message, strlen(message), 0);
    sleep(5);
    message = "This is a good message service...";
    send(FD, message, strlen(message), 0);
    std::cout << "Message sent..." << std::endl;
    sleep(5);

  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}

Client::~Client(){
}


int main(int argc, char *argv[]){
  Client* client = new Client();
  delete client;
}
