// g++ -std=c++11 -o client.o TCPnode.cpp client.cpp && ./client.o
#include <iostream>
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
    // Get some information about the host
    char *IP = get_host_ip_information();
    int PORT = 8080;

    // Make a client and send some messages
    Client* client = new Client(IP, PORT);

    // client->send("Hello from client script");
    // client->send("This is a good message service");
    // client->send("I_really_like_this_service_because_it_is_soooo_good");

    // double prime = 1012;
    // client->send(prime);

    // Send an encrypted message to the server:
    // Send a request to communicate:
    client->send(client->myFD, "Request encryption");

    // Get the server's public key:
    // char *message = client->receive(server->yoFD);
    //
    // double prime = atof(message);

    char *message = client->receive(client->myFD);
    std::cout << "MSG (" << strlen(message) << "): ";
    std::cout << message << std::endl;

    delete client;
    return 0;
}
