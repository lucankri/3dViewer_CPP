#include "affine_transform_utils.h"

namespace s21 {

void AffineTransformUtils::rotate(const Point &not_rotate_point,
                                  Point &rotate_point, const double &radian_sin,
                                  const double &radian_cos) {
  double temp_x = rotate_point.x;
  double temp_y = rotate_point.y;
  double temp_z = rotate_point.z;
  rotate_point.x =
      ((radian_cos +
        (1 - radian_cos) * not_rotate_point.x * not_rotate_point.x) *
       temp_x) +
      (((1 - radian_cos) * not_rotate_point.x * not_rotate_point.y -
        (radian_sin)*not_rotate_point.z) *
       temp_y) +
      (((1 - radian_cos) * not_rotate_point.x * not_rotate_point.z +
        radian_sin * not_rotate_point.y) *
       temp_z);
  rotate_point.y =
      (((1 - radian_cos) * not_rotate_point.y * not_rotate_point.x +
        radian_sin * not_rotate_point.z) *
       temp_x) +
      ((radian_cos +
        (1 - radian_cos) * not_rotate_point.y * not_rotate_point.y) *
       temp_y) +
      (((1 - radian_cos) * not_rotate_point.y * not_rotate_point.z -
        radian_sin * not_rotate_point.x) *
       temp_z);
  rotate_point.z =
      (((1 - radian_cos) * not_rotate_point.z * not_rotate_point.x -
        radian_sin * not_rotate_point.y) *
       temp_x) +
      (((1 - radian_cos) * not_rotate_point.z * not_rotate_point.y +
        radian_sin * not_rotate_point.x) *
       temp_y) +
      ((radian_cos +
        (1 - radian_cos) * not_rotate_point.z * not_rotate_point.z) *
       temp_z);
}

void AffineTransformUtils::move(Point &point, const Point &vector) {
  point += vector;
}

void AffineTransformUtils::scale(Point &point, const double &scale) {
  point.x *= scale;
  point.y *= scale;
  point.z *= scale;
}
}  // namespace s21
