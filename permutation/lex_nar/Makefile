all: main.o permutation_lex_nar.o ../../util/array.o
	gcc main.o permutation_lex_nar.o ../../util/array.o -o main

main.o: permutation_lex_nar.o main.c
	gcc -c main.c -o main.o 

permutation_lex_nar.o: permutation_lex_nar.h permutation_lex_nar.c
	gcc -c permutation_lex_nar.c -o permutation_lex_nar.o

clean:
	rm -f *.o
	rm -f main