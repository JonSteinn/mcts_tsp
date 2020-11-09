#ifndef MCTS_H
#define MCTS_H

#include <chrono>
#include <vector>
#include <limits>
#include <unordered_set>
#include <numeric>
#include "tree.h"
#include "tsp.h"

typedef std::chrono::_V2::system_clock::time_point timing;

class MCTSAgent
{
private:
  const int C = 1;
  struct Node *tree;
  TSP *tsp;
  timing start_time;
  double time_limit;
  std::unordered_set<int> retired_moves;

  int fake_move; // TODO: REMOVE_ME

  bool time_is_up();

public:
  MCTSAgent(TSP *tsp, double time_limit);
  ~MCTSAgent();

  void move_root(Node *node);
  int next_move();

  Node *tree_policy(std::vector<int> &available_moves);
  float simulation(Node *node);
  void back_propagate(float score, Node *node);
  float score(Node *node);
};

#endif
