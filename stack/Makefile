all: stack.o main.o
	gcc main.o stack.o -o main

main.o: stack.o main.c
	gcc -c main.c stack.o -o main.o

stack.o: stack.h stack.c
	gcc -c stack.c -o stack.o

clean:
	rm -f *.o
	rm -f main