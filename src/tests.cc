#include <gtest/gtest.h>

#include "3DViewer_v2/model/model.h"

TEST(Model_test, file_error) {
  std::string file_name = "Object_files/cube";
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 1);
  file_name = "Object_files/error.obj";
  error = model->ParseFile(file_name);
  EXPECT_EQ(error, 1);
}

TEST(Model_test, parser_cube) {
  std::string file_name = "Object_files/cube.obj";
  std::vector<std::vector<double>> vertexes = {
      {-1.0, -1.0, -1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, -1.0},
      {-1.0, 1.0, 1.0},   {1.0, -1.0, -1.0}, {1.0, -1.0, 1.0},
      {1.0, 1.0, -1.0},   {1.0, 1.0, 1.0}};
  std::vector<std::vector<double>> facets = {
      {1, 7, 5}, {1, 3, 7}, {1, 4, 3}, {1, 2, 4}, {3, 8, 7},
      {3, 4, 8}, {5, 7, 8}, {5, 8, 6}, {1, 5, 6}, {1, 6, 2}};
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 0);
  model->compressShapeAfterParsing(1);
  std::pair<std::size_t, std::size_t> numVF = model->getNumberVF();
  EXPECT_EQ(numVF.first, vertexes.size());
  EXPECT_EQ(numVF.second, facets.size() * 3);
  std::vector<s21::Point> model_vertexes = model->getVertexes();
  for (std::size_t i = 0; i < model_vertexes.size(); i++) {
    EXPECT_DOUBLE_EQ(model_vertexes[i].x, vertexes[i][0]);
    EXPECT_DOUBLE_EQ(model_vertexes[i].y, vertexes[i][1]);
    EXPECT_DOUBLE_EQ(model_vertexes[i].z, vertexes[i][2]);
  }
  std::vector<s21::Facet> model_facets = model->getFacets();
  for (std::size_t i = 0; i < model_facets.size(); i++) {
    EXPECT_DOUBLE_EQ(model_facets[i][0], facets[i][0] - 1);
    EXPECT_DOUBLE_EQ(model_facets[i][1], facets[i][1] - 1);
    EXPECT_DOUBLE_EQ(model_facets[i][2], facets[i][2] - 1);
  }
}

TEST(Model_test, parser_pyramid) {
  std::string file_name = "Object_files/pyramid.obj";
  std::vector<std::vector<double>> vertexes = {{10, 10, -10},
                                               {10, -10, -10},
                                               {-10, -10, -10},
                                               {-10, 10, -10},
                                               {0, 0, 10}};
  std::vector<std::vector<double>> facets = {{1, 2, 3}, {1, 3, 4}, {5, 2, 1},
                                             {1, 4, 5}, {4, 3, 5}, {3, 2, 5}};
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 0);
  std::pair<std::size_t, std::size_t> numVF = model->getNumberVF();
  EXPECT_EQ(numVF.first, vertexes.size());
  EXPECT_EQ(numVF.second, facets.size() * 3);
  std::vector<s21::Point> model_vertexes = model->getVertexes();
  for (std::size_t i = 0; i < model_vertexes.size(); i++) {
    EXPECT_DOUBLE_EQ(model_vertexes[i].x, vertexes[i][0]);
    EXPECT_DOUBLE_EQ(model_vertexes[i].y, vertexes[i][1]);
    EXPECT_DOUBLE_EQ(model_vertexes[i].z, vertexes[i][2]);
  }
  std::vector<s21::Facet> model_facets = model->getFacets();
  for (std::size_t i = 0; i < model_facets.size(); i++) {
    EXPECT_DOUBLE_EQ(model_facets[i][0], facets[i][0] - 1);
    EXPECT_DOUBLE_EQ(model_facets[i][1], facets[i][1] - 1);
    EXPECT_DOUBLE_EQ(model_facets[i][2], facets[i][2] - 1);
  }
}

TEST(Model_test, rotationX_cube) {
  std::string file_name = "Object_files/cube.obj";
  double radian = 71;
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 0);
  std::vector<s21::Point> original_vertexes = model->getVertexes();
  std::vector<s21::Facet> original_facets = model->getFacets();
  model->rotationX(radian);
  model->rotationX(-radian);
  std::vector<s21::Point> rotation_vertexes = model->getVertexes();
  std::vector<s21::Facet> rotation_facets = model->getFacets();
  for (std::size_t i = 0; i < original_vertexes.size(); i++) {
    EXPECT_DOUBLE_EQ(original_vertexes[i].x, rotation_vertexes[i].x);
    EXPECT_DOUBLE_EQ(original_vertexes[i].y, rotation_vertexes[i].y);
    EXPECT_DOUBLE_EQ(original_vertexes[i].z, rotation_vertexes[i].z);
  }
  for (std::size_t i = 0; i < original_facets.size(); i++) {
    EXPECT_DOUBLE_EQ(original_facets[i][0], rotation_facets[i][0]);
    EXPECT_DOUBLE_EQ(original_facets[i][1], rotation_facets[i][1]);
    EXPECT_DOUBLE_EQ(original_facets[i][2], rotation_facets[i][2]);
  }
}

TEST(Model_test, rotationY_cube) {
  std::string file_name = "Object_files/cube.obj";
  double radian = 154;
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 0);
  std::vector<s21::Point> original_vertexes = model->getVertexes();
  std::vector<s21::Facet> original_facets = model->getFacets();
  model->rotationY(radian);
  model->rotationY(-radian);
  std::vector<s21::Point> rotation_vertexes = model->getVertexes();
  std::vector<s21::Facet> rotation_facets = model->getFacets();
  for (std::size_t i = 0; i < original_vertexes.size(); i++) {
    EXPECT_DOUBLE_EQ(original_vertexes[i].x, rotation_vertexes[i].x);
    EXPECT_DOUBLE_EQ(original_vertexes[i].y, rotation_vertexes[i].y);
    EXPECT_DOUBLE_EQ(original_vertexes[i].z, rotation_vertexes[i].z);
  }
  for (std::size_t i = 0; i < original_facets.size(); i++) {
    EXPECT_DOUBLE_EQ(original_facets[i][0], rotation_facets[i][0]);
    EXPECT_DOUBLE_EQ(original_facets[i][1], rotation_facets[i][1]);
    EXPECT_DOUBLE_EQ(original_facets[i][2], rotation_facets[i][2]);
  }
}

TEST(Model_test, rotationZ_cube) {
  std::string file_name = "Object_files/cube.obj";
  double radian = 269;
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 0);
  std::vector<s21::Point> original_vertexes = model->getVertexes();
  std::vector<s21::Facet> original_facets = model->getFacets();
  model->rotationZ(radian);
  model->rotationZ(-radian);
  std::vector<s21::Point> rotation_vertexes = model->getVertexes();
  std::vector<s21::Facet> rotation_facets = model->getFacets();
  for (std::size_t i = 0; i < original_vertexes.size(); i++) {
    EXPECT_DOUBLE_EQ(original_vertexes[i].x, rotation_vertexes[i].x);
    EXPECT_DOUBLE_EQ(original_vertexes[i].y, rotation_vertexes[i].y);
    EXPECT_DOUBLE_EQ(original_vertexes[i].z, rotation_vertexes[i].z);
  }
  for (std::size_t i = 0; i < original_facets.size(); i++) {
    EXPECT_DOUBLE_EQ(original_facets[i][0], rotation_facets[i][0]);
    EXPECT_DOUBLE_EQ(original_facets[i][1], rotation_facets[i][1]);
    EXPECT_DOUBLE_EQ(original_facets[i][2], rotation_facets[i][2]);
  }
}

TEST(Model_test, scale_cube) {
  std::string file_name = "Object_files/cube.obj";
  double value = 25;
  s21::Model* model = s21::Model::getInstance();
  int error = model->ParseFile(file_name);
  EXPECT_EQ(error, 0);
  std::vector<s21::Point> original_vertexes = model->getVertexes();
  std::vector<s21::Facet> original_facets = model->getFacets();
  model->scale(value);
  model->scale(1.0 / value);
  std::vector<s21::Point> rotation_vertexes = model->getVertexes();
  std::vector<s21::Facet> rotation_facets = model->getFacets();
  for (std::size_t i = 0; i < original_vertexes.size(); i++) {
    EXPECT_DOUBLE_EQ(original_vertexes[i].x, rotation_vertexes[i].x);
    EXPECT_DOUBLE_EQ(original_vertexes[i].y, rotation_vertexes[i].y);
    EXPECT_DOUBLE_EQ(original_vertexes[i].z, rotation_vertexes[i].z);
  }
  for (std::size_t i = 0; i < original_facets.size(); i++) {
    EXPECT_DOUBLE_EQ(original_facets[i][0], rotation_facets[i][0]);
    EXPECT_DOUBLE_EQ(original_facets[i][1], rotation_facets[i][1]);
    EXPECT_DOUBLE_EQ(original_facets[i][2], rotation_facets[i][2]);
  }
}
