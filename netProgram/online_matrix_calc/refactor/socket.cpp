#include "socket.h"
#include "tool.h"
Tcp_socket::Tcp_socket(){
}
Tcp_socket::~Tcp_socket(){
}
int  Tcp_socket::open_listenfd(int port){
	int fd=_socket();
	_bind(fd,port);
	_listen(fd);
	printf("open listenfd %d on port %d\n",fd,port);
	this->listenfd=fd;
	return fd;
}
	
int  Tcp_socket::open_clientfd(const char *addr,int port){
	int fd=_socket();
	_connect(fd,addr,port);
	printf("open clientfd %d\n",fd);
	return fd;
}
void  Tcp_socket::set_fd_noblock(int fd){
	int cflags=fcntl(fd,F_GETFL,0);
	exit_if(cflags,"fcntl filed!\n");   

	cflags=cflags|O_NONBLOCK;
	int r=fcntl(fd,F_SETFL,cflags);
	exit_if(r,"fcntl failed!\n");
}
void  Tcp_socket::print_sockinfo(struct sockaddr_in *client_addr){
	if(client_addr==NULL) return;
	char addrstr[INET_ADDRSTRLEN]; //16
	int port;
	inet_ntop(AF_INET,&(client_addr->sin_addr),addrstr,sizeof(addrstr));
	port=ntohs(client_addr->sin_port);
	printf("remote ip::%s port:%d\n",addrstr,port);
}

int  Tcp_socket::acceptor(int listenfd){
	return  _accept(listenfd);
}
int  Tcp_socket::_socket(){
	int fd=socket(AF_INET,SOCK_STREAM,0);
	exit_if(fd,"socket error!\n");
	return fd;
}
void  Tcp_socket::_bind(int fd,int port){
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);
	int r=bind(fd,(struct sockaddr *) &servaddr,sizeof(servaddr));
	exit_if(r,"bind error\n");
}
void  Tcp_socket::_listen(int fd){
	int r=listen(fd,30);
	exit_if(r,"listen error\n");
}
int  Tcp_socket::_accept(int listenfd){
	struct sockaddr_in clientaddr;
	socklen_t clientlen=sizeof(clientaddr);
	int connfd=accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen);
	print_sockinfo(&clientaddr);
	return connfd;
}
void  Tcp_socket::_connect(int clientfd,const char *addr,int port){
	struct sockaddr_in servaddr;
	//serveraddr  
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	inet_pton(AF_INET,addr,&servaddr.sin_addr);
	servaddr.sin_port=htons(port);
	int r=connect(clientfd,(struct sockaddr *) &servaddr ,sizeof(servaddr));
	exit_if(r,"connect error\n"); 
}

