#include "server.h"
#include "rio.h"
Http_server::Http_server(int port){
	_socket.open_listenfd(port);
	_eb.event_init();
	
	_eb.set_readFunction(std::bind(&Http_server::_read,this,std::placeholders::_1));
	_eb.set_writeFunction(std::bind(&Http_server::_write,this,std::placeholders::_1));

}
Http_server::~Http_server(){
}

void Http_server::run(){
	_socket.set_fd_noblock(_socket.listenfd);
	_eb.event_add(_socket.listenfd,EPOLLIN|EPOLLET);
	_eb.event_loop();
}
void Http_server::stop(){
//How?

}
void Http_server::_read(int fd){
	if(fd==_socket.listenfd){
		int connfd=_socket.acceptor(_socket.listenfd);
		printf("connfd:%d \n",connfd);
		_socket.set_fd_noblock(connfd);
		_eb.event_add(connfd,EPOLLIN|EPOLLET);
	}
	else{
		char r_buf[100];
		int n_read=rio_readn(fd,r_buf,100);
		printf("server read %d bytes %s\n",n_read,r_buf);
		_eb.event_mod(fd,EPOLLOUT|EPOLLET);
	}
}
void Http_server::_write(int fd){
	char w_buf[10]="1234!";
	int n_write=rio_writen(fd,w_buf,10);
	printf("server write %d byte %s\n",n_write,w_buf);
	close(fd);

}
int main(){
	Http_server server=Http_server();
	server.run();
}
