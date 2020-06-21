#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include "render.hh"

using namespace std;

int mandelbrot(double a, double b) {
	int min = 0;
	int max = 511;

	double tempA = a;
	double tempB = b;
	double newA;
	double newB;

	for(min = 0; (min < max) && ((a * a - b * b) < 4); ++min) {
		newA = (a * a) - (b * b) + tempA;
		newB = (a * b * 2) + tempB;
		a = newA;
		b = newB;
	}
	return min;
}

void slave(int rank, int width, double minX, double minY, double i, double j) {
	MPI_Status state;

	int buffer_send[width + 1];
	int calc_row = 0;
	double tempA;
	double tempB;

	while(true) {
		MPI_Recv(&calc_row, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &state);
		if (state.MPI_TAG == 0) {
			return;
		}
		else {
			tempA = minX;
			tempB = minY + (calc_row * i);
			for (int k = 0; k < width; ++k) {
				buffer_send[k] = mandelbrot(tempA, tempB);
				tempA += j;
			}
			buffer_send[width] = calc_row;
			MPI_Send(buffer_send, width + 1, MPI_INT, 0, 1, MPI_COMM_WORLD);		
		}
	}
} 

void master(int width, int height, double minX, double minY, double j, double size) {
	MPI_Status state;
	double timerBegin = MPI_Wtime();
	int *storeBuffer = new int[width * height];	
	int nextRow = 0;
	int recBuffer[width + 1];

	for (int i = 1; i < size; i++) {
		MPI_Send(&nextRow, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
		nextRow++;
	}

	while (nextRow < height) {
		MPI_Recv(recBuffer, width + 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &state);
		MPI_Send(&nextRow, 1, MPI_INT, state.MPI_SOURCE, 1, MPI_COMM_WORLD);
		memcpy(storeBuffer + (recBuffer[width] * width), recBuffer, width * sizeof(int));
		nextRow++;
	}

	for (int i = 1; i < size; i++) {
		MPI_Recv(recBuffer, width + 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &state);
		MPI_Send(0, 0, MPI_INT, state.MPI_SOURCE, 0, MPI_COMM_WORLD);
		memcpy(storeBuffer + (recBuffer[width] * width), recBuffer, width * sizeof(int));
	}

	gil::rgb8_image_t img(height, width);
	auto img_view = gil::view(img);
	
	for(int r = 0; r < height; ++r) {
		for(int s = 0; s < width; ++s) {
			img_view(s, r) = render(storeBuffer[(r * width) + s]/512.0);
		}
	}
	
	printf("\n");
	printf("Total Time for mandelbrot_ms: %f", MPI_Wtime() - timerBegin);
	printf("\n");

	gil::png_write_view("mandelbrot_ms.png", const_view(img));
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
		fprintf(stderr, "usage: %s <height> <width> \n", argv[0]);
		fprintf(stderr, "where <height> and <width> are the dimensions of the image.\n");		
		return -1;
	}

	double timerBegin;
	double a, b;
	double i = (maxY - minY) / height;
	double j = (maxX - minX) / width;
	int rank;
	int size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0) {
		master(width, height, minX, minY, j, size);
	}
	else {
		slave(rank, width, minX, minY, i, j);
	}
	return 0;
}
