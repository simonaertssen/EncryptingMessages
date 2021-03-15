#ifndef SERVER_H // include guard
#define SERVER_H

#include "TCPnode.hpp"

# define BUFFER_SIZE_CONSTANT 1024


class Server : public TCPnode{
  private:
    int MAX_CONNECTIONS = 3;
    int BUFFER_SIZE = BUFFER_SIZE_CONSTANT;
    char MessageBuffer[BUFFER_SIZE_CONSTANT] = {0};

  public:
    Server(char *IP, int PORT);
    ~Server();
    const char *myName();
    void connectSafely();
    void readContinuously();
};


#endif /* SERVER_H */
