all:
	gcc src/adjMatrix.c src/main.c -I include/ -o main -Wall -std=c99 -g

fleury:
	gcc src/adjMatrix.c src/Fleury.c -I include/ -o main -Wall -std=c99 -g	

run:
	./main

debug:
	gdb ./main

valgrind:
	valgrind --leak-check=full -v ./main