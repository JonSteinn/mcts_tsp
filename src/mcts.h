#ifndef MCTS_H
#define MCTS_H

#include <chrono>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <numeric>
#include "tree.h"
#include "tsp.h"
#include "shortest_next.h"

typedef std::chrono::_V2::system_clock::time_point timing;

class MCTSAgent
{
private:
  const float C = 1.41421356;
  struct Node *tree;
  TSP *tsp;
  timing start_time;
  double time_limit;
  std::unordered_set<int> retired_moves;
  float cost_so_far;
  float greedy_cost;

  bool time_is_up();
  void move_root(Node *node);
  Node *tree_policy(std::vector<int> &available_moves, float *tree_cost);
  float simulation(Node *node, std::vector<int> &possible_moves);
  void back_propagate(float score, Node *node);
  float score(Node *node);

public:
  MCTSAgent(TSP *tsp, double time_limit);
  ~MCTSAgent();
  int next_move();
};

#endif
