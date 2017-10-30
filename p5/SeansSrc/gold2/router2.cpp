// Author Sean Davis
#include "router2.h"
#include "BinaryHeap.h"
#include <iostream>

using namespace std;

Router::Router(short **map, int w):heap(1000000), width(w)
{
  stack = new CityPos[1000000];
  top = 0;
  Dij = new DijNode*[width];
  for(int i = 0; i < width; i++)
  {
    Dij[i] = new DijNode[width];
    for(int j = 0; j < width; j++)
      Dij[i][j].elevation = map[i][j];
  } // for i;
}

Router::~Router()
{
  delete [] stack;
  for(int i = 0; i < width; i++)
    delete [] Dij[i];

  delete [] Dij;
  delete [] connected;
} // ~Router()

void Router::storePath(short x, short y, Edge *paths, int &pathCount)
{
  short pvx, pvy;

  Dij[x][y].cost = 0;
  heap.insert(HeapNode(x, y, 0));
  pvx = Dij[x][y].pvx;
  pvy = Dij[x][y].pvy;

  while(Dij[pvx][pvy].cost > 0)
  {
    Dij[pvx][pvy].cost = 0;
    Dij[pvx][pvy].known = false;
    heap.insert(HeapNode(pvx, pvy, 0));
    paths[pathCount].startX = x;
    paths[pathCount].endX = pvx;
    paths[pathCount].startY = y;
    paths[pathCount++].endY = pvy;
    x = pvx;
    y = pvy;
    pvx = Dij[x][y].pvx;
    pvy = Dij[x][y].pvy;

  }

  paths[pathCount].startX = x;
  paths[pathCount].endX = pvx;
  paths[pathCount].startY = y;
  paths[pathCount++].endY = pvy;

} // storePath()

void Router::shortestPath(short *x3, short *y3)
{
  HeapNode node;
  short x, y, x2, y2, startX, endX, startY, endY;
  int cost, cost2;
  int elevation;

  heap.deleteMin(node);
  x = node.x;
  y = node.y;


  while(true)
  {
    cost = Dij[x][y].cost;
    startX = (0 > x - 1) ? 0 : x - 1;
    endX = (width - 1 < x + 1) ? width - 1 : x + 1;
    startY = (0 > y - 1) ? 0 : y - 1;
    endY = (width - 1 < y + 1) ? width - 1 : y + 1;
    elevation = Dij[x][y].elevation;
    Dij[x][y].known = true;


    for(x2 = startX; x2 <= endX; x2++)
      for(y2 = startY; y2 <= endY; y2++)
        if((x2 != x || y2 != y) && !Dij[x2][y2].known)
        {
          if(Dij[x2][y2].cost < 0)
          {
            Dij[x2][y2].pvx = x;
            Dij[x2][y2].pvy = y;
            *x3 = x2;
            *y3 = y2;
            return;
          }

          cost2 = cost + (elevation - Dij[x2][y2].elevation)
            * (elevation - Dij[x2][y2].elevation) + 10;
          if(x2 == 1 && y2 == 0)
            x2 = 1;

          if(Dij[x2][y2].cost > cost2)
          {
            if(Dij[x2][y2].cost == 0x2FFFFFFF)
            {
              stack[top].x = x2;
              stack[top++].y = y2;
            }
            Dij[x2][y2].cost = cost2;
            Dij[x2][y2].pvx = x;
            Dij[x2][y2].pvy = y;
            heap.insert(HeapNode(x2, y2, cost2));
          } // if an improved cost
        } // if not this one

    do
    {
      heap.deleteMin(node);
      x = node.x;
      y = node.y;
    } while(Dij[x][y].known);
  } // while true
} // ShortestPath()



void Router::fillHeap(Edge *paths, int pathCount)
{
  short x, y;
  for(int i = pathCount - 1; i >= 0; i--)
  {
    x = paths[i].startX;
    y = paths[i].startY;
    if(Dij[x][y].cost > 0)
    {
      Dij[x][y].cost = 0;
      heap.array[++heap.currentSize] = HeapNode(x, y, 0);
    } // if not in heap yet

    x = paths[i].endX;
    y = paths[i].endY;
    if(Dij[x][y].cost > 0)
    {
      Dij[x][y].cost = 0;
      heap.array[++heap.currentSize] = HeapNode(x, y, 0);
    }  // if not in heap yet
  } // for i
}  // fillHeap()


void Router::findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount)
{
  pathCount = 0;
  short x, y;
  int connectedCount = 1;
  connected = new bool[cityCount];

  for(int i = 0; i < cityCount; i++)
  {
    Dij[cityPos[i].x][cityPos[i].y].cost = -1; // mark city
    connected[i] = false;
  } // for i


  connected[0] = true;
  Dij[cityPos[0].x][cityPos[0].y].cost = 0;
  heap.insert(HeapNode(cityPos[0].x, cityPos[0].y, 0));

  while(connectedCount < cityCount)
  {
    //fillHeap(paths, pathCount);
    shortestPath(&x, &y);
    storePath(x, y, paths, pathCount);

    for(int i = 0; i < top; i++)
    {
      if( Dij[stack[i].x][stack[i].y].cost > 0)
      {
        Dij[stack[i].x][stack[i].y].known = false;
        Dij[stack[i].x][stack[i].y].cost = 0x2FFFFFFF;
      }
    }

    top = 0;

    for(int i = 0; i < cityCount; i++)
    {
      if(cityPos[i].x == x && cityPos[i].y == y )
      {
        connected[i] = true;
        connectedCount++;
        cout << i << endl;
      }
      if( Dij[cityPos[i].x][cityPos[i].y].cost == 0x2FFFFFFF)
        Dij[cityPos[i].x][cityPos[i].y].cost = 0; // mark connected city
    } // for i

    //heap.makeEmpty();
  } // while not all cities connected

}
