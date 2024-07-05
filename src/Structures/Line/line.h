#ifndef CONTEST_5_LINE_H
#define CONTEST_5_LINE_H

#include "../../Interfaces/IShape.h"
#include "../Point/point.h"
#include <vector>
#include <memory>

namespace geometry {
class Line : public IShape {
 private:
  geometry::Point point1_;
  geometry::Point point2_;

 public:
  void GetEquationCoef(std::vector<int64_t>& vector_to_fill) const;
  Line(const Point& point1, const Point& point2);
  Line& Move(const Vector& vector) override;
  [[nodiscard]] bool ContainsPoint(const Point& point) const override;
  [[nodiscard]] bool CrossesSegment(const Segment& segment) const override;
  [[nodiscard]] std::unique_ptr<IShape> Clone() const override;
  [[nodiscard]] std::string ToString() const override;
};

}  // namespace geometry

#endif
