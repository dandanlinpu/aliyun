#include <iostream>
#include "socket.h"
int main(){
	Tcp_socket s=Tcp_socket();	
 	int connfd=s.open_clientfd("127.0.0.1",12000);
}


