#ifndef SOCKET_H // include guard
#define SOCKET_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define BUFFER_SIZE_CONSTANT 1024
#define CHECK(ans) communicate_error((ans), __FILE__, __LINE__)


int communicate_error(int error_code, const char *file, int line);

class SimpleSocket {
  // A base class for the socket operations, not to be used directly.
  private:

  protected:
    int e;
    int FD;
    int PORT = 8080;
    int OptionValue = 1;
    // struct sockaddr_in Address;
    struct sockaddr_in Address;
    int AddressLength;
    SimpleSocket();
  public:
    virtual ~SimpleSocket();
};

#endif /* SOCKET_H */
