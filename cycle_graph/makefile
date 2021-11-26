all:graph_edge.o main.c
	gcc -g main.c graph_edge.o -llist -ldisj -ltree -o program.out -I /home/user/exam/include/ -L /home/user/exam/lib/

graph_edge.o: graph_edge.c graph_edge.h
	gcc -g -c graph_edge.c -llist -ldisj -ltree -o graph_edge.o -I /home/user/exam/include/ -L /home/user/exam/lib/

clean:
	rm -f *.o 
	rm -f program.out