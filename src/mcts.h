#ifndef MCTS_H
#define MCTS_H

#include <vector>
#include <numeric>
#include "tree.h"
#include "tsp.h"

class MCTSAgent
{
  struct Node *tree;

public:
  MCTSAgent(TSP *tsp);
  ~MCTSAgent();
  void reset();

  void solve(std::vector<int> &path, double time_limit);
};

#endif
