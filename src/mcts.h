#ifndef MCTS_H
#define MCTS_H

#include <chrono>
#include <vector>
#include <numeric>
#include "tree.h"
#include "tsp.h"

typedef std::chrono::_V2::system_clock::time_point timing;

class MCTSAgent
{
private:
  struct Node *tree;
  TSP *tsp;
  timing start_time;
  double time_limit;
  int fake_move; // TODO: REMOVE_ME

  bool time_is_up();

public:
  MCTSAgent(TSP *tsp, double time_limit);
  ~MCTSAgent();

  int next_move();

  Node *tree_policy();
  float simulation(Node *node);
  void back_propagate(float score, Node *node);
};

#endif
