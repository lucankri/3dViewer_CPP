#include "adapter.h"

namespace s21 {

double *Adapter::adoptPoints(const std::vector<Point> &vertexes,
                             const std::size_t &count) {
  double *v = new double[count * 3];
  for (std::size_t i = 0; i < count; i++) {
    v[i * 3 + 0] = vertexes[i].x;
    v[i * 3 + 1] = vertexes[i].y;
    v[i * 3 + 2] = vertexes[i].z;
  }
  return v;
}

std::pair<unsigned *, std::size_t> Adapter::adoptFacets(
    const std::vector<Facet> &facets, const std::size_t &count) {
  unsigned *f = new unsigned[count * 2];
  std::size_t facets_index = 0;
  for (auto &element : facets) {
    for (std::size_t i = 0; i < element.size(); i++) {
      f[facets_index++] = element[i];
      if (i > 0) {
        f[facets_index++] = element[i];
      }
    }
    f[facets_index++] = element[0];
  }
  return {f, count * 2};
}
}  // namespace s21
