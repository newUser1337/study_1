all: main.o permutation_trans.o ../../util/array.o
	gcc main.o permutation_trans.o ../../util/array.o -o main

main.o: permutation_trans.o main.c
	gcc -c main.c -o main.o 

permutation_trans.o: permutation_trans.h permutation_trans.c
	gcc -c permutation_trans.c -o permutation_trans.o

clean:
	rm -f *.o
	rm -f main