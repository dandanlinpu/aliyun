#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
class Tcp_socket{
public:
	Tcp_socket();
	~Tcp_socket();
public:
	int open_listenfd(int port);
	int open_clientfd(const char *addr,int port);
	void set_fd_noblock(int fd);
	void print_sockinfo(struct sockaddr_in *client_addr);
	int acceptor(int listenfd);
private:
	int _socket();
	void _bind(int fd,int port);
	void _listen(int fd);
	int _accept(int listenfd);
	void _connect(int clientfd,const char *addr,int port);
public:
	int listenfd;
};
