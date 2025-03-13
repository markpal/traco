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

 int c0, c2, c4, c6, c8, c10;

for (c0 = 0; c0 <= floord(NI - 1, 4); c0 += 1) {
  for (c2 = 0; c2 <= (NI - 1) / 4; c2 += 1)
    for (c6 = 4 * c0; c6 <= min(NI - 1, 4 * c0 + 3); c6 += 1)
      for (c8 = 4 * c2; c8 <= min(4 * c2 + 3, NI - 1); c8 += 1)
        c[c6][c8]=c[c6][c8]*beta;
  for (c2 = 0; c2 <= (NI - 1) / 4; c2 += 1)
    for (c4 = 0; c4 <= floord(NJ - 1, 4); c4 += 1)
      for (c6 = 4 * c0; c6 <= min(NI - 1, 4 * c0 + 3); c6 += 1)
        for (c8 = 4 * c4; c8 <= min(NJ - 1, 4 * c4 + 3); c8 += 1)
          for (c10 = 4 * c2; c10 <= min(4 * c2 + 3, NI - 1); c10 += 1) {
            c[c6][c10]=c[c6][c10]+alpha*a[c6][c8]*b[c10][c8];
            c[c6][c10]=c[c6][c10]+alpha*b[c6][c8]*a[c10][c8];
          }
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
