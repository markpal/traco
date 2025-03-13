#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

#ifndef TIME
#define TIME
#endif

#define my_sqrt_array(x,j) sqrt(x[j])

#define N 500
#define M 500

float float_n = (float) N;
float eps = 0.005;

#pragma declarations
float stddev[M + 1];
float data[M + 1][N + 1];
float mean[M + 1];
float symmat[M + 1][M + 1];
#pragma enddeclarations


#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
  int i, j;

  for (i=0; i<M; i++) {
    for (j=0; j<N; j++) {
      data[i][j] = ((float) i*j+1)/N;
    }
  }
}


void print_array()
{
  int i, j;
  for (i=0; i<M; i++) {
    for (j=0; j<M; j++) {
      fprintf(stderr, "%lf ", symmat[i][j]);
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n");
}






#ifdef TIME
double rtclock()
{
  struct timezone Tzp;
  struct timeval Tp;
  int stat;
  stat = gettimeofday (&Tp, &Tzp);
  if (stat != 0) printf("Error return from gettimeofday: %d",stat);
  return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}
#endif

int main(int argc, char** argv)
{
  double t_start, t_end;
  int i, j, j1, j2;
  // float *mean, *stddev;

	int cpus = atoi(argv[2]);
	    int kind = atoi(argv[1]);

	omp_set_num_threads(cpus);

  init_array();

  IF_TIME(t_start = rtclock());

  /* Allocate storage for mean and std. dev. vectors */
  // mean = vector(m);
  // stddev = vector(m);

  /* Determine mean of column vectors of input data matrix */
  for (j = 1; j <= M; j++)
  {
    mean[j] = 0.0;
    for (i = 1; i <= N; i++)
      mean[j] += data[i][j];
    mean[j] /= float_n;
  }

  /* Determine standard deviations of column vectors of data matrix. */
  for (j = 1; j <= M; j++)
  {
    stddev[j] = 0.0;
    for (i = 1; i <= N; i++)
      stddev[j] += (data[i][j] - mean[j]) * (data[i][j] - mean[j]);
    stddev[j] /= float_n;
    stddev[j] = sqrt(stddev[j]);
    /* The following in an inelegant but usual way to handle
       near-zero std. dev. values, which below would cause a zero-
       divide. */
    stddev[j] = stddev[j] <= eps ? 1.0 : stddev[j];
  }

  /* Center and reduce the column vectors. */
  for (i = 1; i <= N; i++)
    for (j = 1; j <= M; j++)
    {
      data[i][j] -= mean[j];
      data[i][j] /= sqrt(float_n) * stddev[j];
    }



if(kind==1){
  for (j1 = 1; j1 <= M-1; j1++)
  {
    symmat[j1][j1] = 1.0;
    for (j2 = j1+1; j2 <= M; j2++)
    {
      symmat[j1][j2] = 0.0;
      for (i = 1; i <= N; i++)
        symmat[j1][j2] += ( data[i][j1] * data[i][j2]);
      symmat[j2][j1] = symmat[j1][j2];
    }
  }}
else{
 int c0,  c1, c2, c4, c6, c8, c10, c3,c7,c5,c9,c11;
#pragma omp parallel for
for (c1 = 0; c1 <= (M - 2)/16; c1 += 1)
  for (c2 = 0; c2 <= 1; c2 += 1) {
    if (c2 == 1) {
      for (c3 = 0; c3 <= -c1 + (M - 2) / 16; c3 += 1) {
        if (N >= 1) {
          if (N >= 17)
            for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
              for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1)
                symmat[c7][c9]=0.0;
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
            for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1) {
              if (N <= 16)
                symmat[c7][c9]=0.0;
              symmat[c9][c7]=symmat[c7][c9];
            }
        } else
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
            for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1)
              symmat[c7][c9]=0.0;
        for (c5 = 0; c5 <= floord(N - 1, 16); c5 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
            for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1)
              for (c11 = 16 * c5 + 1; c11 <= min(N, 16 * c5 + 16); c11 += 1)
                symmat[c7][c9]+=(data[c11][c7]*data[c11][c9]);
      }
    } else
      for (c7 = 16 * c1 + 1; c7 <= min(M - 1, 16 * c1 + 16); c7 += 1)
        symmat[c7][c7]=1.0;
  }

}

  symmat[M][M] = 1.0;

  IF_TIME(t_end = rtclock());
  IF_TIME(fprintf(stdout, "%0.3lf\n", t_end - t_start));

  if (fopen(".test", "r")) {
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
