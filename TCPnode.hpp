#ifndef TCP_NODE_H // include guard
#define TCP_NODE_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

# define BUFFER_SIZE 128


class TCPnode {
  // A base class for the socket operations, not to be used directly.
    protected:
        int e;
        struct sockaddr_in Address;
        int ADL;

        virtual const char *myName();
        void shutdownSafely();

    public:
        TCPnode(char *IP, int PORT);
        virtual ~TCPnode() = default;

        int myFD;
        void send(char const *message);
        void receive(int from_client);

};

#endif /* TCP_NODE_H */
