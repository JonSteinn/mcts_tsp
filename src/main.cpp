#include "tsp.h"
#include "mcts.h"
#include "mcts2.h"
#include "shortest_next.h"
#include <vector>
#include <iostream>
#include <getopt.h>

typedef struct
{
  const char *data;
  int algorithm;
  double time_limit;
} CommandLineArguments;

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

void solve_with_mcts(TSP &tsp, std::vector<int> &path, double time_limit)
{
  TurnBasedMCTSAgent agent(&tsp, time_limit);
  while ((int)path.size() < tsp.get_number_of_data_points())
  {
    path.push_back(agent.next_move());
    std::cout << path.back() << std::endl;
  }
}

void solve_with_mcts2(TSP &tsp, std::vector<int> &path, double time_limit)
{
  FullPathMCTSAgent agent(&tsp, time_limit);
  agent.solve(path);
}

void solve_with_shortest_next_greedy(TSP &tsp, std::vector<int> &path)
{
  ShortestNextGreedyAgent agent(&tsp);
  agent.solve(path);
}

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
    solve_with_shortest_next_greedy(tsp, path);
    break;
  default:
    std::cout << "Unknown algorithm\nPick one of the following:\n";
    std::cout << "0: MCTS [turn based]\n";
    std::cout << "1: MCTS [full path]\n";
    std::cout << "2: Shortest next greedy\n";
    exit(0);
  }
}

int main(int argc, char **argv)
{
  CommandLineArguments cmd_args;
  if (parse_args(argc, argv, &cmd_args))
  {
    TSP tsp(cmd_args.data);
    std::vector<int> path;
    solve(tsp, path, cmd_args.algorithm, cmd_args.time_limit);
    float cost = tsp.calculate_cost_of_path(path);
    std::cout << "Cost: " << cost << "\n";
    std::cout << "Optimal cost: " << tsp.get_optimal_length() << "\n";
    std::cout << "Ratio cost/optimal: " << cost / tsp.get_optimal_length() << "\n";
  }
  return 0;
}
