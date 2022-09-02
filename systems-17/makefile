all: control.c write.c
	gcc -o control control.c && gcc -o write write.c

create:
	./control -c

remove:
	./control -v

input:
	./write

clean:
	rm *.o
	rm control
	rm write
