//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_MPI_STENCIL_HPP
#define AMATH583_MPI_STENCIL_HPP

#include "Grid.hpp"
#include <mpi.h>

class mpiStencil { };


Grid mult(const mpiStencil& A, const Grid& x) {
  Grid y(x);

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  size_t north = (myrank == 0 ? MPI::PROC_NULL : myrank - 1);
  size_t south = (myrank == mysize - 1 ? MPI::PROC_NULL : myrank + 1);
  MPI::COMM_WORLD.Sendrecv(&x(1, 0), x.num_y(), MPI::DOUBLE, north, 322, const_cast<double*>(&x(0, 0)), x.num_y(), MPI::DOUBLE, north, 321);
  MPI::COMM_WORLD.Sendrecv(&x(x.num_x() - 2, 0), x.num_y(), MPI::DOUBLE, south, 321, const_cast<double*>(&x(x.num_x() - 1, 0)), x.num_y(), MPI::DOUBLE, south, 322);

  // SPMD stencil application
  for (size_t i = 1; i < x.num_x() - 1; ++i) {
    for (size_t j = 1; j < x.num_y() - 1; ++j) {
      y(i, j) = x(i, j) - (x(i - 1, j) + x(i + 1, j) + x(i, j - 1) + x(i, j + 1)) / 4.0;
    }
  }

  return y;
}


Grid operator*(const mpiStencil& A, const Grid& x) {
  return mult(A, x);
}


#endif // AMATH583_MPI_STENCIL_HPP
