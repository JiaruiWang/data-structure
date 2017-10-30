#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct char1
{
  char ar[1];
};

struct char10
{
  char ar[10];
};

struct char5
{
  char ar[5];
};

static void display_mallinfo(void)
 {
     struct mallinfo mi;

     mi = mallinfo();

     printf("Total non-mmapped bytes (arena):       %d\n", mi.arena);
     printf("# of free chunks (ordblks):            %d\n", mi.ordblks);
     printf("# of free fastbin blocks (smblks):     %d\n", mi.smblks);
     printf("# of mapped regions (hblks):           %d\n", mi.hblks);
     printf("Bytes in mapped regions (hblkhd):      %d\n", mi.hblkhd);
     printf("Max. total allocated space (usmblks):  %d\n", mi.usmblks);
     printf("Free bytes held in fastbins (fsmblks): %d\n", mi.fsmblks);
     printf("Total allocated space (uordblks):      %d\n", mi.uordblks);
     printf("Total free space (fordblks):           %d\n", mi.fordblks);
     printf("Topmost releasable block (keepcost):   %d\n", mi.keepcost);
 }

int main(int argc, char *argv[])
{
  #define MAX_ALLOCS 2000
  struct mallinfo mi;
  char *alloc[MAX_ALLOCS], *ptr;
  int numBlocks, j, freeBegin, freeEnd, freeStep;
  size_t blockSize, initialSize, newSize;
  printf ("Number of blocks: ");
  scanf ("%d", &numBlocks);
 // printf ("Block size: ");
 //  scanf("%d", &blockSize);
  
  for(j = 24; j < 512; j += 16)
  {
    mi = mallinfo();
    initialSize = mi.uordblks;
    char1 *ptr1 = new char1[j];
    mi = mallinfo();
    newSize = mi.uordblks;
    printf("Change for %d elements of 1 char struct %d\n", j, newSize - initialSize);
    delete [] ptr1;
    mi = mallinfo();
    initialSize = mi.uordblks;
    ptr1 = new char1[j + 1];
    mi = mallinfo();
    newSize = mi.uordblks;
    printf("Change for %d elements of 1 char struct %d\n", j + 1, newSize - initialSize);
    delete [] ptr1;
  } 

  printf("\n5 elements\n");
  for(j = 1; j < numBlocks; j++)
  {
    mi = mallinfo();
    initialSize = mi.uordblks;
    char5 *ptr1 = new char5[j];
    mi = mallinfo();
    newSize = mi.uordblks;
    printf("Change for %d elements of 5 char struct %d\n", j, newSize - initialSize);
    delete [] ptr1;
  }

  printf("\n10 elements\n");
  for(j = 1; j < numBlocks; j++)
  {
    mi = mallinfo();
    initialSize = mi.uordblks;
    char10 *ptr1 = new char10[j];
    mi = mallinfo();
    newSize = mi.uordblks;
    printf("Change for %d elements of 10 char struct %d\n", j, newSize - initialSize);
    delete [] ptr1;
  }
/*    
 for(j = 1; j < numBlocks; j++)
  {
    mi = mallinfo();
    initialSize = mi.uordblks;
    ptr = new char[blockSize * j];
    mi = mallinfo();
    newSize = mi.uordblks;
    printf("Change for %d bytes %d\n", j * blockSize, newSize - initialSize);
    delete [] ptr;
  } 
/*
  for(j = 1; j < numBlocks; j++)
  {
    mi = mallinfo();
    initialSize = mi.uordblks;
    ptr = malloc(blockSize * j);
    mi = mallinfo();
    newSize = mi.uordblks;
    printf("Change for %d bytes %d\n", j * blockSize, newSize - initialSize);
    free(ptr);
  } 
*/
/*
     freeStep = (argc > 3) ? atoi(argv[3]) : 1;
     freeBegin = (argc > 4) ? atoi(argv[4]) : 0;
     freeEnd = (argc > 5) ? atoi(argv[5]) : numBlocks;

     printf("============== Before allocating blocks ==============\n");
     display_mallinfo();

     for (j = 0; j < numBlocks; j++) {
         if (numBlocks >= MAX_ALLOCS)
             printf("Too many allocations");

         alloc[j] = malloc(blockSize);
         if (alloc[j] == NULL)
             printf("malloc");
     }

     printf("\n============== After allocating blocks ==============\n");
     display_mallinfo();

     for (j = freeBegin; j < freeEnd; j += freeStep)
         free(alloc[j]);

     printf("\n============== After freeing blocks ==============\n");
     display_mallinfo();
*/
     exit(EXIT_SUCCESS);
 }

