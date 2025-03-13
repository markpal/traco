#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 1000

#pragma declarations

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

double ey[N][N], ex[N][N], hz[N][N];
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
	int i, j, k, t;
    double t_start, t_end;

	init_array() ;

	int nx,ny,tmax;
	nx = ny = tmax = N - 2;
	int t1, t3, t5, c1, c3, c5;

	t_start = rtclock();
int c = 0;
if (ny >= 1 && nx >= 1)
  for (t1 = 0; t1 < tmax; t1 += 1) {
    if (ny == 1 && nx == 1) {
      if (ny >= 1 && ny + nx >= 3 && nx >= 1 && tmax >= t1 + 1 && t1 >= 0) {
        ey[0][0]=t1;
        if (t1 >= 1) {
          #pragma omp parallel for
          for (c3 = 1; c3 < ny; c3 += 1) {
            ey[0][c3]=t1;
          }
        }
        if (t1 >= 1) {
          #pragma omp parallel for
          for (c3 = 1; c3 < nx; c3 += 1) {
            for (c5 = 0; c5 < ny; c5 += 1) {
              ey[c3][c5]=ey[c3][c5]-0.5*(hz[c3][c5]-hz[c3-1][c5]);
            }
          }
          if (ny >= 2) {
            for (c3 = 0; c3 < nx; c3 += 1) {
              if (c3 == 0) {
                ex[0][1]=ex[0][1]-0.5*(hz[0][1]-hz[0][1-1]);
              }
              for (c5 = max(1, -c3 + 2); c5 < ny; c5 += 1) {
                ex[c3][c5]=ex[c3][c5]-0.5*(hz[c3][c5]-hz[c3][c5-1]);
              }
            }
          }
        }
      } else if (ny == 1 && nx == 1 && tmax >= t1 + 1 && t1 >= 0)
        ey[0][0]=t1;
    } else if (t1 >= 1) {
      if (ny >= 1 && ny + nx >= 3 && nx >= 1 && tmax >= t1 + 1 && t1 >= 0) {
        ey[0][0]=t1;
        if (t1 >= 1) {
          #pragma omp parallel for
          for (c3 = 1; c3 < ny; c3 += 1) {
            ey[0][c3]=t1;
          }
        }
        if (t1 >= 1) {
          #pragma omp parallel for
          for (c3 = 1; c3 < nx; c3 += 1) {
            for (c5 = 0; c5 < ny; c5 += 1) {
              ey[c3][c5]=ey[c3][c5]-0.5*(hz[c3][c5]-hz[c3-1][c5]);
            }
          }
          if (ny >= 2) {
            for (c3 = 0; c3 < nx; c3 += 1) {
              if (c3 == 0) {
                ex[0][1]=ex[0][1]-0.5*(hz[0][1]-hz[0][1-1]);
              }
              for (c5 = max(1, -c3 + 2); c5 < ny; c5 += 1) {
                ex[c3][c5]=ex[c3][c5]-0.5*(hz[c3][c5]-hz[c3][c5-1]);
              }
            }
          }
        }
      } else if (ny == 1 && nx == 1 && tmax >= t1 + 1 && t1 >= 0)
        ey[0][0]=t1;
    } else
      for (t3 = 0; t3 < ny; t3 += 1)
        if ((ny + nx >= 3 && nx >= 1 && tmax >= 1 && ny >= t3 + 1 && t3 >= 0) || (ny == 1 && nx == 1 && tmax >= 1 && t3 == 0)) {
          ey[0][t3]=0;
        }
    if (t1 == 0) {
      for (t3 = 1; t3 < nx; t3 += 1)
        for (t5 = 0; t5 < ny; t5 += 1)
          if (tmax >= 1 && ny >= t5 + 1 && t5 >= 0 && t3 >= 1 && nx >= t3 + 1) {
            ey[t3][t5]=ey[t3][t5]-0.5*(hz[t3][t5]-hz[t3-1][t5]);
          }
      for (t3 = 0; t3 < nx; t3 += 1)
        for (t5 = 1; t5 < ny; t5 += 1)
          if (tmax >= 1 && t5 >= 1 && ny >= t5 + 1 && nx >= t3 + 1 && t3 >= 0) {
            ex[t3][t5]=ex[t3][t5]-0.5*(hz[t3][t5]-hz[t3][t5-1]);
          }
    }
    if (ny >= 1 && tmax >= t1 + 1 && t1 >= 0) {
      #pragma omp parallel for
      for (c3 = 0; c3 < nx; c3 += 1) {
        if (c3 == 0) {
          hz[0][0]=hz[0][0]-0.7*(ex[0][0+1]-ex[0][0]+ey[0+1][0]-ey[0][0]);
        }
        for (c5 = max(0, -c3 + 1); c5 < ny; c5 += 1) {
          hz[c3][c5]=hz[c3][c5]-0.7*(ex[c3][c5+1]-ex[c3][c5]+ey[c3+1][c5]-ey[c3][c5]);
        }
      }
    }
  }





	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
