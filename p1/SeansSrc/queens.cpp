#include <iostream>
#include "CPUTimer.h"

using namespace std;

int main()
{
  CPUTimer ct;
  ct.reset();
  int P[9];
  int i, diff, k = 1;
  
  P[1] = 1;
  
  while(true)
  {
  	while(P[k] == 9)
  	{ // if exhausted this column back up
  	  if(k == 1)
  	  	return 0; // done
  	  P[k--] = 1;
  	  ++P[k];
  	} 
  	
  	for(i = 1; i < k; i++)
   	{
   	  diff = P[i] - P[k];
   	  if(diff == 0 || diff == k - i || diff == i - k)
   	    break;
   	}

   	if(i == k) // success for this column
  	{
  	  if(k == 8) // success for whole board
  	  {
  	   	for(int j = 1; j < 8; j ++)
  	   	  cout << P[j] << ',';
  	  	cout << P[8] << endl;
     		P[7]++;
     		k--; 	  	  	
  	  } 
  	  else // success for column < 8 so move to next column 
   	  	P[++k] = 1;
	  }  // if success for this column
  	else // failed at this column
  	  if(++P[k] > 8) // exhausted this column so backup
  	    ++P[--k];
  } // while P[1] not exhausted	
  
  cout << "CPU time: " << ct.cur_CPUTime() << endl;
  return 0;
} // main()
