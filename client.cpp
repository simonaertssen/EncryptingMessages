// g++ -std=c++11 -o client.o TCPnode.cpp client.cpp && ./client.o
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "client.hpp"


Client::Client(char *IP, int PORT) : TCPnode(IP, PORT){
    int connected = 0;
      try {
        if (inet_pton(AF_INET, IP, &Address.sin_addr) < 0) {
            throw std::runtime_error("Address is not supported...");
        }

        if (connect(myFD, (struct sockaddr*)&Address, ADL) < 0) {
            throw std::runtime_error("Connection failed...");
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


Client::~Client(){
}


const char *Client::myName() {
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
    Client* client = new Client(IP, PORT);
    delete client;

    return 0;
}
