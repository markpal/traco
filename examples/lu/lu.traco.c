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

	t_start = rtclock();

  int num_proc=1;
  num_proc = atoi(argv[1]);



    omp_set_num_threads(num_proc);


int t1,t3,t5,c1,c3,c5,n=N,c=0;
#pragma scop

for (t1 = 0; t1 < N - 1; t1 += 1) {
  if (t1 >= 1) {
    if (N >= t1 + 2 && t1 >= 0) {
      a[t1][t1+1]=a[t1][t1+1]/a[t1][t1];

      if (t1 >= 1) {
        #pragma omp parallel for
        for (c5 = t1 + 2; c5 < N; c5 += 1) {
          a[t1][c5]=a[t1][c5]/a[t1][t1];

        }
      }
    }
  } else
    for (t5 = 1; t5 < N; t5 += 1)
      if (t5 >= 1 && N >= t5 + 1) {
        a[0][t5]=a[0][t5]/a[0][0];
      }
  if (N >= t1 + 3 && t1 >= 1) {
    if (t1 >= 0) {
      #pragma omp parallel for
      for (c3 = t1 + 1; c3 < N; c3 += 1) {
        a[c3][t1+1]=a[c3][t1+1]-a[c3][t1]*a[t1][t1+1];

        if (t1 >= 1) {
          for (c5 = t1 + 2; c5 < N; c5 += 1) {
            a[c3][c5]=a[c3][c5]-a[c3][t1]*a[t1][c5];

          }
        }
      }
    }
  } else if (t1 + 2 == N) {
    if (N >= 2) {
      a[N-1][N-1]=a[N-1][N-1]-a[N-1][N-2]*a[N-2][N-1];

    }
  } else
    for (t5 = 1; t5 < N; t5 += 1)
      if (t5 >= 1 && N >= t5 + 1) {
        #pragma omp parallel for
        for (c3 = 1; c3 < N; c3 += 1) {
          a[c3][t5]=a[c3][t5]-a[c3][0]*a[0][t5];

        }
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

for(i=0; i<N; i++)
for(j=0; j<N; j++)
if(!(isnan(a[i][j]) && isnan(a1[i][j])))
 if(a[i][j] != a1[i][j]) { printf("Error %i %i %f %f\n", i, j, a[i][j], a1[i][j]); exit(0);}

    return 0;
}
