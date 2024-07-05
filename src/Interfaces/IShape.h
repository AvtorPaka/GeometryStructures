#ifndef CONTEST_5_ISHAPE_H
#define CONTEST_5_ISHAPE_H

#include <iostream>
#include <memory>

namespace geometry {
class Point;
class Segment;
class Vector;

class IShape {
 public:
  virtual IShape& Move(const Vector&) = 0;
  [[nodiscard]] virtual bool ContainsPoint(const Point&) const = 0;
  [[nodiscard]] virtual bool CrossesSegment(const Segment&) const = 0;
  [[nodiscard]] virtual std::unique_ptr<IShape> Clone() const = 0;
  [[nodiscard]] virtual std::string ToString() const = 0;
  virtual ~IShape() = default;
};

}  // namespace geometry

#endif
