#ifndef CONTEST_5_CIRCLE_H
#define CONTEST_5_CIRCLE_H

#include "../../Interfaces/IShape.h"
#include "../Point/point.h"
#include <memory>

namespace geometry {
class Circle : public IShape {
 private:
  geometry::Point center_;
  int64_t radius_;

 public:
  Circle(const Point& point, int64_t num);
  Circle& Move(const Vector& vector) override;
  [[nodiscard]] bool ContainsPoint(const Point& point) const override;
  [[nodiscard]] bool CrossesSegment(const Segment& segment) const override;
  [[nodiscard]] std::unique_ptr<IShape> Clone() const override;
  [[nodiscard]] std::string ToString() const override;
};

}  // namespace geometry

#endif
