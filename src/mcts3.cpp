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
  this->make_mcts2_solve(path);
  this->post_process(path);
}

void PostProcessedMCTSAgent::make_mcts2_solve(std::vector<int> &path)
{
  FullPathMCTSAgent agent(this->tsp, time_limit);
  agent.solve(path);
}

void PostProcessedMCTSAgent::post_process(std::vector<int> &path)
{
}
