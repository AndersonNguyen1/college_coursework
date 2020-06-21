#makefile

make all: EditDistance

EditDistance: EditDistance.o
	g++ EditDistance.o -o EditDistance

EditDistance.o: EditDistance.cpp
	g++ -c EditDistance.cpp -o EditDistance.o

clean:
	rm -f *o
	rm -f EditDistance
