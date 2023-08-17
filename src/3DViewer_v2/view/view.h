#ifndef VIEW_H
#define VIEW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <QToolTip>
#include <QWheelEvent>

#include "controller/controller.h"
#include "library/GIF/qgifimage.h"
#include "oglwidget.h"

namespace s21 {

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  QOGLWidget *widget_;
  View(s21::Controller *controller, QWidget *parent = nullptr);
  ~View();

 protected:
  void keyPressEvent(QKeyEvent *event) override;

  void wheelEvent(QWheelEvent *event) override;

 private slots:
  void on_OpenFile_clicked();

  void on_slider_scale_valueChanged(int value);

  void on_slider_move_x_valueChanged(int value);

  void on_slider_move_y_valueChanged(int value);

  void on_slider_move_z_valueChanged(int value);

  void on_slider_rotate_x_valueChanged(int value);

  void on_slider_rotate_y_valueChanged(int value);

  void on_slider_rotate_z_valueChanged(int value);

  void on_ButtonEdgesColor_clicked();

  void on_ButtonVerticesColor_clicked();

  void on_ButtonBackgroundColor_clicked();

  void on_edges_type_currentIndexChanged(int index);

  void on_edges_size_valueChanged(int value);

  void on_vertex_size_valueChanged(int value);

  void on_vertex_type_currentIndexChanged(int index);

  void on_projection_type_currentIndexChanged(int index);

  void on_save_file_clicked();

  void create_gif();

  void take_screen();

  void save_gif();

  void gif_changeStyleRed();

  void on_reset_clicked();

  void on_SavePreferences_clicked();

  void on_load_settings_clicked();

 private:
  void resetSliders();
  QTimer *timer_;
  QVector<QImage> gif_;
  double counter_;
  int error_, settings_flag_;
  Ui::View *ui;
  s21::Controller *controller_;
  QString path_, filename_;
  void newData();
  void makeStyleSheets(QPushButton *btn, QColor clr);
};
}  // namespace s21
#endif  // VIEW_H
