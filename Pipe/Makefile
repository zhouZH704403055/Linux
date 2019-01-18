.PHNOY:all
all:client server

client:client.c
	gcc $^ -o $@

server:server.c
	gcc $^ -o $@
.PHNOY:clean
clean:
	rm -f client server pipefile
