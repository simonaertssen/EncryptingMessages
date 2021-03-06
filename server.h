#ifndef SERVER_H // include guard
#define SERVER_H

#include "simplesocket.h"


class Server : public SimpleSocket{
  private:

  public:
    Server(int socketId);
    ~Server();
};


#endif /* SERVER_H */
