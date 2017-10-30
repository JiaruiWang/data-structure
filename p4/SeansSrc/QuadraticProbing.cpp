#include <cstring>
#include "QuadraticProbing.h"


/**
 * Construct the hash table.
 */
template <int wordSize>
QuadraticHashTable<wordSize>::QuadraticHashTable(int sz ) : tableSize(sz)
{
  array = new CharArray<wordSize> [tableSize];
}

 
template <int wordSize>
void QuadraticHashTable<wordSize>::insert(const char *x, unsigned currentPos2)
{
        // Insert x as active
    unsigned currentPos = findPos( x, currentPos2 );
    strcpy(array[ currentPos ].array, x);
}


template <int wordSize>
unsigned QuadraticHashTable<wordSize>::findPos( const char *x, unsigned currentPos ) const
{
//  for( int i = 0; x[i]; i++ )
//     currentPos = 37 * currentPos + x[ i ];

  currentPos %= tableSize;
  //if( currentPos < 0 )
   //   currentPos += tableSize;

  while( array[ currentPos ].array[0] != '\0' 
    && strcmp(array[ currentPos ].array, x ) != 0)
  {
    currentPos++;
     currentPos = currentPos % tableSize;
  }

  return currentPos;
}  // findPos()


template <int wordSize>
bool QuadraticHashTable<wordSize>::find( const char* x, unsigned currentPos2 ) const
{
  unsigned currentPos = findPos( x, currentPos2 );
  return  array[currentPos ].array[0] != '\0';
}
