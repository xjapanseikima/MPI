#include "mpi.h"
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	int rank, size, r_passenger;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);
	int passengers = 30; // there are 30 passengers waiting for taking ride
	r_passenger = 5;
	int empty = 0; // check roller coaster if it's empty＝1, full=0
	int r = 3;
	/* rank=0
	 * Passenger
	 * everytime only 5 passenger can take a ride
	 * */
	if (rank == 0) {
		usleep(1000);
		while (passengers > 0) {
			//	printf("I am %d of %d\n", rank, size);
			passengers = passengers - r_passenger;
			if (passengers > 0) {
				printf("Five passenger get into roller coaster\n");
				MPI_Send(&r_passenger, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // send message to roller coaster.
				printf("%d passengers on the queue \n", passengers);
				printf("Wait for all passenger get into car....\n");
				usleep(900000);// it's time for let passenger get inside the roller coaster
				//printf(" haven't recevied value is %d ", empty);
				/*	MPI_Recv(&empty, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, // receive message from empty roller coaster
				 MPI_STATUS_IGNORE);*/
				printf("Car empty now , let other passenger get into car\n");
				printf("\n");
				empty = 1;
				//printf(" Test from %d \n", empty);

			} else {
				//passengers = passengers - r_passenger;
				//MPI_Send(&r_passenger, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // send message to roller coaster.
				//printf("now.. %d left\n ",r_passenger);
				printf("No more passenger process, finished\n");
				if (r > 1) {
					printf("\n");
					printf("Passenger want to take more rides !!!!\n");
					r = r - 1;
					printf("OKOKO... BUT ONLY %d times left \n", r);
					printf("\n");
					passengers = 30;
				} else {
					printf("No more rides!!!! Go home guys..., it's closed.\n");
				}

			}
		}

	}

	/*
	 * rank=1, roller Coaster
	 * */

	if (rank == 1) {
		//loading
		//loading time
		// roller caster go around time
		passengers = 90;
		while (passengers > 20) {
			passengers = passengers - r_passenger;
			//	printf("I am %d of %d\n", rank, size);
			MPI_Recv(&r_passenger, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
			printf(
					"Ready  to go and %d passenger on the roller coaster from rank1 \n",
					r_passenger);
			printf("processing...\n");
			usleep(1000000);// having fun time
			//	printf("就差你這一步 passenger是多少拉 %d\n", passengers);
			//	MPI_Send(&empty, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);	//send the empty message to the roller coaster
		}
		printf("Roller coaster Process finished \n");
	}
	MPI_Finalize();
	return 0;
}
