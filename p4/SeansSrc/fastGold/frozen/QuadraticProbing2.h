#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

#include "mynew.h"
#include <iostream>
using namespace std;

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an initialization for ITEM_NOT_FOUND
//       and an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items
//--> Static method to hash strings

class Int1_5
{
public:
  Int1_5(unsigned v1 = 0, unsigned short v0 = 0) 
  {*((unsigned int*) ar) = v1; *((unsigned short*) &ar[4]) = v0;  }
  char ar[6];
  bool operator!= (const Int1_5 &rhs) const {
    return *((unsigned int*) ar) !=  *((unsigned int*) rhs.ar)
    || *((unsigned short*) &ar[4]) != *((unsigned short*) &rhs.ar[4]);}
}; // class Int2


class Int2
{
public:
  Int2(unsigned v1 = 0x8000, unsigned v0 = 0): value0(v0), value1(v1){}
  unsigned value0;
  unsigned value1;
  bool operator!= (const Int2 &rhs) const {return value0 != rhs.value0
    || value1 != rhs.value1;}
}; // class Int2

class Int3
{
public:
  Int3(unsigned v2 = 0x8000, unsigned v1 = 0, unsigned v0 = 0): value0(v0),
    value1(v1), value2(v2){}
  unsigned value0;
  unsigned value1;
  unsigned value2;
  bool operator!= (const Int3 &rhs) const {return value0 != rhs.value0
    || value1 != rhs.value1 || value2 != rhs.value2;}
}; // class Int3

class Int4
{
public:
  Int4(unsigned v3 = 0x8000, unsigned v2 = 0, unsigned v1 = 0, unsigned v0 = 0):
    value0(v0), value1(v1), value2(v2), value3(v3){}
  unsigned value0;
  unsigned value1;
  unsigned value2;
  unsigned value3;
  bool operator!= (const Int4 &rhs) const {return value0 != rhs.value0
    || value1 != rhs.value1 || value2 != rhs.value2 || value3 != rhs.value3;}
}; // class Int3
template <class HashedObj>
class QuadraticHashTable2
{
  public:
    explicit QuadraticHashTable2( const HashedObj & notFound, int sz = 101 );
    ~QuadraticHashTable2(){delete [] array;} // cout << size << " " << currentSize << endl;}
    const HashedObj & find( const HashedObj & x ) const;
    void makeEmpty( );
    void insert( const HashedObj & x );
  private:
    HashedObj *array;
    int currentSize;
    int size;
    const HashedObj ITEM_NOT_FOUND;
    int findPos( const HashedObj & x ) const;
    int hash(unsigned key, int tableSize ) const;
    int hash(const Int1_5 &key, int tableSize ) const;
    int hash(const Int2 &key, int tableSize ) const;
    int hash(const Int3 &key, int tableSize ) const;
    int hash(const Int4 &key, int tableSize ) const;

    void rehash( );
};

#include "QuadraticProbing2.cpp"
#endif
