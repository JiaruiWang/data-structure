#include "speller.h"

Speller::Speller(char *dictionary[], int dictSize)
{
  int i, length;
  unsigned currentPos;
  double surplus = 1.30;
  
  tables[1] = new QuadraticHashTable<2>(107 * surplus);
  tables[2] = new QuadraticHashTable<3>(107 * surplus);
  tables[3] = new QuadraticHashTable<4>(1236 * surplus);
  tables[4] = new QuadraticHashTable<5>(4971 * surplus);
  tables[5] = new QuadraticHashTable<6>(9213 * surplus);
  tables[6] = new QuadraticHashTable<7>(13548 * surplus);
  tables[7] = new QuadraticHashTable<8>(16419 * surplus);
  tables[8] = new QuadraticHashTable<9>(15577 * surplus);
  tables[9] = new QuadraticHashTable<10>(13501 * surplus);
  tables[10] = new QuadraticHashTable<11>(10325 * surplus);
  tables[11] = new QuadraticHashTable<12>(6843 * surplus);
  tables[12] = new QuadraticHashTable<13>(4305 * surplus);
  tables[13] = new QuadraticHashTable<14>(2591 * surplus);
  tables[14] = new QuadraticHashTable<15>(1215 * surplus);
  tables[15] = new QuadraticHashTable<16>(651 * surplus);
  tables[16] = new QuadraticHashTable<17>(248 * surplus);
  tables[17] = new QuadraticHashTable<18>(122 * surplus);
  tables[18]= new QuadraticHashTable<19>(47 * surplus);
  tables[19] = new QuadraticHashTable<20>(7 * surplus + 1);
  tables[20] = new QuadraticHashTable<21>(7 * surplus);
  
  for(i = 0; i < dictSize; i++)
  {
    currentPos = 0;
    
    for( length = 0; dictionary[i][length]; length++)
     currentPos = 37 * currentPos + dictionary[i][length];
    
    tables[length]->insert(dictionary[i], currentPos);
    // length is the length of the word
    
  } // for each word in dictionary
}  // Speller()


Speller::~Speller()
{
  for(int i = 1; i < 21; i++)
    delete tables[i];
}  // ~Speller()


void Speller::check(char *document[], int docSize, int misspelled[], 
  int *misspelledCount)
{
  int i, length;
  unsigned currentPos;
  *misspelledCount = 0;
  
  for(i = 0; i < docSize; i++)
  {
    currentPos = 0;
    
    for( length = 0; document[i][length]; length++)
     currentPos = 37 * currentPos + document[i][length];
    
    if(! tables[length]->find(document[i], currentPos))
      misspelled[(*misspelledCount)++] = i;
  } // for each word in document
}  // check()

