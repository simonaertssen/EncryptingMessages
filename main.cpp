// g++ -std=c++11 -o main.o main.cpp simplesocket.cpp server.cpp client.cpp && ./main.o
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


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
    std::cout << HOST << " is hosting this script on " << IP << std::endl;

    // Make a client and a server

    

    return 0;
}
