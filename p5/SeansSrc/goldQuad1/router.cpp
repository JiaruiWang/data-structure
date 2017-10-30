// Author Sean Davis
#include "router.h"
#include <iostream>

using namespace std;

Router::Router(short **map, int w):heap(1000000), width(w)
{
  top = 0;
  Dij = new DijNode*[width];
  stack = new CityPos[1000000];
  for(int i = 0; i < width; i++)
  {
    Dij[i] = new DijNode[width];
    for(int j = 0; j < width; j++)
      Dij[i][j].elevation = map[i][j];
  } // for i;
}

Router::~Router()
{
  for(int i = 0; i < width; i++)
    delete [] Dij[i];

  delete [] Dij;
  // delete [] connected;
  delete [] stack;
} // ~Router()

void Router::storePath(short x, short y, Edge *paths, int &pathCount)
{
  short pvx, pvy;
  Dij[x][y].cost = 0;  // This is a city
  Dij[x][y].known = KNOWN;
  pvx = Dij[x][y].pvx;
  pvy = Dij[x][y].pvy;

  while(Dij[pvx][pvy].cost > 0 || Dij[pvx][pvy].known == KNOWN)
  {
    Dij[pvx][pvy].cost = 0;
    Dij[pvx][pvy].known = UNKNOWN;
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

  for(int i = 0; i < top; i++)
    if(Dij[stack[i].x][stack[i].y].cost != 0)
      Dij[stack[i].x][stack[i].y].cost = 0x2FFFFFF;

  top = heap.currentSize;
  
  for(int i = 1; i < top; i++)
  {
    heap.position[heap.array[i].x * 1000 + heap.array[i].y] = -1;
    if(Dij[heap.array[i].x][heap.array[i].y].cost != 0)
      Dij[heap.array[i].x][heap.array[i].y].cost = 0x2FFFFFF; 
  }
   
  top = 0;
} // storePath()

void Router::shortestPath(short *x3, short *y3)
{
  HeapNode node;
  short x, y, x2, y2, startX, endX, startY, endY;
  int cost, cost2;
  int elevation;
  DijNode *ptr;

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
    Dij[x][y].known = KNOWN;


    for(x2 = startX; x2 <= endX; x2++)
      for(y2 = startY; y2 <= endY; y2++)
        if((x2 != x || y2 != y) ) // && Dij[x2][y2].known < 1)
        {
          ptr = & Dij[x2][y2];

           if(ptr->cost == 0 && ptr->known != KNOWN)
           {
             ptr->pvx = x;
             ptr->pvy = y;
             *x3 = x2;
             *y3 = y2;
             return;
           }
           cost2 = cost + (elevation - ptr->elevation)
            * (elevation - ptr->elevation) + 10;
       

          if(ptr->cost > cost2)
          {
            ptr->pvx = x;
            ptr->pvy = y;

            if(heap.position[x2 * 1000 + y2] == -1)  // not in heap
              heap.insert(HeapNode(x2, y2, cost2));
            else
              heap.decreaseKey(HeapNode(x2, y2, cost2));

            ptr->cost = cost2;
          } // if an improved cost
        } // if not this one

    do
    {
      heap.deleteMin(node);
      x = node.x;
      y = node.y;

     } while(Dij[x][y].cost < node.cost);

    stack[top].x = x;
    stack[top++].y = y;

    if(Dij[x][y].known == CITY)
    {
      cout << Dij[x][y].cost << " " << (int) Dij[x][y].elevation <<  endl;
      *x3 = x;
      *y3 = y;
      return;
    }

  } // while true
} // ShortestPath()

int CityPosCmp(const void *ptr1, const void *ptr2)
{
  return ((CityPos*) ptr1)->x - ((CityPos*) ptr2)->x;
}

void Router::findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount)
{
  pathCount = 0;
  short x, y;
  CityPos cityPos2[20];

  for(int i = 0; i < cityCount; i++)
  {
    Dij[cityPos[i].x][cityPos[i].y].known = CITY; // mark city
    cityPos2[i] = cityPos[i];
  } // for i

 
  qsort(cityPos2, cityCount, sizeof(CityPos), CityPosCmp);
 
  for(int j = 0;  j < cityCount; j++)
  {
    Dij[cityPos2[j].x][cityPos2[j].y].cost = 0;
    heap.insert(HeapNode(cityPos2[j].x, cityPos2[j].y, 0));
    Dij[cityPos2[j].x][cityPos2[j].y].known = KNOWN;
    shortestPath(&x, &y);
    storePath(x, y, paths, pathCount);
  }

}
