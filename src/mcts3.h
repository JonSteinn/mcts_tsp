#include "tsp.h"
#include <vector>

class PostProcessedMCTSAgent
{
private:
  TSP *tsp;
  double time_limit;

public:
  PostProcessedMCTSAgent(TSP *tsp, double time_limit);
  ~PostProcessedMCTSAgent();
  void solve(std::vector<int> &path);
};
