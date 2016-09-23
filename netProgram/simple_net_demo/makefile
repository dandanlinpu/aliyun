#nc 127.0.0.1 port
alltarget: client server
client: client.c common.c
	g++ client.c common.c -o client
server: server.c common.c
	g++ server.c common.c -o server
clean:
	rm client server	
