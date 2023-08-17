#include "parser.h"

namespace s21 {

Parser::ParserResult Parser::parse(const std::string &filename) {
  ParserResult result;
  if (filename.substr(filename.length() - 4) != ".obj") {
    result.error = 1;
    return result;
  }
  std::ifstream file(filename);
  if (file.is_open()) {
    result.error = 0;
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string token;
      iss >> token;
      if (token == "v") {
        parseV(result, iss);
      } else if (token == "f") {
        parseF(result, iss);
      }
      if (result.error > 0) {
        break;
      }
    }
    std::size_t number_facets = 0;
    for (auto &element : result.facets) {
      number_facets += element.size();
    }
    result.number_v_f.first = result.vertexes.size();
    result.number_v_f.second = number_facets;
    file.close();
  } else {
    result.error = 1;
  }
  return result;
}

void Parser::parseV(Parser::ParserResult &result, std::istringstream &iss) {
  Point v{};
  iss >> v.x >> v.y >> v.z;
  result.vertexes.push_back(v);
}

void Parser::parseF(Parser::ParserResult &result, std::istringstream &iss) {
  std::string vertex_index_str;
  Facet f;
  while (iss >> vertex_index_str) {
    std::istringstream vertex_index_iss(vertex_index_str);
    unsigned vertex_index;
    if (vertex_index_iss.str()[0] == '-') {
      result.error = 2;
      break;
    }
    vertex_index_iss >> vertex_index;
    f.push_back(vertex_index - 1);
  }
  result.facets.push_back(f);
}
}  // namespace s21
