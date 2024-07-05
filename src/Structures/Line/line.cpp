#include "line.h"
#include "../Vector/vector.h"
#include "../Segment/segment.h"
#include <vector>

geometry::Line::Line(const geometry::Point& point1, const geometry::Point& point2) {
  this->point1_ = point1;
  this->point2_ = point2;
}

geometry::Line& geometry::Line::Move(const geometry::Vector& vector) {
  this->point1_.Move(vector);
  this->point2_.Move(vector);
  return *this;
}

bool geometry::Line::ContainsPoint(const geometry::Point& point) const {
  Vector vec_1 = (point - this->point1_);
  Vector vec_2 = (this->point2_ - point);
  double first_cf = vec_1.GetYValue() == 0 ? INT32_MAX / 2
                                           : static_cast<double>(vec_1.GetXValue()) / (double)(1.0 * vec_1.GetYValue());
  double second_cf = vec_2.GetYValue() == 0
                         ? INT32_MAX / 2
                         : static_cast<double>(vec_2.GetXValue()) / (double)(1.0 * vec_2.GetYValue());
  geometry::Vector nullVector = Vector();
  return (first_cf == second_cf) || (vec_1 == nullVector || vec_2 == nullVector);
}

std::unique_ptr<geometry::IShape> geometry::Line::Clone() const {
  return std::make_unique<geometry::Line>(this->point1_, this->point2_);
}

std::string geometry::Line::ToString() const {
  std::vector<int64_t> coefs;
  coefs.reserve(3);
  GetEquationCoef(coefs);
  std::string line_string = "Line(";
  for (uint32_t i = 0; i < 3; ++i) {
    line_string += std::to_string(coefs[i]) + (i == 2 ? ")" : ", ");
  }
  return line_string;
}

bool geometry::Line::CrossesSegment(const geometry::Segment& segment) const {
  Vector cur_segment_vector = (this->point1_ - this->point2_);

  int64_t factor_for_max_1;
  int64_t factor_for_min_2;
  if (cur_segment_vector.GetXValue() == 0) {
    factor_for_max_1 = (INT32_MAX - this->point1_.y_) / cur_segment_vector.GetYValue();
    factor_for_min_2 = (this->point2_.y_ - INT32_MAX) / cur_segment_vector.GetYValue();
  } else if (cur_segment_vector.GetYValue() == 0) {
    factor_for_max_1 = (INT32_MAX - this->point1_.x_) / cur_segment_vector.GetXValue();
    factor_for_min_2 = (this->point2_.x_ - INT32_MAX) / cur_segment_vector.GetXValue();
  } else {
    factor_for_max_1 = std::min((INT32_MAX - this->point1_.x_) / cur_segment_vector.GetXValue(),
                                (INT32_MAX - this->point1_.y_) / cur_segment_vector.GetYValue());
    factor_for_min_2 = std::max((this->point2_.x_ - INT32_MAX) / cur_segment_vector.GetXValue(),
                                (this->point2_.y_ - INT32_MAX) / cur_segment_vector.GetYValue());
  }

  Point new_point_1(this->point1_.x_ + cur_segment_vector.GetXValue() * factor_for_max_1,
                    this->point1_.y_ + cur_segment_vector.GetYValue() * factor_for_max_1);
  Point new_point_2(this->point2_.x_ + cur_segment_vector.GetXValue() * factor_for_min_2,
                    this->point2_.y_ + cur_segment_vector.GetYValue() * factor_for_min_2);
  Segment around_infinite_segment(new_point_1, new_point_2);
  return around_infinite_segment.CrossesSegment(segment);
}

void geometry::Line::GetEquationCoef(std::vector<int64_t>& vector_to_fill) const {
  Vector dir_vector = (this->point2_ - this->point1_);
  vector_to_fill.push_back(dir_vector.GetYValue());
  vector_to_fill.push_back(-dir_vector.GetXValue());
  vector_to_fill.push_back(this->point1_.y_ * dir_vector.GetXValue() - this->point1_.x_ * dir_vector.GetYValue());
}
