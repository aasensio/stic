#include <mpi.h>
#include <iostream>
#include "master_sparse.h"
#include "slave.h"
using namespace std;
//
int main(int narg, char* argv[]){


  //
  // Init MPI
  //
  int nprocs = 1, myrank = 0, hlen = 0;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  int status = 0;
  MPI_Init(&narg, &argv);


  //
  // Fill-in vars
  //
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);// Job number
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);// number of processors
  MPI_Get_processor_name(&hostname[0], &hlen);// Hostname
  
  //
  // Split master/slave work
  //
  if(myrank == 0) do_master_sparse(myrank, nprocs, hostname);
  else do_slave(myrank, nprocs, hostname);

  
  //
  // Finalize work
  //
  MPI_Barrier(MPI_COMM_WORLD); // Wait until all processors reach this point
  MPI_Finalize();
  
}
