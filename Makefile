CC = gcc

CFLAGS = -Wall -g

calculator: main.o matfunc.o instructions.o
	$(CC) $(CFLAGS) -o calculator main.o matfunc.o instructions.o
main.o: main.c matfunc.h
	$(CC) $(CFLAGS) -c main.c

matfunc.o: matfunc.c matfunc.h
	$(CC) $(CFLAGS) -c matfunc.c
instructions.0: instructions.c instructions.h
	$(CC) $(CFLAGS) -c instructions.c
clean:
	rm -f *.o calculator
