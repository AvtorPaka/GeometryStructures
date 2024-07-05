#include "polygon.h"
#include "../Segment/segment.h"
#include "../Ray/ray.h"
#include <vector>
#include <cmath>

geometry::Polygon::Polygon(const std::vector<geometry::Point>& points) {
  this->points_ = points;
}

geometry::Polygon& geometry::Polygon::Move(const geometry::Vector& vector) {
  size_t n = this->points_.size();
  for (uint i = 0; i < n; ++i) {
    this->points_[i].Move(vector);
  }
  return *this;
}

bool geometry::Polygon::ContainsPoint(const geometry::Point& point) const {
  std::vector<geometry::Point> polygon_points = this->points_;
  size_t n = polygon_points.size();
  if (n == 1) {
    return point.ContainsPoint(polygon_points[0]);
  }
  Point random_middle_point(INT32_MAX / 4, point.y_ + 1);
  geometry::Ray random_ray(point, random_middle_point);

  int32_t cnt = 0;
  for (uint32_t i = 0; i < n; ++i) {
    Point cur_point_1 = polygon_points[i];
    if (cur_point_1.ContainsPoint(point)) {
      return true;
    }
    Point cur_point_2 = polygon_points[(i + 1) % n];
    Segment cur_segment(cur_point_1, cur_point_2);
    if (cur_segment.ContainsPoint(point)) {
      return true;
    }
    if (random_ray.CrossesSegment(cur_segment)) {
      ++cnt;
    }
  }

  return (cnt % 2 == 1);
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment& segment) const {
  size_t n = this->points_.size();
  for (uint32_t i = 0; i < n; ++i) {
    Segment cur_segment(this->points_[i], this->points_[(i + 1) % n]);
    if (segment.CrossesSegment(cur_segment)) {
      return true;
    }
  }
  return false;
}

std::unique_ptr<geometry::IShape> geometry::Polygon::Clone() const {
  return std::make_unique<geometry::Polygon>(this->points_);
}

std::string geometry::Polygon::ToString() const {
  std::string polygon_string = "Polygon(";
  size_t n = this->points_.size();
  for (uint i = 0; i < n; ++i) {
    polygon_string += this->points_[i].ToString() + (i == n - 1 ? ")" : ", ");
  }
  return polygon_string;
}
