
.PHONY:all
all:server server_A server_B client

server:server.c deal.c
	gcc -o $@ $^

server_A:server_A.c
	gcc -o $@ $^	
server_B:server_B.c
	gcc -o $@ $^
client:client.c
	gcc -o $@ $^
	
.PHONY:clean
clean:
	rm -f server server_A server_B client
