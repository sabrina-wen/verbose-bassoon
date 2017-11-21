all: main.c
	gcc -o pipes main.c

run: all
	./pipes
