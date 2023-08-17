#ifndef INC_3DVIEWER_CPP_AFFINE_TRANSFORM_UTILS_H
#define INC_3DVIEWER_CPP_AFFINE_TRANSFORM_UTILS_H
#include <cmath>

#include "point.h"

namespace s21 {

class AffineTransformUtils {
 public:
  static void rotate(const Point &not_rotate_point, Point &rotate_point,
                     const double &radian_sin, const double &radian_cos);
  static void move(Point &point, const Point &vector);
  static void scale(Point &point, const double &scale);
};

}  // namespace s21

#endif  // INC_3DVIEWER_CPP_AFFINE_TRANSFORM_UTILS_H
