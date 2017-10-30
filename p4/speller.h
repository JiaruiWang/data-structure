// Author: Sean Davis
#ifndef SPELLER_H
#define SPELLER_H

class Speller
{
public:
  Speller(char *dictionary[], int dictSize);
  ~Speller();
  void check(char *document[], int docSize, int misspelled[], int *misspelledCount);
}; // class Speller


#endif
