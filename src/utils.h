#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
#include "tsp.h"

std::vector<int> sort_indexes_float(const std::vector<float> &v);

void reverse_opt(std::vector<int> &path, int i, int j);
bool opt2(std::vector<int> &path, TSP *tsp);

std::vector<std::tuple<int, int, int>> all_segments(int n);
float reverse_if_better(std::vector<int> &path, int i, int j, int k, TSP *tsp);
bool opt3(std::vector<int> &path, TSP *tsp);

#endif
