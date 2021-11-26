all: lib main.c
	gcc -g main.c stack.o -o program.out -I /home/user/exam/include/

lib: stack.o
	ar cr /home/user/exam/lib/libstack.a stack.o

stack.o: /home/user/exam/include/stack.h stack.c
	gcc -g -c stack.c -o stack.o -I /home/user/exam/include/

clean:
	rm -f *.o
	rm -f program.out
	rm -f /home/user/exam/lib/libstack.a