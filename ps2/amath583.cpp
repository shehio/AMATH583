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

void zeroize(Vector& x) {
  for (auto i = 0; i < x.num_rows(); i++)
  {
    x(i) = 0;
  }
}

double one_norm(const Vector& x) {
  auto sum = 0.0;
  for (auto i = 0; i < x.num_rows(); ++i) {
    sum += std::abs(x(i));
  }
  return sum;
}

double two_norm(const Vector& x) {
  auto sum = 0.0;
  for (auto i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * x(i);
  }
  return std::sqrt(sum);
}

double inf_norm(const Vector& x) {
  double result = std::numeric_limits<double>::lowest();
  for (auto i = 0; i < x.num_rows(); ++i) {
    result = std::max(result, x(i));
  }
  return result;
}

double dot(const Vector& x, const Vector& y) {
  assert(x.num_rows() == y.num_rows());
  auto sum = 0.0;
  for (auto i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * y(i);
  }
  return sum;
}

double two_norm_d(const Vector& x) { 
  return std::sqrt(dot(x, x));  
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
  auto sum = 0.0;
  for (auto i = 0; i < A.num_rows(); ++i) {
    auto tmp = 0.0;
    for (auto j = 0; j < A.num_cols(); ++j) {
      tmp += std::abs(A(i, j));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}

double f_norm(const Matrix& A) {
  auto sum = 0.0;
  for (auto i = 0; i < A.num_rows(); ++i) {
    for (auto j = 0; j < A.num_cols(); ++j) {
      sum += A(i, j) * A(i, j);
    }
  }
  return std::sqrt(sum);
}
