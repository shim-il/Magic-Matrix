magic:magic.o
	gcc -g -Wall -ansi -pedantic magic.c -o magic

magic.o:magic.c
	gcc -c magic.c -o magic.o

