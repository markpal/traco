#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 6000

#define alpha 1
#define beta 1

#pragma declarations
double A[N][N];
double B[N][N];

double x[N];
double u1[N];
double u2[N];
double v2[N];
double v1[N];
double w[N];
double y[N];
double z[N];
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
        u1[i] = i;
        u2[i] = (i+1)/N/2.0;
        v1[i] = (i+1)/N/4.0;
        v2[i] = (i+1)/N/6.0;
        y[i] = (i+1)/N/8.0;
        z[i] = (i+1)/N/9.0;
        x[i] = 0.0;
        w[i] = 0.0;
        for (j=0; j<N; j++) {
            A[i][j] = ((double) i*j)/N;
        }
    }
}

void print_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        fprintf(stderr, "%0.2lf ", w[i]);
        if (i%80 == 20) fprintf(stderr, "\n");
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

int main(int argc, char** argv)
{
    double t_start, t_end;
    int i, j;

    init_array();

    t_start = rtclock();
int ub = floord(N - 1, 400);
int c0,c1,c2,c3,c4,c6,c0_0;

  int num_proc = atoi(argv[1]);

  omp_set_num_threads(num_proc);

#pragma omp parallel for
for (c0 = 0; c0 <= ub; c0 += 1)
  if (N >= 400 * c0 + 1 && c0 >= 0)
    for (c0_0 = 0; c0_0 <= (N - 1) / 400; c0_0 += 1) {
      if (c0 >= 1 && c0_0 >= c0 + 1) {
        for (c4 = 400 * c0_0; c4 <= min(400 * c0_0 + 399, N - 1); c4 += 1)
          for (c6 = 0; c6 <= 15; c6 += 1)
            x[c6]=x[c6]+beta*B[c6][c4]*y[c4];
      } else if (c0_0 == c0)
        for (c2 = 0; c2 < 25 * c0; c2 += 1)
          for (c4 = 400 * c0; c4 <= min(400 * c0 + 399, N - 1); c4 += 1)
            for (c6 = 16 * c2; c6 <= 16 * c2 + 15; c6 += 1) {
              B[c4][c6]=A[c4][c6]+u1[c4]*v1[c6]+u2[c4]*v2[c6];
              if (c2 == 0)
                x[c6]=x[c6]+beta*B[c6][c4]*y[c4];
            }
      for (c2 = 25 * c0; c2 <= min((N - 1) / 16, 25 * c0 + 24); c2 += 1)
        for (c4 = 400 * c0_0; c4 <= min(400 * c0_0 + 399, N - 1); c4 += 1)
          for (c6 = 16 * c2; c6 <= min(N - 1, 16 * c2 + 15); c6 += 1) {
            if (c0_0 == c0)
              B[c4][c6]=A[c4][c6]+u1[c4]*v1[c6]+u2[c4]*v2[c6];
            x[c6]=x[c6]+beta*B[c6][c4]*y[c4];
          }
      if (c0_0 == c0)
        for (c2 = 25 * c0 + 25; c2 <= (N - 1) / 16; c2 += 1)
          for (c4 = 400 * c0; c4 <= 400 * c0 + 399; c4 += 1)
            for (c6 = 16 * c2; c6 <= min(N - 1, 16 * c2 + 15); c6 += 1)
              B[c4][c6]=A[c4][c6]+u1[c4]*v1[c6]+u2[c4]*v2[c6];
    }

#pragma omp parallel for
    for (i=0; i<N; i++)
        x[i] = x[i] + z[i];

#pragma omp parallel for
for (c0 = 0; c0 <= ub; c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 16; c1 += 1)
    for (c2 = 16 * c1; c2 <= min(N - 1, 16 * c1 + 15); c2 += 1)
      for (c3 = 400 * c0; c3 <= min(400 * c0 + 399, N - 1); c3 += 1)
        w[c3]=w[c3]+alpha*B[c3][c2]*x[c2];


 t_end= rtclock();
  printf("%0.6f\n", t_end - t_start);

    if (fopen(".test", "r")) {
#ifdef MPI
        if (my_rank == 0) {
            print_array();
        }
#else
        print_array();
#endif
    }

    return 0;
}
