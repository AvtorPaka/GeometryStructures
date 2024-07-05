#include "circle.h"
#include "../Vector/vector.h"
#include "../Segment/segment.h"
#include "../Line/line.h"
#include <cmath>

geometry::Circle::Circle(const geometry::Point& point, int64_t num) {
  this->center_ = point;
  this->radius_ = num;
}

geometry::Circle& geometry::Circle::Move(const geometry::Vector& vector) {
  this->center_.Move(vector);
  return *this;
}

bool geometry::Circle::ContainsPoint(const geometry::Point& point) const {
  return ((this->center_ - point).GetLength() <= this->radius_);
}

bool geometry::Circle::CrossesSegment(const geometry::Segment& segment) const {
  Point point_1 = segment.point1_;
  Point point_2 = segment.point2_;
  double distance_to_segment;

  if (segment.ContainsPoint(this->center_)) {
    return true;
  }
  bool isActuallyCrosses = false;
  Vector segment_vec_1 = (point_2 - point_1);
  Vector segment_vec_2 = segment_vec_1 * -1;
  Vector vector_1 = (this->center_ - point_1);
  Vector vector_2 = (this->center_ - point_2);

  if (segment_vec_1.ScalarMulti(vector_1) <= 0 || segment_vec_2.ScalarMulti(vector_2) <= 0) {
    distance_to_segment = segment_vec_1.ScalarMulti(vector_1) <= 0 ? vector_1.GetLength() : vector_2.GetLength();

    geometry::Line segment_line(segment.point1_, segment.point2_);
    double distance_to_segment_line = this->center_.GetDistanceToLine(segment_line);
    double big_part = std::sqrt(std::pow(radius_, 2.0) - std::pow(distance_to_segment_line, 2.0));
    double small_part = std::sqrt(std::pow(distance_to_segment, 2.0) - std::pow(distance_to_segment_line, 2.0));

    isActuallyCrosses = (segment_vec_1.GetLength() >= big_part - small_part);
  } else {
    geometry::Line segment_line(segment.point1_, segment.point2_);
    distance_to_segment = this->center_.GetDistanceToLine(segment_line);
    isActuallyCrosses =
        (2 * std::sqrt(std::pow(radius_, 2.0) - std::pow(distance_to_segment, 2.0)) <= segment_vec_1.GetLength());
  }

  if (vector_1.GetLength() == this->radius_ || vector_2.GetLength() == this->radius_) {
    return true;
  }

  return (distance_to_segment <= this->radius_) && isActuallyCrosses;
}

std::unique_ptr<geometry::IShape> geometry::Circle::Clone() const {
  return std::make_unique<geometry::Circle>(this->center_, this->radius_);
}

std::string geometry::Circle::ToString() const {
  std::string circle_string = "Circle(" + this->center_.ToString() + ", " + std::to_string(this->radius_) + ')';
  return circle_string;
}
