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
    fflush(stdout);
    
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


void TCPnode::send(int to_client, const char *message) {
    std::cout << myName() << " sending: " << message;
    std::cout << " of size " << strlen(message) << " bytes" << std::endl;

    // Send message size:
    int msg_size = strlen(message), num_bytes_received = sizeof(msg_size);
    if (::send(to_client, &msg_size, num_bytes_received, 0) != num_bytes_received) {
        std::perror("Sending message size failed...");
        exit(-1);
    }

    // Copy message into buffer (piece by piece if too large):
    int total_bytes_sent = 0, send_size = BUFFER_SIZE;
    int num_packets = msg_size / BUFFER_SIZE, num_bytes_remain = msg_size % BUFFER_SIZE;
    for (int packet = 0; packet < num_packets + 1; packet++) {
        if (packet == num_packets) send_size = msg_size % BUFFER_SIZE;  // Leftover bytes

        memset(msg_buffer, 0, BUFFER_SIZE);
        strncpy(msg_buffer, message + packet * BUFFER_SIZE, send_size);
        if (::send(to_client, msg_buffer, send_size, 0) != send_size) {
            std::perror("Sending message failed...");
        }
    }

    // Get a signal from the other side that everything came through:
    int verify;
    num_bytes_received = recv(to_client, &verify, sizeof(verify), 0);
    if (num_bytes_received != sizeof(int) || verify != msg_size) {
        std::perror("Sent wrong number of verification bytes...");
        exit(-1);
    }
}


void TCPnode::send(int to_client, const double message) {
    std::string message_string = std::to_string(message);
    send(to_client, const_cast<char*>(message_string.c_str()));
}


char *TCPnode::receive(int from_client) {
    int msg_size, num_bytes_received, total_bytes_received;

    // Receive message length:
    num_bytes_received = recv(from_client, &msg_size, sizeof(msg_size), 0);
    if (num_bytes_received <= 0) {
        std::cout << "No new message received." << std::endl;
        return NULL;

    } else if (num_bytes_received != sizeof(int)) {
        std::perror("Received wrong number of bytes...");
        exit(-1);
    }

    // Receive the actual message (piece by piece if too large):
    char *message = NULL;
    message = (char *)malloc(msg_size);
    memset(message, 0, msg_size);

    int total_bytes_recv = 0, recv_size = BUFFER_SIZE;
    int num_packets = msg_size / BUFFER_SIZE, num_bytes_remain = msg_size % BUFFER_SIZE;
    for (int packet = 0; packet < num_packets + 1; packet++) {
        if (packet == num_packets) recv_size = msg_size % BUFFER_SIZE;  // Leftover bytes

        memset(msg_buffer, 0, BUFFER_SIZE);
        if (recv(from_client, msg_buffer, recv_size, 0) != recv_size) {
            std::perror("Receiving message failed...");
            exit(-1);
        }

        // Copy into the full receiving buffer:
        strncpy(message + packet * BUFFER_SIZE, msg_buffer, recv_size);
    }

    // Signal reception was good:
    if (::send(from_client, &msg_size, sizeof(msg_size), 0) != sizeof(int)) {
        std::perror("Sending verification failed...");
        exit(-1);
    }

    return message;
}


const char *TCPnode::myName() {
    return typeid(this).name();
}


void TCPnode::shutdownSafely() {
    std::cout << myName() << " shutting down safely" << std::endl;
    shutdown(myFD, SHUT_RDWR);
    close(myFD);
}
