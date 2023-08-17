#ifndef ADAPTER_H
#define ADAPTER_H
#include <vector>

#include "model/facet.h"
#include "model/point.h"

namespace s21 {
class Adapter {
 public:
  double *adoptPoints(const std::vector<Point> &vertexes,
                      const std::size_t &count);
  std::pair<unsigned *, std::size_t> adoptFacets(
      const std::vector<Facet> &facets, const std::size_t &count);
};

}  // namespace s21

#endif  // ADAPTER_H
