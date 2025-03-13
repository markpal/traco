#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define NMAX 512


#pragma declarations
double a[NMAX][NMAX], b[NMAX][NMAX], c[NMAX][NMAX];
#pragma enddeclarations

#define TIME 1

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}


double t_start, t_end;

int main()
{
  int i,j, k;

  for (i = 0; i < NMAX; i++) {
    for (j = 0; j < NMAX; j++) {
      c[i][j] = 0.0;
      a[i][j] = 1.0+i*j*32.5/(NMAX*NMAX);
      b[i][j] = 1.0+i*j*3.4565/(NMAX*NMAX);
    }
  }

  IF_TIME(t_start = rtclock());
  int  beta = 1;
int alpha  = 1;
int NJ  = NMAX;
int NI = NMAX;

 int c0, c2, c4, c6, c8, c10, c1, c3, c5;

for (c0 = 0; c0 <= floord(NI - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= (NI - 1) / 16; c1 += 1) {
    for (c2 = 0; c2 <= floord(NJ - 1, 16); c2 += 1)
      for (c3 = 16 * c0; c3 <= min(NI - 1, 16 * c0 + 15); c3 += 1) {
        for (c4 = 16 * c2; c4 <= min(NJ - 1, 16 * c2 + 15); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NI >= c4 + 1)
            c[c3][c4]*=beta;
          for (c5 = 16 * c1; c5 <= min(16 * c1 + 15, NI - 1); c5 += 1) {
            c[c3][c5]+=alpha*a[c3][c4]*b[c5][c4];
            c[c3][c5]+=alpha*b[c3][c4]*a[c5][c4];
          }
        }
        if (c2 == 0) {
          for (c4 = max(16, 16 * c1); c4 <= min(min(NI - 1, 16 * c1 + 15), NJ - 1); c4 += 1)
            c[c3][c4]*=beta;
          for (c4 = max(16 * c1, NJ); c4 <= min(NI - 1, 16 * c1 + 15); c4 += 1)
            c[c3][c4]*=beta;
        }
      }
    if (NJ <= 0)
      for (c3 = 16 * c0; c3 <= min(NI - 1, 16 * c0 + 15); c3 += 1)
        for (c4 = 16 * c1; c4 <= min(16 * c1 + 15, NI - 1); c4 += 1)
          c[c3][c4]*=beta;
  }






  IF_TIME(t_end = rtclock());
  IF_TIME(fprintf(stdout, "%0.6lfs\n", t_end - t_start));

  if (fopen(".test", "r")) {
#ifdef MPI
      if (my_rank == 0) {
#endif
          for (i = 0; i < NMAX; i++) {
              for (j = 0; j < NMAX; j++) {
                  fprintf(stderr, "%lf ", c[i][j]);
              }
          }
          fprintf(stderr, "\n");
#ifdef MPI
      }
#endif
  }

  return 0;

}
