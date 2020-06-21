#makefile

make all: linearProbing chaining prims

linearProbing: linearProbing.o
	gcc -std=c99 -lm linearProbing.o -o linearProbing

chaining: chaining.o
	gcc -std=c99 -lm chaining.o -o chaining

prims: prims.o timer.o
	g++ prims.o timer.o -o prims

timer.o: timer.c timer.h
	gcc -c -std=c99 timer.c -o timer.o

linearProbing.o: linearProbing.c
	gcc -lm -c -std=c99 linearProbing.c -o linearProbing.o

chaining.o: chaining.c
	gcc -c -std=c99 -lm chaining.c -o chaining.o

prims.o: prims.cpp
	g++ -c prims.cpp -o prims.o

clean:
	rm -f *o
	rm -f linearProbing
	rm -f chaining
	rm -f prims


