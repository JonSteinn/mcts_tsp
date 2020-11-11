#include "utils.h"

std::vector<int> sort_indexes_float(const std::vector<float> &v)
{
  std::vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  stable_sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });
  return idx;
}

void reverse_opt(std::vector<int> &path, int i, int j)
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
        reverse_opt(path, i + 1, j);
      }
    }
  }
  return improved;
}

std::vector<std::tuple<int, int, int>> all_segments(int n)
{
  std::vector<std::tuple<int, int, int>> segments;
  for (int i = 0; i < n; i++)
    for (int j = i + 2; j < n; j++)
      for (int k = j + 2; k < n + (i > 0); k++)
      {
        segments.push_back(std::make_tuple(i, j, k));
      }
  return segments;
}

float reverse_if_better(std::vector<int> &path, int i, int j, int k, TSP *tsp)
{
  int A = path[i - 1];
  int B = path[i];
  int C = path[j - 1];
  int D = path[j];
  int E = path[k - 1];
  int F = path[k % path.size()];
  float d0 = tsp->get_distance_between(A, B) + tsp->get_distance_between(C, D) + tsp->get_distance_between(E, F);
  float d1 = tsp->get_distance_between(A, C) + tsp->get_distance_between(B, D) + tsp->get_distance_between(E, F);
  float d2 = tsp->get_distance_between(A, B) + tsp->get_distance_between(C, E) + tsp->get_distance_between(D, F);
  float d3 = tsp->get_distance_between(A, D) + tsp->get_distance_between(E, B) + tsp->get_distance_between(C, F);
  float d4 = tsp->get_distance_between(F, B) + tsp->get_distance_between(C, D) + tsp->get_distance_between(E, A);
  if (d0 > d1)
  {
    reverse_opt(path, i, j - 1);
    return -d0 + d1;
  }
  else if (d0 > d2)
  {
    reverse_opt(path, j, k - 1);
    return -d0 + d2;
  }
  else if (d0 > d4)
  {
    reverse_opt(path, i, k - 1);
    return -d0 + d4;
  }
  else if (d0 > d3)
  {
    std::vector<int> tmp;
    for (int l = j; l < k; l++)
      tmp.push_back(path[l]);
    for (int l = i; l < j; l++)
      tmp.push_back(path[l]);
    for (int l = 0; l < k - i; l++)
      path[i + l] = tmp[l];
    return -d0 + d3;
  }
  return 0.0;
}

bool opt3(std::vector<int> &path, TSP *tsp)
{
  float delta = 0.0f;
  std::vector<std::tuple<int, int, int>> segments = all_segments(path.size());
  for (auto it = segments.begin(); it != segments.end(); ++it)
  {
    delta += reverse_if_better(path, std::get<0>(*it), std::get<1>(*it), std::get<2>(*it), tsp);
  }
  return delta < 0.0;
}
