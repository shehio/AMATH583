//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_FNORM_HPP
#define AMATH583_FNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

// Write us
double worker_a(const Vector& x, size_t begin, size_t end) {
  double sum_of_squares = 0.0;
  return sum_of_squares;
}

// Write us
double partitioned_two_norm_a(const Vector& x, size_t partitions) {
  double sum = 0.0;
  return std::sqrt(sum);
}

// Write us
double partitioned_two_norm_b(const Vector& x, size_t partitions) {
  double sum = 0.0;
  return std::sqrt(sum);
}

#endif    // AMATH_583_FNORM_HPP
