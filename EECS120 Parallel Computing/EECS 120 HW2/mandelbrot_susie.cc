#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include "render.hh"

#define WIDTH 1000
#define HEIGHT 1000

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
		fprintf(stderr, "usage: %s <height> <width>\n", argv[0]);
		fprintf(stderr, "where <height> and <width> are the dimensions of the image.\n");
		return -1;
	}

	double timerBegin;
	double a, b;
	double i = (maxY - minY) / height;
	double j = (maxX - minX) / width;
	int rank;
	int totalNumberOfProcesses;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &totalNumberOfProcesses);

	gil::rgb8_image_t img(height, width);
	auto img_view = gil::view(img);

	int *buffer_receive = new int[height * width];
	int buffer_send[(height * width) / totalNumberOfProcesses];

	timerBegin = MPI_Wtime();

	b = minY + rank * i;
	for(int k = 0; k < (height / totalNumberOfProcesses); k++) {
		a = minX;
		for(int l = 0; l < width; ++l) {
			buffer_send[(k * width) + l] = mandelbrot(a, b);
			a += j;
		}
		b += i * totalNumberOfProcesses; 
	}

	MPI_Gather(buffer_send, (height / totalNumberOfProcesses) * width, MPI_INT, buffer_receive, (height / totalNumberOfProcesses) * width, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		int pieces = 0;
		int row = 0;
		int col = 0;

		while(row < height) {
			if (row % totalNumberOfProcesses == 0) {
				pieces = row / totalNumberOfProcesses;
			}
			col = 0;

			while(col < width) {
				img_view(col++, row) = render(buffer_receive[(pieces * width) + col] / 512.0);
			}
			pieces += height / totalNumberOfProcesses;
			row++;
		}
		gil::png_write_view("mandelbrot_susie.png", const_view(img));
	}
	
	printf("\n");
	printf("Total Time for mandelbrot_susie: %f", MPI_Wtime() - timerBegin);
	printf("\n");
	MPI_Finalize();
	return 0;
}
/* eof */
