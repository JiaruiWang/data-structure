#include <sys/time.h>
#include <stdio.h>


int main()
{
  int i, longest = 9;
  struct timezone tz;
  struct timeval start_time, end_time, elapsed_time;

  for(i = 0; i < 20000000; i++)
  {
    gettimeofday(&start_time, &tz);
    if(start_time.tv_usec > longest)
      longest = start_time.tv_usec;
  }

  printf("%d\n", longest);
  return 0;

}



