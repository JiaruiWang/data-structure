// Author: Sean Davis

#ifndef routerH
#define routerH

#include "RouterRunner.h"
#include "QuadnaryHeap.h"
#define CITY -1
#define UNKNOWN 0
#define KNOWN 1




class DijNode
{
public:
  short pvx;
  short pvy;
  int cost;
  char elevation;
  char known;
  DijNode():cost(0x2FFFFFFF), known(0){}
}; // class DijNode


class Router
{
  BinaryHeap<HeapNode> heap;
  DijNode **Dij;
  bool *connected;
  int top;
  short width;
  void shortestPath(short *x3, short *y3);
  void storePath(short x, short y, Edge *paths, int &pathCount);
public:
  Router(short **map, int widt);
  ~Router();
  void findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount);
};


#endif
