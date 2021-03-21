#ifndef TCP_NODE_H // include guard
#define TCP_NODE_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

# define BUFFER_SIZE 16


char *get_host_ip_information();

class TCPnode {
  // A base class for the socket operations, not to be used directly.
    protected:
        int e;
        struct sockaddr_in Address;
        int ADL;
        char *msg_buffer = new char[BUFFER_SIZE];

        double p, q, n, e, tot, d;

        virtual const char *myName();
        void shutdownSafely();

    public:
        TCPnode(char *IP, int PORT);
        ~TCPnode();

        int myFD;
        void send(int to_client, const char *message);
        void send(int to_client, const double message);
        char *receive(int from_client);

};

#endif /* TCP_NODE_H */
