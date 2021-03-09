#ifndef SERVER_H // include guard
#define SERVER_H

#include "simplesocket.h"


class Server : public SimpleSocket{
  private:
    int MAX_CONNECTIONS = 3;
    int ListenToFD;
  public:
    Server();
    void ReadContinuously();
    ~Server();
};


#endif /* SERVER_H */
