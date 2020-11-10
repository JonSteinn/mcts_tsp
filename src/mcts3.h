#include "tsp.h"
#include "mcts2.h"
#include <vector>

class PostProcessedMCTSAgent
{
private:
  TSP *tsp;
  double time_limit;

  void make_mcts2_solve(std::vector<int> &path);
  void post_process(std::vector<int> &path);

public:
  PostProcessedMCTSAgent(TSP *tsp, double time_limit);
  ~PostProcessedMCTSAgent();
  void solve(std::vector<int> &path);
};
