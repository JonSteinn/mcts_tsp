#ifndef MCTS_H
#define MCTS_H

#include <vector>
#include <numeric>
#include "tree.h"

class MCTSAgent
{
  int best_path;
  struct Node *tree;
  int max_location;

public:
  MCTSAgent(int best, int max_l);
  ~MCTSAgent();
  void reset();
};

#endif
