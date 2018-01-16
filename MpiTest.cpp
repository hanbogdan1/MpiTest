// MpiTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>


#define MAX_BUFF_SIZE 100
#define ARRAY_SIZE 15
using namespace std;

int main(int argc, char ** argv)
{
	
	int vect[MAX_BUFF_SIZE];
	MPI_Status status;

	// variabilele in care stochez detalii despre sesiunea curenta 
	int namelen, myid, numprocs;
	MPI_Init(&argc, &argv);

	//MPI_COMM_WORLD - 	comunicatorul	predefinit	

	// nr de procese 
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	//procesul actual
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);


	if (myid != 0) {
		int local_var =0 ;
		MPI_Recv(vect, ARRAY_SIZE, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		
		for (auto x = 0; x < ARRAY_SIZE; x++) {
			local_var += vect[x];
		}

		MPI_Send(&local_var, 1, MPI_INT,0, 2, MPI_COMM_WORLD);
	}
	else {
		int* vectzero = new int[ARRAY_SIZE * numprocs];
		
		int Suma_totala = 0;

		for (auto x = 0; x < ARRAY_SIZE * numprocs; x++) {
			vectzero[x] = 1;
		}

		for (int i = 1; i < numprocs; i++) {
			MPI_Send(vectzero + i * ARRAY_SIZE, ARRAY_SIZE, MPI_INT,i, 1, MPI_COMM_WORLD);
		}

		int total = 0,recvsum = 0;

		for (int i = 1; i < numprocs; i++) {
			MPI_Recv(&recvsum, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
			total += recvsum;
		}
		for (auto x = 0; x < ARRAY_SIZE; x++) {
			total += vectzero[x];
		}
		printf("output :%d", total);
		/*delete[] vectzero;*/
	}

	MPI_Finalize();
    return 0;
}

