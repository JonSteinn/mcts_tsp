#include "mcts.h"

MCTSAgent::MCTSAgent(TSP *tsp, double time_limit)
{
  tree = new Node(0, NULL);
  this->tsp = tsp;
  this->time_limit = time_limit;
  this->fake_move = 0;
}

MCTSAgent::~MCTSAgent()
{
  delete tree;
}

int MCTSAgent::next_move()
{
  if (this->retired_moves.empty())
  {
    this->retired_moves.insert(0);
    return 0;
  }

  this->start_time = std::chrono::high_resolution_clock::now();
  std::vector<int> available_moves;

  while (not this->time_is_up())
  {
    Node *new_node = this->tree_policy(available_moves);
    // 1. Tree policy
    // 2. Playouts
    // 3. Back propagate
  }
  return this->fake_move++;
}

bool MCTSAgent::time_is_up()
{
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count() >= this->time_limit;
}

Node *MCTSAgent::tree_policy(std::vector<int> &available_moves)
{
  Node *curr = this->tree;
  while (curr->fully_expanded())
  {
    Node *next = nullptr;
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
    this->retired_moves.insert(next->current_location);
  }

  curr = curr->get_next();
  this->retired_moves.insert(curr->current_location);

  int n = this->tsp->get_number_of_data_points();
  for (int i = 0; i < n; i++)
  {
    if (this->retired_moves.find(i) == this->retired_moves.end())
    {
      available_moves.push_back(i);
    }
  }

  curr->expand(available_moves);
  return curr;
}

float MCTSAgent::simulation(Node *node)
{
  return 0.0f;
}

void MCTSAgent::back_propagate(float score, Node *node)
{
  node->N += 1;
  node->Q += score;
  if (node->parent != NULL)
  {
    MCTSAgent::back_propagate(score, node->parent);
  }
}

float MCTSAgent::score(Node *node)
{
  float avg = node->Q / node->N;
  float member2 = this->C * sqrt(log(node->parent->N) / node->N);
  return avg - member2;
}
