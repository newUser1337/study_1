all: main.c lib
	gcc -g main.c queue.o -o program.out -I /home/user/exam/include/

lib: queue.o 
	ar cr /home/user/exam/lib/libqueue.a queue.o

queue.o: /home/user/exam/include/queue.h queue.c
	gcc -c -g queue.c -o queue.o -I /home/user/exam/include/

clean:
	rm -f *.o
	rm -f program.out
	rm -f /home/user/exam/lib/libqueue.a