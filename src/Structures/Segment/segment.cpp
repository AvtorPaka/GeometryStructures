#include "segment.h"
#include "../Vector/vector.h"
#include <vector>

geometry::Segment::Segment(const geometry::Point& point1, const geometry::Point& point2) {
  this->point1_ = point1;
  this->point2_ = point2;
}

geometry::Segment& geometry::Segment::Move(const geometry::Vector& vector) {
  this->point1_.Move(vector);
  this->point2_.Move(vector);
  return *this;
}

std::string geometry::Segment::ToString() const {
  std::string segment_string = "Segment(" + this->point1_.ToString() + ", " + this->point2_.ToString() + ')';
  return segment_string;
}

std::unique_ptr<geometry::IShape> geometry::Segment::Clone() const {
  return std::make_unique<geometry::Segment>(this->point1_, this->point2_);
}

bool geometry::Segment::ContainsPoint(const geometry::Point& point) const {
  return point.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const geometry::Segment& segment) const {
  if (ContainsPoint(segment.point1_) || ContainsPoint(segment.point2_)) {
    return true;
  }
  Point seg_1_a = this->point1_;
  Point seg_1_b = this->point2_;
  Point seg_2_a = segment.point1_;
  Point seg_2_b = segment.point2_;

  int64_t triangle_1 = TriangleArea(seg_1_a, seg_1_b, seg_2_a);
  int64_t triangle_2 = TriangleArea(seg_1_a, seg_1_b, seg_2_b);
  int64_t triangle_3 = TriangleArea(seg_2_a, seg_2_b, seg_1_a);
  int64_t triangle_4 = TriangleArea(seg_2_a, seg_2_b, seg_1_b);
  bool triangle_1_b = ((triangle_1 >= 0 && triangle_2 <= 0) || (triangle_1 <= 0 && triangle_2 >= 0));
  bool triangle_2_b = ((triangle_3 >= 0 && triangle_4 <= 0) || (triangle_3 <= 0 && triangle_4 >= 0));
  return Intersects(seg_1_a.x_, seg_1_b.x_, seg_2_a.x_, seg_2_b.x_) &&
         Intersects(seg_1_a.y_, seg_1_b.y_, seg_2_a.y_, seg_2_b.y_) && triangle_1_b && triangle_2_b;
}

int64_t geometry::Segment::TriangleArea(const geometry::Point& a, const geometry::Point& b, const geometry::Point& c) {
  return (b.x_ - a.x_) * (c.y_ - a.y_) - (b.y_ - a.y_) * (c.x_ - a.x_);
}

bool geometry::Segment::Intersects(int64_t a, int64_t b, int64_t c, int64_t d) {
  if (a > b) {
    Swap(a, b);
  }
  if (c > d) {
    Swap(c, d);
  }
  return std::max(a, c) <= std::min(b, d);
}

void geometry::Segment::Swap(int64_t& x, int64_t& y) {
  int64_t tmp = x;
  x = y;
  y = tmp;
}
