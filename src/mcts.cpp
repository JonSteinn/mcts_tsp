#include "mcts.h"

MCTSAgent::MCTSAgent(TSP *tsp, double time_limit)
{
  tree = new Node(0, NULL);
  for (int i = 1; i < tsp->get_number_of_data_points(); i++)
  {
    tree->children.push_back(new Node(i, tree));
  }

  this->tsp = tsp;
  this->time_limit = time_limit;
}

MCTSAgent::~MCTSAgent()
{
  delete tree;
}

void MCTSAgent::move_root(Node *node)
{
  if (not node->is_root())
  {
    node->make_root();
    delete this->tree;
    tree = node;
  }
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
    float tree_cost = 0.0f;
    Node *new_node = this->tree_policy(available_moves, &tree_cost);
    float score = tree_cost + this->simulation(new_node, available_moves);
    this->back_propagate(score, new_node);
    available_moves.clear();
  }

  Node *best_move = nullptr;
  int best = -1;
  for (auto it = this->tree->children.begin(); it != this->tree->children.end(); ++it)
  {
    if ((*it)->N > best)
    {
      best = (*it)->N;
      best_move = *it;
    }
  }

  int move = best_move->current_location;
  this->retired_moves.insert(move);
  this->move_root(best_move);
  return move;
}

bool MCTSAgent::time_is_up()
{
  timing now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->start_time;
  return elapsed.count() >= this->time_limit;
}

Node *MCTSAgent::tree_policy(std::vector<int> &available_moves, float *tree_cost)
{
  Node *curr = this->tree;
  while (curr->fully_expanded())
  {
    Node *next = nullptr;
    float best = std::numeric_limits<float>::max();

    if (curr->children.empty())
      return curr;

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
    this->retired_moves.insert(next->current_location);
  }

  curr = curr->get_next();
  *tree_cost += this->tsp->get_distance_between(curr->parent->current_location, curr->current_location);
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

float MCTSAgent::simulation(Node *node, std::vector<int> &possible_moves)
{
  if (possible_moves.empty())
  {
    return tsp->get_distance_between(node->current_location, 0);
  }

  unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(possible_moves.begin(), possible_moves.end(), std::default_random_engine(num));
  float cost = this->tsp->get_distance_between(node->current_location, possible_moves[0]);
  cost += this->tsp->get_distance_between(possible_moves.back(), 0);
  for (unsigned int i = 1; i < possible_moves.size(); i++)
  {
    cost += tsp->get_distance_between(possible_moves[i - 1], possible_moves[i]);
  }
  return cost;
}

void MCTSAgent::back_propagate(float score, Node *node)
{
  node->N += 1;
  node->Q += score;
  if (not node->is_root())
  {
    this->retired_moves.erase(node->current_location);
    MCTSAgent::back_propagate(score, node->parent);
  }
}

float MCTSAgent::score(Node *node)
{
  float avg = node->Q / node->N;
  float member2 = this->C * sqrt(log(node->parent->N) / node->N);
  return avg - member2;
}
