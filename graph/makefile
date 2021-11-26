all: main.c graph.o
	gcc -g main.c graph.o -llist -ltree -lstack -lqueue -o program.out -I include/ -L lib/
graph.o: include/graph.h graph.c
	gcc -g -c graph.c -llist -ltree -o graph.o -I include/ -L lib/
clean: 
	rm -f program.out
	rm -f *.o