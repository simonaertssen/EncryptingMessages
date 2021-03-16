// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "server.hpp"


Server::Server(char *IP, int PORT) : TCPnode(IP, PORT){
  Address.sin_addr.s_addr = INADDR_ANY;

  int connected = 0;
  try {
      if (bind(myFD, (struct sockaddr*)&Address, ADL) != 0) {
          throw std::runtime_error("Unable to bind socket...");
      }

      if (listen(myFD, MAX_CONNECTIONS) != 0) {
          throw std::runtime_error("Unable to listen...");
      }

      yoFD = accept(myFD, (struct sockaddr*)&Address, (socklen_t *)&ADL);
      if (yoFD < 0) {
          if (errno == ETIMEDOUT || errno == EAGAIN || errno == EWOULDBLOCK) {
              throw std::runtime_error("Connection timed out...");
          } else {
              throw std::runtime_error("Connection was not accepted...");
          }
      }

      connected = 1;
      std::cout << myName() << " is safely connected" << std::endl;
  } catch (const std::runtime_error& e) {
      std::cout << myName() << ": error code " << errno << ". ";
      std::cout << e.what() << std::endl;
      exit(errno);
  }

  if (connected == 0) {
      shutdownSafely();
  }
}


Server::~Server(){
}


const char *Server::myName() {
    return typeid(this).name();
}


int main(int argc, char *argv[]){
    // Get host name, set ip and port
    char HOST[256];
    if (gethostname(HOST, sizeof(HOST)) != 0) {
        std::perror("Hostname was not found...");
        exit(-1);
    }
    struct hostent *HOST_INFO = gethostbyname(HOST);
    if (HOST_INFO == NULL || HOST_INFO->h_length == 0) {
        std::perror("Host information was not found or is incorrect...");
        exit(-1);
    }
    struct in_addr **addr_list = (struct in_addr **)HOST_INFO->h_addr_list;
    char *IP = inet_ntoa(*addr_list[0]);
    int PORT = 8080;
    std::cout << HOST << " is hosting this script on " << IP << std::endl;

    // Make a client and a server
    Server *test = new Server(IP, PORT);
    test->receive(test->yoFD);
    delete test;

    return 0;
}
