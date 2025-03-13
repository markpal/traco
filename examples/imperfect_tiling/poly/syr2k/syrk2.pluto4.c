#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define NMAX 512


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

int main()
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




  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

 register int lbv, ubv;

/* Start of CLooG code */
if (NI >= 1) {
  for (t2=0;t2<=floord(NI-1,4);t2++) {
    for (t3=0;t3<=floord(NI-1,4);t3++) {
      for (t4=4*t2;t4<=min(NI-1,4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NI-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t10=lbv;t10<=ubv;t10++) {
          c[t4][t10]*=beta;;
        }
      }
    }
  }
  if (NJ >= 1) {
    for (t2=0;t2<=floord(NI-1,4);t2++) {
      for (t3=0;t3<=floord(NI-1,4);t3++) {
        for (t4=0;t4<=floord(NJ-1,4);t4++) {
          for (t5=4*t2;t5<=min(NI-1,4*t2+3);t5++) {
            for (t6=4*t3;t6<=min(NI-1,4*t3+3);t6++) {
              for (t7=4*t4;t7<=min(NJ-1,4*t4+3);t7++) {
                c[t5][t6]+=alpha*a[t5][t7]*b[t6][t7];;
                c[t5][t6]+=alpha*b[t5][t7]*a[t6][t7];;
              }
            }
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
