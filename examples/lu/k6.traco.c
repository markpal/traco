#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <assert.h>

#define N 1000
#define T 1000

#define max(x,y)    ((x) > (y)? (x) : (y))

#pragma declarations
double w[N];
double b[N][N];
#pragma enddeclarations

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            b[i][j] = ((double)j)/N;
        }
    }
}


double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}
#define __PLACE_TO_INSERT_FORWARD_DECLARATIONS

int main()
{
    int t, i, j, k, l, t1, t3, t5, loop, n, c5;
    double t_start, t_end;

    init_array();

    loop = N;
    n = N;

    t_start = rtclock();

omp_set_num_threads(4);

#pragma scop
  if (n >= 9 && loop >= 9)
  for (t1 = 1; t1 <= loop; t1 += 1)
    for (t3 = 1; t3 < n; t3 += 1) {
        if (t3 <= 2)
            w[t3]+=b[0][t3]*w[t3-0-1];
        for (t5 = max(0, -t3 + t3 / 2 + 2); t5 <= 1; t5 += 1)
            if (t3 >= 2) {
              w[t3]+=b[t5][t3]*w[t3-t5-1];
              if (t5 == 1) {
                #pragma omp parallel for
                for (c5 = 2; c5 < t3; c5 += 1) {
                  w[t3]+=b[c5][t3]*w[t3-c5-1];
                }
              }
            } else if (t5 + t1 >= 2) {
              w[t5+1]+=b[0][t5+1]*w[t5+1-0-1];
            } else
              w[1]+=b[0][1]*w[1-0-1];
          }

#pragma endscop

    t_end = rtclock();
    printf("%0.6lfs\n", t_end - t_start);


    return 0;
}
