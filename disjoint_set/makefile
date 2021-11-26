all: lib main.c
	gcc -g main.c disj.o -ltree -o program.out -I /home/user/exam/include/ -L /home/user/exam/lib/

lib: disj.o
	ar cr /home/user/exam/lib/libdisj.a disj.o

disj.o: disj.c /home/user/exam/include/disj.h 
	gcc -g -c disj.c -ltree -o disj.o -I /home/user/exam/include/ -L /home/user/exam/lib/

clean: 
	rm -f proram.out
	rm -f *.o
	rm -f /home/user/exam/lib/libdisj.a