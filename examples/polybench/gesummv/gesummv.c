#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NY, NX;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int i,j,k, alpha=0,beta=0;

#pragma scop
for (i=0; i<NX; i++) {
 tmp[i] = 0;
 y[i] = 0;
 for (j=0; j<NX; j++) {
  tmp[i] = A[i][j] * x[j] + tmp[i];
  y[i] = B[i][j] * x[j] + y[i];
 }
 y[i] = alpha*tmp[i] + beta*y[i];
}
#pragma endscop

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int c0, c1, c2;
int i,j,k, alpha=0,beta=0;
// scc

#include <omp.h>
#pragma omp parallel for private(c0)
for (c0 = 0; c0 < NX; c0 += 1) {
  tmp[c0]=0;
  y[c0]=0;
}
#pragma omp parallel for private(c1,c0)
for (c0 = 0; c0 < NX; c0 += 1) {
  for (c1 = 0; c1 < NX; c1 += 1) {
    tmp[c0]=A[c0][c1]*x[c1]+tmp[c0];
    y[c0]=B[c0][c1]*x[c1]+y[c0];
  }
}
#pragma omp parallel for private(c0)
for (c0 = 0; c0 < NX; c0 += 1) {
  y[c0]=alpha*tmp[c0]+beta*y[c0];
}


}

void comp_pluto(float A[DIM1][DIM2], float B[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int i,j,k, alpha=0,beta=0;


  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (NX >= 1) {
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    y[t2]=0;;
  }
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NX-1;t3++) {
      y[t2]=B[t2][t3]*x[t3]+y[t2];;
    }
  }
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    tmp[t2]=0;;
  }
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NX-1;t3++) {
      tmp[t2]=A[t2][t3]*x[t3]+tmp[t2];;
    }
  }
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    y[t2]=alpha*tmp[t2]+beta*y[t2];;
  }
}
/* End of CLooG code */


}




int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NX = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2], *x, *y, *tmp;

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  x = (float (*))malloc(DIM1 * sizeof(float));
  y = (float (*))malloc(DIM1 * sizeof(float));
  tmp = (float (*))malloc(DIM1 * sizeof(float));




  //printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(tool_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B,y,tmp,x);
  else if (tool_kind == 2){
          comp(A,B,y,tmp,x);
   }
       else{
          comp_pluto(A,B,y,tmp,x);

   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









