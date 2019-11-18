all: main.o
	gcc -o dirtest.exe main.o

main.o: main.c
	gcc -c main.c

run:
	./dirtest.exe

clean:
	rm *.o
	rm *~
