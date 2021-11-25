all: main.c kdtree.o
	gcc -g main.c kdtree.o -o program.out
kdtree.o: kdtree.c kdtree.h
	gcc -g -c kdtree.c -o kdtree.o
clean:
	rm -f program.out
	rm -f *.o