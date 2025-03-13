#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#include<openacc.h>

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


   int n = N;
   int ny = n;
   int nx = n;

 #pragma acc data copyout(s[0:n],q[0:n]) copyin(A[0:n*n], r[0:n], p[0:n],n,ny,nx) private(i,j)
 {
  for (i = 0; i < ny; i++)
    s[i] = 0;
  for (i = 0; i < nx; i++)
  {
      q[i] = 0;
      for (j = 0; j < ny; j++)
      {
	     s[j] = s[j] + r[i] * A[i][j];
         q[i] = q[i] + A[i][j] * p[j];
      }
  }
 }

}







void comp(float A[DIM1][DIM2], float q[DIM1], float p[DIM1], float r[DIM1], float s[DIM1]) {

   int n = N;
   int ny = n;
   int nx = n;

     int i, c0, c1, c2,t1,t2;

 #pragma acc data copyout(s[0:n],q[0:n]) copyin(A[0:n*n], r[0:n], p[0:n],n,ny,nx)
 {


// SCC

  #pragma acc kernels loop private(i)
  for (i = 0; i < NY; i++)
    s[i] = 0;


  #pragma acc kernels loop private(t1,t2)
  for(t2 = 0; t2 <= NY-1; t2++) {
       #pragma acc loop
      for(t1 = 0; t1 <= NX-1; t1++) {
        s[t2]=s[t2]+r[t1]*A[t1][t2];
      }
  }

// IND loop
#pragma acc kernels loop private(t1)
for(t1 = 0; t1 <= NX-2; t1++) {
  q[t1]=0;
}
if (NX >= 1 && NY >= 1) {
  q[NX-1]=0;
}
if (NX == 1) {
     #pragma acc kernels loop private(t2)
  for(t2 = 0; t2 <= NY-1; t2++) {
    s[t2]=s[t2]+r[0]*A[0][t2];
  }
}
if (NX >= 2 && NY <= 0) {
  q[NX-1]=0;
}
 #pragma acc kernels loop private(t1,t2)
for (c0 = 0; c0 < NX; c0 += 1) {
    #pragma acc loop
  for (c1 = 0; c1 < NY; c1 += 1) {
    q[c0]=q[c0]+A[c0][c1]*p[c1];
  }
}

 }

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









