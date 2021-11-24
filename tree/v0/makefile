all: tree.o main.c book.c
	gcc -g main.c tree.o -o program
	gcc -g book.c tree.o -o rvx
	
tree.o: tree.h tree.c
	gcc -g -c tree.c -o tree.o

clean:
	rm -f rvx
	rm -f program
	rm -f *.o