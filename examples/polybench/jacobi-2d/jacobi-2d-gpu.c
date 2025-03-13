#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#include <openacc.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK, TSTEPS;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2]) {
int i,j,k,t, alpha=0;

#pragma acc data copyinout(A[0:N*N],B[0:N*N]) copyin(N,TSTEPS) private(t,i)
{
for (t=0; t<TSTEPS; t++) {
 for (i=1; i<N-1; i++) {
  for (j=1; j<N-1; j++) {
   if (i < N-1 && j < N-1) {
    B[i][j] = 0.2 * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);
   }
  }
 }
 for (i=1; i<N-1; i++) {
  for (j=1; j<N-1; j++) {
   A[i][j] = B[i][j];
   }
  }
}
}

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2]) {



#pragma acc data copyinout(A[0:N*N],B[0:N*N]) copyin(N,TSTEPS)
{
    int c0, c2, c3;

#pragma acc loop
for (c0 = 0; c0 < 2 * TSTEPS; c0 += 1){
if(c0%2==1)
#pragma acc kernels loop private(c2,c3)
 for (c2 = 1; c2 < N - 1; c2 += 1)
 #pragma acc loop
  for (c3 = 1; c3 < N - 1; c3 += 1)
    B[c2][c3] = 0.2 * (A[c2][c3] + A[c2][c3-1] + A[c2][1+c3] + A[1+c2][c3] + A[c2-1][c3]);
else
#pragma acc kernels loop private(c2,c3)
   for (c2 = 1; c2 < N - 1; c2 += 1)
   #pragma acc loop
    for (c3 = 1; c3 < N - 1; c3 += 1)
      A[c2][c3] = B[c2][c3];
}
}

}

int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);


  TSTEPS = N;

  TSTEPS = NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));



 // printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B);
  else if (tool_kind == 2){
         comp(A,B);
   }
       else{
          comp_pluto(A,B);
   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









