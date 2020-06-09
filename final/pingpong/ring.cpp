//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char* argv[]) {
  MPI::Init();

  int token     = 0;
  size_t rounds = 1;
  if (argc >= 2) rounds = std::stol(argv[1]);

  int myrank = MPI::COMM_WORLD.Get_rank();
  int mysize = MPI::COMM_WORLD.Get_size();

  std::cout << "my rank: " << myrank << std::endl;
  std::cout << "my size: " << mysize << std::endl;

  while (rounds--) {
    if (0 == myrank) {
      int left  = (myrank + 1) % mysize;
      int right = (myrank - 1) % mysize;
      std::cout << myrank << ": sending token: " << token << std::endl;
      MPI::COMM_WORLD.Send(&token, 1, MPI::INT, left, 321);
      MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, right, 321);
      std::cout << myrank << ": received token: " << token << std::endl;
      ++token;
    } else {
      int left  = (myrank - 1) % mysize;
      int right = (myrank + 1) % mysize;
      MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, left, 321);
      std::cout << myrank << ": received token: " << token << std::endl;
      ++token;
      std::cout << myrank << ": sending token: " << token << std::endl;
      MPI::COMM_WORLD.Send(&token, 1, MPI::INT, right, 321);
    }
  }

  MPI::Finalize();

  return 0;
}
