all: sparce.o main.c
	gcc -g main.c sparce.o -lm -o program
sparce.o: sparce.c sparce.h
	gcc -c -g sparce.c -o sparce.o
clean:
	rm -f *.o
	rm -f program