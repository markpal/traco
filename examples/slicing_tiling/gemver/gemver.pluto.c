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



  int num_proc = atoi(argv[1]);

  omp_set_num_threads(num_proc);



  int t1, t2, t3, t4, t5, t6, t7, t8;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (N >= 1) {
  lbp=0;
  ubp=floord(N-1,400);
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=floord(N-1,16);t3++) {
      for (t4=16*t3;t4<=min(N-1,16*t3+15);t4++) {
        lbv=400*t2;
        ubv=min(N-1,400*t2+399);
#pragma ivdep
#pragma vector always
        for (t8=lbv;t8<=ubv;t8++) {
          B[t4][t8]=A[t4][t8]+u1[t4]*v1[t8]+u2[t4]*v2[t8];;
        }
        lbv=400*t2;
        ubv=min(N-1,400*t2+399);
#pragma ivdep
#pragma vector always
        for (t8=lbv;t8<=ubv;t8++) {
          x[t8]=x[t8]+beta*B[t4][t8]*y[t4];;
        }
      }
    }
  }
  lbp=0;
  ubp=N-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    x[t2]=x[t2]+z[t2];;
  }
  lbp=0;
  ubp=floord(N-1,400);
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=floord(N-1,16);t3++) {
      for (t4=400*t2;t4<=min(N-1,400*t2+399);t4++) {
        for (t5=16*t3;t5<=min(N-1,16*t3+15);t5++) {
          w[t4]=w[t4]+alpha*B[t4][t5]*x[t5];;
        }
      }
    }
  }
}
/* End of CLooG code */
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
