#ifndef SOCKET_H // include guard
#define SOCKET_H

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define BUFFER_SIZE_CONSTANT 1024
#define CHECK(ans) communicate_error((ans), __FILE__, __LINE__)

int communicate_error(int error_code, const char *file, int line){
  int SUCCESS = 0;
	if (error_code != SUCCESS){
    message = f'{type_exc}({text}) in {func_name}(), file {file_name}, line {line_no}.'
    throw std::system_error(errcode, std::generic_category(), msg);

		fprintf(stderr, "GPUassert: error in file %s, line %d\n", file, line);
  	fprintf(stderr,"code %d with reason %s\n", code, cudaGetErrorString(code));
    exit(1);
  }
  return code;
}

class SimpleSocket {
  // A base class for the socket operations, not to be used directly.
  private:

  protected:
    int e;
    int FD;
    int PORT = 8080;
    int OptionValue = 1;
    // struct sockaddr_in Address;
    struct sockaddr_un Address;
    int AddressLength;
    int BUFFER_SIZE = BUFFER_SIZE_CONSTANT;
    char MessageBuffer[BUFFER_SIZE_CONSTANT] = {0};
    SimpleSocket();
  public:
    void err(const std::string msg, int errcode);
    virtual ~SimpleSocket();
};

#endif /* SOCKET_H */
