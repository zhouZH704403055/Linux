.PHONY:all
all:server client
cc=g++
client:client.cpp
	$(cc) -o $@ $^
server:server.cpp
	$(cc) -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f client server
