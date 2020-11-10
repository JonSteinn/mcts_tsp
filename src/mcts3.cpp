#include "mcts3.h"

PostProcessedMCTSAgent::PostProcessedMCTSAgent(TSP *tsp, double time_limit)
{
  this->tsp = tsp;
  this->time_limit = time_limit;
}

PostProcessedMCTSAgent::~PostProcessedMCTSAgent()
{
}

void PostProcessedMCTSAgent::solve(std::vector<int> &path)
{
  for (int i = 0; i < this->tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
}
