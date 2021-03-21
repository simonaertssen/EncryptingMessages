#ifndef CLIENT_H // include guard
#define CLIENT_H

#include "TCPnode.hpp"


class Client : public TCPnode {
private:
    double private_key = 13;

public:
    Client(char *IP, int PORT);
    ~Client();

    double public_key = 11;
    const char *myName();
};


#endif /* CLIENT_H */
