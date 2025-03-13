// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o atax.exe atax_acc.c

#include<omp.h>
#include<stdio.h>
#include<openacc.h>


#define N 1024


float A[N][N];
float y[N];
float x[N];
float tmp[N];



int main(int argc, char *argv[]) {

   int i,j;
   const int n = N;
   int NY =  N;
   int NX =  N;



  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

#pragma acc data copy(tmp[0:n],y[0:n]) copyin(A[0:n*n],x[0:n],n,NY,NX,i,j)
{
#pragma acc kernels loop
for (i = 0; i < NY; i++)
{
    y[i] = 0;
}

#pragma acc kernels loop
 for (i = 0; i < NX; i++){
   #pragma acc loop
    for (j = 0; j < NY; j++){
	y[j] = y[j] + A[i][j] * tmp[i];
    }
}

#pragma acc kernels loop
 for (i = 0; i < NX; i++){
      tmp[i] = 0;
}

#pragma acc kernels loop
for (i = 0; i < NX; i++){
   #pragma acc loop
      for (j = 0; j < NY; j++)
      {
	tmp[i] = tmp[i] + A[i][j] * x[j];
      }
  }
}








   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









