#include "speller.h"

Speller::Speller(char *dictionary[], int dictSize)
{
  int i, length, bitPos, bitLen, letter;
  unsigned currentPos;
  double surplus = 4.271;
  
 // tables[1] = new QuadraticHashTable<1>(1343 * surplus);
  tables[2] = new QuadraticHashTable<2>(1343 * surplus);
  tables[3] = new QuadraticHashTable<3>(4852 * surplus);
  tables[4] = new QuadraticHashTable<4>(22712 * surplus);
  tables[5] = new QuadraticHashTable<5>(16123 * surplus);
  tables[6] = new QuadraticHashTable<6>(29078 * surplus);
  tables[7] = new QuadraticHashTable<7>(16912 * surplus);
  tables[8] = new QuadraticHashTable<8>(4136 * surplus);
  tables[9] = new QuadraticHashTable<9>(3806 * surplus);
  tables[10] = new QuadraticHashTable<10>(620 * surplus);
  tables[11] = new QuadraticHashTable<11>(367 * surplus);
  tables[12] = new QuadraticHashTable<12>(51 * surplus);
  tables[13] = new QuadraticHashTable<13>(10 * surplus);
  
  
  for(i = 0; i < dictSize; i++)
  {
    currentPos = 0;
    bitLen = bitPos = 0;
    char word[20];
    
    *((long long*)&word[0]) = *((long long*) &word[8]) = 0;
    
    for( length = 0; dictionary[i][length]; length++)
    {  
     currentPos = 37 * currentPos + dictionary[i][length];
     letter = dictionary[i][length] - 96;
     if(bitPos < 3)
       word[bitLen] |= letter << (3 - bitPos);
     else
     {
       word[bitLen++] |= letter >> (bitPos - 3);
       word[bitLen] |= letter << (11 - bitPos);
     }
     bitPos = (bitPos + 5) % 8;
    } // for length
    
    tables[bitLen + 1]->insert(word, currentPos);
    // length is the length of the word
    
  } // for each word in dictionary
}  // Speller()

Speller::~Speller()
{
  for(int i = 2; i < 14; i++)
    delete tables[i];
}


void Speller::check(char *document[], int docSize, int misspelled[], 
  int *misspelledCount)
{
  int i, length, bitLen, bitPos;
  unsigned currentPos;
  *misspelledCount = 0;
  
  for(i = 0; i < docSize; i++)
  {
    //if(i == 716)
  //  cout << i << endl;
    currentPos = 0;
    bitLen = bitPos = 0;
    char letter;
    char word[20];
    
    *((long long*)&word[0]) = *((long long*) &word[8]) = 0;
    
    for( length = 0; document[i][length]; length++)
    {  
      currentPos = 37 * currentPos + document[i][length];
      letter = document[i][length] - 96;
      if(bitPos < 3)
        word[bitLen] |= letter << (3 - bitPos);
      else
      {
        word[bitLen++] |= letter >> (bitPos - 3);
        word[bitLen] |= letter << (11 - bitPos);
      }  // else going to use next char
      
      bitPos = (bitPos + 5) % 8;
    } // for length
    
    if(! tables[bitLen + 1]->find(word, currentPos))
      misspelled[(*misspelledCount)++] = i;
  } // for each word in document
}  // check()

