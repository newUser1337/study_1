all: main.c tree.o
	gcc -g main.c tree.o -o program.out
tree.o: tree.c tree.h
	gcc -g -c tree.c -o tree.o
clean:
	rm -f program.out
	rm -f *.o