#ifndef CONTEST_5_POLYGON_H
#define CONTEST_5_POLYGON_H
#include "../../Interfaces/IShape.h"
#include "../Point/point.h"
#include <vector>
#include <memory>

namespace geometry {
class Polygon : public IShape {
 private:
  std::vector<geometry::Point> points_;

 public:
  explicit Polygon(const std::vector<geometry::Point>& points);
  Polygon& Move(const Vector& vector) override;
  [[nodiscard]] bool ContainsPoint(const Point& point) const override;
  [[nodiscard]] bool CrossesSegment(const Segment& segment) const override;
  [[nodiscard]] std::unique_ptr<IShape> Clone() const override;
  [[nodiscard]] std::string ToString() const override;
};

}  // namespace geometry

#endif
