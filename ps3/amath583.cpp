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
#include <random>
#include <cassert>
#include <cmath>
#include <iostream>


// ----------------------------------------------------------------
//
// Vector arithmetic
//
// ----------------------------------------------------------------
void zeroize(Vector& x) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = 0.0;
  }
}

void   randomize(Vector& x);
double one_norm(const Vector& x);
double two_norm(const Vector& x);
double inf_norm(const Vector& x);
double p_norm(const Vector& x);

Vector operator+(const Vector& x, const Vector& y);
Vector operator-(const Vector& x, const Vector& y);
Vector operator*(double alpha, const Vector& x);
Vector& operator*=(const Vector& x, double alpha);
Vector& operator+=(const Vector& x, const Vector& y);
Vector& operator-=(const Vector& x, const Vector& y);



// ----------------------------------------------------------------
//
// Matrix arithmetic
//
// ----------------------------------------------------------------
void   zeroize(Matrix& A) {
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      A(i, j) = 0.0;
    }
  }
}

void randomize(Matrix& A) {
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(2.0, 32.0);
  static auto                            dice = std::bind(distribution, generator);

  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      A(i, j) = dice();
    }
  }
}

double one_norm(const Matrix& x);
double two_norm(const Matrix& x);
double inf_norm(const Matrix& x);

double f_norm(const Matrix& A) {
  auto sum = 0.0;
  for (auto i = 0; i < A.num_rows(); ++i) {
    for (auto j = 0; j < A.num_cols(); ++j) {
      sum += A(i, j) * A(i, j);
    }
  }
  return std::sqrt(sum);
}

Matrix operator+(const Matrix& A, const Matrix& B) {
  assert(A.num_rows() == B.num_rows());
  assert(A.num_cols() == B.num_cols());
  Matrix C(A.num_rows(), A.num_cols());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      C(i,j) = A(i, j) + B(i, j);
    }
  }
  return C;
}

Matrix operator-(const Matrix& A, const Matrix& B) {
  assert(A.num_rows() == B.num_rows());
  assert(A.num_cols() == B.num_cols());
  Matrix C(A.num_rows(), A.num_cols());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      C(i,j) = A(i, j) - B(i, j);
    }
  }
  return C;
}

Matrix& operator*=(double alpha, const Matrix& x);
Matrix& operator+=(const Matrix& x, const Matrix& y);
Matrix& operator-=(const Matrix& x, const Matrix& y);



// ----------------------------------------------------------------
//
// Matrix-vector operations
//
// ----------------------------------------------------------------
Vector operator*(const Matrix& A, const Vector& x);
void   matvec(const Matrix& A, const Vector& x, Vector& y);



// ----------------------------------------------------------------
//
// Matrix-matrix operations
//
// ----------------------------------------------------------------
Matrix operator*(const Matrix& A, const Matrix& B);
void   matmat(const Matrix& A, const Vector& B, Matrix& C);


Matrix transpose(const Matrix& A) {
  Matrix B (A.num_cols(), A.num_rows());

  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      B(j, i) = A(i, j);
    }
  }

  return B;
}


void mult_0(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_cols() == C.num_cols());
  assert(A.num_cols() == B.num_rows());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}


// Hoisting
void mult_1(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_cols() == C.num_cols());
  assert(A.num_cols() == B.num_rows());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      double t = C(i, j);
      for (size_t k = 0; k < A.num_cols(); ++k) {
        t += A(i, k) * B(k, j);
      }
      C(i, j) = t;
    }
  }
}


// Hoisting and Tiling
void mult_2(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_cols() == C.num_cols());
  assert(A.num_cols() == B.num_rows());

  for (size_t i = 0; i < C.num_rows(); i += 2) {
    for (size_t j = 0; j < C.num_cols(); j += 2) {

      double t00 = C(i, j);
      double t01 = C(i, j + 1);
      double t10 = C(i + 1, j);
      double t11 = C(i + 1, j + 1);

      for (size_t k = 0; k < A.num_cols(); ++k) {
        t00 += A(i, k) * B(k, j);
        t01 += A(i, k) * B(k, j + 1);
        t10 += A(i + 1, k) * B(k, j);
        t11 += A(i + 1, k) * B(k, j + 1);
      }
      C(i, j)         = t00;
      C(i, j + 1)     = t01;
      C(i + 1, j)     = t10;
      C(i + 1, j + 1) = t11;
    }
  }
}


// Hoisting and Tiling and Blocking
void mult_3(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_cols() == C.num_cols());
  assert(A.num_cols() == B.num_rows());

  size_t blocksize = 32;
  for (size_t ii = 0; ii < C.num_rows(); ii += blocksize) {
    for (size_t jj = 0; jj < C.num_cols(); jj += blocksize) {
      for (size_t kk = 0; kk < A.num_cols(); kk += blocksize) {

        size_t stop_i  = std::min(ii + blocksize, C.num_rows());
        size_t stop_j  = std::min(jj + blocksize, C.num_cols());
        size_t stop_k  = std::min(kk + blocksize, A.num_cols());

        for (size_t i = ii; i < stop_i; i += 2) {
          for (size_t j = jj; j < stop_j; j += 2) {

            double t00 = C(i, j);
            double t01 = C(i, j + 1);
            double t10 = C(i + 1, j);
            double t11 = C(i + 1, j + 1);

            for (size_t k = kk; k < stop_k; ++k) {
              t00 += A(i, k) * B(k, j);
              t01 += A(i, k) * B(k, j + 1);
              t10 += A(i + 1, k) * B(k, j);
              t11 += A(i + 1, k) * B(k, j + 1);
            }

            C(i, j)         = t00;
            C(i, j + 1)     = t01;
            C(i + 1, j)     = t10;
            C(i + 1, j + 1) = t11;
          }
        }
      }
    }
  }
}


void mult_trans_0(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_rows() == C.num_cols());
  assert(A.num_cols() == B.num_cols());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(j, k);
      }
    }
  }
}


void mult_trans_1(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_rows() == C.num_cols());
  assert(A.num_cols() == B.num_cols());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      double t = C(i, j);
      for (size_t k = 0; k < A.num_cols(); ++k) {
        t += A(i, k) * B(j, k);
      }
      C(i, j) = t;
    }
  }
}


void mult_trans_2(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_rows() == C.num_cols());
  assert(A.num_cols() == B.num_cols());

  for (size_t i = 0; i < C.num_rows(); i += 2) {
    for (size_t j = 0; j < C.num_cols(); j += 2) {
      double t00 = C(i, j);
      double t01 = C(i, j + 1);
      double t10 = C(i + 1, j);
      double t11 = C(i + 1, j + 1);

      for (size_t k = 0; k < A.num_cols(); ++k) {
        t00 += A(i, k) * B(j, k);
        t01 += A(i, k) * B(j + 1, k);
        t10 += A(i + 1, k) * B(j, k);
        t11 += A(i + 1, k) * B(j + 1, k);
      }
      C(i, j)         = t00;
      C(i, j + 1)     = t01;
      C(i + 1, j)     = t10;
      C(i + 1, j + 1) = t11;
    }
  }
}


void mult_trans_3(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_rows() == C.num_cols());
  assert(A.num_cols() == B.num_cols());

  size_t blocksize = 32;
  for (size_t ii = 0; ii < C.num_rows(); ii += blocksize) {
    for (size_t jj = 0; jj < C.num_cols(); jj += blocksize) {
      for (size_t kk = 0; kk < A.num_cols(); kk += blocksize) {

        size_t stop_i  = std::min(ii + blocksize, C.num_rows());
        size_t stop_j  = std::min(jj + blocksize, C.num_cols());
        size_t stop_k  = std::min(kk + blocksize, A.num_cols());

        for (size_t i = ii; i < stop_i; i += 2) {
          for (size_t j = jj; j < stop_j; j += 2) {

            double t00 = C(i, j);
            double t01 = C(i, j + 1);
            double t10 = C(i + 1, j);
            double t11 = C(i + 1, j + 1);

            for (size_t k = kk; k < stop_k; ++k) {
              t00 += A(i, k) * B(j, k);
              t01 += A(i, k) * B(j + 1, k);
              t10 += A(i + 1, k) * B(j, k);
              t11 += A(i + 1, k) * B(j + 1, k);
            }

            C(i, j)         = t00;
            C(i, j + 1)     = t01;
            C(i + 1, j)     = t10;
            C(i + 1, j + 1) = t11;
          }
        }
      }
    }
  }
}

void mult_trans_4(const Matrix& A, Matrix& C) {
  assert(A.num_rows() == C.num_rows());

  size_t blocksize = 32;

  for (size_t ii = 0; ii < C.num_rows(); ii += blocksize) {
    for (size_t jj = 0; jj < C.num_cols(); jj += blocksize) {
      for (size_t kk = 0; kk < A.num_cols(); kk += blocksize) {

        size_t stop_i  = std::min(ii + blocksize, C.num_rows());
        size_t stop_j  = std::min(jj + blocksize, C.num_cols());
        size_t stop_k  = std::min(kk + blocksize, A.num_cols());

        for (size_t i = ii; i < stop_i; i += 2) {
          for (size_t j = jj; j < stop_j; j += 2) {
            double t00 = C(i, j);
            double t01 = C(i, j + 1);
            double t10 = C(i + 1, j);
            double t11 = C(i + 1, j + 1);

            for (size_t k = kk; k < stop_k; ++k) {
              t00 += A(i, k) * A(j, k);
              t01 += A(i, k) * A(j + 1, k);
              t10 += A(i + 1, k) * A(j, k);
              t11 += A(i + 1, k) * A(j + 1, k);
            }

            C(i, j)         = t00;
            C(i, j + 1)     = t01;
            C(i + 1, j)     = t10;
            C(i + 1, j + 1) = t11;
	        }
        }
      }
    }
  }
}

void mult_trans_5(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_rows() == C.num_cols());
  assert(A.num_cols() == B.num_cols());

  Matrix test(C.num_rows(), C.num_cols());
  Matrix test2(C.num_rows(), C.num_cols());
  mult_trans_0(A, B, test);
  mult_0(A, B, test2);

  Matrix ret = strassen(A, transpose(B));

  // std::cout << "Trans Mult 0" << std::endl;
  // print(test);
  // std::cout << "Mult 0" << std::endl;
  // print(test2);

  // std::cout << "C strassen w transpose B" << std::endl;
  // print(ret);


  for (int i = 0; i < C.num_rows(); i++) {
    for (int j = 0; j < C.num_cols(); j++) {
        C(i, j) = ret(i, j);
    }
  }
}

// Assumes that A and B are square matrices of power 2.
Matrix strassen(const Matrix& A, const Matrix& B) {
  int n = A.num_rows();
  int LEAF_SIZE = 2;
  Matrix ret(n, n);

  if (n <= LEAF_SIZE) {
    for (size_t i = 0; i < A.num_rows(); ++i) {
      for (size_t j = 0; j < A.num_cols(); ++j) {
        for (size_t k = 0; k < A.num_cols(); ++k) {
          ret(i, j) += A(i, k) * B(k, j);
        }
      }
    }
  }
  else
  {
    int half_size = n / 2;

    Matrix a11(half_size, half_size);
    Matrix a12(half_size, half_size);
    Matrix a21(half_size, half_size);
    Matrix a22(half_size, half_size);

    Matrix b11(half_size, half_size);
    Matrix b12(half_size, half_size);
    Matrix b21(half_size, half_size);
    Matrix b22(half_size, half_size);

    for (int i = 0; i < half_size; i++) {
      for (int j = 0; j < half_size; j++) {
          a11(i, j) = A(i, j);
          a12(i, j) = A(i, j + half_size);
          a21(i, j) = A(i + half_size, j);
          a22(i, j) = A(i + half_size, j + half_size);

          b11(i, j) = B(i, j);
          b12(i, j) = B(i, j + half_size);
          b21(i, j) = B(i + half_size, j);
          b22(i, j) = B(i + half_size, j + half_size);
      }
    }

    // std::cout << "a11" << std::endl;
    // print(a11);

    // std::cout << "a22" << std::endl;
    // print(a22);

    // std::cout << "a11 + a22" << std::endl;

    // print(a11 + a22);

    // std::cout << "b11" << std::endl;
    // print(b11);

    // std::cout << "b22" << std::endl;
    // print(b22);

    // std::cout << "b11 + b22" << std::endl;
    // print(b11 + b22);

    Matrix M1 = strassen(a11 + a22, b11 + b22);

    Matrix M2 = strassen(a21 + a22, b11);
    Matrix M3 = strassen(a11, b12 - b22);
    Matrix M4 = strassen(a22, b21 - b11);
    Matrix M5 = strassen(a11 + a12, b22);
    Matrix M6 = strassen(a21 - a11, b11 + b12);
    Matrix M7 = strassen(a12 - a22, b21 + b22);

    Matrix c11 = M1 + M4 - M5 + M7;
    Matrix c12 = M3 + M5;
    Matrix c21 = M2 + M4;
    Matrix c22 = M1 - M2 + M3 + M6;
    
    for (int i = 0; i < half_size; i++) {
      for (int j = 0; j < half_size; j++) {
          ret(i, j) = c11(i, j);
          ret(i, j + half_size) = c12(i, j);
          ret(i + half_size, j) = c21(i, j);
          ret(i + half_size, j + half_size) = c22(i, j);
      }
    }
  }

  return ret;
}

void print(const Matrix& A) 
{
  for (int i = 0; i < A.num_rows(); i++)
  {
    for (int j = 0; j < A.num_cols(); j++)
    {
      std::cout << A(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}