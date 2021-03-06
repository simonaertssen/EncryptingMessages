#ifndef SOCKET_H // include guard
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE_CONSTANT 1024

class SimpleSocket {
  // A base class for the socket operations, not to be used directly.
  private:

  protected:
    int Id;
    int FileDescriptor;
    int PORT = 8080;
    int OptionValue = 1;
    struct sockaddr_in Address;
    int AddressLength;
    int BUFFER_SIZE = BUFFER_SIZE_CONSTANT;
    char MessageBuffer[BUFFER_SIZE_CONSTANT] = {0};
    SimpleSocket();
  public:
    ~SimpleSocket();
};

#endif /* SOCKET_H */
