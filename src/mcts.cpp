#include "mcts.h"

MCTSAgent::MCTSAgent(int best, int max_l)
{
  best_path = best;
  tree = new Node(-1, NULL);
  max_location = max_l;
  std::vector<int> v(max_location);
  std::iota(std::begin(v), std::end(v), 0);
  tree->expand(v);
}

MCTSAgent::~MCTSAgent()
{
  delete tree;
  delete this;
}

void MCTSAgent::reset()
{
  tree->reset();
}
