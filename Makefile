all:
	gcc src/*.c -I include/ -o main -std=c99 -g

run:
	./main

debug:
	valgrind --leak-check=full -v ./main