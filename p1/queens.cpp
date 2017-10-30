#include <iostream>
#include "StackAr.h"
#include "CPUTimer.h"

using namespace std;

bool isFeasible(int s, int i, int* p)
{
  /*  if (i == 0)
   return true;
   else //
   return (p[s] != p[i] && p[s] - p[i] != s-i && p[s] - p[i] != i - s) &&
   isFeasible(s, i - 1, p);
   */ // recursion approach
   
  bool all = true;
  
  while(i > 0)
  {
    all = all && (p[s] != p[i] && p[s] - p[i] != s-i && p[s] - p[i] != i - s);
    i--;
  }
  
  return all;  // change recursion to iteration
}//

// void queens(int start, int end, int* p)
// {
  // if (start == end + 1)
  // {
  //   for (int i = 1; i < 8; ++i)
  //     cout << p[i] << ",";
  //   cout << p[8] << endl;
  // }//
  // else //
  //   for (p[start] = 1; p[start] <= 8; ++p[start])
  //     if (isFeasible(start, start - 1, p))
  //       queens(start + 1, end, p); 
  
// }//// recursion approach

int main(int argc, char const *argv[])
{
  CPUTimer ct;
  ct.reset();
  int p[9];
  // queens(1, 8, p); //recursion approach  

  int pre = 1; // if current p[i] > 8, go back to pre = i - 1
  int i = 1;
  int next = 1; // if if current p[i] > 8, go back to pre = i - 1, start after p[pre] in line pre
  while (pre > 0)
  { // if pre <= 0 , it means p[1] = 9, iteration is done
    for (i = pre; i < 9; ++i) 
    {
      for (p[i] = next; p[i] < 9; ++p[i])
        if (isFeasible(i, i - 1, p))
        {
          if (i == 8) 
          {
            for (int j = 1; j < 8; j++)
              cout << p[j] << ",";

            cout << p[8] << endl;
            pre = i;  // go to next solution, right after current solution, keep i after p[8]
            next = p[8] + 1; // go to next solution, right after current solution, keep i after p[8]
            break; // keep next = p[8] + 1, other wise next = 1
          }// found one solution

          next = 1; // current p[i] is feasible, break to next i and p[i], set next = 1 for next line
          break; // keep current p[i] to see if it is feasible or run out 1 to 8
        }// if current i is feasible

      if (p[i] == 9)
      {
        pre = i - 1;
        next = p[pre] + 1;
        break; // break to go to pre i, otherwise go to next i
      }// current i has no feasible solution, go to pre i,
    }//
  }//
  cout << "CPU time: " << ct.cur_CPUTime() << endl;
  return 0;
}//