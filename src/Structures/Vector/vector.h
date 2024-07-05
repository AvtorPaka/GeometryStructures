#ifndef CONTEST_5_VECTOR_H
#define CONTEST_5_VECTOR_H

#include <cstdint>
#include <string>

namespace geometry {
class Vector {
 private:
  int64_t x_;
  int64_t y_;

 public:
  Vector(int64_t x, int64_t y);
  Vector();
  [[nodiscard]] std::string ToString() const;
  friend Vector operator+(const Vector& vec_1, const Vector& vec_2);
  friend Vector operator+(const Vector& vec_1);
  friend Vector operator-(const Vector& vec_1, const Vector& vec_2);
  friend Vector operator-(const Vector& vec_1);
  friend Vector& operator+=(Vector& vec_1, const Vector& vec_2);
  friend Vector& operator-=(Vector& vec_1, const Vector& vec_2);
  friend Vector operator*(const Vector& vec_1, int64_t num);
  friend Vector operator*(int64_t num, const Vector& vec_1);
  friend Vector& operator*=(Vector& vec_1, int64_t num);
  friend Vector operator/(const Vector& vec_1, int64_t num);
  friend Vector& operator/=(Vector& vec_1, int64_t num);
  friend bool operator==(const Vector& vec_1, const Vector& vec_2);
  friend bool operator!=(const Vector& vec_1, const Vector& vec_2);
  [[nodiscard]] int64_t GetXValue() const;
  [[nodiscard]] int64_t GetYValue() const;
  [[nodiscard]] double GetLength() const;
  [[nodiscard]] int64_t ScalarMulti(const Vector& other) const;
};

}  // namespace geometry

#endif
