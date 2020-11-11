#include "mcts2.h"

FullPathMCTSAgent::FullPathMCTSAgent(TSP *tsp, double time_limit) : m_mt((std::random_device())())
{
  // Store environment
  this->tsp = tsp;
  this->time_limit = time_limit;
  this->C = 1.41f;
  this->D = 10000.0f;

  // Calculate greedy for scaling
  ShortestNextGreedyAgent greedy(tsp);
  greedy.solve(this->best_path);
  this->greedy_cost = tsp->calculate_cost_of_path(this->best_path);
  this->best_cost = this->greedy_cost;

  // Pre-allocate all mempory
  this->mem_max = MAX_FP_NODES;
  this->mem_idx = 0;
  this->node_mem = new FP_Node[this->mem_max];

  // Stats
  this->expansion_counter = 1;

  // Construct tree
  this->tree = &this->node_mem[this->mem_idx++];
  this->tree->set_parent_and_location(nullptr, 0);
  std::vector<int> path;
  for (int i = 1; i < tsp->get_number_of_data_points(); i++)
  {
    path.push_back(i);
  }
  this->tree->expand(path, this->node_mem, &this->mem_idx, this->mem_max);

  // Start timer
  this->start_time = std::chrono::high_resolution_clock::now();
}

FullPathMCTSAgent::~FullPathMCTSAgent()
{
  delete[] this->node_mem;
}

void FullPathMCTSAgent::solve(std::vector<int> &path)
{
  std::vector<int> available_moves;

  while (this->elapsed_time() < time_limit)
  {
    available_moves.clear();
    float cost = 0.0f;
    FP_Node *new_node = this->tree_policy(available_moves, &cost);

    if (new_node == nullptr)
    {
      break; // Out of mem
    }

    cost += this->simulation(new_node, available_moves);

    // Found better
    if (cost < this->best_cost)
    {
      this->best_cost = cost;
      this->best_leaf = new_node;
      this->best_path.clear();
      this->best_path.insert(this->best_path.begin(), available_moves.begin(), available_moves.end());
    }

    back_propagate(cost / this->greedy_cost, new_node);
  }

  // Fill path with best
  FP_Node *curr = this->best_leaf;
  while (curr != nullptr)
  {
    path.push_back(curr->current_location);
    curr = curr->parent;
  }
  std::reverse(path.begin(), path.end());
  path.insert(path.end(), this->best_path.begin(), this->best_path.end());

  std::cout << "Expansions: " << this->expansion_counter << std::endl;
}

double FullPathMCTSAgent::elapsed_time()
{
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count();
}

FP_Node *FullPathMCTSAgent::tree_policy(std::vector<int> &available_moves, float *tree_cost)
{
  std::unordered_set<int> visited({0});
  FP_Node *curr = this->tree;
  while (curr->fully_expanded())
  {
    if (curr->is_leaf())
      return curr;

    FP_Node *next = nullptr;
    float best = std::numeric_limits<float>::max();

    for (auto it = curr->children.begin(); it != curr->children.end(); ++it)
    {
      float curr_score = this->score(*it);
      if (curr_score < best)
      {
        next = *it;
        best = curr_score;
      }
    }

    *tree_cost += this->tsp->get_distance_between(curr->current_location, next->current_location);
    curr = next;
    visited.insert(next->current_location);
  }

  curr = curr->get_next(this->tsp);
  *tree_cost += this->tsp->get_distance_between(curr->parent->current_location, curr->current_location);
  visited.insert(curr->current_location);

  int n = this->tsp->get_number_of_data_points();
  for (int i = 0; i < n; i++)
  {
    if (visited.find(i) == visited.end())
    {
      available_moves.push_back(i);
    }
  }

  if (!curr->expand(available_moves, this->node_mem, &this->mem_idx, this->mem_max))
  {
    return nullptr;
  }
  this->expansion_counter++;

  return curr;
}

float FullPathMCTSAgent::simulation(FP_Node *node, std::vector<int> &available_moves)
{
  if (available_moves.empty())
  {
    return tsp->get_distance_between(node->current_location, 0);
  }

  if (node->N == 0)
  {
    float cost = 0.0f;
    int last = node->current_location;
    std::unordered_set<int> visited(available_moves.begin(), available_moves.end());
    int index = 0;
    while (!visited.empty())
    {
      int best_node = -1;
      float best = std::numeric_limits<float>::max();
      for (auto it = visited.begin(); it != visited.end(); ++it)
      {
        float dist = tsp->get_distance_between(last, *it);
        if (dist < best)
        {
          best = dist;
          best_node = *it;
        }
      }
      cost += best;
      last = best_node;
      available_moves[index++] = last;
      visited.erase(last);
    }
    return cost + tsp->get_distance_between(last, 0);
  }

  std::uniform_real_distribution<> dis(0, 1);
  unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(available_moves.begin(), available_moves.end(), std::default_random_engine(num));
  float cost = this->tsp->get_distance_between(node->current_location, available_moves[0]);
  cost += this->tsp->get_distance_between(available_moves.back(), 0);
  for (unsigned int i = 1; i < available_moves.size(); i++)
  {
    cost += tsp->get_distance_between(available_moves[i - 1], available_moves[i]);
  }
  return cost;
}

float FullPathMCTSAgent::score(FP_Node *node)
{
  float avg = node->Q / node->N;
  float var = node->Q2 / node->N - avg * avg;

  float m1 = this->C * sqrt(log(node->parent->N) / node->N);
  float m2 = sqrt(var + this->D / node->N);
  float m3 = node->best_Q;

  return m3 + avg - m1 - m2;
}

void FullPathMCTSAgent::back_propagate(float score, FP_Node *node)
{
  while (node != nullptr)
  {
    node->best_Q = std::min(node->best_Q, score);
    node->N += 1;
    node->Q += score;
    node->Q2 += score * score;
    node = node->parent;
  }
}
