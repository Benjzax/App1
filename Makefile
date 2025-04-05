# Makefile sencillo para compilar App1

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = main.o parse.o metrics.o

app1: $(OBJ)
	$(CC) $(CFLAGS) -o app1 $(OBJ)

main.o: main.c parse.h metrics.h
	$(CC) $(CFLAGS) -c main.c

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c

metrics.o: metrics.c metrics.h
	$(CC) $(CFLAGS) -c metrics.c

clean:
	rm -f *.o app1
