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
  int nextToExpand = 0;
  struct Node *getNext()
  {
    return children[nextToExpand++];
  }
};

#endif