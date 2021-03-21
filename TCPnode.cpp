#include <iostream>
#include <unistd.h>
#include <ctime>

#include <arpa/inet.h>
#include <netdb.h>

#include "TCPnode.hpp"


char *get_host_ip_information() {
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
    std::cout << HOST << " is hosting this script on " << IP << std::endl;
    return IP;
}


TCPnode::TCPnode(char *IP, int PORT) {
    // Construct the socket object
    if ((myFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::perror("Unable to create socket...");
        exit(-1);
    }

    // Set socket to reuse addresses:
    const int opt = 1;  // has size of 4 bytes
    if (setsockopt(myFD, SOL_SOCKET, SO_REUSEADDR, &opt, 4) < 0) {
        std::perror("Unable to set socket options...");
        exit(-1);
    }

    // Set reception and sending timeout
    struct timeval timeout;  // has size of 16 bytes
    timeout.tv_sec  = 1;
    timeout.tv_usec = 10;
    if (setsockopt(myFD, SOL_SOCKET, SO_RCVTIMEO, &timeout, 16) < 0 ||
        setsockopt(myFD, SOL_SOCKET, SO_SNDTIMEO, &timeout, 16) < 0) {
        std::perror("Unable to set recv/send timeout options...");
    }

    memset((char *) &Address, 0, sizeof(Address));
    Address.sin_family = AF_INET;
    Address.sin_port = htons(PORT);
    ADL = sizeof(Address);
}


TCPnode::~TCPnode() {
    delete[] msg_buffer;
}

void TCPnode::send(char const *message) {
    std::cout << myName() << " sending " << message;
    std::cout << " of size " << strlen(message) << " bytes" << std::endl;

    // Send message size:
    int msg_size = strlen(message);
    if (::send(myFD, &msg_size, sizeof(msg_size), 0) < 0) {
        std::perror("Sending message size failed...");
        exit(-1);
    }

    // Copy message into buffer:
    // memset(msg_buffer, 0, BUFFER_SIZE);
    strncpy(msg_buffer, message, msg_size);
    if (::send(myFD, msg_buffer, msg_size, 0) < 0) {
        std::perror("Sending message failed...");
    }
}


void TCPnode::receive(int from_client) {
    int msg_size, num_bytes_received, total_bytes_received;

    // Receive message length:
    num_bytes_received = recv(from_client, &msg_size, sizeof(msg_size), 0);
    std::cout << "Message contains " << msg_size << " bytes" << std::endl;
    if (num_bytes_received < 0) {
        std::perror("Receiving message size failed...");
        exit(-1);

    } else if (num_bytes_received != sizeof(int)) {
        std::perror("Received wrong number of bytes...");
        exit(-1);
    }

    // Receive the actual message:
    std::cout << "Message start ---- " << std::endl;
    memset(msg_buffer, 0, BUFFER_SIZE);
    // strcat(msg_buffer, "\n");
    num_bytes_received = recv(from_client, msg_buffer, msg_size, 0);
    if (num_bytes_received < 0) {
        std::perror("Receiving message failed...");
        exit(-1);
    } else if (num_bytes_received != msg_size) {
        std::perror("Received wrong number of bytes in message...");
        exit(-1);
    }
    std::cout << msg_buffer << std::endl;
    std::cout << "Message end ----" << std::endl;
}


const char *TCPnode::myName() {
    return typeid(this).name();
}


void TCPnode::shutdownSafely() {
    std::cout << myName() << " shutting down safely" << std::endl;
    shutdown(myFD, SHUT_RDWR);
    close(myFD);
}
