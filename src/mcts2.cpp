#include "mcts2.h"

FullPathMCTSAgent::FullPathMCTSAgent(TSP *tsp, double time_limit)
{
  this->tsp = tsp;
  this->time_limit = time_limit;
}

FullPathMCTSAgent::~FullPathMCTSAgent()
{
}

void FullPathMCTSAgent::solve(std::vector<int> &path)
{
  for (int i = 0; i < this->tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
}
