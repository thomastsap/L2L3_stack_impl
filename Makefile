CC=gcc
CFLAGS=-g -Wall -Wextra
TARGET:main.exe

OBJS=graph.o

main.exe:main.c util.o graph.o net.o
	${CC} ${CFLAGS} main.c -o main.exe graph.o net.o util.o

graph.o:graph.c util.h
	${CC} -c ${CFLAGS} graph.c -o graph.o

net.o:net.c util.h
	${CC} -c ${CFLAGS} net.c -o net.o

util.o:util.c util.h
	${CC} -c ${CFLAGS} util.c -o util.o

clean:
	rm *.o
	rm *.exe