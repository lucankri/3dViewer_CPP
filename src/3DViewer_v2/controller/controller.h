#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "adapter.h"
#include "model/model.h"

namespace s21 {
// данный класс является одиночкой
class Controller {
 public:
  Controller(const Controller &other) = delete;
  Controller &operator=(const Controller &other) = delete;
  ~Controller();
  static Controller *getInstance();
  int loadFile(const std::string &filename);
  std::pair<double *, std::pair<unsigned *, std::size_t>> getData() const;
  void reset();
  double *getV() const;
  const std::pair<std::size_t, std::size_t> &getNumberVF() const;
  void compressShapeAfterParsing(const int &value);
  void rotateX(const int &value);
  void rotateY(const int &value);
  void rotateZ(const int &value);
  void moveX(const int &value);
  void moveY(const int &value);
  void moveZ(const int &value);
  void scale(const int &value);

 private:
  Controller(Model *model);
  Point move_vector_;
  Adapter *adapter_;
  Model *model_;
  static Controller *singleton_;
};
}  // namespace s21

#endif  // CONTROLLER_H
