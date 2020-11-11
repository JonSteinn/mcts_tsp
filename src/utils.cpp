#include "utils.h"

std::vector<int> sort_indexes_float(const std::vector<float> &v)
{
  std::vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  stable_sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });
  return idx;
}

void reverse_opt2(std::vector<int> &path, int i, int j)
{
  while (i < j)
  {
    int tmp = path[j];
    path[j--] = path[i];
    path[i++] = tmp;
  }
}

bool opt2(std::vector<int> &path, TSP *tsp)
{
  auto test = [](int xj, int xim1, int xi, int xip1) {
    return (xj != xim1) and (xj != xi) and (xj != xip1);
  };
  auto test_distance = [](int xi, int xip1, int xj, int xjp1, TSP *tsp) {
    return tsp->get_distance_between(xi, xip1) + tsp->get_distance_between(xj, xjp1) > tsp->get_distance_between(xi, xj) + tsp->get_distance_between(xip1, xjp1);
  };
  bool improved = false;
  int s = path.size();
  for (int i = 0; i < s; i++)
  {
    for (int j = 0; j < s; j++)
    {
      if (test(path[j], path[(i - 1) % s], path[i], path[(i + 1) % s]) and
          test_distance(path[i], path[(i + 1) % s], path[j], path[(j + 1) % s], tsp))
      {
        improved = true;
        reverse_opt2(path, i + 1, j);
      }
    }
  }
  return improved;
}
