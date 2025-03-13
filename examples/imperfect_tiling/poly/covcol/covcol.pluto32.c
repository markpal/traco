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

#define N 1000
#define M 1000

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




  int t1, t2, t3, t4, t5, t6, t7, t8, t9;

 register int lbv, ubv;

/* Start of CLooG code */
if (M >= 1) {
  if (N >= 1) {
    for (t2=0;t2<=floord(M,32);t2++) {
      for (t3=t2;t3<=floord(M,32);t3++) {
        for (t4=0;t4<=floord(N,32);t4++) {
          for (t5=max(1,32*t2);t5<=min(M,32*t2+31);t5++) {
            for (t6=max(1,32*t4);t6<=min(N,32*t4+31);t6++) {
              lbv=max(32*t3,t5);
              ubv=min(M,32*t3+31);
#pragma ivdep
#pragma vector always
              for (t9=lbv;t9<=ubv;t9++) {
                symmat[t5][t9]+=data[t6][t5]*data[t6][t9];;
              }
            }
          }
        }
      }
    }
  }
  for (t2=0;t2<=floord(M,32);t2++) {
    for (t3=t2;t3<=floord(M,32);t3++) {
      for (t4=max(1,32*t2);t4<=min(M,32*t2+31);t4++) {
        lbv=max(32*t3,t4);
        ubv=min(M,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t5=lbv;t5<=ubv;t5++) {
          symmat[t5][t4]=symmat[t4][t5];;
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
