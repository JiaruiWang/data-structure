#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_


template <int wordSize>
class CharArray
{
  public:
  char array[wordSize];
  CharArray() {array[0] = '\0';}
};

class HashTable
{
public:
  virtual ~HashTable() {};
  virtual  bool find( const char* x, unsigned currentPos) const = 0;
  virtual void insert( const char * x, unsigned currentPos) = 0;
};

template <int wordSize>
class QuadraticHashTable : public HashTable
{
  public:
    explicit QuadraticHashTable(int sz);
    ~QuadraticHashTable() { delete [] array; }
    bool find( const char* x, unsigned currentPos) const;
    void insert( const char * x, unsigned currentPos );
  private:
    CharArray<wordSize> *array;
    int currentSize;
    int tableSize;
    unsigned findPos( const char *x, unsigned currentPos ) const;
};

#include "QuadraticProbing.cpp"
#endif
