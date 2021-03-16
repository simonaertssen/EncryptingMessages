#ifndef SERVER_H // include guard
#define SERVER_H

#include "TCPnode.hpp"


class Server : public TCPnode {
private:
    int MAX_CONNECTIONS = 3;

public:
    Server(char *IP, int PORT);
    ~Server();

    int yoFD;
    const char *myName();
};


#endif /* SERVER_H */
