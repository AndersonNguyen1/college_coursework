#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <cmath>
#include "render.hh"

#define WIDTH 1000
#define HEIGHT 1000
#define TOTAL_ROWS 1000

using namespace std;

int mandelbrot(double a, double b) {
	int min = 0;
	int max = 511;

	double tempA = a;
	double tempB = b; 
	double newA;
	double newB;

	for (min = 0; (min < max) && ((a * a + b * b) < 4); ++min) {
		newA = (a * a) - (b * b) + tempA;
		newB = (a * b * 2) + tempB;
		a = newA;
		b = newB;
	}
	return min;
}

int main (int argc, char* argv[])
{
	double minX = -2.1;
	double maxX = 0.7;
	double minY = -1.25;
	double maxY = 1.25;

	int height;
	int width;
	if (argc == 3) {
		height = atoi(argv[1]);
		width = atoi(argv[2]);
		assert(height > 0 && width > 0);
	}
	else {
		fprintf(stderr, "usage: %s <height> <width?\n", argv[0]);
		fprintf(stderr, "where <height> and <width> are the dimensions of the image.\n");
		return -1;
	}

	double timerBegin;
	double a, b;
	double i = (maxY - minY) / height;
	double j = (maxX - minX) / width;
	int rank;
	int size;
	
	// asks the user for number of processes
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// splits up the work
	int split = height / size;
	int data = (split * width);
	int sendBuffer[data];

	// built in timer function for MPI
	timerBegin = MPI_Wtime();

	b = minY + (rank * split * i);
	for (int k = 0; k < split; ++k) {
		a = minX;
		for (int l = 0; l < width; ++l) {
			sendBuffer[(k * width) + l] = mandelbrot(a, b);
			a += j;
		}
		b += i;
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	int *recBuffer = 0;
	if(rank == 0) {
		recBuffer = new int[size * data];
	}

	// gathers the values from a group of processes
	MPI_Gather(sendBuffer, data, MPI_INT, recBuffer, data, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		gil::rgb8_image_t img(height, width);
		auto img_view = gil::view(img);
		for(int r = 0; r < (split * size); ++r) {
			for(int s = 0; s < width; s++) {
				img_view(s, r) = render(recBuffer[(r * width) + s]/512.0);
			}
		}
		gil::png_write_view("mandelbrot_joe.png", const_view(img));
	}	
	printf("\n");
	printf("Total Time for mandelbrot_joe: %f", MPI_Wtime() - timerBegin);
	printf("\n");
	MPI_Finalize();
	return 0;
}
/* eof */
