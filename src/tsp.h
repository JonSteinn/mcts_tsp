#ifndef TSP_H
#define TSP_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <math.h>
#include <unordered_set>

class TSP
{
private:
  std::vector<std::vector<float>> matrix;
  std::vector<std::vector<int>> closests;
  float optimal_length;

public:
  TSP(std::string file_name);
  float get_optimal_length(void);
  float get_distance_between(int a, int b);
  int get_number_of_data_points(void);
  std::vector<int> &get_closests(int a);

  int shortest_distance_from(int src, std::unordered_set<int> &not_included);
  float calculate_cost_of_path(std::vector<int> &path);
};

#endif
