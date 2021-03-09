#ifndef CLIENT_H // include guard
#define CLIENT_H

#include "simplesocket.h"


class Client : public SimpleSocket{
  public:
    Client();
    ~Client();
};


#endif /* CLIENT_H */
