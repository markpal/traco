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
#pragma scop
	for (i=0; i<NI; i++) {
		for (j=0; j<NI; j++) {
			c[i][j] *= beta;
			for (k=0; k<NJ; k++) {
				c[i][j] += alpha * a[i][k] * b[j][k];
				c[i][j] += alpha * b[i][k] * a[j][k];
			}
		}
	}
#pragma endscop


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



if (NJ >= 1)
#pragma omp parallel for
  for (c0 = 0; c0 <= floord(NI - 1, 16); c0 += 1)
    for (c1 = 0; c1 <= (NI - 1) / 16; c1 += 1)
      if (c0 >= 0 && c1 >= 0)
        for (c2 = 0; c2 <= floord(NJ - 1, 16); c2 += 1)
          for (c3 = 16 * c0; c3 <= min(NI - 1, 16 * c0 + 15); c3 += 1)
            for (c4 = 16 * c1; c4 <= min(16 * c1 + 15, NI - 1); c4 += 1) {
              if (c2 == 0)
                c[c3][c4]*=beta;
              for (c5 = 16 * c2; c5 <= min(NJ - 1, 16 * c2 + 15); c5 += 1) {
                c[c3][c4]+=alpha*a[c3][c5]*b[c4][c5];
                c[c3][c4]+=alpha*b[c3][c5]*a[c4][c5];
              }
            }

