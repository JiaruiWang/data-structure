        #include "BinaryHeap.h"
#include <iostream>
using namespace std;

        /**
         * Construct the binary heap.
         * capacity is the capacity of the binary heap.
         */
        template <class Comparable>
        BinaryHeap<Comparable>::BinaryHeap( int cap )
          : currentSize(0), capacity(cap)
        {
          array = new Comparable[capacity + 1];
        }


        template <class Comparable>
        BinaryHeap<Comparable>::~BinaryHeap( )
        {
          delete [] array;
        }
        /**
         * Insert item x into the priority queue, maintaining heap order.
         * Duplicates are allowed.
         * Throw Overflow if container is full.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::insert( const Comparable & x )
        {
            if( isFull( ) )
                cout << "Heap Overflow";

                // Percolate up
            int hole = ++currentSize;
            for( ; hole > 1 && x.cost < array[ hole / 2 ].cost; hole /= 2 )
                array[ hole ] = array[ hole / 2 ];
            array[ hole ] = x;
        }

        /**
         * Find the smallest item in the priority queue.
         * Return the smallest item, or throw Underflow if empty.
         */
        template <class Comparable>
        const Comparable & BinaryHeap<Comparable>::findMin( ) const
        {
            if( isEmpty( ) )
                cout << "Heap Underflow\n";

            return array[ 1 ];
        }

        /**
         * Remove the smallest item from the priority queue.
         * Throw Underflow if empty.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::deleteMin( )
        {
            if( isEmpty( ) )
                cout << "Heap Underflow\n";
            else
            {
              array[ 1 ] = array[ currentSize-- ];
              percolateDown( 1 );
            }
        }

        /**
         * Remove the smallest item from the priority queue
         * and place it in minItem. Throw Underflow if empty.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
        {
            if( isEmpty( ) )
              cout << "Heap Underflow\n";
            else
            {
              minItem = array[ 1 ];
              array[ 1 ] = array[ currentSize-- ];
              percolateDown( 1 );
            }
        }

        /**
         * Establish heap order property from an arbitrary
         * arrangement of items. Runs in linear time.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::buildHeap( )
        {
            for( int i = currentSize / 2; i > 0; i-- )
                percolateDown( i );
        }

        /**
         * Test if the priority queue is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Comparable>
        bool BinaryHeap<Comparable>::isEmpty( ) const
        {
            return currentSize == 0;
        }

        /**
         * Test if the priority queue is logically full.
         * Return true if full, false otherwise.
         */
        template <class Comparable>
        bool BinaryHeap<Comparable>::isFull( ) const
        {
            return currentSize == capacity - 1;
        }

        /**
         * Make the priority queue logically empty.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::makeEmpty( )
        {
            currentSize = 0;
        }

        /**
         * Internal method to percolate down in the heap.
         * hole is the index at which the percolate begins.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::percolateDown( int hole )
        {
/* 1*/      int child;
/* 2*/      Comparable tmp = array[ hole ];

/* 3*/      for( ; hole * 2 <= currentSize; hole = child )
            {
/* 4*/          child = hole * 2;
/* 5*/          if( child != currentSize
                  && array[ child + 1 ].cost < array[ child ].cost )
/* 6*/              child++;
/* 7*/          if( array[ child ].cost < tmp.cost )
/* 8*/              array[ hole ] = array[ child ];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;
        }
