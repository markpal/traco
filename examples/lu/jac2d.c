#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <assert.h>

#define N 2000
#define T 1000

#pragma declarations
double a[N][N];
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
            a[i][j] = ((double)j)/N;
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
    int t, i, j;
    double t_start, t_end;

    init_array();

    t_start = rtclock();

#pragma scop
    for (t=0; t<T; t++) {
        for (i=2; i<N-1; i++) {
            for (j=2; j<N-1; j++) {
                b[i][j]= 0.2*(a[i][j]+a[i][j-1]+a[i][1+j]+a[1+i][j]+a[i-1][j]);
            }
        }
        for (i=2; i<N-1; i++) {
            for (j=2; j<N-1; j++)   {
                a[i][j]=b[i][j];
            }
        }
    }
#pragma endscop

    t_end = rtclock();
    printf("%0.6lfs\n", t_end - t_start);


    return 0;
}
