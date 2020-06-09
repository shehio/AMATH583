//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_GRID_HPP
#define AMATH583_GRID_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class Grid {

public:
  explicit Grid(size_t x, size_t y) : x_points_(x + 2), y_points_(y + 2), storage_(x_points_ * y_points_) {}
  explicit Grid(size_t x, size_t y, double init) : x_points_(x + 2), y_points_(y + 2), storage_(x_points_ * y_points_, init) {}

  double&       operator()(size_t i, size_t j) { return storage_[i * y_points_ + j]; }
  const double& operator()(size_t i, size_t j) const { return storage_[i * y_points_ + j]; }

  size_t num_x() const { return x_points_; }
  size_t num_y() const { return y_points_; }

  void swap(Grid& x) {
    std::swap(x.x_points_, x_points_);
    std::swap(x.y_points_, y_points_);
    storage_.swap(x.storage_);
  }

  void operator=(const Grid& x) {
    assert(x.x_points_ == x_points_ && x.y_points_ == y_points_);
    std::copy(x.storage_.begin(), x.storage_.end(), storage_.begin());
  }

private:
  size_t              x_points_, y_points_;
  std::vector<double> storage_;
};

Grid operator-(const Grid& X, const Grid& Y) {
  Grid Z(X);
  for (size_t i = 0; i < Z.num_x(); ++i) {
    for (size_t j = 0; j < Z.num_y(); ++j) {
      Z(i, j) = X(i, j) - Y(i, j);
    }
  }
  return Z;
}

Grid operator+(const Grid& X, const Grid& Y) {
  Grid Z(X);
  for (size_t i = 0; i < Z.num_x(); ++i) {
    for (size_t j = 0; j < Z.num_y(); ++j) {
      Z(i, j) = X(i, j) + Y(i, j);
    }
  }
  return Z;
}

void operator+=(Grid& Z, const Grid& X) {
  for (size_t i = 0; i < Z.num_x(); ++i) {
    for (size_t j = 0; j < Z.num_y(); ++j) {
      Z(i, j) += X(i, j);
    }
  }
}

void operator-=(Grid& Z, const Grid& X) {
  for (size_t i = 0; i < Z.num_x(); ++i) {
    for (size_t j = 0; j < Z.num_y(); ++j) {
      Z(i, j) -= X(i, j);
    }
  }
}

Grid operator*(double a, const Grid& Y) {
  Grid Z(Y);
  for (size_t i = 1; i < Z.num_x() - 1; ++i) {
    for (size_t j = 1; j < Z.num_y() - 1; ++j) {
      Z(i, j) = a * Y(i, j);
    }
  }
  return Z;
}

double dot(const Grid& X, const Grid& Y) {
  double sum = 0.0;
  for (size_t i = 0; i < X.num_x(); ++i) {
    for (size_t j = 0; j < X.num_y(); ++j) {
      sum += X(i, j) * Y(i, j);
    }
  }
  return sum;
}

void swap(Grid& x, Grid& y) { x.swap(y); }

#endif    // AMATH583_GRID_HPP
