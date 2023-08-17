#include "oglwidget.h"

QOGLWidget::QOGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), data({nullptr, {nullptr, 0}}) {
  edgesColor = QColor(160, 35, 180);
  vertexColor = QColor(50, 80, 220);
  bgColor = QColor(0, 0, 0);
  edgesType = 2;
  edgesThick = 1;
  vertexType = 2;
  vertexSize = 1;
  projectionType = 0;
}

QOGLWidget::~QOGLWidget() { clearWidgetData(); }

void QOGLWidget::clearWidgetData() {
  delete[] data.first;
  delete[] data.second.first;
  data.first = nullptr;
  data.second.first = nullptr;
  data.second.second = 0;
}

void QOGLWidget::initializeGL() {
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  if (projectionType) {
    gluPerspective(45.0f, (GLfloat)670 / (GLfloat)645, 0.0001, 1000000.0);
    glTranslatef(0, 0, -2.0f);
  }
}

void QOGLWidget::drawEdges() {
  glColor3d(edgesColor.redF(), edgesColor.greenF(), edgesColor.blueF());
  if (edgesType == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 5);
  } else if (edgesType == 2) {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(edgesThick);
  glDrawElements(GL_LINES, data.second.second, GL_UNSIGNED_INT,
                 data.second.first);
}

void QOGLWidget::drawPoint() {
  glColor3d(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
  if (vertexType == 2) {
    glEnable(GL_POINT_SMOOTH);
  } else if (vertexType == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(vertexSize);
  glDrawElements(GL_POINTS, data.second.second, GL_UNSIGNED_INT,
                 data.second.first);
}

void QOGLWidget::paintGL() {
  glClearColor(bgColor.redF(), bgColor.greenF(), bgColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  initializeGL();
  glVertexPointer(3, GL_DOUBLE, 0, data.first);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (edgesType) {
    drawEdges();
  }
  if (vertexType) {
    drawPoint();
  }
}

void QOGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
