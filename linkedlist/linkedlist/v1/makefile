all: main.c list.o
	gcc -g main.c list.o -o program.out

lib: list.o
	ar cr lib/liblist.a list.o

list.o: list.c list.h
	gcc -g -c list.c -o list.o
clean:
	rm -f *.o
	rm -f program.out
	rm -f lib/*