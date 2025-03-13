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





void seq(float A[DIM1][DIM2], float q[DIM1], float p[DIM1], float r[DIM1], float s[DIM1]) {
int i,j,k, alpha=0;

#pragma scop
  for (i = 0; i < NY; i++)
    s[i] = 0;
  for (i = 0; i < NX; i++)
  {
      q[i] = 0;
      for (j = 0; j < NY; j++)
      {
	     s[j] = s[j] + r[i] * A[i][j];
         q[i] = q[i] + A[i][j] * p[j];
      }
  }
#pragma endscop
}







void comp(float A[DIM1][DIM2], float q[DIM1], float p[DIM1], float r[DIM1], float s[DIM1]) {
// SCC
  int i, c0, c1, c2,t1,t2;
  #pragma omp parallel for
  for (i = 0; i < NY; i++)
    s[i] = 0;


 #pragma omp parallel for  private(t2,t1)
  for(t2 = 0; t2 <= NY-1; t2++) {
      for(t1 = 0; t1 <= NX-1; t1++) {
        s[t2]=s[t2]+r[t1]*A[t1][t2];
      }
  }

// IND loop
#pragma omp parallel for private(t1)
for(t1 = 0; t1 <= NX-2; t1++) {
  q[t1]=0;
}
if (NX >= 1 && NY >= 1) {
  q[NX-1]=0;
}
if (NX == 1) {
    #pragma omp parallel for private(t2)
  for(t2 = 0; t2 <= NY-1; t2++) {
    s[t2]=s[t2]+r[0]*A[0][t2];
  }
}
if (NX >= 2 && NY <= 0) {
  q[NX-1]=0;
}
#pragma omp parallel for private(c1,c0)
for (c0 = 0; c0 < NX; c0 += 1) {
  for (c1 = 0; c1 < NY; c1 += 1) {
    q[c0]=q[c0]+A[c0][c1]*p[c1];
  }
}


}

void comp_pluto(float A[DIM1][DIM2], float q[DIM1], float p[DIM1], float r[DIM1], float s[DIM1]) {

  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
lbp=0;
ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
for (t2=lbp;t2<=ubp;t2++) {
  q[t2]=0;;
}
if (NY >= 1) {
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NY-1;t3++) {
      q[t2]=q[t2]+A[t2][t3]*p[t3];;
    }
  }
}
lbp=0;
ubp=NY-1;
#pragma omp parallel for private(lbv,ubv)
for (t2=lbp;t2<=ubp;t2++) {
  s[t2]=0;;
}
if (NX >= 1) {
  lbp=0;
  ubp=NY-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NX-1;t3++) {
      s[t2]=s[t2]+r[t3]*A[t3][t2];;
    }
  }
}
/* End of CLooG code */

}




int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1,num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 2)
    N = atoi(argv[3]);



  NY = NX = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], *q, *p, *r, *s;

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  q = (float (*))malloc(DIM1 * sizeof(float));
  p = (float (*))malloc(DIM1 * sizeof(float));
  r = (float (*))malloc(DIM1 * sizeof(float));
  s = (float (*))malloc(DIM1 * sizeof(float));




 // printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,q,p,r,s);
  else if (tool_kind == 2){
          comp(A,q,p,r,s);
   }
       else{
          comp_pluto(A,q,p,r,s);

   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









