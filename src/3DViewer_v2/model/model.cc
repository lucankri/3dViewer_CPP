#include "model.h"

namespace s21 {
Model::Model()
    : center_(0, 0, 0),
      position_axis_(0, 0, 0),
      axis_x_(1, 0, 0),
      axis_y_(0, 1, 0),
      axis_z_(0, 0, 1),
      scale_(0) {}

Model *Model::singleton_ = nullptr;
Model *Model::getInstance() {
  if (singleton_ == nullptr) {
    singleton_ = new Model();
  }
  return singleton_;
}

Model::~Model() { delete singleton_; }

Model::MoveCommand::MoveCommand(const Point &vector) : vector_(vector) {}

void Model::MoveCommand::execute(Point &point) {
  AffineTransformUtils::move(point, vector_);
}

int Model::ParseFile(const std::string &filename) {
  Parser::ParserResult result = Parser::parse(filename);
  if (result.error == 0) {
    vertexes_.clear();
    this->vertexes_ = std::move(result.vertexes);
    this->facets_ = std::move(result.facets);
    this->number_v_f_ = result.number_v_f;
    searchMinMax();
    centerShapeAfterParsing();
    default_vertexes_ = vertexes_;
    reset();
  }
  return result.error;
}

void Model::centerShapeAfterParsing() {
  Point center;
  center.x = -(min_max_xyz_.first.x +
               (min_max_xyz_.second.x - min_max_xyz_.first.x) / 2);
  center.y = -(min_max_xyz_.first.y +
               (min_max_xyz_.second.y - min_max_xyz_.first.y) / 2);
  center.z = -(min_max_xyz_.first.z +
               (min_max_xyz_.second.z - min_max_xyz_.first.z) / 2);
  move(center);
  center_.x = center_.y = center_.z = 0;
}

void Model::compressShapeAfterParsing(const double &value_compress) {
  Point max_min_difference;
  max_min_difference.x = min_max_xyz_.second.x - min_max_xyz_.first.x;
  max_min_difference.y = min_max_xyz_.second.y - min_max_xyz_.first.y;
  max_min_difference.z = min_max_xyz_.second.z - min_max_xyz_.first.z;
  double max =
      max3(max_min_difference.x, max_min_difference.y, max_min_difference.z);
  double v_scale = (value_compress - (value_compress * (-1))) / max;
  scale(v_scale);
  scale_ = value_compress;
}

double Model::max3(const double &v1, const double &v2, const double &v3) {
  return (v1 >= v2 && v1 >= v3) ? v1 : (v2 >= v3 ? v2 : v3);
}

void Model::searchMinMax() {
  auto it_begin = vertexes_.begin();
  Point min = *it_begin;
  Point max = *it_begin;
  for (++it_begin; it_begin != vertexes_.end(); ++it_begin) {
    if ((min.x - it_begin->x) > Model::kEPS) min.x = it_begin->x;
    if ((min.y - it_begin->y) > Model::kEPS) min.y = it_begin->y;
    if ((min.z - it_begin->z) > Model::kEPS) min.z = it_begin->z;
    if ((max.x - it_begin->x) < Model::kEPS) max.x = it_begin->x;
    if ((max.y - it_begin->y) < Model::kEPS) max.y = it_begin->y;
    if ((max.z - it_begin->z) < Model::kEPS) max.z = it_begin->z;
  }
  min_max_xyz_.first = min;
  min_max_xyz_.second = max;
}

void Model::move(const Point &vector) {
  MoveCommand moveCommand(vector);
  vertexes_.forEach(moveCommand);
  center_ += vector;
}

void Model::scale(const double &value) {
  Point move_center(-center_.x, -center_.y, -center_.z);
  Point move_back_center(center_.x, center_.y, center_.z);
  for (auto &point : vertexes_) {
    AffineTransformUtils::move(point, move_center);
    AffineTransformUtils::scale(point, value);
    AffineTransformUtils::move(point, move_back_center);
  }
  scale_ = value * scale_;
}

void Model::transform(const double &degree, const Point &axis, Point &axis1,
                      Point &axis2) {
  Point move_center(-center_.x, -center_.y, -center_.z);
  Point move_back_center(center_.x, center_.y, center_.z);
  double rcos = std::cos(degree);
  double rsin = std::sin(degree);
  for (Point &point : vertexes_) {
    AffineTransformUtils::move(point, move_center);
    AffineTransformUtils::rotate(axis, point, rsin, rcos);
    AffineTransformUtils::move(point, move_back_center);
  }
  AffineTransformUtils::rotate(axis, axis1, rsin, rcos);
  AffineTransformUtils::rotate(axis, axis2, rsin, rcos);
}

void Model::rotationX(const double &degree) {
  transform(degree, axis_x_, axis_y_, axis_z_);
  position_axis_.x += degree;
}

void Model::rotationY(const double &degree) {
  transform(degree, axis_y_, axis_x_, axis_z_);
  position_axis_.y += degree;
}

void Model::rotationZ(const double &degree) {
  transform(degree, axis_z_, axis_y_, axis_x_);
  position_axis_.z += degree;
}

const Point &Model::getCenter() const { return center_; }

const Point &Model::getPositionAxis() const { return position_axis_; }

const std::vector<Point> &Model::getVertexes() const { return vertexes_; }

const std::vector<Facet> &Model::getFacets() const { return facets_; }

const std::pair<std::size_t, std::size_t> &Model::getNumberVF() const {
  return number_v_f_;
}

const double &Model::getScale() const { return scale_; }

void Model::reset() {
  vertexes_ = default_vertexes_;
  center_ = Point(0, 0, 0);
  axis_x_ = Point(1, 0, 0);
  axis_y_ = Point(0, 1, 0);
  axis_z_ = Point(0, 0, 1);
  position_axis_ = Point(0, 0, 0);
  scale_ = 0;
}

}  // namespace s21
