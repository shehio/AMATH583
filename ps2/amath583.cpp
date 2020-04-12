//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <cmath>
#include <cstddef>

void zeroize(/* WRITE ME */) {
  // WRITE ME
}

double one_norm(const Vector& x) {
  // WRITE ME
  double sum = 0.0;

  return sum;
}

double two_norm(const Vector& x) {
  // WRITE ME
  return /* FIX ME */ -1.0;
}

double inf_norm(const Vector& x) {
  double result = 0.0;
  // WRITE ME

  return result;
}

double dot(const Vector& x, const Vector& y) {
  // WRITE ME

  return /* FIX ME */ 0.0;
}

double two_norm_d(const Vector& x) { 
  // WRITE ME / FIX ME -- can you make the function only one line long including return?
  return 0.0;  
}

double one_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t j = 0; j < A.num_cols(); ++j) {    // for each column
    double tmp = 0.0;
    for (size_t i = 0; i < A.num_rows(); ++i) {    // compute column sum
      tmp += std::abs(A(i, j));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}


double inf_norm(const Matrix& A) {
  double sum = 0.0;
  // WRITE ME
  return sum;
}

// WRITE ME f_norm()
