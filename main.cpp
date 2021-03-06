#include <iostream>
#include "server.h"
#include "client.h"

#define PORT 8080

int main(int argc, char *argv[]){
  std::cout << "Creating objects..." << std::endl;
  Server* server = new Server(1);
  Client* client = new Client(2);

  std::cout << "Deleting objects..." << std::endl;
  delete server;
  delete client;
}
