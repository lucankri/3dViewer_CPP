#ifndef INC_3DVIEWER_CPP_MODEL_H
#define INC_3DVIEWER_CPP_MODEL_H
#include <cmath>

#include "affine_transform_utils.h"
#include "iterable_vector.h"
#include "parser.h"

namespace s21 {
// данный класс является одиночкой
class Model {
 public:
  Model(const Model &other) = delete;
  Model &operator=(const Model &other) = delete;
  static Model *getInstance();
  ~Model();
  int ParseFile(const std::string &filename);
  void rotationX(const double &degree);
  void rotationY(const double &degree);
  void rotationZ(const double &degree);
  void move(const Point &vector);
  void scale(const double &value);
  void compressShapeAfterParsing(const double &value_compress);
  const Point &getCenter() const;
  const Point &getPositionAxis() const;
  const std::vector<Point> &getVertexes() const;
  const std::vector<Facet> &getFacets() const;
  const std::pair<std::size_t, std::size_t> &getNumberVF() const;
  const double &getScale() const;
  void reset();

 private:
  Model();
  void searchMinMax();
  void centerShapeAfterParsing();
  static double max3(const double &value1, const double &value2,
                     const double &value3);
  void transform(const double &degree, const Point &axis, Point &axis1,
                 Point &axis2);
  std::pair<Point, Point> min_max_xyz_;
  Point center_, position_axis_, axis_x_, axis_y_, axis_z_;
  double scale_;
  std::pair<std::size_t, std::size_t> number_v_f_;
  IterableVector<Point> vertexes_, default_vertexes_;
  std::vector<Facet> facets_;
  static Model *singleton_;
  static constexpr double kEPS = 1e-6;
  class MoveCommand : public IterableVector<Point>::Command {
   public:
    MoveCommand(const Point &vector);
    void execute(Point &point) override;

   private:
    const Point &vector_;
  };
};

}  // namespace s21

#endif  // INC_3DVIEWER_CPP_MODEL_H
