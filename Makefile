all: main

main: main.o table.o
	gcc -o main main.o table.o

main.o: main.c main.h table.h
	gcc -c main.c

table.o: table.c table.h
	gcc -c table.c

clean:
ifeq ($(OS),Windows_NT)
	del /Q main.exe main.o table.o
else
	rm -f main main.o table.o
endif