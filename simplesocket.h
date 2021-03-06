#ifndef SOCKET_H // include guard
#define SOCKET_H

class SimpleSocket {
  // A base class for the socket operations, not to be used directly.
  private:
    int socketId;
  protected:
    SimpleSocket(int socketId);
    int getSocketId() const {return socketId;}
  public:
    ~SimpleSocket();
    void close();
};

#endif /* SOCKET_H */
