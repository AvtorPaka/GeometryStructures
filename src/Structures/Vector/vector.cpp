#include <iostream>
#include <cmath>
#include "vector.h"

namespace geometry {

geometry::Vector::Vector(int64_t x, int64_t y) {
  this->x_ = x;
  this->y_ = y;
}

geometry::Vector::Vector() : Vector(0, 0) {
}

geometry::Vector operator+(const geometry::Vector& vec_1, const geometry::Vector& vec_2) {
  return {vec_1.x_ + vec_2.x_, vec_1.y_ + vec_2.y_};
}

geometry::Vector operator+(const geometry::Vector& vec_1) {
  return vec_1;
}

geometry::Vector operator-(const geometry::Vector& vec_1, const geometry::Vector& vec_2) {
  return {vec_1.x_ - vec_2.x_, vec_1.y_ - vec_2.y_};
}

geometry::Vector operator-(const geometry::Vector& vec_1) {
  return {-vec_1.x_, -vec_1.y_};
}

geometry::Vector& operator+=(geometry::Vector& vec_1, const geometry::Vector& vec_2) {
  vec_1.x_ += vec_2.x_;
  vec_1.y_ += vec_2.y_;
  return vec_1;
}

geometry::Vector& operator-=(geometry::Vector& vec_1, const geometry::Vector& vec_2) {
  vec_1.x_ -= vec_2.x_;
  vec_1.y_ -= vec_1.y_;
  return vec_1;
}

geometry::Vector operator*(const geometry::Vector& vec_1, int64_t num) {
  return {vec_1.x_ * num, vec_1.y_ * num};
}

geometry::Vector operator*(int64_t num, const geometry::Vector& vec_1) {
  return {vec_1.x_ * num, vec_1.y_ * num};
}

std::string geometry::Vector::ToString() const {
  std::string vector_string = "Vector(" + std::to_string(this->x_) + ", " + std::to_string(this->y_) + ')';
  return vector_string;
}

geometry::Vector& operator*=(geometry::Vector& vec_1, const int64_t num) {
  vec_1.x_ *= num;
  vec_1.y_ *= num;
  return vec_1;
}

geometry::Vector operator/(const geometry::Vector& vec_1, int64_t num) {
  return {vec_1.x_ / num, vec_1.y_ / num};
}

geometry::Vector& operator/=(geometry::Vector& vec_1, int64_t num) {
  vec_1.x_ /= num;
  vec_1.y_ /= num;
  return vec_1;
}

bool operator==(const geometry::Vector& vec_1, const geometry::Vector& vec_2) {
  return (vec_1.x_ == vec_2.x_ && vec_1.y_ == vec_2.y_);
}

bool operator!=(const geometry::Vector& vec_1, const geometry::Vector& vec_2) {
  return (vec_1.x_ != vec_2.x_ || vec_1.y_ != vec_2.y_);
}

int64_t geometry::Vector::GetXValue() const {
  return this->x_;
}

int64_t geometry::Vector::GetYValue() const {
  return this->y_;
}

double geometry::Vector::GetLength() const {
  return std::sqrt(std::pow(this->x_, 2.0) + std::pow(this->y_, 2.0));
}

int64_t geometry::Vector::ScalarMulti(const geometry::Vector& other) const {
  return this->x_ * other.x_ + this->y_ * other.y_;
}
}  // namespace geometry
