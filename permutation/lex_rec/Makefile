all: main.o permutation_lex_rec.o ../../util/array.o
	gcc main.o permutation_lex_rec.o ../../util/array.o -o main

main.o: permutation_lex_rec.o main.c
	gcc -c main.c -o main.o 

permutation_lex_rec.o: permutation_lex_rec.h permutation_lex_rec.c
	gcc -c permutation_lex_rec.c -o permutation_lex_rec.o

clean:
	rm -f *.o
	rm -f main