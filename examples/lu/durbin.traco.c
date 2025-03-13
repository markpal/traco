#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 2000

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

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
int t1,t3,c3,c1;

#pragma scop
for (t1 = 1; t1 < N; t1 += 1) {
  if (t1 == 1)
    if (N >= 2) {
      beta[1]=beta[1-1]-alpha[1-1]*alpha[1-1]*beta[1-1];
    }
  if (t1 >= 1 && N >= t1 + 1) {
    sum[0][t1]=r[t1];
  }
  if (t1 >= 1 && N >= t1 + 1) {
    alpha[t1]=-sum[t1][t1]*beta[t1];
  }
  if (t1 >= 1) {
    #pragma omp parallel for
    for (c1 = t1; c1 <= min(N - 1, t1 + 1); c1 += 1) {
      if (c1 == t1 + 1) {
        beta[t1+1]=beta[t1+1-1]-alpha[t1+1-1]*alpha[t1+1-1]*beta[t1+1-1];
      } else
        y[t1][t1]=alpha[t1];
      if (c1 == t1) {
        for (c3 = 0; c3 < t1; c3 += 1) {
          y[c3][t1]=y[c3][t1-1]+alpha[t1]*y[t1-c3-1][t1-1];
        }
      }
    }
  }
  for (t3 = 0; t3 < t1; t3 += 1)
    if (t3 >= 0 && t1 >= t3 + 1 && N >= t1 + 1) {
      sum[t3+1][t1]=sum[t3][t1]+r[t1-t3-1]*y[t3][t1-1];
    }
}
#pragma endscop


	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
