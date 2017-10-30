#include <iostream>
#include "mynew.h"
using namespace std;

class Char7
{
  char ar[7];
};  // Char7

extern int currentRAM;

int main()
{
  currentRAM = 0;

  for(int i = 0; i < 10; i++)
    char *ptr = new char[7]; 

  cout << "10 char[7]'s: " << currentRAM << endl;
  currentRAM = 0;
  Char7 *ptr7 = new Char7[10];
  cout << "10 Char7's: " << currentRAM << endl;
  return 0;
} // main()
