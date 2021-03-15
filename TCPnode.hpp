#ifndef TCP_NODE_H // include guard
#define TCP_NODE_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>


class TCPnode {
  // A base class for the socket operations, not to be used directly.
    private:

    protected:
        int e;
        int myFD;
        int yoFD;
        struct sockaddr_in Address;
        int ADL;

        virtual const char *myName();
        void shutdownSafely();

    public:
        TCPnode(char *IP, int PORT);
        ~TCPnode();
};

#endif /* TCP_NODE_H */
