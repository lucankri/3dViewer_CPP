#ifndef INC_3DVIEWER_CPP_PARSER_H
#define INC_3DVIEWER_CPP_PARSER_H
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "facet.h"
#include "point.h"

namespace s21 {

class Parser {
 public:
  struct ParserResult {
    std::vector<Point> vertexes;
    std::vector<Facet> facets;
    std::pair<std::size_t, std::size_t> number_v_f;
    int error;
  };
  static ParserResult parse(const std::string &filename);

 private:
  static void parseV(ParserResult &result, std::istringstream &iss);
  static void parseF(ParserResult &result, std::istringstream &iss);
};

}  // namespace s21
#endif  // INC_3DVIEWER_CPP_PARSER_H
