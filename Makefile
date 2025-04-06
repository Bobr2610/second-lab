all: main

main: main.o table.o
	gcc -o main main.o table.o

main.o: main.c table.h
	gcc -c main.c

table.o: table.c table.h
	gcc -c table.c

clean:
	rm -f main main.o table.o