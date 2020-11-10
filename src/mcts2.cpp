#include "mcts2.h"

FullPathMCTSAgent::FullPathMCTSAgent(TSP *tsp, double time_limit)
{
  this->tsp = tsp;
  this->time_limit = time_limit;

  ShortestNextGreedyAgent greedy(tsp);
  std::vector<int> path;
  greedy.solve(path);
  this->greedy_cost = tsp->calculate_cost_of_path(path);

  this->mem_idx = 0;
  this->tree = &this->node_mem[this->mem_idx++];
  this->tree->set_parent_and_location(nullptr, 0);
  path.clear();
  for (int i = 1; i < tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
  this->tree->expand(path, this->node_mem, &this->mem_idx);

  this->start_time = std::chrono::high_resolution_clock::now();
}

FullPathMCTSAgent::~FullPathMCTSAgent()
{
}

void FullPathMCTSAgent::solve(std::vector<int> &path)
{

  while (this->elapsed_time() < time_limit)
  {
    // 1. Tree policy
    // 2. Playouts
    // 3. Back propagate
  }

  for (int i = 0; i < this->tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
}

double FullPathMCTSAgent::elapsed_time()
{
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count();
}
