#ifndef INC_3DVIEWER_CPP_POINT_H
#define INC_3DVIEWER_CPP_POINT_H

namespace s21 {

class Point {
 public:
  Point() = default;
  Point(const double &x, const double &y, const double &z) : x(x), y(y), z(z) {}
  Point &operator+=(const Point &point) {
    this->x += point.x;
    this->y += point.y;
    this->z += point.z;
    return *this;
  }

  double x, y, z;
};

}  // namespace s21

#endif  // INC_3DVIEWER_CPP_POINT_H
