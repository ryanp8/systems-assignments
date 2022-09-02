all: main.o linked_list.o library.o
	gcc -o program main.o linked_list.o library.o

main.o: main.c library.h linked_list.h
	gcc -c main.c

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

library.o: library.c library.h linked_list.h
	gcc -c library.c

run:
	./program

clean:
	rm *.o
	rm ./program

