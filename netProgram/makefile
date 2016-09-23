#nc 127.0.0.1 port  
alltarget: simple_server simple_client
simple_server:simple_server.c rio.c
	g++ -o simple_server simple_server.c rio.c
simple_client:simple_client.c
	g++ -o simple_client simple_client.c
clean:
	rm  simple_server simple_client	
