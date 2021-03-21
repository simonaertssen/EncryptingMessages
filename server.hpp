#ifndef SERVER_H // include guard
#define SERVER_H

#include "TCPnode.hpp"


class Server : public TCPnode {
private:
    double private_key = 17;
    int MAX_CONNECTIONS = 3;

public:
    Server(char *IP, int PORT);
    ~Server();

    int yoFD;
    double public_key = 19;
    const char *myName();
};

#endif /* SERVER_H */
