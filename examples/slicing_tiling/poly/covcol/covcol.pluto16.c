#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#define my_sqrt_array(x,j) sqrt(x[j])

#ifndef TIME
#define TIME
#endif

#include "util.h"

double float_n = (float) N;
double eps = 0.005;
double stddev[M + 1];
double data[M + 1][N + 1];
double mean[M + 1];
double symmat[M + 1][M + 1];

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
    int i, j;
    int n = N;
    int m = M;

    for (i=0; i<=n; i++) {
      for (j=0; j<=m; j++) {
        data[i][j] = ((float) i*j)/N;
      }
    }
}

void print_array()
{
  int i, j;
  int n = N;
  int m = M;
  for (i=1; i<=m; i++) {
    for (j=1; j<=m; j++) {
      fprintf(stderr, "%0.2lf ", symmat[i][j]);
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n");
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

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

int main(int argc, char** argv)
{
  double t_start, t_end;
  int i, j, j1, j2;

    num_proc = atoi(argv[1]);
  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  init_array();

  IF_TIME(t_start = rtclock());

  /* Determine mean of column vectors of input data matrix */
  for (j = 1; j <= M; j++) {
    mean[j] = 0.0;
    for (i = 1; i <= N; i++)
      mean[j] += data[i][j];
    mean[j] /= float_n;
  }

  /* Center the column vectors. */
  for (i = 1; i <= N; i++)
    for (j = 1; j <= M; j++)
      data[i][j] -= mean[j];

  for (j1 = 1; j1 <= M; j1++) {
    for (j2 = j1; j2 <= M; j2++) {
      symmat[j1][j2] = 0.0;
    }
  }




  int t1, t2, t3, t4, t5, t6, t7, t8;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (M >= 1) {
  lbp=0;
  ubp=floord(M,16);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=t1;t2<=floord(M,16);t2++) {
      if (N >= 1) {
        for (t4=0;t4<=floord(N,16);t4++) {
          for (t5=max(1,16*t1);t5<=min(M,16*t1+15);t5++) {
            for (t7=max(1,16*t4);t7<=min(N,16*t4+15);t7++) {
              lbv=max(16*t2,t5);
              ubv=min(M,16*t2+15);
#pragma ivdep
#pragma vector always
              for (t8=lbv;t8<=ubv;t8++) {
                symmat[t5][t8]+=data[t7][t5]*data[t7][t8];;
              }
            }
          }
        }
      }
      for (t5=max(1,16*t1);t5<=min(M,16*t1+15);t5++) {
        lbv=max(16*t2,t5);
        ubv=min(M,16*t2+15);
#pragma ivdep
#pragma vector always
        for (t8=lbv;t8<=ubv;t8++) {
          symmat[t8][t5]=symmat[t5][t8];;
        }
      }
    }
  }
}
/* End of CLooG code */


  IF_TIME(t_end = rtclock());
  IF_TIME(fprintf(stdout, "%0.6lfs\n", t_end - t_start));

  if (fopen(".test", "r"))  {
#ifdef MPI
      if (my_rank == 0) {
          print_array();
      }
#else
      print_array();
#endif
  }

  return 0;
}
