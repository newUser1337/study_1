all: main.c trie.o
	gcc -g main.c trie.o -llist -o program.out -I /home/user/exam/linkedlist/linkedlist/v1 -L /home/user/exam/linkedlist/linkedlist/v1/lib
trie.o: trie.c trie.h
	gcc -g -c trie.c -o trie.o -I /home/user/exam/linkedlist/linkedlist/v1
clean:
	rm -f *.o
	rm -f program.out