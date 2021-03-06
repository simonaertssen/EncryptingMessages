#ifndef CLIENT_H // include guard
#define CLIENT_H

#include "simplesocket.h"


class Client : public SimpleSocket{
  public:
    Client(int socketId);
    ~Client();
};


#endif /* CLIENT_H */
