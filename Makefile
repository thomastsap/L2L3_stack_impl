CC=gcc
CFLAGS=-g -Wall -Wextra
TARGET:main.exe

OBJS=graph.o

main.exe:main.c graph.o net.o
	${CC} ${CFLAGS} main.c -o main.exe graph.o net.o

graph.o:graph.c
	${CC} -c ${CFLAGS} graph.c -o graph.o

net.o:net.c
	${CC} -c ${CFLAGS} net.c -o net.o

clean:
	rm *.o
	rm *.exe