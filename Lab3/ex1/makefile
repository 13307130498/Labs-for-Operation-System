all:	shdMem server client

shdMem:	shdMemAndFork.c
	gcc -Wall shdMemAndFork.c -o shdMem

server:	server.c
	gcc -Wall server.c -o server

client:	client.c
	gcc -Wall client.c -o client

clean:
	rm -f shdMem server client
