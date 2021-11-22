all: main.o subset_gray.o ../util/array.o
	gcc main.o subset_gray.o ../util/array.o -o main

main.o: subset_gray.o main.c
	gcc -c main.c -o main.o 

subset_gray.o: subset_gray.h subset_gray.c
	gcc -c subset_gray.c -o subset_gray.o

clean:
	rm -f *.o
	rm -f main