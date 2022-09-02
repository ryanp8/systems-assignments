all: main.o mystring.o
	gcc -o program main.o mystring.o

main.o: main.c mystring.h
	gcc -c main.c

mystring.o: mystring.c mystring.h
	gcc -c mystring.c

run:
	./program

clean:
	rm *.o
	rm ./program