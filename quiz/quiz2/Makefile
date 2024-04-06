all: run

run: arraylist.o main.c
	gcc -g arraylist.c main.c -o list

arraylist.o: arraylist.c arraylist.h
	gcc -c -Wall -g arraylist.c -o arraylist.o