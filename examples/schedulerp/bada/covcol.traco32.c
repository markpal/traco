#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#ifndef TIME
#define TIME
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>
#include <omp.h>

#define my_sqrt_array(x,j) sqrt(x[j])

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

  	int cpus = atoi(argv[2]);
	    int kind = atoi(argv[1]);

	omp_set_num_threads(cpus);

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

if(kind==1){
#pragma scop
  for (j1 = 1; j1 <= M; j1++) {
    for (j2 = j1; j2 <= M; j2++) {
      for (i = 1; i <= N; i++) {
        symmat[j1][j2] += data[i][j1] * data[i][j2];
      }
      symmat[j2][j1] = symmat[j1][j2];
    }
  }

#pragma endscop
}
else{
 int c0,  c1, c2, c4, c6, c8, c10, c3,c7,c5,c9,c11;


if (N >= 1)
#pragma omp parallel for
  for (c1 = 0; c1 <= (M - 1) / 32; c1 += 1)
    for (c3 = 0; c3 <= -c1 + (M - 1) / 32; c3 += 1)
      if (c1 >= 0 && N >= 1 && c3 >= 0) {
        for (c7 = 32 * c1 + 1; c7 <= min(32 * c1 + 32, M - 32 * c3); c7 += 1)
          for (c9 = 32 * c3 + c7; c9 <= min(M, 32 * c3 + c7 + 31); c9 += 1)
            symmat[c9][c7]=symmat[c7][c9];
        for (c5 = 0; c5 <= floord(N - 1, 32); c5 += 1)
          for (c7 = 32 * c1 + 1; c7 <= min(32 * c1 + 32, M - 32 * c3); c7 += 1)
            for (c9 = 32 * c3 + c7; c9 <= min(M, 32 * c3 + c7 + 31); c9 += 1)
              for (c11 = 32 * c5 + 1; c11 <= min(N, 32 * c5 + 32); c11 += 1)
                symmat[c7][c9]+=data[c11][c7]*data[c11][c9];

      }
}

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
