#ifndef TCP_NODE_H // include guard
#define TCP_NODE_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define BUFFER_SIZE_CONSTANT 1024
#define CHECK(ans) communicate_error((ans), __FILE__, __LINE__)


int communicate_error(int error_code, const char *file, int line);

class TCPnode {
  // A base class for the socket operations, not to be used directly.
    private:

    protected:
        int e;
        int FD;
        struct sockaddr_in Address;
        int AddressLength;

    public:
        TCPnode(char *IP, int PORT);
        char *myName();
        // void connectSafely();
        // virtual void connect_or_bind();
        virtual void releaseDependencies();
        void shutdownSafely();


      virtual ~TCPnode();
};

#endif /* TCP_NODE_H */