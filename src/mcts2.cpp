#include "mcts2.h"

FullPathMCTSAgent::FullPathMCTSAgent(TSP *tsp, double time_limit)
{
  // Store environment
  this->tsp = tsp;
  this->time_limit = time_limit;

  // Calculate greedy for scaling
  ShortestNextGreedyAgent greedy(tsp);
  std::vector<int> path;
  greedy.solve(path);
  this->greedy_cost = tsp->calculate_cost_of_path(path);

  // Pre-allocate all mempory
  this->mem_max = MAX_FP_NODES;
  this->mem_idx = 0;
  this->node_mem = new FP_Node[this->mem_max];

  // Construct tree
  this->tree = &this->node_mem[this->mem_idx++];
  this->tree->set_parent_and_location(nullptr, 0);
  path.clear();
  for (int i = 1; i < tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
  this->tree->expand(path, this->node_mem, &this->mem_idx);

  // Store best
  this->best_leaf = this->tree;
  this->best_cost = std::numeric_limits<float>::max();

  // Start timer
  this->start_time = std::chrono::high_resolution_clock::now();
}

FullPathMCTSAgent::~FullPathMCTSAgent()
{
  delete[] this->node_mem;
}

void FullPathMCTSAgent::solve(std::vector<int> &path)
{
  std::cout << sizeof(FP_Node) << std::endl;
  while (this->elapsed_time() < time_limit)
  {
    float tree_cost = 0.0f;
    std::unordered_set<int> visited = {0};
    FP_Node *new_node = this->tree_policy(visited, &tree_cost);
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

FP_Node *FullPathMCTSAgent::tree_policy(std::unordered_set<int> &visited, float *tree_cost)
{
}
