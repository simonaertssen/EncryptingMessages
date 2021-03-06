#ifndef SOCKET_H // include guard
#define SOCKET_H

class SimpleSocket {
  // A base class for the socket operations, not to be used directly.
  private:
    int socketId;
  protected:
    SimpleSocket();
    SimpleSocket(int socketId);
  public:
    ~SimpleSocket();
};

#endif /* SOCKET_H */
