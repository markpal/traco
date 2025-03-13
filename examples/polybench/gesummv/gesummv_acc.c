// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024

int N = 1024;

float A[N][N];
float B[N][N];

float x[N];
float tmp[N];
float y[N];



/*
void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int i,j,k, alpha=0,beta=0;

#pragma acc data copyinout(tmp[0:n],y[0:n]) copyin(alpha, beta, A[0:n*n], B[0:n*n], x[0:n], NX, N)
{

for (i=0; i<NX; i++) {
 tmp[i] = 0;
 y[i] = 0;
 for (j=0; j<NX; j++) {
  tmp[i] = A[i][j] * x[j] + tmp[i];
  y[i] = B[i][j] * x[j] + y[i];
 }
 y[i] = alpha*tmp[i] + beta*y[i];
}
}

}
*/





int main(int argc, char *argv[]) {

  const int n = N;
  int NY=N, NX=N;

int c0, c1, c2;
int i,j,k, alpha=0,beta=0;


  //printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(tool_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

    #pragma acc data copy(tmp[0:n],y[0:n]) copyin(alpha, beta, A[0:n*n], B[0:n*n], x[0:n], NX, N, n, c0, c1)
    {

    #pragma acc kernels loop private(c0)
    for (c0 = 0; c0 < NX; c0 += 1) {
      tmp[c0]=0;
      y[c0]=0;
    }
    #pragma acc kernels loop  private(c1,c0)
    for (c0 = 0; c0 < NX; c0 += 1) {
        #pragma acc loop
      for (c1 = 0; c1 < NX; c1 += 1) {
        tmp[c0]=A[c0][c1]*x[c1]+tmp[c0];
        y[c0]=B[c0][c1]*x[c1]+y[c0];
      }
    }
    #pragma acc kernels loop private(c0)
    for (c0 = 0; c0 < NX; c0 += 1) {
      y[c0]=alpha*tmp[c0]+beta*y[c0];
    }
    }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









