#include "mpi.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
int main(int argc, char *argv[]) {
	int rank, size;
	double npoint = 10000; /*10000 point */
	double x_coordinate;
	double y_coordinate;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);
	double pi;
	int x;
	int circle_count = 0;
	unsigned seed;
	seed = (unsigned) time(NULL); // 取得時間序列
	srand(seed); // 以時間序列當亂數種子
	/*
	 * I am worker,
	 *
	 * */
	if (rank == 0) {
		for (int i = 1; i <= 10000; i++) {
			x_coordinate = rand() / (RAND_MAX + 1.0);
			usleep(100);
			MPI_Send(&x_coordinate, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD); // send message to roller coaster.
			y_coordinate = rand() / (RAND_MAX + 1.0);
			usleep(100);
			MPI_Send(&y_coordinate, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD); // send message to roller coaster.
		//	printf("座標 %d, x為: %f, y 座標為: %f \n", i, x_coordinate,y_coordinate);
		}
	}

	/*
	 * I am manager rank=1,
	 * */
	if (rank == 1) {
		for (int i = 1; i <= 10000; i++) {
			MPI_Recv(&x_coordinate, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
			MPI_Recv(&y_coordinate, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
			printf("coordinate %d: x coordinate: %f		y coordinate: %f \n", i, x_coordinate,y_coordinate);
			if ((x_coordinate - 0.5) * (x_coordinate - 0.5)
					+ (y_coordinate - 0.5) * (y_coordinate - 0.5)
					< 0.25) {
				circle_count = circle_count + 1;

			}

		}
		pi = 4 * circle_count / npoint;
		printf("circle_count = %d \n", circle_count);
		printf("pi = %f\n", pi);

	}
	MPI_Finalize();
	return 0;
}

