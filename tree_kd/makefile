all: main.c kdtree.o
	gcc -g main.c kdtree.o -llist -o program.out -I /home/user/exam/linkedlist/linkedlist/v1 -L /home/user/exam/linkedlist/linkedlist/v1/lib
kdtree.o: kdtree.c kdtree.h
	gcc -g -c kdtree.c -llist -o kdtree.o -I /home/user/exam/linkedlist/linkedlist/v1 -L /home/user/exam/linkedlist/linkedlist/v1/lib
clean:
	rm -f program.out
	rm -f *.o