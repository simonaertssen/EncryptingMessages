#include <iostream>
#include "client.h"

Client::Client() : SimpleSocket(){
  std::cout << "Creating Client..." << std::endl;
}

Client::~Client(){
  std::cout << "Destroying Client..." << std::endl;
}

int main(int argc, char *argv[]){
  Client* client = new Client();
  delete client;
}
