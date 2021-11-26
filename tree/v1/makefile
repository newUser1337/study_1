all: main.c lib
	gcc -g main.c tree.o -o program.out
lib: tree.o
	ar cr lib/libtree.a tree.o
tree.o: tree.c tree.h
	gcc -g -c tree.c -o tree.o
clean:
	rm -f program.out
	rm -f *.o