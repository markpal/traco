#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 2000

#pragma declarations
double alpha[N];
double beta[N];
double r[N];

double sum[N][N], y[N][N];
//double v_a[32][35];
//double v_b[32][32];
//double v_c[32][33];
#pragma enddeclarations

#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
    int i, j, k;

    for (i=0; i<N; i++) {
        alpha[i] = beta[i] = r[i] = (i+1)*j;
        for (j=0; j<N; j++) {
            y[i][j] = (i+1)*(j+1);//i==j?1:0;
            sum[i][j] = (i+1)*(j+1);//i==j?1:0;
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

int main()
{
	int i, j, k;
    double t_start, t_end;

	init_array() ;

	t_start = rtclock();
int c = 0;
#pragma scop
  for (k = 1; k < N; k++)
    {
      beta[k] = beta[k-1] - alpha[k-1] * alpha[k-1] * beta[k-1];

      sum[0][k] = r[k];
      for (i = 0; i <= k - 1; i++)
	sum[i+1][k] = sum[i][k] + r[k-i-1] * y[i][k-1];
      alpha[k] = -sum[k][k] * beta[k];
      for (i = 0; i <= k-1; i++)
	y[i][k] = y[i][k-1] + alpha[k] * y[k-i-1][k-1];
      y[k][k] = alpha[k];
    }
#pragma endscop


	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
