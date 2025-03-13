#include<omp.h>
#include<stdio.h>
#include<openacc.h>


#define N 1024

float A[N][N];
float B[N][N];
float C[N][N];


int main(int argc, char *argv[]) {

  int i,j,k, alpha=0, beta = 0;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


   const int n = N;
   int NK = N;
   int NJ = N;
   int NI = N;

   double start = omp_get_wtime();

  #pragma acc data copy(C[0:n*n]) copyin(alpha, beta, A[0:n*n], B[0:n*n], NI,NJ,NK,n)
  {
    #pragma acc kernels loop private(i,j,k)
	for (i=0; i<NI; i++) {
	 #pragma acc loop
     for (j=0; j<NJ; j++) {
      C[i][j] *= beta;
      #pragma acc loop
      for (k=0; k<NK; k++) {
       C[i][j] += alpha * A[i][k] * B[k][j];
      }
     }
    }
  }


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









