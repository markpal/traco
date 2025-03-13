#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 500

#pragma declarations
double a[N][N];
double a1[N][N];
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

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

void init_array()
{
    int i, j, k;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                a[i][j] =  (i+k+1)*(k+j+1);//i==j?1:0;
                a1[i][j] =  (i+k+1)*(k+j+1);//i==j?1:0;
            }
        }
    }
}


void print_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            fprintf(stderr, "%lf ", round(a[i][j]));
            if (j%80 == 79) fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
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

int main(int argc, char *argv[])
{
	int i, j, k;
    double t_start, t_end;



	init_array() ;
/*
#pragma scop
    for (k=0; k<N; k++) {
        for (j=k+1; j<N; j++)   {
            a1[k][j] = a1[k][j]/a1[k][k];

        }
        for(i=k+1; i<N; i++)    {
            for (j=k+1; j<N; j++)   {
                a1[i][j] = a1[i][j] - a1[i][k]*a1[k][j];

            }
        }
    }
#pragma endscop
*/
	t_start = rtclock();

  int num_proc=1;
  num_proc = atoi(argv[1]);



    omp_set_num_threads(num_proc);


int t1,t3,t5,c1,c3,c5,n=N,c=0,c6,c8,c0,c4;
#pragma scop



for (c0 = -1; c0 < 2 * N - 3; c0 += 1)
#pragma omp parallel
  for (c1 = max(-1, -N + (N + c0 + 1) / 2); c1 < (c0 + 2) / 4; c1 += 1)
    for (c3 = max(max(max(0, c1), -N + c0 - 2 * c1 + N / 2 - 1), -c1 + floord(-N + 2 * c0 + 2 * c1 + 1, 4)); c3 <= min(min(c0 - 3 * c1 - 1, c0 - c1), N / 2 - 1); c3 += 1) {
      for (c4 = max(max(max(0, 2 * c1 + 1), -2 * N + 2 * c0 - 2 * c1 + 2), -N + 2 * c0 - 2 * c1 - 2 * c3 - 1); c4 <= min(min(2 * c1 + 2, c0 - c1 - c3 - 2), 2 * c3 + 1); c4 += 1)
        for (c6 = max(2 * c0 - 2 * c1 - 2 * c3 - c4 - 2, -N + 2 * c0 - 2 * c1 - c4 + 1); c6 <= min(min(N - 1, 2 * c0 - 2 * c1 - 2 * c3 - c4), 2 * c0 - 2 * c1 - 2 * c4); c6 += 1)
          for (c8 = max(max(2 * c3 + 1, c4 + 1), 2 * c0 - 2 * c1 - c4 - c6); c8 <= min(min(N - 1, 2 * c3 + 2), 2 * c0 - 2 * c1 - c4 - c6 + 1); c8 += 1)
              a[c6][c8] = a[c6][c8] - a[c6][c4]*a[c4][c8];
      if (2 * c0 >= N + 2 * c1 && 2 * c0 >= N + 6 * c1 + 2 && N + 6 * c1 + 4 >= 2 * c0 && 2 * c3 + 2 == N)
        for (c6 = (-N / 2) + c0 - c1 + 1; c6 <= min(N - 1, (-N / 2) + c0 - c1 + 2); c6 += 1)
          a[c6][N-1] = a[c6][N-1] - a[c6][(-N / 2) + c0 - c1]*a[(-N / 2) + c0 - c1][N-1];

      for (c4 = max(max(max(0, 2 * c1 + 1), c0 - c1 - c3 - 1), -N + c0 - c1 + c3 + 2); c4 <= min(min(2 * c1 + 2, c0 - c1 - c3), -c1 + floord(c0 + c1 + c3, 2)); c4 += 1) {
         a[c4][c0 - c1 + c3 - c4 + 1] = a[c4][c0 - c1 + c3 - c4 + 1]/a[c4][c4];
        if (c1 + c3 + c4 + 1 == c0)
          for (c6 = c0 - c1 - c3; c6 <= min(c0 - c1 - c3 + 1, 2 * c3 + 2); c6 += 1)
            for (c8 = max(c0 - c1 - c3, 2 * c3 + 1); c8 <= c0 - c1 + c3 - c6 + 2; c8 += 1)
              a[c6][c8] = a[c6][c8] - a[c6][c0 - c1 - c3 - 1]*a[c0 - c1 - c3 - 1][c8];
      }
    }


#pragma endscop

	t_end = rtclock();
	printf("%0.6lfs %i\n", t_end - t_start,c);

    if (fopen(".test", "r")) {
#ifdef MPI
        if (my_rank == 0) {
            print_array();
        }
#else
        print_array();
#endif
    }
/*
for(i=0; i<N; i++)
for(j=0; j<N; j++)
if(!(isnan(a[i][j]) && isnan(a1[i][j])))
 if(a[i][j] != a1[i][j]) { printf("Error %i %i %f %f\n", i, j, a[i][j], a1[i][j]); exit(0);}
*/
    return 0;
}
