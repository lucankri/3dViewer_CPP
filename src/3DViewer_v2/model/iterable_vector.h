#ifndef ITERABLEVECTOR_H
#define ITERABLEVECTOR_H
#include <vector>

namespace s21 {
template <typename T>
class IterableVector : public std::vector<T> {
 public:
  IterableVector &operator=(std::vector<T> &&other) {
    if (this != &other) {
      for (auto &element : other) {
        this->push_back(std::move(element));
      }
    }
    return *this;
  }
  class Command {
   public:
    virtual void execute(T &item) = 0;
  };
  void forEach(Command &command) {
    for (T &element : *this) {
      command.execute(element);
    }
  }
};
}  // namespace s21

#endif  // ITERABLEVECTOR_H
