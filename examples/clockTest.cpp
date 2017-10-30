#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;


#include <stdint.h>
extern "C" {
   __inline__ uint64_t rdtsc() {
   uint32_t lo, hi;
   /* We cannot use "=A", since this would use %rax on x86_64 */
   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
   return (uint64_t)hi << 32 | lo;
   }
}

int main()
{
  time_t  t0, t1; /* time_t is defined on <time.h> and <sys/types.h> as long */
  clock_t c0, c1; /* clock_t is defined on <time.h> and <sys/types.h> as int */
  uint64_t r0, r1, diff, ticksPerSecond;
  uint64_t u = 10123123123LL;
  long count;
  unsigned long long g;
  double a, b, c;
  printf( "testing printf: %lld\n", u);
  cout << "testing cout: " << u;
  cout << "rdtsc: " << rdtsc() << endl;
 
  printf ("using UNIX function time to measure wallclock time ... \n");
  printf ("using UNIX function clock to measure CPU time ... \n");

  t0 = time(NULL);
  r0 = rdtsc();
  c0 = clock();
 
  printf ("\tbegin (wall):            %ld\n", (long) t0);
  printf ("\tbegin (CPU):             %d\n", (int) c0);

  //printf ("\t\tsleep for 5 seconds ... \n");
  sleep(5);

 // printf ("\t\tperform some computation ... \n");
  /*for (count = 1l; count < 10000000l; count++) {
     a = sqrt(count);
     b = 1.0/a;
     c = b - a;
  }
*/
  t1 = time(NULL);
  r1 = rdtsc();
  c1 = clock();

  printf ("\tend (wall):              %ld\n", (long) t1);
  printf ("\tend (CPU);               %d\n", (int) c1);
  printf ("\telapsed wall clock time: %ld\n", (long) (t1 - t0));
  printf ("\telapsed CPU time:        %lf\n", (double) (c1 - c0)/CLOCKS_PER_SEC);
  diff = r1 - r0;
  printf ("\tCPU clock ticks:         %lld\n", diff);
  ticksPerSecond = diff / 5;
  printf ("\tCPU clock ticks/second:  %lld\n", ticksPerSecond);
  printf ("\tclock() ticks/second: %ld\n", CLOCKS_PER_SEC);
  return 0;
}
