all: main.o read.o write.o print.o
	gcc -o structrw main.o read.o write.o print.o

main.o: main.c read.h entry.h print.h write.h
	gcc -c main.c

read.o: read.c read.h print.h entry.h
	gcc -c read.c

write.o: write.c write.h print.h entry.h read.h
	gcc -c write.c

print.o: print.c print.h read.h entry.h
	gcc -c print.c

run:
	./program

clean:
	rm *.o
	rm structrw
	rm a.out