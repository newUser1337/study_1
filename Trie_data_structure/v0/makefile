all: main.c trie.o
	gcc -g main.c trie.o -o program.out
trie.o: trie.c trie.h
	gcc -g -c trie.c -o trie.o
clean:
	rm -f *.o
	rm -f program.out