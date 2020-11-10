#ifndef MCTS_H
#define MCTS_H

#include <chrono>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <numeric>
#include "tsp.h"
#include "shortest_next.h"

typedef std::chrono::_V2::system_clock::time_point timing;

struct Node
{
  int current_location;
  float Q;
  float Q_square;
  int N;
  struct Node *parent;
  std::vector<struct Node *> children;
  int next_to_expand;

  Node(int current, struct Node *p)
  {
    current_location = current;
    Q = 0;
    Q_square = 0;
    N = 0;
    next_to_expand = 0;
    parent = p;
  }

  ~Node()
  {
    while (not children.empty())
    {
      struct Node *to_delete = children.back();
      children.pop_back();
      delete to_delete;
    }
  }

  void expand(std::vector<int> &possible_moves, std::vector<int> &order)
  {
    for (auto it = order.begin(); it != order.end(); it++)
    {
      if (std::find(possible_moves.begin(), possible_moves.end(), *it) != possible_moves.end())
      {
        Node *child = new Node(*it, this);
        children.push_back(child);
      }
    }
  }

  bool is_root()
  {
    return parent == NULL;
  }

  void make_root()
  {
    parent->children.erase(
        std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
    parent = NULL;
  }

  bool is_leaf()
  {
    return children.empty();
  }

  struct Node *get_next()
  {
    return children[next_to_expand++];
  }

  bool fully_expanded()
  {
    return next_to_expand >= (int)children.size();
  }
};

class TurnBasedMCTSAgent
{
private:
  const int C = 0.5;
  const int D = 10000;
  struct Node *tree;
  TSP *tsp;
  timing start_time;
  double time_limit;
  std::unordered_set<int> retired_moves;
  float cost_so_far;
  float greedy_cost;

  bool time_is_up();
  void move_root(Node *node);
  Node *tree_policy(std::vector<int> &available_moves, float *tree_cost);
  float simulation(Node *node, std::vector<int> &possible_moves);
  void back_propagate(float score, Node *node);
  float score(Node *node);

public:
  TurnBasedMCTSAgent(TSP *tsp, double time_limit);
  ~TurnBasedMCTSAgent();
  int next_move();
};

#endif
