all: program clear

program: main.o
		gcc main.o -o program

main.o: grafo.o main.c
		gcc -c main.c

grafo.o: grafo.c grafo.h
		gcc -c grafo.c

clear:
		rm *.o prog
