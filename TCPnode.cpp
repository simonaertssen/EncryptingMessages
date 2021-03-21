#include <iostream>
#include <unistd.h>
#include <ctime>

#include "TCPnode.hpp"


TCPnode::TCPnode(char *IP, int PORT) {
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


void TCPnode::send(char const *message) {
    std::cout << myName() << " sending " << message;
    std::cout << " of size " << strlen(message) << " bytes" << std::endl;

    int msg_size = strlen(message);
    if (::send(myFD, &msg_size, sizeof(msg_size), 0) < 0) {
        std::perror("Sending message size failed...");
        exit(-1);
    }

    // Copy message into buffer:
    // if
    // memcpy ( person.name, myname, strlen(myname)+1 );
    if (::send(myFD, message, strlen(message), 0) < 0) {
        std::perror("Sending message failed...");
    }
}


void TCPnode::receive(int from_client) {
    int msg_size, num_bytes_received, total_bytes_received;
    char msg_buffer[BUFFER_SIZE];
    std::clock_t start_time = std::clock(), now = std::clock();
    double elapsed_time, MAX_TIME = 5.0;

    // Receive message length:
    num_bytes_received = recv(from_client, &msg_size, sizeof(msg_size), 0);
    if (num_bytes_received < 0) {
        std::perror("Receiving message size failed...");
        exit(-1);

    } else if (num_bytes_received != sizeof(int)) {
        std::perror("Received wrong number of bytes...");
        // exit(-1);
    }
    std::cout << "Received " << num_bytes_received << " bytes";
    std::cout << ", message is " << msg_size << " bytes" <<std::endl;
    std::cout << "Message start ---- " << std::endl;
    memset(msg_buffer, 0, BUFFER_SIZE);
    num_bytes_received = recv(from_client, msg_buffer, BUFFER_SIZE, 0);
    if (num_bytes_received < 0) {
        std::perror("Receiving message failed...");
        exit(-1);
    } else if (num_bytes_received != msg_size) {
        // std::perror("Received wrong number of bytes in message...");
        // exit(-1);
        std::cout << "Received wrong number of bytes in message..." << std::endl;
    }
    std::cout << msg_buffer << std::endl;
    std::cout << "Message end ----" << std::endl;

    // while(1) {
    //     // Register timeout
    //     // now = std::clock();
    //     // elapsed_time = (now - start_time)/(double)CLOCKS_PER_SEC;
    //     // if (total_bytes_received == 0 && elapsed_time > MAX_TIME) {
    //     //     std::perror("Reception timeout error...");
    //     //     break;
    //     // }
    //     // Receive the message
    //     memset(msg_buffer, 0, BUFFER_SIZE);
    //     num_bytes_received = recv(from_client, msg_buffer, BUFFER_SIZE, 0);
    //     if (num_bytes_received < 0) {
    //         std::cout << "received " << num_bytes_received  << " bytes" << std::endl;
    //         break;
    //     } else {
    //         std::cout << "received " << num_bytes_received  << " bytes" << std::endl;
    //         total_bytes_received += num_bytes_received;
    //         std::cout << msg_buffer;
    //     }
    // }

    // memset(msgBuffer, 0, BUFFER_SIZE);
    // num_bytes_received = recv(from_client, msgBuffer, BUFFER_SIZE, 0);
    // std::cout << msgBuffer << std::endl;

    // std::cout << "Message end ----" << std::endl;
}


const char *TCPnode::myName() {
    return typeid(this).name();
}


void TCPnode::shutdownSafely() {
    std::cout << myName() << " shutting down safely" << std::endl;
    shutdown(myFD, SHUT_RDWR);
    close(myFD);
}
