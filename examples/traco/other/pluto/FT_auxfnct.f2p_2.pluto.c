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

float x[DIM1][DIM2][DIM3], y[DIM1][DIM2][DIM3], twiddle[DIM1][DIM2][DIM3];



int main(){
int k, i, j;





  int t1, t2, t3, t4;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  lbp=1;
  ubp=N1;
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=1;t2<=N2;t2++) {
      for (t3=1;t3<=N3;t3++) {
        y[t3][t2][t1]=y[t3][t2][t1]*twiddle[t3][t2][t1];;
        x[t3][t2][t1]=y[t3][t2][t1];;
      }
    }
  }
}
/* End of CLooG code */
return 0;
}


