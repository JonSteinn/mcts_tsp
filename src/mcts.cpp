#include "mcts.h"

MCTSAgent::MCTSAgent(TSP *tsp)
{
  tree = new Node(0, NULL);
  this->tsp = tsp;
  this->start_time = std::chrono::high_resolution_clock::now();
}

MCTSAgent::~MCTSAgent()
{
  delete tree;
}

void MCTSAgent::solve(std::vector<int> &path, double time_limit)
{
  while (this->elapsed_time() < time_limit)
  {
    // 1. Tree policy
    // 2. Playouts
    // 3. Back propagate
  }
  // take best path, fill in gap with greedy alg

  // fake using of variable: TODO: REMOVE
  path.push_back(0);
  path.push_back(1);
}

double MCTSAgent::elapsed_time()
{
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count();
}

Node MCTSAgent::*tree_policy()
{
}

float MCTSAgent::simulation(Node *node)
{
}

void MCTSAgent::back_propagate(float score, Node *node)
{
}
