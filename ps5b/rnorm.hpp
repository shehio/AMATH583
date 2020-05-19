//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_RNORM_HPP
#define AMATH583_RNORM_HPP

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

// Useful utility function for computing sum_of_squares over a range of a vector
double sum_of_squares(const Vector& x, size_t begin, size_t end) {
  double sum = 0.0;
  for (size_t i = begin; i < end; ++i) {
    sum += x(i) * x(i);
  }
  return sum;
}

double recursive_worker(const Vector& x, size_t begin, size_t end, size_t level, std::launch launch_policy)
{
  // Decided based on empircal evidence.
  if (level == 0)
  {
    return sum_of_squares(x, begin, end);
  }

  double sum = 0.0;
  std::vector<std::future<double>> futures;
  futures.push_back(std::async(launch_policy, recursive_worker, std::cref(x), begin, (begin + end) / 2, level - 1, launch_policy));
  futures.push_back(std::async(launch_policy, recursive_worker, std::cref(x), (begin + end) / 2, end, level - 1, launch_policy));

  for (size_t i = 0; i < futures.size(); ++i)
  {
    sum += futures[i].get();
  }

  return sum;
}

// Dispatch to the actual recursive function -- start with 0 and num_rows() as begin and end
double recursive_two_norm_a(const Vector& x, size_t levels) {
  double sum = recursive_worker(std::cref(x), 0, x.num_rows(), levels, std::launch::async);
  return std::sqrt(sum);
}

// Dispatch to the actual recursive function -- start with 0 and num_rows() as begin and end
double recursive_two_norm_b(const Vector& x, size_t levels) {
  double sum = recursive_worker(std::cref(x), 0, x.num_rows(), levels, std::launch::deferred);
  return std::sqrt(sum);
}

#endif    // AMATH583_RNORM_HPP
