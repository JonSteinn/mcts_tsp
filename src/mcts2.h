#ifndef MCTC2_H
#define MCTC2_H

#include <vector>

#include "tsp.h"
#include "shortest_next.h"

#define MAX_FP_NODES 1000000

struct FP_Node
{
  float Q;
  int N;
  struct FP_Node *parent;
  std::vector<struct FP_Node *> children;
  int next_to_expand;
  int current_location;

  FP_Node()
  {
    this->Q = 0.0f;
    this->N = 0;
    this->current_location = 0;
    this->parent = nullptr;
    this->next_to_expand = 0;
  }

  void set_parent_and_location(struct FP_Node *parent, int location)
  {
    this->parent = parent;
    this->current_location = location;
  }

  bool is_leaf()
  {
    return children.empty();
  }

  struct FP_Node *get_next()
  {
    return children[next_to_expand++];
  }

  bool fully_expanded()
  {
    return next_to_expand >= (int)children.size();
  }

  bool expand(std::vector<int> &possible_moves, FP_Node *mem_stack, int *mem_idx, int max_mem)
  {
    for (auto it = possible_moves.begin(); it != possible_moves.end(); it++)
    {
      if (*mem_idx == max_mem)
      {
        return false;
      }
      FP_Node *new_node = &mem_stack[(*mem_idx)++];
      new_node->set_parent_and_location(this, *it);
      children.push_back(new_node);
    }
    return true;
  }

  bool is_root()
  {
    return parent == NULL;
  }
};

class FullPathMCTSAgent
{
private:
  TSP *tsp;
  double time_limit;
  float greedy_cost;
  FP_Node *node_mem;
  int mem_idx;
  int max_mem;
  FP_Node *tree;

public:
  FullPathMCTSAgent(TSP *tsp, double time_limit);
  ~FullPathMCTSAgent();

  void solve(std::vector<int> &path);
};

#endif
