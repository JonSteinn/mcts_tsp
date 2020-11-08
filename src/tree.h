#include <vector>

#ifndef TREE_H
#define TREE_H

const int MAX = 10;

struct Node
{
  int currentLocation;
  float Q;
  int N;
  struct Node *parent;
  std::vector<struct Node *> children;
  int nextToExpand;
  Node(int current, struct Node *p)
  {
    currentLocation = current;
    Q = 0;
    N = 0;
    nextToExpand = 0;
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
  struct Node *getNext()
  {
    return children[nextToExpand++];
  }
};

#endif