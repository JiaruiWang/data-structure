#include "QuadraticProbing2.h"
#include "mynew.h"

/**
* Construct the hash table.
*/
template <class HashedObj>
QuadraticHashTable2<HashedObj>::QuadraticHashTable2( const HashedObj & notFound,
  int sz ) : size(sz), ITEM_NOT_FOUND( notFound )
{
  array = new HashedObj[size];
  makeEmpty( );
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void QuadraticHashTable2<HashedObj>::insert( const HashedObj & x )
{
  currentSize++;
   int currentPos = findPos( x );
   array[ currentPos ] = x;
}


/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
template <class HashedObj>
int QuadraticHashTable2<HashedObj>::findPos( const HashedObj & x ) const
{
   int collisionNum = 0;
   int currentPos = hash( x, size);

   while( array[ currentPos ] != x
      && array[ currentPos ] != ITEM_NOT_FOUND )
   {
      currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
      if( currentPos >= size)
      currentPos -= size;
   }

/* 7*/      return currentPos;
}



/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj & QuadraticHashTable2<HashedObj>::find( const HashedObj & x ) const
{
   int currentPos = findPos( x );
   return array[currentPos ];
}

/**
* Make the hash table logically empty.
*/
template <class HashedObj>
void QuadraticHashTable2<HashedObj>::makeEmpty( )
{
   currentSize = 0;
   for( int i = 0; i < size; i++ )
       array[ i ] = ITEM_NOT_FOUND;
}


/**
* A hash routine for ints.
*/
template <class HashedObj>
int QuadraticHashTable2<HashedObj>::hash( unsigned key, int tableSize ) const
{
   return key % tableSize;
}

template <class HashedObj>
int QuadraticHashTable2<HashedObj>::hash(const Int1_5 &key, int tableSize ) const
{
   return *((unsigned int*) key.ar) % tableSize;
}

template <class HashedObj>
int QuadraticHashTable2<HashedObj>::hash(const Int2 &key, int tableSize ) const
{
   return key.value0 % tableSize;
}


template <class HashedObj>
int QuadraticHashTable2<HashedObj>::hash(const Int3 &key, int tableSize ) const
{
   return key.value0 % tableSize;
}


template <class HashedObj>
int QuadraticHashTable2<HashedObj>::hash(const Int4 &key, int tableSize ) const
{
   return key.value0 % tableSize;
}
