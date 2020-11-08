#include "shortest_next.h"


ShortestNextGreedyAgent::ShortestNextGreedyAgent(TSP *tsp)
{
  this->tsp = tsp;
}

void ShortestNextGreedyAgent::solve(std::vector<int> &path)
{
  std::unordered_set<int> visited;
  int length = this->tsp->get_number_of_data_points();
  path.push_back(0);
  visited.insert(0);

  while (path.size() < length)
  {
    path.push_back(tsp->shortest_distance_from(path.back(), visited));
    visited.insert(path.back());
  }
}
