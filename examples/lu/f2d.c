#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 1000

#pragma declarations

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

	t_start = rtclock();
int c = 0;
#pragma scop
if(nx > 0 && ny > 0)
    for(t=0; t<tmax; t++)  {
        for (i=0; i<ny; i++)
          for (j=0; j<1; j++)
            ey[0][i] = t;
        for (i=1; i<nx; i++)
            for (j=0; j<ny; j++)
                ey[i][j] = ey[i][j] - 0.5*(hz[i][j]-hz[i-1][j]);
        for (i=0; i<nx; i++)
            for (j=1; j<ny; j++)
                ex[i][j] = ex[i][j] - 0.5*(hz[i][j]-hz[i][j-1]);
        for (i=0; i<nx; i++)
            for (j=0; j<ny; j++)
                hz[i][j]=hz[i][j]-0.7*(ex[i][j+1]-ex[i][j]+ey[i+1][j]-ey[i][j]);
    }
#pragma endscop



	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
