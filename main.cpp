// g++ -std=c++11 -o main.o main.cpp simplesocket.cpp server.cpp client.cpp && ./main.o
#include <iostream>
#include "server.h"
#include "client.h"

int main(int argc, char *argv[]){
  std::cout << "Creating objects..." << std::endl;
  Server* server = new Server();
  Client* client = new Client();

  std::cout << "Deleting objects..." << std::endl;
  delete server;
  delete client;
}
