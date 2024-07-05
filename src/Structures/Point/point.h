#ifndef CONTEST_5_POINT_H
#define CONTEST_5_POINT_H

#include "../../Interfaces/IShape.h"
#include <memory>

namespace geometry {
class Line;

class Point : public IShape {
 public:
  int64_t x_;
  int64_t y_;
  [[nodiscard]] double GetDistanceToLine(const Line& line) const;
  Point();
  Point(int64_t x, int64_t y);
  geometry::Vector operator-(const Point& other) const;
  Point& Move(const Vector& vector) override;
  [[nodiscard]] bool ContainsPoint(const Point& point) const override;
  [[nodiscard]] bool CrossesSegment(const Segment& segment) const override;
  [[nodiscard]] std::unique_ptr<IShape> Clone() const override;
  [[nodiscard]] std::string ToString() const override;
};
}  // namespace geometry

#endif
