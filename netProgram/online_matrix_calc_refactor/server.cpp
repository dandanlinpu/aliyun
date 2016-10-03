#include "server.h"
#include "rio.h"
#include "http_helper.h"
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
		int connfd;
        	while(  (connfd=_socket.acceptor(_socket.listenfd))>0 ){  
                	printf("connfd: %d\n",connfd);
                	_eb.event_add(connfd,EPOLLIN|EPOLLET);
                	_socket.set_fd_noblock(connfd);
        	}	   
        	if(connfd==-1){
                	if(errno==EAGAIN){
                		printf("has process all SYN request \n");
            		}else{
                		perror("accept error");
                		exit(-1);
            		}   
        	} 
	}
	else{
		char r_buf[8192];
		int n_read=rio_readn(fd,r_buf,sizeof(r_buf));
		printf("server read %d bytes %s\n",n_read,r_buf);
		char delim[]=" ";
		char *token=strtok(r_buf,delim);
        	if(token!=NULL){
	    		token=strtok(NULL,delim);
		}
 		printf("token : %s\n",token);
		if(strcmp(token,"/")==0){
			strcpy(request_file_name,"index.html");
		}else{
			strcpy(request_file_name,"none");
			strcpy(request_url,token);	
		}
		
		_eb.event_mod(fd,EPOLLOUT|EPOLLET);
	}
}
void Http_server::_write(int fd){
        if(strcmp(request_file_name,"none")!=0){
		show_index(fd,request_file_name);
        }else{
        	calc(fd,request_url);
        }
	close(fd);
}


int main(){
	Http_server server=Http_server();
	server.run();
}
