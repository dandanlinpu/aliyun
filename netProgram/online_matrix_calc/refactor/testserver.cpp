#include <iostream>
#include "socket.h"
int main(){
	Tcp_socket s=Tcp_socket();	
 	int listen=s.open_listenfd(12000);
	int connfd=s.acceptor(s.listenfd);
}


