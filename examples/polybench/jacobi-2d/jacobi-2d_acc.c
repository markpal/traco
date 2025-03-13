// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float A[N][N];
float B[N][N];


/*

void seq(float A[DIM1][DIM2], float B[DIM1][DIM2]) {
int i,j,k,t, alpha=0;

#pragma acc data copy(A[0:n*n],B[0:n*n]) copyin(n,TSTEPS) private(t,i)
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

*/






int main(int argc, char *argv[]) {

int i,j,k,t, alpha=0;


 // printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();



   const int n = N;
   int TSTEPS = N;


#pragma acc data copy(A[0:n*n],B[0:n*n]) copyin(n,TSTEPS)
{
    int c0, c2, c3;

#pragma acc loop
for (c0 = 0; c0 < 2 * TSTEPS; c0 += 1){
if(c0%2==1)
#pragma acc kernels loop private(c2,c3)
 for (c2 = 1; c2 < n - 1; c2 += 1){
 #pragma acc loop
  for (c3 = 1; c3 < n - 1; c3 += 1){
    B[c2][c3] = 0.2 * (A[c2][c3] + A[c2][c3-1] + A[c2][1+c3] + A[1+c2][c3] + A[c2-1][c3]);
  }
 }
else
#pragma acc kernels loop private(c2,c3)
   for (c2 = 1; c2 < n - 1; c2 += 1){
   #pragma acc loop
    for (c3 = 1; c3 < n - 1; c3 += 1){
      A[c2][c3] = B[c2][c3];
    }
   }
}
}



   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









