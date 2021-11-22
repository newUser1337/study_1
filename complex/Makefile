all: main.o compl.o
	gcc main.o compl.o -o main

main.o:	compl.o main.c
	gcc -c main.c compl.o -o main.o

compl.o: compl.h compl.c
	gcc -c compl.c -o compl.o

clean:
	rm -f *.o
	rm -f main