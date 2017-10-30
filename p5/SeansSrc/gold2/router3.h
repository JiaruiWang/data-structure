// Author: Sean Davis

#ifndef router3H
#define router3H

#include "RouterRunner.h"
#include "BinaryHeap.h"
#include <limits.h>

class DijNode
{
public:
  short pvx;
  short pvy;
  int cost;
  char elevation;
  bool known;
  DijNode():cost(INT_MAX), known(false){}
}; // class DijNode


class Router
{
  BinaryHeap<HeapNode> heap;
  CityPos *stack;
  DijNode **Dij;
  bool *connected;
  int top;
  short width;
  void shortestPath(short *x3, short *y3);
  void storePath(short x, short y, Edge *paths, int &pathCount);
  void fillHeap(Edge *paths, int pathCount);

public:
  Router(short **map, int widt);
  ~Router();
  void findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount);
};


#endif
