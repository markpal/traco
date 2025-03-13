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




  int t1, t2, t3, t4, t5, t6;

 register int lbv, ubv;

/* Start of CLooG code */
if (N >= 1) {
  for (t1=0;t1<=floord(N-1,4);t1++) {
    for (t2=0;t2<=floord(N-1,4);t2++) {
      for (t3=0;t3<=t2;t3++) {
        if (t2 >= t3+1) {
          for (t4=4*t2;t4<=min(N-1,4*t2+3);t4++) {
            for (t5=4*t3;t5<=4*t3+3;t5++) {
              for (t6=4*t1;t6<=min(N-1,4*t1+3);t6++) {
                B[t4][t6]=B[t4][t6]-L[t4][t5]*B[t5][t6];;
              }
            }
          }
        }
        if (t2 == t3) {
          for (t6=4*t1;t6<=min(N-1,4*t1+3);t6++) {
            B[4*t2][t6]=B[4*t2][t6]/L[4*t2][4*t2];;
          }
        }
        if (t2 == t3) {
          for (t4=4*t2+1;t4<=min(N-1,4*t2+3);t4++) {
            for (t5=4*t2;t5<=t4-1;t5++) {
              for (t6=4*t1;t6<=min(N-1,4*t1+3);t6++) {
                B[t4][t6]=B[t4][t6]-L[t4][t5]*B[t5][t6];;
              }
            }
            for (t6=4*t1;t6<=min(N-1,4*t1+3);t6++) {
              B[t4][t6]=B[t4][t6]/L[t4][t4];;
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
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
