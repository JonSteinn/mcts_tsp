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
  TSP* tsp;
  timing start_time;

  double elapsed_time();

public:
  MCTSAgent(TSP *tsp);
  ~MCTSAgent();
  void reset();

  void solve(std::vector<int> &path, double time_limit);
};

#endif
