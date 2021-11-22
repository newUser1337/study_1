all: main.o partition.o ../util/array.o
	gcc -g main.o partition.o ../util/array.o -o main

main.o: partition.o main.c
	gcc -c -g main.c -o main.o 

partition.o: partition.h partition.c
	gcc -c -g partition.c -o partition.o

clean:
	rm -f *.o
	rm -f main