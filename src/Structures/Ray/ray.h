#ifndef CONTEST_5_RAY_H
#define CONTEST_5_RAY_H

#include "../../Interfaces/IShape.h"
#include "../Point/point.h"
#include <memory>

namespace geometry {
class Ray : public IShape {
 private:
  geometry::Point point1_;
  geometry::Point point2_;
  static int32_t Sign(int64_t num);

 public:
  Ray(const Point& point1, const Point& point2);
  Ray& Move(const Vector& vector) override;
  [[nodiscard]] bool ContainsPoint(const Point& point) const override;
  [[nodiscard]] bool CrossesSegment(const Segment& segment) const override;
  [[nodiscard]] std::unique_ptr<IShape> Clone() const override;
  [[nodiscard]] std::string ToString() const override;
};

}  // namespace geometry

#endif
