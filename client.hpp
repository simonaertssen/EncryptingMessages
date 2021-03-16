#ifndef CLIENT_H // include guard
#define CLIENT_H

#include "TCPnode.hpp"


class Client : public TCPnode {
public:
    Client(char *IP, int PORT);
    ~Client();

    const char *myName();
};


#endif /* CLIENT_H */
