#include "ray.h"
#include "../Vector/vector.h"
#include "../Segment/segment.h"
#include <vector>
#include <cmath>

geometry::Ray::Ray(const geometry::Point& point1, const geometry::Point& point2) {
  this->point1_ = point1;
  this->point2_ = point2;
}

geometry::Ray& geometry::Ray::Move(const geometry::Vector& vector) {
  this->point1_.Move(vector);
  this->point2_.Move(vector);
  return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point& point) const {
  Vector vec_1 = (point - this->point1_);
  Vector vec_2 = (this->point2_ - point);
  double first_cf = vec_1.GetYValue() == 0
                        ? INT32_MAX / 2
                        : std::abs(static_cast<double>(vec_1.GetXValue()) / (double)(1.0 * vec_1.GetYValue()));
  double second_cf = vec_2.GetYValue() == 0
                         ? INT32_MAX / 2
                         : std::abs(static_cast<double>(vec_2.GetXValue()) / (double)(1.0 * vec_2.GetYValue()));
  Vector dir_vector = this->point2_ - this->point1_;
  bool isOneWay = (Sign(dir_vector.GetXValue()) == Sign(vec_1.GetXValue()) &&
                   Sign(dir_vector.GetYValue()) == Sign(vec_1.GetYValue()));
  geometry::Vector nullVector = Vector();
  return (first_cf == second_cf && isOneWay) || (vec_1 == nullVector || vec_2 == nullVector);
}

bool geometry::Ray::CrossesSegment(const geometry::Segment& segment) const {
  Vector cur_segment_vector = (this->point2_ - this->point1_);
  int64_t factor_for_max_1;

  if (cur_segment_vector.GetXValue() == 0) {
    factor_for_max_1 = (INT32_MAX - point2_.y_) / cur_segment_vector.GetYValue();
  } else if (cur_segment_vector.GetYValue() == 0) {
    factor_for_max_1 = (INT32_MAX - point2_.x_) / cur_segment_vector.GetXValue();
  } else if (cur_segment_vector.GetXValue() > 0) {
    factor_for_max_1 = std::min((INT32_MAX - point2_.x_) / cur_segment_vector.GetXValue(),
                                (INT32_MAX - point2_.y_) / cur_segment_vector.GetYValue());
  } else {
    factor_for_max_1 = -1 * std::max((point2_.x_ - INT32_MAX) / cur_segment_vector.GetXValue(),
                                     (point2_.y_ - INT32_MAX) / cur_segment_vector.GetYValue());
  }

  if (cur_segment_vector.GetYValue() <= 0) {
    factor_for_max_1 = (factor_for_max_1 + 100) * -1;
  }
  Point new_point_2(this->point2_.x_ + cur_segment_vector.GetXValue() * factor_for_max_1,
                    this->point2_.y_ + cur_segment_vector.GetYValue() * factor_for_max_1);
  Segment around_infinite_segment(this->point1_, new_point_2);
  return around_infinite_segment.CrossesSegment(segment);
}

std::unique_ptr<geometry::IShape> geometry::Ray::Clone() const {
  return std::make_unique<geometry::Ray>(this->point1_, this->point2_);
}

std::string geometry::Ray::ToString() const {
  std::string ray_string = "Ray(" + this->point1_.ToString() + ", " + (this->point2_ - this->point1_).ToString() + ')';
  return ray_string;
}

int32_t geometry::Ray::Sign(int64_t num) {
  if (num <= 0) {
    return -1;
  }
  return 1;
}
