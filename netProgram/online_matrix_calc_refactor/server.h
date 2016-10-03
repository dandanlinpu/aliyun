#include "socket.h"
#include "event.h"
#include <iostream>
#include <functional>
class Http_server{
public:
	Http_server(int port=10001);
	~Http_server();	
public:
	void run();
	void stop();
private:
	Tcp_socket _socket;
	Event_base _eb;
	void _read(int fd);
	//void _write(int fd,int buf,int size);
	void _write(int fd);
	
	char request_file_name[20];
	char request_url[200];
	
};
