#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 500

#pragma declarations

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

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

    int t1, t3, c1, c3, c5, t5;
	t_start = rtclock();
int c = 0;
#pragma scop
if (N >= 2 && T >= 2)
  for (t1 = 0; t1 < T; t1 += 1) {
    if (t1 >= 1) {
      if (N >= 2 && T >= 2 && T >= t1 + 1 && t1 >= 0) {
        if (t1 >= 1) {
          #pragma omp parallel for
          for (c3 = 1; c3 <= N; c3 += 1) {
            if (c3 == 1) {
              A[t1+1][1][1]=0.125*(A[t1][1+1][1]-2*A[t1][1][1]+A[t1][1-1][1])+0.125*(A[t1][1][1+1]-2*A[t1][1][1]+A[t1][1][1-1])+A[t1][1][1];
            }
            for (c5 = max(1, -2 * c3 + 4); c5 <= N; c5 += 1) {
              A[t1+1][c3][c5]=0.125*(A[t1][c3+1][c5]-2*A[t1][c3][c5]+A[t1][c3-1][c5])+0.125*(A[t1][c3][c5+1]-2*A[t1][c3][c5]+A[t1][c3][c5-1])+A[t1][c3][c5];
            }
          }
        } else
          A[0+1][1][1]=0.125*(A[0][1+1][1]-2*A[0][1][1]+A[0][1-1][1])+0.125*(A[0][1][1+1]-2*A[0][1][1]+A[0][1][1-1])+A[0][1][1];
      }
    } else
      for (t3 = 1; t3 <= N; t3 += 1)
        for (t5 = 1; t5 <= N; t5 += 1)
          if (N >= 2 && T >= 2 && t5 >= 1 && N >= t5 && t3 >= 1 && N >= t3) {
            A[0+1][t3][t5]=0.125*(A[0][t3+1][t5]-2*A[0][t3][t5]+A[0][t3-1][t5])+0.125*(A[0][t3][t5+1]-2*A[0][t3][t5]+A[0][t3][t5-1])+A[0][t3][t5];
          }
  }
#pragma endscop



	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
