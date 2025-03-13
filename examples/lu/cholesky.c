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



	t_start = rtclock();



int t1,t3,t5,c1,c3,c5,n=N,c=0;


	for (i=0; i<N; i++) {
		x[i] = A[i][i];
		//c++;
		for (j=0; j<=i-1; j++) {
			x[i] = x[i] - A[i][j] * A[i][j];
			//c++;
		}
		p[i] = 1 * x[i];
		//c++;
		for (j=i+1; j<N; j++) {
			x[i] = A[i][j];
			//c++;
			for (k=0; k<=i-1; k++) {
				x[i] = x[i] - A[j][k] * A[i][k];
				//c++;
			}
			A[j][i] = x[i] * p[i];
			//c++;
		}
	}


	t_end = rtclock();
	printf("%0.6lfs %i\n", t_end - t_start,c);


    return 0;
}
