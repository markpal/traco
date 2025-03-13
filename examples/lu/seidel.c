#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define N 200

#pragma declarations
double a[N+2][N+2];

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
            a[i][j] = i*j/N;
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
	int i, j, k,l,t;
    double t_start, t_end;
    int t1,t3,t5,c1,c3,c5;

    int n;
    int T,ub;
    n = T = N-1;

	init_array() ;

	t_start = rtclock();
int c = 0;

#pragma scop
if(N> 5 && T > 5)
    for (t=0; t<=T-1; t++)  {
        for (i=1; i<=N-2; i++)  {
            for (j=1; j<=N-2; j++)  {
                a[i][j] = (a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] + a[i][j-1] + a[i][j] + a[i][j+1] + a[i+1][j-1] + a[i+1][j] + a[i+1][j+1])/9.0;;
            }
        }
    }

#pragma endscop



	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
