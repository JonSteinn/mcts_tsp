#ifndef TREE_H
#define TREE_H

#include <vector>

struct Node
{
  int current_location;
  float Q;
  int N;
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
    for (int it = begin(c); it != end(c); it++)
    {
      Node *child = new Node(it, this);
      children.push_back(child)
    }
  }
  void reset()
  {
    for (auto it = begin(children); it != end(children); ++it)
    {
      if (current_location == -1)
      {
        (*it).reset()
      }
      else
      {
        delete it;
      }
    }
    Q = 0;
    N = 0;
    next_to_expand = 0;
    if (current_location != -1)
    {
      children.clear()
    }
  }
  struct Node *get_next()
  {
    return children[next_to_expand++];
  }
};

#endif