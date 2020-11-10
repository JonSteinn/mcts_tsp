#ifndef MCTC2_H
#define MCTC2_H

#include <vector>

#include "tsp.h"
#include "shortest_next.h"

struct FP_Node
{
  float Q;
  int N;
  struct FP_Node *parent;
  std::vector<struct FP_Node *> children;
  int next_to_expand;
  int current_location;
};

class FullPathMCTSAgent
{
private:
  TSP *tsp;
  double time_limit;
  float greedy_cost;

public:
  FullPathMCTSAgent(TSP *tsp, double time_limit);
  ~FullPathMCTSAgent();

  void solve(std::vector<int> &path);
};

#endif
