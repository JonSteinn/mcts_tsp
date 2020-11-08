#include <vector>

#ifndef TREE_H
#define TREE_H

const int MAX = 10;

struct Node
{
  int current_location;
  float q;
  int n;
  struct Node *parent;
  std::vector<struct Node *> children;
  int next_to_expand;
  Node(int current, struct Node *p)
  {
    current_location = current;
    Q = 0;
    N = 0;
    next_to_expand = 0;
    parent = p;
  }
  ~Node()
  {
    for (auto it = begin(children); it != end(children); ++it)
    {
      delete it;
    }
    delete this;
  }
  void expand(std::vector<int> &c)
  {
    for (auto it = begin(c); it != end(c); ++it)
    {
      Node *child = new Node(it, this);
      children.push_back(child)
    }
  }
  struct Node *get_next()
  {
    return children[next_to_expand++];
  }
};

#endif