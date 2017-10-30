#include <iostream>
#include"CPUTimer.h"
using namespace std;

int main(){
  int i, j = 0;
  CPUTimer ct;
  ct.reset();

  for(i = 0; i < 100000000; i++)
    if(++j == 3)
      j = 0;

  cout << "CPU time for if statement: " << ct.cur_CPUTime() << endl;
  ct.reset();

  for(i = 0; i < 100000000; i++)
    if(j == 2)
      j = 0;
    else
      ++j;
  

  cout << "CPU time for if-else statement: " << ct.cur_CPUTime() << endl;

   ct.reset();

  for(i = 0; i < 100000000; i++)
    j = ++j % 3;
      
  cout << "CPU time for mod: " << ct.cur_CPUTime() << endl;

   ct.reset();

  for(i = 0; i < 100000000; i++)
    j = 0xFFFFF >> 12;

  cout << "CPU time for  bit shifting: " << ct.cur_CPUTime() << endl;

   ct.reset();

  for(i = 0; i < 100000000; i++)
    j = 0xFFFFF / 0x1000;

  cout << "CPU time for division: " << ct.cur_CPUTime() << endl;

   ct.reset();

  for(i = 0; i < 100000000; i++)
    j = 0xFFFFF << 12;

  cout << "CPU time for  bit shifting : " << ct.cur_CPUTime() << endl;

   ct.reset();

  for(i = 0; i < 100000000; i++)
    j = 0xFFFFF * 0x1000;

  cout << "CPU time for multicplication: " << ct.cur_CPUTime() << endl;
  return 0;

}


