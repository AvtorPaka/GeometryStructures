#ifndef CONTEST_5_SEGMENT_H
#define CONTEST_5_SEGMENT_H

#include "../../Interfaces/IShape.h"
#include "../Point/point.h"
#include <memory>

namespace geometry {
class Segment : public IShape {
 private:
  static void Swap(int64_t& x, int64_t& y);
  static int64_t TriangleArea(const Point& a, const Point& b, const Point& c);
  static bool Intersects(int64_t a, int64_t b, int64_t c, int64_t d);

 public:
  geometry::Point point1_;
  geometry::Point point2_;
  Segment(const Point& point1, const Point& point2);
  Segment& Move(const Vector& vector) override;
  [[nodiscard]] bool ContainsPoint(const Point& point) const override;
  [[nodiscard]] bool CrossesSegment(const Segment& segment) const override;
  [[nodiscard]] std::unique_ptr<IShape> Clone() const override;
  [[nodiscard]] std::string ToString() const override;
};

}  // namespace geometry

#endif
