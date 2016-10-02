#include <sys/epoll.h>
#include "sock_common.h"
#include "rio.h"
#include "http_server.h"
#include <map>
#include <string>
using namespace std;

void exit_if(int r,const char *info){
     if(r<0){
     	printf(info);
     	printf("%s:%d errno:%d,err msg:%s\n",__FILE__,__LINE__,errno,strerror(errno));
     	exit(-1);
     }
}

char request_url[200];
char request_file_name[20];


void event_add(int epfd,int fd,uint32_t event){
	struct epoll_event ev;
 	ev.data.fd=fd;
	ev.events=event;
	int r=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);
	exit_if(r,"event_add failed!\n");
}
void event_mod(int epfd,int fd,uint32_t event){
	struct epoll_event ev;
	ev.data.fd=fd;
        ev.events=event;
        int r=epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
	exit_if(r,"event_mod failed!\n");
}
void event_del(int epfd,int fd){
        int r=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL); //内核版本在2.9之前不能用NULL参数，有bug
        exit_if(r,"event_del failed!\n");
} 

void accept_handler(int epfd,int listenfd){
	printf("process listenfd %d \n",listenfd);
 	//accept
	struct sockaddr_in clientaddr;
        socklen_t clientlen=sizeof(clientaddr);
        int connfd;
	while(  (connfd=accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen))>0  ){
  		printf("connfd: %d\n",connfd);
		print_sockinfo(&clientaddr);
                event_add(epfd,connfd,EPOLLIN|EPOLLET);
		set_fd_noblock(connfd);
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

void read_handler(int epfd,int fd){
	printf("\nEPOLLIN, fd:%d \n",fd);
	int  bufsize=88192;
        char r_buf[bufsize];
        memset(r_buf,0,bufsize);
        int n_read=rio_readn(fd,r_buf,bufsize); //client在nc上输入ctrl+d 服务器收到FIN
        printf("EPOLLIN read %d bytes data\n",n_read);
	//process_http_request(r_buf,bufsize); 
	//获取get后的uri
	char delim[]=" ";
	char *token=strtok(r_buf,delim);
        if(token!=NULL){
	    token=strtok(NULL,delim);
	}
 	printf("token : %s\n",token);
	if(strcmp(token,"/")==0){
		strcpy(request_file_name,"index.html");
        }else if(strcmp(token,"/bootstrap.min.js")==0){
		strcpy(request_file_name,"bootstrap.min.js");
	}else if(strcmp(token,"/jquery.min.js")==0){
 	    strcpy(request_file_name,"jquery.min.js");
	}else if(strcmp(token,"/bootstrap.min.css")==0){
 	    strcpy(request_file_name,"bootstrap.min.css");
	}else{
 	    strcpy(request_file_name,"none");
  	    strcpy(request_url,token);
        	printf("request_url: %s request_file_name: %s\n",request_url,request_file_name);
	}
        printf("request_file_name: %s\n",request_file_name);
  	//epoll_ctl MOD:when receive data,use this fd to write data.
  	event_mod(epfd,fd,EPOLLOUT|EPOLLET);
}

void write_handler(int epfd,int fd){
	printf("\n EPOLLOUT, fd:%d\n",fd);
        if(strcmp(request_file_name,"none")!=0){
            show_index(fd,request_file_name);
	}else{
	    calc(fd,request_url);
        }
        close(fd);
}

void epoll_process(int listenfd){
  //epoll_create 
  int epfd=epoll_create1(0);
  if(epfd==-1){
     perror("epoll_create error");
     exit(-1);
  }
  //epoll_ctl: ADD listenfd
  event_add(epfd,listenfd,EPOLLIN|EPOLLET);

  //epoll_wait
  while(true){
     int maxevents=100;
     struct epoll_event events[maxevents];
     int n_events=epoll_wait(epfd,events,maxevents,-1);
     for(int i=0;i<n_events;i++){
        if(events[i].data.fd==listenfd){
		accept_handler(epfd,listenfd); 
	}else if(events[i].events & EPOLLIN){
		read_handler(epfd,events[i].data.fd);
	}else if(events[i].events & EPOLLOUT){
                write_handler(epfd,events[i].data.fd);
 	}
   
     }//for 
  }  //while
}
int main(){
  printf("epoll test main..\n");
  
  //socket bind listen
  int  listenfd=open_listenfd(10000);
  set_fd_noblock(listenfd);
  epoll_process(listenfd);
  return 0;
}
