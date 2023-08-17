#include "controller.h"

namespace s21 {
Controller::Controller(Model *model) : model_(model), adapter_(new Adapter) {}

Controller::~Controller() {
  delete adapter_;
  delete singleton_;
}

Controller *Controller::singleton_ = nullptr;
Controller *Controller::getInstance() {
  if (Controller::singleton_ == nullptr) {
    singleton_ = new Controller(Model::getInstance());
  }
  return singleton_;
}

int Controller::loadFile(const std::string &filename) {
  return model_->ParseFile(filename);
}

std::pair<double *, std::pair<unsigned *, std::size_t>> Controller::getData()
    const {
  const std::pair<std::size_t, std::size_t> number_vf = model_->getNumberVF();
  return {getV(), adapter_->adoptFacets(model_->getFacets(), number_vf.second)};
}

void Controller::reset() { model_->reset(); }

double *Controller::getV() const {
  const std::size_t number_v = model_->getNumberVF().first;
  return adapter_->adoptPoints(model_->getVertexes(), number_v);
}

const std::pair<std::size_t, std::size_t> &Controller::getNumberVF() const {
  return model_->getNumberVF();
}

void Controller::compressShapeAfterParsing(const int &value) {
  model_->compressShapeAfterParsing((double)value / 100);
}

void Controller::rotateX(const int &value) {
  model_->rotationX(((double)value / 100) - model_->getPositionAxis().x);
}

void Controller::rotateY(const int &value) {
  model_->rotationY(((double)value / 100) - model_->getPositionAxis().y);
}

void Controller::rotateZ(const int &value) {
  model_->rotationZ(((double)value / 100) - model_->getPositionAxis().z);
}

void Controller::moveX(const int &value) {
  double d_value = (double)value / 100;
  move_vector_.x = d_value - model_->getCenter().x;
  move_vector_.y = 0;
  move_vector_.z = 0;
  model_->move(move_vector_);
}

void Controller::moveY(const int &value) {
  double d_value = (double)value / 100;
  move_vector_.x = 0;
  move_vector_.y = d_value - model_->getCenter().y;
  move_vector_.z = 0;
  model_->move(move_vector_);
}

void Controller::moveZ(const int &value) {
  double d_value = (double)value / 100;
  move_vector_.x = 0;
  move_vector_.y = 0;
  move_vector_.z = d_value - model_->getCenter().z;
  model_->move(move_vector_);
}

void Controller::scale(const int &value) {
  model_->scale(((double)value / 100) / model_->getScale());
}

}  // namespace s21
