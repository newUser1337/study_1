all: lib main.c
	gcc main.c stack.o -o program.out

lib: stack.o
	ar cr lib/libstack.a stack.o

stack.o: stack.h stack.c
	gcc -g -c stack.c -o stack.o

clean:
	rm -f *.o
	rm -f program.out