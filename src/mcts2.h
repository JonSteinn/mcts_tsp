#ifndef MCTC2_H
#define MCTC2_H

#include <vector>

#include "tsp.h"

class FullPathMCTSAgent
{
private:
  TSP *tsp;
  double time_limit;

public:
  FullPathMCTSAgent(TSP *tsp, double time_limit);
  ~FullPathMCTSAgent();

  void solve(std::vector<int> &path);
};

#endif
