all: main.o editor.o console.o
	gcc -o editor main.o editor.o console.o -lncurses

main.o: main.c editor.h
	gcc -c main.c

editor.o: editor.c editor.h
	gcc -c editor.c

console.o: console.c console.h
	gcc -c console.c

clean:
	rm *.o
	rm editor console main 

run:
	make
	./editor test.c