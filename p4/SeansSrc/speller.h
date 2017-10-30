// Author: Sean Davis
#ifndef SPELLER_H
#define SPELLER_H

#include "QuadraticProbing.h"

class Speller
{
  HashTable *tables[21];
public:
  Speller(char *dictionary[], int dictSize);
  void check(char *document[], int docSize, int misspelled[], int *misspelledCount);
  ~Speller();
}; // class Speller


#endif
