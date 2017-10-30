        #ifndef _BINARY_HEAP_H_
        #define _BINARY_HEAP_H_


        // BinaryHeap class
        //
        // CONSTRUCTION: with a negative infinity sentinel and
        //               optional capacity (that defaults to 100)
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Throws Underflow and Overflow as warranted

        class HeapNode
        {
          public:
            short x;
            short y;
            int cost;
            HeapNode(){}
            HeapNode(short x2, short y2, int c):x(x2), y(y2), cost(c){}

        };

        template <class Comparable>
        class BinaryHeap
        {
          public:
            int currentSize;  // Number of elements in heap

            Comparable *array;        // The heap array
            int *position;

            explicit BinaryHeap( int cap = 100 );
            ~BinaryHeap();
            bool isEmpty( ) const;
            bool isFull( ) const;
            const Comparable & findMin( ) const;

            void insert( const Comparable & x );
            void deleteMin( );
            void deleteMin( Comparable & minItem );
            void makeEmpty( );
            void buildHeap( );
            void decreaseKey(const Comparable & x);
          private:
            int capacity;

            void percolateDown( int hole );
        };

        #include "BinaryHeap.cpp"
        #endif
