#include "tsp.h"
#include "mcts2.h"
#include "utils.h"
#include <vector>
#include <chrono>

#define AGENT_TIME_PORPORTION 0.5

typedef std::chrono::_V2::system_clock::time_point timing;

class PostProcessedMCTSAgent
{
private:
  TSP *tsp;
  double time_limit;
  timing start_time;

  double elapsed_time();

  void make_mcts2_solve(std::vector<int> &path);
  void post_process(std::vector<int> &path);

public:
  PostProcessedMCTSAgent(TSP *tsp, double time_limit);
  ~PostProcessedMCTSAgent();
  void solve(std::vector<int> &path);
};
