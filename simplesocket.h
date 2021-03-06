// simplesocket.h
#ifndef SOCKET_H // include guard
#define SOCKET_H

class SimpleSocket {
  private:
    int socketId;
  protected:
    // Designed not to be used directly.
    SimpleSocket(int socketId);
    int getSocketId() const {return socketId;}
  public:
    ~SimpleSocket();
    void close();
};

#endif /* SOCKET_H */
