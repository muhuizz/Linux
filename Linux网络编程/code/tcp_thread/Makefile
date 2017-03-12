.PHONY:all
all:client server

pt = -lpthread

client:client.c
	gcc -o $@ $^ $(pt)
server:server.c
	gcc -o $@ $^ $(pt)

.PHONY:clean
clean:
	rm -f client server
