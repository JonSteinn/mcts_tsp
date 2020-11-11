#include <vector>
#include <iostream>
#include <getopt.h>

#include "tsp.h"
#include "mcts.h"
#include "mcts2.h"
#include "mcts3.h"
#include "shortest_next.h"

/**
 * Parsed data.
 */
typedef struct
{
  const char *data;
  int algorithm;
  double time_limit;
} CommandLineArguments;

/**
 * Parse arguments. Returns true if succesful, false otherwise.
 */
bool parse_args(int argc, char **argv, CommandLineArguments *cmd_args)
{
  cmd_args->algorithm = 0;
  cmd_args->time_limit = 10.0;
  cmd_args->data = nullptr;
  int32_t opt;
  while ((opt = getopt(argc, argv, "a:f:t:")) != -1)
  {
    switch (opt)
    {
    case 'a':
      cmd_args->algorithm = std::stoi(optarg);
      break;
    case 'f':
      cmd_args->data = optarg;
      break;
    case 't':
      cmd_args->time_limit = std::stod(optarg);
      break;
    default:
      break;
    }
  }
  return cmd_args->data != nullptr;
}

/**
 * Turn based MCTS. This plays this as a game and returns next move
 * each time.
 */
void solve_with_mcts(TSP &tsp, std::vector<int> &path, double time_limit)
{
  std::cout << "MCTS1" << std::endl;
  TurnBasedMCTSAgent agent(&tsp, time_limit / tsp.get_number_of_data_points());
  while ((int)path.size() < tsp.get_number_of_data_points())
  {
    path.push_back(agent.next_move());
  }
}

/**
 * This one finds a single solution, all in one call.
 */
void solve_with_mcts2(TSP &tsp, std::vector<int> &path, double time_limit)
{
  std::cout << "MCTS2" << std::endl;
  FullPathMCTSAgent agent(&tsp, time_limit);
  agent.solve(path);
}

/**
 * This one uses mcts2 internally but adds some post processing.
 */
void solve_with_mcts3(TSP &tsp, std::vector<int> &path, double time_limit)
{
  std::cout << "MCTS3" << std::endl;
  PostProcessedMCTSAgent agent(&tsp, time_limit);
  agent.solve(path);
}

/**
 * Find a greedy solution - nearest neighbor.
 */
void solve_with_shortest_next_greedy(TSP &tsp, std::vector<int> &path)
{
  std::cout << "Greedy" << std::endl;
  ShortestNextGreedyAgent agent(&tsp);
  agent.solve(path);
}

/**
 * Pick the correct agent. They will update the path variable with their solution.
 */
void solve(TSP &tsp, std::vector<int> &path, int algorithm, double time_limit)
{
  switch (algorithm)
  {
  case 0:
    solve_with_mcts(tsp, path, time_limit);
    break;
  case 1:
    solve_with_mcts2(tsp, path, time_limit);
    break;
  case 2:
    solve_with_mcts3(tsp, path, time_limit);
    break;
  case 3:
    solve_with_shortest_next_greedy(tsp, path);
    break;
  default:
    std::cout << "Unknown algorithm\nPick one of the following:\n";
    std::cout << "0: MCTS [turn based]\n";
    std::cout << "1: MCTS [full path]\n";
    std::cout << "2: MCTS [full path, post processed]\n";
    std::cout << "3: Shortest next greedy\n";
    exit(0);
  }
}

/**
 * Display result of solution given by agent.
 */
void display_results(TSP &tsp, std::vector<int> &path, float cost)
{
  std::cout << "Path:";
  for (auto it = path.begin(); it != path.end(); ++it)
  {
    std::cout << " " << *it;
  }
  putchar('\n');
  std::cout << "Cost: " << cost << "\n";
  std::cout << "Optimal cost: " << tsp.get_optimal_length() << "\n";
  std::cout << "Ratio cost/optimal: " << cost / tsp.get_optimal_length() << "\n";
}

/**
 * Starting point. Available arguments:
 *  -a <agents>
 *  -f <file with tsp data>
 *  -t <time limit>
 */
int main(int argc, char **argv)
{
  CommandLineArguments cmd_args;
  if (parse_args(argc, argv, &cmd_args))
  {
    TSP tsp(cmd_args.data);
    std::vector<int> path;
    solve(tsp, path, cmd_args.algorithm, cmd_args.time_limit);
    float cost = tsp.calculate_cost_of_path(path);
    display_results(tsp, path, cost);
  }
  return 0;
}
