all: fenw.o main.c
	gcc -g main.c fenw.o -o program 

fenw.o: fenw.c fenw.h
	gcc -c -g fenw.c -o fenw.o

clean:
	rm -f *.o
	rm -f program