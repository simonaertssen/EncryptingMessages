#ifndef TCP_CLIENT_H // include guard
#define TCP_CLIENT_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define BUFFER_SIZE_CONSTANT 1024
#define CHECK(ans) communicate_error((ans), __FILE__, __LINE__)


int communicate_error(int error_code, const char *file, int line);

class TCPClient {
  // A base class for the socket operations, not to be used directly.
  private:

  protected:
    int e;
    int FD;
    struct sockaddr_in Address;
    int AddressLength;

    TCPClient(char *IP, int PORT);
    void connect_or_bind();
    void *connectSafely();
    void releaseDependencies();

  public:
    virtual ~TCPClient();
};

#endif /* TCP_CLIENT_H */
