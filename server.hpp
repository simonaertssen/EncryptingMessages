#ifndef SERVER_H // include guard
#define SERVER_H

#include "TCPnode.hpp"


class Server : public TCPnode{
  private:
    int MAX_CONNECTIONS = 3;
    int BUFFER_SIZE = 1024;
    char MessageBuffer[BUFFER_SIZE] = {0};
  public:
    Server();
    void connectSafely();
    void readContinuously();
    ~Server();
};


#endif /* SERVER_H */
