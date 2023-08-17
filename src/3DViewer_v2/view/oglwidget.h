#ifndef OGLWIDGET_H
#define OGLWIDGET_H
#define GL_SILENCE_DEPRECATION
#include <QtOpenGLWidgets>
// #include <QOpenGLWidget>
#include <openGL/glu.h>
// #include <GL/glu.h>

class QOGLWidget : public QOpenGLWidget {
 public:
  QOGLWidget(QWidget* parent = nullptr);
  ~QOGLWidget();
  std::pair<double*, std::pair<unsigned*, std::size_t>> data;
  QColor edgesColor, vertexColor, bgColor;
  int edgesType, edgesThick, vertexType, vertexSize, projectionType;
  void clearWidgetData();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  void drawEdges();
  void drawPoint();
};

#endif  // OGLWIDGET_H
