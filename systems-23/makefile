all: client server


client: basic_client.o socket_networking.o
	gcc -o client basic_client.o socket_networking.o

server: basic_server.o socket_networking.o
	gcc -o server basic_server.o socket_networking.o

basic_client.o: basic_client.c socket_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c socket_networking.h
	gcc -c basic_server.c

socket_networking.o: socket_networking.c socket_networking.h
	gcc -c socket_networking.c

clean:
	rm *.o
	rm *~