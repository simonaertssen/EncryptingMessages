#include <iostream>
#include "server.h"
#include "client.h"

#define PORT 8080

int main(int argc, char *argv[]){
  std::cout << "Creating objects..." << std::endl;
  Server* server = new Server();
  Client* client = new Client();

  std::cout << "Deleting objects..." << std::endl;
  delete server;
  delete client;
}
