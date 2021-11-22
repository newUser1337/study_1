main: main.o vector.o 
	gcc main.o vector.o -o main -lm

main.o: vector.o main.c
	gcc -c main.c -o main.o

vector.o: vector.h vector.c
	gcc -c vector.c -o vector.o

clean:
	rm -f *.o
	rm -f main