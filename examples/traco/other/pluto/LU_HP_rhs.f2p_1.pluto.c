#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define N 200
#define N1 200
#define N2 200
#define N3 200

#define DIM1 200
#define DIM2 200
#define DIM3 200

float rsd[6][DIM1][DIM2][DIM3];
float u[6][DIM1][DIM2][DIM3];
float rho_i[DIM1][DIM2][DIM3];
float qs[DIM1][DIM2][DIM3];
float frct[6][DIM1][DIM2][DIM3];


int main() {
int k, m, i, j,tmp;






  int t1, t2, t3, t4, t5, t6;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  for (t1=1;t1<=N1;t1++) {
    for (t2=1;t2<=N2;t2++) {
      for (t3=1;t3<=N3;t3++) {
        tmp=1.0/u[1][t3][t2][t1];;
        qs[t3][t2][t1]=0.5*(u[2][t3][t2][t1]*u[2][t3][t2][t1]+u[3][t3][t2][t1]*u[3][t3][t2][t1]+u[4][t3][t2][t1]*u[4][t3][t2][t1])*tmp;;
        rho_i[t3][t2][t1]=tmp;;
        lbp=1;
        ubp=5;
#pragma omp parallel for private(lbv,ubv)
        for (t4=lbp;t4<=ubp;t4++) {
          rsd[t4][t3][t2][t1]=-frct[t4][t3][t2][t1];;
        }
      }
    }
  }
}
/* End of CLooG code */
return 0;
}


