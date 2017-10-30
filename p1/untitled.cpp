#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{

   cout << "File creation program \n";
   ofstream outf("aa.dat");

   outf << "Has a series of 10 random, unique insertions from 1 to 10 followed by 10 random, unique deletions\n";
   srand(1);
   int *nums = new int[10];
   for(int i = 1; i <= 10; i++)
     nums[i - 1] = i;

   for(int i = 10; i >= 1; i--)
   {
     int pos = rand() % i; 
     outf << "i" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   for(int i = 1; i <= 10; i++)
     nums[i - 1] = i;

   for(int i = 10; i >= 1; i--)
   {
     int pos = rand() % i;
     outf << "d" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   outf.close();

  return 1;
}
