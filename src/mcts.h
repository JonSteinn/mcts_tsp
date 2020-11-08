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
  MCTSAgent(int best, int max_l)
  {
    best_path = best;
    tree = new Node(-1, NULL);
    max_location = max_l;
    std::vector<int> v(max_location);
    std::iota(std::begin(v), std::end(v), 0);
    (*tree).expand(v);
  }
  ~MCTSAgent()
  {
    delete tree;
    delete this;
  }
  void reset()
  {
    (*tree).reset();
  }
};

#endif