#nc 127.0.0.1 port
#tcpdump -i any -nn tcp port 1000 
alltarget: client server
client: client.c sock_common.c
	g++ client.c sock_common.c -o client
server: server.c sock_common.c
	g++ server.c sock_common.c -o server
clean:
	rm client server	
