#include <unistd.h>
#include <sys/time.h>

#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

#include "omp.h"
int num_proc=1;

void init_array()
{
    int i, j;
    int k;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            C4[i][j] = (i*i+j*j)/((double)N*N);
            for (k=0; k<N; k++) {
                A[i][j][k] = (i*i+j*j + k)/((double)N*N);
            }
        }
    }
}


void print_array()
{
    int i, j, k;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                fprintf(stdout, "%0.2lf ", A[i][j][k]);
                if (j%80 == 20) fprintf(stdout, "\n");
            }
        }
    }
    fprintf(stdout, "\n");
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
