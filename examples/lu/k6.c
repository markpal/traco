#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <assert.h>

#define N 1000
#define T 1000

#pragma declarations
double w[N];
double b[N][N];
#pragma enddeclarations

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            b[i][j] = ((double)j)/N;
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
#define __PLACE_TO_INSERT_FORWARD_DECLARATIONS

int main()
{
    int t, i, j, k, l, loop, n;
    double t_start, t_end;

    init_array();

    loop = N;
    n = N;

    t_start = rtclock();

#pragma scop
if(n> 8 && loop > 8)
     for ( l=1 ; l<=loop ; l++ ) {
        for ( i=1 ; i<n ; i++ ) {
            for ( k=0 ; k<i ; k++ ) {
                w[i] += b[k][i] * w[i-k-1];
            }
        }
    }
#pragma endscop

    t_end = rtclock();
    printf("%0.6lfs\n", t_end - t_start);


    return 0;
}
