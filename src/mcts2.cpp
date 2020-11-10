#include "mcts2.h"

FullPathMCTSAgent::FullPathMCTSAgent(TSP *tsp, double time_limit)
{
  this->tsp = tsp;
  this->time_limit = time_limit;

  ShortestNextGreedyAgent greedy(tsp);
  std::vector<int> path;
  greedy.solve(path);
  this->greedy_cost = tsp->calculate_cost_of_path(path);

  this->max_mem = MAX_FP_NODES;
  this->mem_idx = 0;
  this->node_mem = new FP_Node[this->max_mem];

  this->tree = &this->node_mem[this->mem_idx++];
  path.clear();
  for (int i = 1; i < tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
  this->tree->expand(path, this->node_mem, &this->mem_idx, this->max_mem);
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
  return;
}
