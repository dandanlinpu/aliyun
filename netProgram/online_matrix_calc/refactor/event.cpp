#include "event.h"
#include "tool.h"
Event_base::Event_base(){
}
Event_base::~Event_base(){
}
void Event_base::event_init(){
	epfd=epoll_create1(0);
}
void Event_base::event_add(int fd,uint32_t event){	
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=event;
	int r=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);
	exit_if(r,"event_add failed!\n");
}
void Event_base::event_mod(int fd,uint32_t event){
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=event;
        int r=epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
	exit_if(r,"event_mod failed!\n");
}
void Event_base::event_del(int fd){
        int r=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL); //内核版本在2.9之前不能用NULL参数，有bug
        exit_if(r,"event_del failed!\n");
}
void Event_base::event_loop(int maxevents,int time){
  	while(true){
		int maxevents=100;
		struct epoll_event events[maxevents];
     		int n=epoll_wait(epfd,events,maxevents,time);
     		for(int i=0;i<n;i++){
			if(events[i].events & EPOLLIN){
				read_handler(events[i].data.fd);
			}else if(events[i].events & EPOLLOUT){
                		write_handler(events[i].data.fd);
 			}else{
				//report error
			}
     		}//for 
  	}//while
}

void Event_base::read_handler(int fd){
	_read(fd);
}
void Event_base::write_handler(int fd){
	_write(fd);
}
void Event_base::set_readFunction(std::function<void(int)> read_func){
	_read=read_func;
}void Event_base::set_writeFunction(std::function<void(int)> write_func){
	_write=write_func;
}
