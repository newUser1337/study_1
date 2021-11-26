all: main.c graph.o
	gcc -g main.c graph.o -llist -ltree -lstack -lqueue -o program.out -I /home/user/exam/include -L /home/user/exam/lib
graph.o: /home/user/exam/include/graph.h graph.c
	gcc -g -c graph.c -llist -ltree -o graph.o -I /home/user/exam/include -L /home/user/exam/lib
clean: 
	rm -f program.out
	rm -f *.o