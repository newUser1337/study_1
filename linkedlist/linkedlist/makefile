all: main.o linkedlist.o
	gcc -g linkedlist.o main.o -o main

main.o: main.c linkedlist.o
	gcc -g -c -Wall main.c 

linkedlist.o: linkedlist.c linkedlist.h 
	gcc -g -c -Wall linkedlist.c

clean:
	rm -f *.o 
	rm -f main