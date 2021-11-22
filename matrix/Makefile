all: main.o matrix.o ../util/array.o ../permutation/trans/permutation_trans.o
	gcc main.o matrix.o ../util/array.o ../permutation/trans/permutation_trans.o -o main

main.o: matrix.o main.c
	gcc -c main.c -o main.o 

matrix.o: matrix.h matrix.c matrix_det_perm.c matrix_det_tri.c matrix_multi.c
	gcc -c matrix.c 		 -o matrix_core.o
	gcc -c matrix_det_perm.c -o matrix_det_perm.o
	gcc -c matrix_det_tri.c  -o matrix_det_tri.o
	gcc -c matrix_multi.c    -o matrix_multi.o
	ld -relocatable matrix_core.o matrix_det_perm.o matrix_det_tri.o matrix_multi.o -o matrix.o

clean:
	rm -f *.o
	rm -f main