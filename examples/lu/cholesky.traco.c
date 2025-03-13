#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 500

#pragma declarations
double A[N][N];
double x[N];
double p[N];
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
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                A[i][j] =  (i+k+1)*(k+j+1);//i==j?1:0;
                A[i][j] =  (i+k+1)*(k+j+1);//i==j?1:0;
            }
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

omp_set_num_threads(4);

	t_start = rtclock();



int t1,t3,t5,c1,c3,c5,n=N,c=0;


for (t1 = 0; t1 < N; t1 += 1) {
  if (N >= t1 + 1 && t1 >= 0) {
    x[t1]=A[t1][t1];
    //c++;
  }
  if (N >= t1 + 1 && t1 >= 0) {
    p[t1]=1*x[t1];
    //c++;
  }
  if (N >= 2 && t1 + 1 == N)
    if (N >= 2) {
      x[N-1]=x[N-1]-A[N-1][N-2]*A[N-1][N-2];
      //c++;
    }
  for (t3 = t1 + 1; t3 < N; t3 += 1) {
    if (N >= t3 + 1 && t3 >= t1 + 1 && t1 >= 0) {
//      #pragma omp parallel for
      for (c1 = t1; c1 < t3; c1 += 1) {
        if (t3 >= c1 + 2 && c1 >= t1 + 1) {
          x[c1]=x[c1]-A[t3-1][t1]*A[c1][t1];
          //c++;
        } else if (c1 == t1) {
          x[t1]=A[t1][t3];
          //c++;
        } else
          x[t3-1]=x[t3-1]-A[t3-1][t1]*A[t3-1][t1];
          //c++;
      }
    }
    if (N >= t3 + 1 && t3 >= t1 + 1 && t1 >= 0) {
      A[t3][t1]=x[t1]*p[t1];
      //c++;
    }
    if (t1 >= 1 && t3 + 1 == N)
      if (N >= t1 + 2 && t1 >= 1) {
  //      #pragma omp parallel for
        for (c1 = t1; c1 < N; c1 += 1) {
          if (N >= c1 + 2) {
          x[c1]=x[c1]-A[N-1][t1-1]*A[c1][t1-1];
        //  c++;
          } else
            x[N-1]=x[N-1]-A[N-1][t1-1]*A[N-1][t1-1];
            //c++;
        }
      }
  }
}


	t_end = rtclock();
	printf("%0.6lfs %i\n", t_end - t_start,c);


    return 0;
}
