deb: static dynamic
	rm -f -r deb 
	rm -f libbigint.so.1.0.deb
	mkdir deb 
	mkdir deb/DEBIAN
	mkdir deb/usr
	mkdir deb/usr/lib
	mkdir deb/usr/include
	cp lib/* deb/usr/lib
	cp include/* deb/usr/include
	cp postinst/* deb/DEBIAN
	chmod 755 deb/DEBIAN/postinst
	touch deb/DEBIAN/control
	echo "Package: bigint" >> deb/DEBIAN/control
	echo "Version: 1.0" >> deb/DEBIAN/control 
	echo "Architecture: amd64" >> deb/DEBIAN/control
	echo "Maintainer: User" >> deb/DEBIAN/control
	echo "Description: bigint arithmetics" >> deb/DEBIAN/control
	#dpkg-deb --build deb
	dpkg-deb --build --root-owner-group deb libbigint.so.1.0.deb

dynamic: include/bigint.h bigint.c
	gcc -fpic -c bigint.c -o bigint_dyn.o -L include
	gcc -fpic bigint_dyn.o -shared -Wl,-soname,libbigint.so.1 -o lib/libbigint.so.1.0.0

main_static: main_static.o static
	gcc main_static.o -lbigint -o main_static -I include -L lib

main_static.o: static main.c
	gcc -c main.c -lbigint -o main_static.o -I include -L lib

static: bigint.c include/bigint.h
	gcc -c bigint.c -o bigint.o
#	ar cr lib/libbigint.a bigint.o

main: main.o bigint.o
	gcc main.o bigint.o -o main -I include

main.o: bigint.o main.c
	gcc -c main.c -o main.o -I include

bigint.o: include/bigint.h bigint.c
	gcc -c bigint.c -o bigint.o -lm

clean:
	rm -f *.o
	rm -f main
	rm -f main_static
	rm -f a.out
	rm -f lib/*