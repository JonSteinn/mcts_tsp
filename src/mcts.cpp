#include "mcts.h"

MCTSAgent::MCTSAgent(TSP *tsp)
{
  tree = new Node(0, NULL);
  this->tsp = tsp;
  this->start_time = std::chrono::high_resolution_clock::now();
}

MCTSAgent::~MCTSAgent()
{
  // TODO:
}

void MCTSAgent::reset()
{
  tree->reset();
}

void MCTSAgent::solve(std::vector<int> &path, double time_limit)
{
  // TODO: REmove, current is placeholder...
  for (int i = 0; i < 5; i++) {
    path.push_back(i);
  }

  // Tree-policty
  // and so on...
}



double MCTSAgent::elapsed_time() {
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count();
}
