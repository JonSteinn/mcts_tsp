#include "mcts3.h"
#include "utils.h"

PostProcessedMCTSAgent::PostProcessedMCTSAgent(TSP *tsp, double time_limit)
{
  this->tsp = tsp;
  this->time_limit = time_limit;
  this->start_time = std::chrono::high_resolution_clock::now();
}

PostProcessedMCTSAgent::~PostProcessedMCTSAgent()
{
}

void PostProcessedMCTSAgent::solve(std::vector<int> &path)
{
  this->make_mcts2_solve(path);
  this->post_process(path);
}

void PostProcessedMCTSAgent::make_mcts2_solve(std::vector<int> &path)
{
  FullPathMCTSAgent agent(this->tsp, time_limit * AGENT_TIME_PORPORTION);
  agent.solve(path);
}

double PostProcessedMCTSAgent::elapsed_time()
{
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count();
}

void PostProcessedMCTSAgent::post_process(std::vector<int> &path)
{
  while (this->elapsed_time() < time_limit)
  {
    if (!opt2(path, this->tsp))
      break;
  }
}
