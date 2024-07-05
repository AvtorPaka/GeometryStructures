#include "point.h"
#include "../Vector/vector.h"
#include "../Segment/segment.h"
#include "../Line/line.h"
#include <string>
#include <cmath>

namespace geometry {

Point::Point(int64_t x, int64_t y) {
  this->x_ = x;
  this->y_ = y;
}

Point::Point() : Point(0, 0) {
}

Vector geometry::Point::operator-(const geometry::Point& other) const {
  return {this->x_ - other.x_, this->y_ - other.y_};
}

Point& geometry::Point::Move(const geometry::Vector& vector) {
  this->x_ += vector.GetXValue();
  this->y_ += vector.GetYValue();
  return *this;
}

bool Point::ContainsPoint(const geometry::Point& point) const {
  return (this->x_ == point.x_ && this->y_ == point.y_);
}

bool Point::CrossesSegment(const geometry::Segment& segment) const {
  Vector vec_1 = *this - segment.point1_;
  Vector vec_2 = segment.point2_ - *this;
  double_t first_cf = vec_1.GetYValue() == 0
                          ? INT32_MAX / 2
                          : static_cast<double>(vec_1.GetXValue()) / (double)(1.0 * vec_1.GetYValue());
  double_t second_cf = vec_2.GetYValue() == 0
                           ? INT32_MAX / 2
                           : static_cast<double>(vec_2.GetXValue()) / (double)(1.0 * vec_2.GetYValue());
  bool oneSignX =
      (vec_1.GetXValue() >= 0 && vec_2.GetXValue() >= 0) || (vec_1.GetXValue() <= 0 && vec_2.GetXValue() <= 0);
  bool oneSignY =
      (vec_1.GetYValue() >= 0 && vec_2.GetYValue() >= 0) || (vec_1.GetYValue() <= 0 && vec_2.GetYValue() <= 0);
  geometry::Vector nullVector = Vector();
  return (first_cf == second_cf && oneSignX && oneSignY) || (vec_1 == nullVector || vec_2 == nullVector);
}

std::unique_ptr<geometry::IShape> Point::Clone() const {
  return std::make_unique<geometry::Point>(this->x_, this->y_);
}

std::string Point::ToString() const {
  std::string string_point = "Point(" + std::to_string(this->x_) + ", " + std::to_string(this->y_) + ")";
  return string_point;
}

double Point::GetDistanceToLine(const geometry::Line& line) const {
  std::vector<int64_t> segment_coefs;
  line.GetEquationCoef(segment_coefs);
  return std::abs(segment_coefs[0] * this->x_ + segment_coefs[1] * this->y_ + segment_coefs[2]) /
         std::sqrt(std::pow(segment_coefs[0], 2.0) + std::pow(segment_coefs[1], 2.0));
}
}  // namespace geometry
