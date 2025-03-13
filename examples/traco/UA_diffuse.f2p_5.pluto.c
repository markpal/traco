#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

int N = 100;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {
int k, iz, i, j;




  int t1, t2, t3, t4, t5, t6, t7, t8;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1) && (N4 >= 1)) {
  lbp=0;
  ubp=floord(N2,32);
#pragma omp parallel for private(lbv,ubv,t1,t2,t3,t4,t5,t6,t7,t8)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N3,32);t2++) {
      for (t3=0;t3<=floord(N4,32);t3++) {
        for (t4=0;t4<=floord(N1,32);t4++) {
          for (t5=max(1,32*t2);t5<=min(N3,32*t2+31);t5++) {
            for (t6=max(1,32*t3);t6<=min(N4,32*t3+31);t6++) {
              for (t7=max(1,32*t4);t7<=min(N1,32*t4+31);t7++) {
                lbv=max(1,32*t1);
                ubv=min(N2,32*t1+31);
#pragma ivdep
#pragma vector always
                for (t8=lbv;t8<=ubv;t8++) {
                  r[t6][t5][t8]=r[t6][t5][t8]+u[t6][t5][t7]*wdtdr[t7][t8];;
                }
              }
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
}


void comp(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {
int t2,t3,t4,t1;

if (N3 >= 1 && N1 >= 2 && N4 >= 1) {
  #pragma omp parallel for  private(t4,t2,t3,t1)
  for(t2 = 1; t2 <= N2; t2++) {
    for(t3 = 1; t3 <= N3; t3++) {
      for(t4 = 1; t4 <= N4; t4++) {
        r[t4][t3][t2]=r[t4][t3][t2]+u[t4][t3][1]*wdtdr[1][t2];
        if (t2 <= N2 && t4 >= 1 && t4 <= N4 && t3 >= 1 && N3 >= t3 && t2 >= 1) {
          for(t1 = 2; t1 <= N1; t1++) {
            r[t4][t3][t2]=r[t4][t3][t2]+u[t4][t3][t1]*wdtdr[t1][t2];
          }
        }

      }
    }
  }
}

}




int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*u)[DIM2][DIM3], (*wdtdr)[DIM2], (*r)[DIM2][DIM3];
  wdtdr = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  r = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  if(num_proc == 1)
    seq(u, wdtdr, r);
  else
    comp(u, wdtdr, r);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas sekwencyjny: %2.3f seconds\n", duration);




}


