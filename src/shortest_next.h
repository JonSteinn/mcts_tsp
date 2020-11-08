#ifndef SHORTEST_NEXT_H
#define SHORTEST_NEXT_H

#include "tsp.h"
#include <vector>
#include <unordered_set>

class ShortestNextGreedyAgent
{
private:
  TSP *tsp;
public:
  ShortestNextGreedyAgent(TSP *tsp);
  void solve(std::vector<int> &path);
};

#endif

