all:
	gcc src/adjMatrix.c src/main.c -I include/ -o main -Wall -std=c99 -g

fleury:
	gcc src/adjMatrix.c src/Fleury.c -I include/ -o main -Wall -std=c99 -g	

plagio:
	gcc src/adjMatrix.c src/plagio.c -I include/ -o main -Wall -std=c99 -g;

parser:
	gcc src/adjMatrix.c src/parser.c -I include/ -o main -Wall -std=c99 -g;	

run:
	./main txt1 txt2

debug:
	gdb ./main

valgrind:
	valgrind --leak-check=full -v ./main txt1 txt2