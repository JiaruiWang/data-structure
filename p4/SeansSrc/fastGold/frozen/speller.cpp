#include "speller.h"
#include <iostream>
#include "mynew.h"

using namespace std;
double surplus = 1.5;

Speller::Speller(char *dictionary[], int dictSize)
  : hash1(0x8000, surplus * 28969), hash1_5(Int1_5(), surplus * 45023),  hash2(Int2(), surplus * 21241), hash3(Int3(), surplus * 4760),
    hash4(Int4(), surplus * 10), dictionarySize(dictSize)
{
  int j, k, temp, keys[4];
  for(int i = 0; i < dictSize; i++)
  {
    j = 0;
    temp = 0;
    k = 0;
    for(char *ptr = dictionary[i]; *ptr; ptr++)
    {
      temp = (temp << 5) + *ptr - 96; // 96 = 'a' - 1
      if(++j == 6)
      {
        keys[k++] = temp;
        j = 0;
        temp = 0;
      }
    }

    if(j > 0)
      keys[k++] = temp;
    if(k == 1)
      hash1.insert(keys[0]);
    else
      if(k == 2)
      {
        if(j > 0 && j < 4)
          hash1_5.insert(Int1_5(keys[0], (unsigned short) keys[1] & 0xFFFF)); 
        else
          hash2.insert(Int2(keys[1], keys[0]));
      }  
      else
        if(k == 3)
          hash3.insert(Int3(keys[2], keys[1], keys[0]));
        else
          hash4.insert(Int4(keys[3], keys[2], keys[1], keys[0]));
  }
} // Speller()


void Speller::check(char *document[], int docSize, int misspelled[],
  int *misspelledCount)
{
  int j, k, temp, keys[4], count = 0;
  for(int i = 0; i < docSize; i++)
  {
    j = 0;
    temp = 0;
    k = 0;
   // if(i == 7121)
     // cout << i << endl;
    for(char *ptr = document[i]; *ptr; ptr++)
    {
      temp = (temp << 5) + *ptr - 96;  // 96 = 'a' - 1
      if(++j == 6)
      {
        keys[k++] = temp;
        j = 0;
        temp = 0;
      }
    }

    if(j > 0)
      keys[k++] = temp;
    if(k == 1)
    {
      if(hash1.find(keys[0]) == 0x8000)
        misspelled[count++] = i;
    }
    else
      if(k == 2)
      {
        if(j > 0 && j < 4)
        {
          if(hash1_5.find(Int1_5(keys[0], (unsigned short) keys[1] & 0xFFFF)).ar[0] == 0) 
            misspelled[count++] = i;
        }
        else
        {
          if(hash2.find(Int2(keys[1], keys[0])).value1 == 0x8000)
            misspelled[count++] = i;
        }
      }
      else
        if(k == 3)
        {
          if(hash3.find(Int3(keys[2], keys[1], keys[0])).value2 == 0x8000)
            misspelled[count++] = i;
        }
        else
          if(hash4.find(Int4(keys[3],keys[2], keys[1], keys[0])).value3 == 0x8000)
          {
            misspelled[count++] = i;
          }
  } // for i

  *misspelledCount = count;
} // check()

