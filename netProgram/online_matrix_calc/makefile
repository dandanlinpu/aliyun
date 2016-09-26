#nc 127.0.0.1 port  
alltarget: simple_server 
simple_server:simple_server.c rio.c sock_common.c http_server.c url_encode.c
	g++ -o simple_server simple_server.c rio.c sock_common.c http_server.c url_encode.c
clean:
	rm  simple_server 	
