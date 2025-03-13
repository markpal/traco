#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "util.h"

#pragma declarations
double a[NMAX][NMAX], b[NMAX][NMAX], c[NMAX][NMAX];
#pragma enddeclarations

#define TIME 1

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}


double t_start, t_end;

int main(int argc, char *argv[])
{
  int i,j, k;

  for (i = 0; i < NMAX; i++) {
    for (j = 0; j < NMAX; j++) {
      c[i][j] = 0.0;
      a[i][j] = 1.0+i*j*32.5/(NMAX*NMAX);
      b[i][j] = 1.0+i*j*3.4565/(NMAX*NMAX);
    }
  }

  IF_TIME(t_start = rtclock());
  int  beta = 1;
int alpha  = 1;
int NJ  = NMAX;
int NI = NMAX;
num_proc = atoi(argv[1]);
    printf("Ilosc procesorow: %i \n\n", num_proc);
    omp_set_num_threads(num_proc);

   int t1, t2, t3, t4, t5, t6, t7, t8;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (NI >= 1) {
  lbp=0;
  ubp=floord(NI-1,32);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(NI-1,32);t2++) {
      for (t3=0;t3<=floord(NJ,32);t3++) {
        if ((NJ >= 1) && (t3 == 0)) {
          for (t4=32*t1;t4<=min(NI-1,32*t1+31);t4++) {
            for (t5=32*t2;t5<=min(NI-1,32*t2+31);t5++) {
              c[t4][t5]*=beta;;
              for (t6=0;t6<=min(31,NJ-1);t6++) {
                c[t4][t5]+=alpha*a[t4][t6]*b[t5][t6];;
                c[t4][t5]+=alpha*b[t4][t6]*a[t5][t6];;
              }
            }
          }
        }
        if ((NJ == 0) && (t3 == 0)) {
          for (t4=32*t1;t4<=min(NI-1,32*t1+31);t4++) {
            for (t5=32*t2;t5<=min(NI-1,32*t2+31);t5++) {
              c[t4][t5]*=beta;;
            }
          }
        }
        if ((t3 >= 1) && (t3 <= floord(NJ-1,32))) {
          for (t4=32*t1;t4<=min(NI-1,32*t1+31);t4++) {
            for (t5=32*t2;t5<=min(NI-1,32*t2+31);t5++) {
              for (t6=32*t3;t6<=min(NJ-1,32*t3+31);t6++) {
                c[t4][t5]+=alpha*a[t4][t6]*b[t5][t6];;
                c[t4][t5]+=alpha*b[t4][t6]*a[t5][t6];;
              }
            }
          }
        }
      }
      if (NJ <= -1) {
        for (t4=32*t1;t4<=min(NI-1,32*t1+31);t4++) {
          for (t5=32*t2;t5<=min(NI-1,32*t2+31);t5++) {
            c[t4][t5]*=beta;;
          }
        }
      }
    }
  }
}
/* End of CLooG code */



  IF_TIME(t_end = rtclock());
  IF_TIME(fprintf(stdout, "%0.6lfs\n", t_end - t_start));

  if (fopen(".test", "r")) {
#ifdef MPI
      if (my_rank == 0) {
#endif
          for (i = 0; i < NMAX; i++) {
              for (j = 0; j < NMAX; j++) {
                  fprintf(stderr, "%lf ", c[i][j]);
              }
          }
          fprintf(stderr, "\n");
#ifdef MPI
      }
#endif
  }

  return 0;

}
