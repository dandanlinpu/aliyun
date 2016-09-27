#nc 127.0.0.1 port  
alltarget: simple_server 
simple_server:simple_server.c rio.c sock_common.c http_server.c url_encode.c multi_matrix.c
	g++ -o simple_server simple_server.c rio.c sock_common.c http_server.c url_encode.c multi_matrix.c
clean:
	rm  simple_server 	
