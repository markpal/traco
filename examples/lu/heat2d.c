#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 500

#pragma declarations

double A[N+2][N+2][N+2];
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
      //  alpha[i] = beta[i] = r[i] = (i+1)*j;
        for (j=0; j<N; j++) {
          //  y[i][j] = (i+1)*(j+1);//i==j?1:0;
          //  sum[i][j] = (i+1)*(j+1);//i==j?1:0;
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
	int i, j, k, t, T=N;
    double t_start, t_end;

	init_array() ;


	t_start = rtclock();
int c = 0;
#pragma scop
if(N>1)
for ( t = 0; t < T; t++) {
  for ( i = 1; i < N+1; i++) {
    for ( j = 1; j < N+1; j++) {
      A[t+1][i][j] = 0.125 * (A[t][i+1][j] - 2 * A[t][i][j] + A[t][i-1][j]) + 0.125 * (A[t][i][j+1] - 2 * A[t][i][j] + A[t][i][j-1]) + A[t][i][j];
    }
  }
 }
#pragma endscop



	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
