// g++ -std=c++11 -o server.o simplesocket.cpp server.cpp && ./server.o
#include <iostream>
#include <cerrno>

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
    // Get some information about the host
    char *IP = get_host_ip_information();
    int PORT = 8080;

    // Make a server and receive some messages:
    Server *server = new Server(IP, PORT);
    char *message = server->receive(server->yoFD);
    std::cout << message << std::endl;

    server->send(server->yoFD, "I_really_like_this_service_because_it_is_soooo_good");

    // double prime = atof(message);
    // std::cout << "MSG (" << strlen(message) << "): ";
    // std::cout << prime << std::endl;

    // free(message);
    delete server;
    return 0;
}
