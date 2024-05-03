install:
	sudo cp clist.h /usr/local/include
	gcc -c -o clist.o clist.c
	ar rcs libclist.a clist.o
	sudo cp libclist.a /usr/local/lib