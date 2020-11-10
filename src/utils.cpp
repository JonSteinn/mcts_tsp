#include "utils.h"

std::vector<int> sort_indexes_float(const std::vector<float> &v)
{
  std::vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  stable_sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });
  return idx;
}

bool opt2(std::vector<int> &path)
{
  for (auto it = path.begin(); it != path.end(); ++it)
  {
    // TODO: REMOVE ME
    std::cout << *it << std::endl;
  }
  return false;
}
