all: main.c lib
	gcc -g main.c queue.o -o program.out

lib: queue.o 
	ar cr lib/libqueue.a queue.o

queue.o: queue.h queue.c
	gcc -c -g queue.c -o queue.o

clean:
	rm -f *.o
	rm -f program.out