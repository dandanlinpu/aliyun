#include <sys/epoll.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <functional>
 
class Event_base{
public:
	Event_base();
	~Event_base();
public:
	void event_init();
	void event_loop(int maxevents=100,int time=-1);
	void event_add(int fd,uint32_t event);
	void event_mod(int fd,uint32_t event);
	void event_del(int fd);
public:
	void set_readFunction(std::function<void(int fd)>);
	void set_writeFunction(std::function<void(int fd)>);
private:
	int epfd;
	void read_handler(int fd); //epoll in
	void write_handler(int fd);//epoll out 事件处理器
	
	std::function <void(int)> _read;
	std::function <void(int)> _write;
	
};
