all: queue.o main.o
	gcc main.o queue.o -o program.out

main.o: queue.o main.c
	gcc -c main.c -o main.o

queue.o: queue.h queue.c
	gcc -c queue.c -o queue.o

clean:
	rm -f *.o
	rm -f program.out