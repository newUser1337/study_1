all: main.o doublelinkedlist.o
	gcc -g doublelinkedlist.o main.o -o main

main.o: main.c doublelinkedlist.o
	gcc -g -c -Wall main.c 

doublelinkedlist.o: doublelinkedlist.c doublelinkedlist.h 
	gcc -g -c -Wall doublelinkedlist.c

clean:
	rm -f *.o 
	rm -f main