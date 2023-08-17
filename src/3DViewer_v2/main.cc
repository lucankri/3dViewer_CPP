#include <QApplication>

#include "view/view.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::Controller* controller = s21::Controller::getInstance();
  s21::View w(controller);
  w.show();
  return a.exec();
}
