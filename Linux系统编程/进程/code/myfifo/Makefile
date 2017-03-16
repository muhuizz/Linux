server=fifo_server
client=fifo_client
cc=gcc

serverSrc=server.c
clientSrc=client.c

.PHONY:all
all:$(server) $(client)
$(server):$(serverSrc)
	$(cc) -o $@ $^
$(client):$(clientSrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(server) $(client) myfifo
