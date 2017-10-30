// Author: Sean Davis
#ifndef spellerH
#define spellerH

#include "QuadraticProbing2.h"




class Speller
{
  QuadraticHashTable2 <unsigned> hash1;
  QuadraticHashTable2 <Int1_5> hash1_5;
  QuadraticHashTable2 <Int2> hash2;
  QuadraticHashTable2 <Int3> hash3;
  QuadraticHashTable2 <Int4> hash4;
  int dictionarySize;
public:
  Speller(char *dictionary[], int dictSize);
  void check(char *document[], int docSize, int misspelled[], int *misspelledCount);
}; // class Speller


#endif
