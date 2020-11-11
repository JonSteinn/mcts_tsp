#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
#include "tsp.h"

/**
 * Returns an array with indexes from v sorted by their value
 */
std::vector<int> sort_indexes_float(const std::vector<float> &v);

/**
 * Reverse the path between i and j
 */
void reverse_opt(std::vector<int> &path, int i, int j);

/**
 * 2-opt algorithm. Returns true if the path has been shortened
 */
bool opt2(std::vector<int> &path, TSP *tsp);

/**
 * Generates all segments between 3 nodes
 */
std::vector<std::tuple<int, int, int>> all_segments(int n);

/**
 * Reverses if a shorter path is found for the segment. returns the saved cost
 */

float reverse_if_better(std::vector<int> &path, int i, int j, int k, TSP *tsp);

/**
 * 3-opt algorithm. Returns true if the path has been shortened
 */
bool opt3(std::vector<int> &path, TSP *tsp);

#endif
