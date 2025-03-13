#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define NMAX 100

static double B[NMAX][NMAX], L[NMAX][NMAX];


#include "util.h"

#ifndef TIME
#define TIME
#endif

void trisolv(long N)
{
    long i,j,k;
int c0, c1, c2, c3, c4, c5, c6,c8,c10;

for (c0 = 0; c0 <= floord(N - 1, 16); c0 += 1)
  for (c2 = 0; c2 <= (N - 1) / 16; c2 += 1)
    for (c4 = max(c2 - 1, 0); c4 <= min(floord(N - 2, 16), c2); c4 += 1) {
      for (c6 = max(16 * c4 + 1, 16 * c2); c6 <= min(min(N - 1, 16 * c4 + 16), 16 * c2 + 15); c6 += 1) {
        if (c4 == c2)
          for (c8 = 16 * c0; c8 <= min(16 * c0 + 15, N - 1); c8 += 1)
            for (c10 = 16 * c2 + 1; c10 < c6; c10 += 1)
              B[c8][c10]=B[c8][c10]-L[c8][c6]*B[c6][c10];
        for (c8 = 16 * c0; c8 <= min(N - 1, 16 * c0 + 15); c8 += 1)
          B[c6][c8]=B[c6][c8]/L[c6][c6];
      }
      if (c4 == c2)
        for (c6 = 16 * c2 + 16; c6 < N; c6 += 1)
          for (c8 = 16 * c0; c8 <= min(N - 1, 16 * c0 + 15); c8 += 1)
            for (c10 = 16 * c2 + 1; c10 <= 16 * c2 + 15; c10 += 1)
              B[c8][c10]=B[c8][c10]-L[c8][c6]*B[c6][c10];
    }



}


int main()
{
    long N=NMAX;
    int i,j;
    double t_start, t_end;

    t_start = rtclock();
    trisolv(N);
    t_end = rtclock();
    fprintf(stderr, "%0.6lfs\n", t_end - t_start);

    if (fopen(".test", "r")) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                fprintf(stdout, "%lf ", B[i][j]);
            }
            fprintf(stdout, "\n");
        }
    }
    return 0;
}
