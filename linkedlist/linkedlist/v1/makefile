all: main.c lib
	gcc -g main.c list.o -o program.out -I /home/user/exam/include/

lib: list.o
	ar cr /home/user/exam/lib/liblist.a list.o

list.o: list.c /home/user/exam/include/list.h
	gcc -g -c list.c -o list.o -I /home/user/exam/include/
clean:
	rm -f *.o
	rm -f program.out
	rm -f /home/user/exam/lib/liblist.a