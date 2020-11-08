#include "mcts.h"

MCTSAgent::MCTSAgent(TSP *tsp)
{
  tree = new Node(0, NULL);

  // TODO: Remove, placehodler to use tsp
  if (tsp->get_number_of_data_points() == -3) {
    tree = nullptr;
  }
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
