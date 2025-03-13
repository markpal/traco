#include<omp.h>
#include<stdio.h>
#include<openacc.h>


#define N 1024

float A[N][N];
float B[N][N];
float C[N][N];
float D[N][N];
float tmp[N][N];


int main(int argc, char *argv[]) {


  int i,j,k,alpha,beta;

  //printf("Ilosc procesorow: %i \n\n", num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  double start = omp_get_wtime();

   const int n = N;
   int ni =  N;
   int nj =  N;
   int nl =  N;
   int nk =  N;


#pragma acc data copy(tmp[0:n*n],D[0:n*n]) copyin(beta,alpha,A[0:n*n],B[0:n*n],C[0:n*n],n,ni,nj,nl,nk)
{

	#pragma acc kernels loop
	for (i=0; i<ni; i++) {
	 #pragma acc loop
     for (j=0; j<nj; j++) {
      tmp[i][j] = 0;
       #pragma acc loop
      for (k=0; k<nk; k++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
     }
    }

    #pragma acc kernels loop
  	for (i=0; i<ni; i++) {
  	 #pragma acc loop
     for (j=0; j<nl; j++) {
      D[i][j] *= beta;
         #pragma acc loop
       for (k=0; k<nj; k++) {
         D[i][j] += tmp[i][k] * C[k][j];
      }
    }
   }

}


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}



