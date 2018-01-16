// MpiTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);
	cout << "hello world";
	MPI_Finalize();
    return 0;
}

