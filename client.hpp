#ifndef CLIENT_H // include guard
#define CLIENT_H

#include "TCPnode.hpp"


class Client : public TCPnode{
  public:
    Client();
    ~Client();
    void connectSafely();
};


#endif /* CLIENT_H */
