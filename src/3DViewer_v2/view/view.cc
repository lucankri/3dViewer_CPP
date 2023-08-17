#include "view.h"

#include "./ui_view.h"

namespace s21 {

View::View(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      widget_(new QOGLWidget),
      controller_(controller),
      ui(new Ui::View),
      counter_(0.0),
      error_(0),
      settings_flag_(0),
      timer_(new QTimer(this)) {
  ui->setupUi(this);
  ui->gridLayout_1->addWidget(widget_, 0, 0);
  ui->statusbar->setStyleSheet("color: rgb(221, 231, 220); font-size: 14px;");
  ui->toolBox->setCurrentIndex(0);
  makeStyleSheets(ui->ButtonEdgesColor, widget_->edgesColor);
  makeStyleSheets(ui->ButtonVerticesColor, widget_->vertexColor);
  makeStyleSheets(ui->ButtonBackgroundColor, widget_->bgColor);
  ui->edges_type->setCurrentIndex(widget_->edgesType);
  ui->edges_size->setValue(widget_->edgesThick);
  ui->vertex_type->setCurrentIndex(widget_->vertexType);
  ui->vertex_size->setValue(widget_->vertexSize);
  ui->projection_type->setCurrentIndex(widget_->projectionType);
  connect(ui->create_gif, SIGNAL(clicked()), this, SLOT(create_gif()));
  connect(timer_, SIGNAL(timeout()), this, SLOT(take_screen()));
}

View::~View() {
  delete timer_;
  delete widget_;
  delete ui;
}

void View::keyPressEvent(QKeyEvent *event) {
  int value = 0;
  if (event->key() == Qt::Key_W) {
    ui->slider_move_y->setValue(ui->slider_move_y->value() + 4);
  } else if (event->key() == Qt::Key_S) {
    ui->slider_move_y->setValue(ui->slider_move_y->value() - 4);
  } else if (event->key() == Qt::Key_A) {
    ui->slider_move_x->setValue(ui->slider_move_x->value() - 4);
  } else if (event->key() == Qt::Key_D) {
    ui->slider_move_x->setValue(ui->slider_move_x->value() + 4);
  } else if (event->key() == Qt::Key_Z) {
    ui->slider_move_z->setValue(ui->slider_move_z->value() - 4);
  } else if (event->key() == Qt::Key_X) {
    ui->slider_move_z->setValue(ui->slider_move_z->value() + 4);
  }
}

void View::wheelEvent(QWheelEvent *event) {
  int offset = 0;
  if (event->angleDelta().y() > 0) {
    offset = 8;
  } else if (event->angleDelta().y() < 0) {
    offset = -8;
  }
  ui->slider_scale->setValue(ui->slider_scale->value() + offset);
}

void View::on_OpenFile_clicked() {
  if (settings_flag_ == 0) {
    filename_ = QFileDialog::getOpenFileName(this, "Upload a file",
                                             QDir::homePath(), "*.obj");
  }
  if (!filename_.isEmpty()) {
    resetSliders();
    widget_->clearWidgetData();
    int error = controller_->loadFile(filename_.toStdString());
    QString status_message;
    if (error == 0) {
      controller_->compressShapeAfterParsing(ui->slider_scale->value());
      widget_->data = controller_->getData();
      QString str_number_v = QString::number(controller_->getNumberVF().first);
      QString str_number_f = QString::number(controller_->getNumberVF().second);
      status_message = "File name: " + filename_ +
                       "      |      V: " + str_number_v +
                       "      |      F: " + str_number_f;
      ui->statusbar->showMessage(status_message);
      if (settings_flag_ == 0) {
        widget_->update();
      }
    } else if (error == 1) {
      status_message = "File name: file not found...";
      ui->statusbar->showMessage(status_message);
    } else if (error == 2) {
      status_message =
          "File name: " + filename_ + "      |      Incorrect file format...";
      ui->statusbar->showMessage(status_message);
    }
  }
}

void View::newData() {
  delete[] widget_->data.first;
  widget_->data.first = controller_->getV();
  widget_->update();
}

void View::on_reset_clicked() {
  resetSliders();
  controller_->reset();
  controller_->compressShapeAfterParsing(ui->slider_scale->value());
  delete[] widget_->data.first;
  widget_->data.first = controller_->getV();
  widget_->update();
}

void View::resetSliders() {
  ui->slider_move_x->setValue(0);
  ui->slider_move_y->setValue(0);
  ui->slider_move_z->setValue(0);
  ui->slider_rotate_x->setValue(0);
  ui->slider_rotate_y->setValue(0);
  ui->slider_rotate_z->setValue(0);
  ui->slider_scale->setValue(50);
}

void View::on_slider_scale_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->scale(value);
  newData();
}

void View::on_slider_move_x_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->moveX(value);
  newData();
}

void View::on_slider_move_y_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->moveY(value);
  newData();
}

void View::on_slider_move_z_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->moveZ(value);
  newData();
}

void View::on_slider_rotate_x_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->rotateX(value);
  newData();
}

void View::on_slider_rotate_y_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->rotateY(value);
  newData();
}

void View::on_slider_rotate_z_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  controller_->rotateZ(value);
  newData();
}

// Смена цвета ребер
void View::on_ButtonEdgesColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    widget_->edgesColor = color;
    makeStyleSheets(ui->ButtonEdgesColor, color);
    widget_->update();
  }
}

// Смена цвета точек
void View::on_ButtonVerticesColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    widget_->vertexColor = color;
    makeStyleSheets(ui->ButtonVerticesColor, color);
    widget_->update();
  }
}

// Смена цвета фона
void View::on_ButtonBackgroundColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    widget_->bgColor = color;
    makeStyleSheets(ui->ButtonBackgroundColor, color);
    widget_->update();
  }
}

// Смена типа ребер
void View::on_edges_type_currentIndexChanged(int index) {
  widget_->edgesType = index;
  widget_->update();
}

// Смена толщины ребер
void View::on_edges_size_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  widget_->edgesThick = value;
  widget_->update();
}

// Смена типа точек
void View::on_vertex_type_currentIndexChanged(int index) {
  widget_->vertexType = index;
  widget_->update();
}

// Смена толщины точек
void View::on_vertex_size_valueChanged(int value) {
  QToolTip::showText(QCursor::pos(), QString("%1").arg(value));
  widget_->vertexSize = value;
  widget_->update();
}

// Смена типа проекции
void View::on_projection_type_currentIndexChanged(int index) {
  widget_->projectionType = index;
  widget_->update();
}

// Изменение цвета кнопки под выбранный цвет
void View::makeStyleSheets(QPushButton *btn, QColor clr) {
  QString style = "border-radius: 8px; background-color: rgb(" +
                  QString::number(clr.red()) + "," +
                  QString::number(clr.green()) + "," +
                  QString::number(clr.blue()) + ");";
  btn->setStyleSheet(style);
}

// Сохранение изображения
void View::on_save_file_clicked() {
  QString save_picture = NULL;
  save_picture = QFileDialog::getSaveFileName(this, NULL, NULL,
                                              "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!save_picture.isNull())
    widget_->grabFramebuffer().save(save_picture, NULL, 100);
}

// Запись гифки
void View::create_gif() {
  gif_changeStyleRed();
  timer_->start(100);
  take_screen();
  counter_ = 0.0;
}

// Захват изображений
void View::take_screen() {
  if (counter_ <= 5.0) {
    gif_.push_back(widget_->grabFramebuffer());
    counter_ += 0.1;
  } else {
    save_gif();
    timer_->stop();
  }
}

// Сохранение захваченных изображений в гифку
void View::save_gif() {
  QString gif_name = NULL;
  gif_name = QFileDialog::getSaveFileName(this, NULL, NULL,
                                          "GIF (*.gif) ;; GIF (*.gif)");
  if (!gif_name.isNull()) {
    QGifImage gif_file(QSize(widget_->width() * 2, widget_->height() * 2));
    gif_file.setDefaultDelay(100);
    for (QVector<QImage>::Iterator frames = gif_.begin(); frames != gif_.end();
         frames++) {
      gif_file.addFrame(*frames);
    }
    gif_file.save(gif_name);
  }
  ui->create_gif->setStyleSheet(ui->save_file->styleSheet());
  gif_.clear();
  counter_ = 0.0;
}

void View::gif_changeStyleRed() {
  ui->create_gif->setStyleSheet(
      "QPushButton {border-radius: 10px;border-style: solid;\
               background-color: rgb(220, 80, 80);\
               font-size: 13px;color: rgb(221, 231, 220);}");
}

void View::on_SavePreferences_clicked() {
  path_ = QFileDialog::getSaveFileName(this, "Save preferences",
                                       QDir::homePath(), "ini (*.ini)");
  if (!path_.isEmpty()) {
    QSettings settings(path_, QSettings::IniFormat);
    settings.setValue("settings_flag", 1);
    settings.setValue("filename", filename_);

    settings.beginGroup("Axis_rotation");
    settings.setValue("rotate_x", ui->slider_rotate_x->value());
    settings.setValue("rotate_y", ui->slider_rotate_y->value());
    settings.setValue("rotate_z", ui->slider_rotate_z->value());
    settings.endGroup();

    settings.beginGroup("Axes_movement");
    settings.setValue("move_x", ui->slider_move_x->value());
    settings.setValue("move_y", ui->slider_move_y->value());
    settings.setValue("move_z", ui->slider_move_z->value());
    settings.endGroup();

    settings.beginGroup("Object_scaling");
    settings.setValue("scale", ui->slider_scale->value());
    settings.endGroup();

    settings.beginGroup("Type_and_thickness_of_the_edges");
    settings.setValue("edges_thickness", widget_->edgesThick);
    settings.setValue("edges_type", widget_->edgesType);
    settings.endGroup();

    settings.beginGroup("Type_and_size_of_the_vertices");
    settings.setValue("vertices_size", widget_->vertexSize);
    settings.setValue("vertices_type", widget_->vertexType);
    settings.endGroup();

    settings.beginGroup("Type_of_projection");
    settings.setValue("projection_type", widget_->projectionType);
    settings.endGroup();

    settings.beginGroup("RGB_components_for_background_color");
    settings.setValue("red_background", widget_->bgColor.redF());
    settings.setValue("green_background", widget_->bgColor.greenF());
    settings.setValue("blue_background", widget_->bgColor.blueF());
    settings.endGroup();

    settings.beginGroup("RGB_components_for_edges_color");
    settings.setValue("red_edges", widget_->edgesColor.redF());
    settings.setValue("green_edges", widget_->edgesColor.greenF());
    settings.setValue("blue_edges", widget_->edgesColor.blueF());
    settings.endGroup();

    settings.beginGroup("RGB_components_for_vertices_color");
    settings.setValue("red_vertices", widget_->vertexColor.redF());
    settings.setValue("green_vertices", widget_->vertexColor.greenF());
    settings.setValue("blue_vertices", widget_->vertexColor.blueF());
    settings.endGroup();
  }
}

void View::on_load_settings_clicked() {
  path_ = QFileDialog::getOpenFileName(this, "Upload a file", QDir::homePath(),
                                       "*.ini");
  QSettings settings(path_, QSettings::IniFormat);
  settings_flag_ = settings.value("settings_flag", 0).toInt();
  if (settings_flag_ == 1) {
    filename_ = settings.value("filename").toString();
    on_OpenFile_clicked();

    settings.beginGroup("Axis_rotation");
    ui->slider_rotate_x->setValue(settings.value("rotate_x", 0).toInt());
    ui->slider_rotate_y->setValue(settings.value("rotate_y", 0).toInt());
    ui->slider_rotate_z->setValue(settings.value("rotate_z", 0).toInt());
    settings.endGroup();

    settings.beginGroup("Axes_movement");
    ui->slider_move_x->setValue(settings.value("move_x", 0).toInt());
    ui->slider_move_y->setValue(settings.value("move_y", 0).toInt());
    ui->slider_move_z->setValue(settings.value("move_z", 0).toInt());
    settings.endGroup();

    settings.beginGroup("Object_scaling");
    ui->slider_scale->setValue(settings.value("scale", 50).toInt());
    settings.endGroup();

    settings.beginGroup("Type_and_thickness_of_the_edges");
    widget_->edgesThick = settings.value("edges_thickness", 1.0).toInt();
    widget_->edgesType = settings.value("edges_type", 2).toInt();
    settings.endGroup();

    settings.beginGroup("Type_and_size_of_the_vertices");
    widget_->vertexSize = settings.value("vertices_size", 1.0).toInt();
    widget_->vertexType = settings.value("vertices_type", 2).toInt();
    settings.endGroup();

    settings.beginGroup("Type_of_projection");
    widget_->projectionType = settings.value("projection_type", 0).toInt();
    settings.endGroup();

    settings.beginGroup("RGB_components_for_background_color");
    widget_->bgColor.setRedF(settings.value("red_background", 0.0).toDouble());
    widget_->bgColor.setGreenF(
        settings.value("green_background", 0.0).toDouble());
    widget_->bgColor.setBlueF(
        settings.value("blue_background", 0.0).toDouble());
    settings.endGroup();
    makeStyleSheets(ui->ButtonBackgroundColor, widget_->bgColor);

    settings.beginGroup("RGB_components_for_edges_color");
    widget_->edgesColor.setRedF(settings.value("red_edges", 160.0).toDouble());
    widget_->edgesColor.setGreenF(
        settings.value("green_edges", 35.0).toDouble());
    widget_->edgesColor.setBlueF(
        settings.value("blue_edges", 180.0).toDouble());
    settings.endGroup();
    makeStyleSheets(ui->ButtonEdgesColor, widget_->edgesColor);

    settings.beginGroup("RGB_components_for_vertices_color");
    widget_->vertexColor.setRedF(
        settings.value("red_vertices", 50.0).toDouble());
    widget_->vertexColor.setGreenF(
        settings.value("green_vertices", 80.0).toDouble());
    widget_->vertexColor.setBlueF(
        settings.value("blue_vertices", 220.0).toDouble());
    settings.endGroup();
    makeStyleSheets(ui->ButtonVerticesColor, widget_->vertexColor);

    ui->projection_type->setCurrentIndex(widget_->projectionType);
    ui->vertex_type->setCurrentIndex(widget_->vertexType);
    ui->edges_type->setCurrentIndex(widget_->edgesType);
    settings_flag_ = 0;
    widget_->update();
  }
}
}  // namespace s21
