#ifndef SERVER_H // include guard
#define SERVER_H

#include "simplesocket.hpp"


class Server : public SimpleSocket{
  private:
    int MAX_CONNECTIONS = 3;
    int ListenToFD;
    int BUFFER_SIZE = BUFFER_SIZE_CONSTANT;
    char MessageBuffer[BUFFER_SIZE_CONSTANT] = {0};
  public:
    Server();
    void ReadContinuously();
    ~Server();
};


#endif /* SERVER_H */
