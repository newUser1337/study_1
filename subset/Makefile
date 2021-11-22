all: main.o subset.o ../util/array.o
	gcc main.o subset.o ../util/array.o -o main

main.o: subset.o main.c
	gcc -c main.c -o main.o 

subset.o: subset.h subset.c
	gcc -c subset.c -o subset.o

clean:
	rm -f *.o
	rm -f main