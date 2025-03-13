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
int NI, NJ, NL, NM, NK;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;

   int n = N;
   int ni = n;
   int nj = n;
   int nl = n;
   int nk = n;
    #pragma acc data copyinout(tmp[0:n*n],D[0:n*n]) copyin(alpha, A[0:n*n], B[0:n*n], C[0:n*n],n,ni,nj,nl,nk) private(i,j,k)
    {
     for (i=0; i<ni; i++) {
     for (j=0; j<nj; j++) {
      tmp[i][j] = 0;
      for (k=0; k<nk; k++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
     }
    }

  	for (i=0; i<ni; i++) {
     for (j=0; j<nl; j++) {
      D[i][j] *= beta;
       for (k=0; k<nj; k++) {
         D[i][j] += tmp[i][k] * C[k][j];
      }
    }
   }


   }

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;


   int n = N;
   int ni = n;
   int nj = n;
   int nl = n;
   int nk = n;

#pragma acc data copyinout(tmp[0:n*n],D[0:n*n]) copyin(alpha, A[0:n*n], B[0:n*n], C[0:n*n],n,ni,nj,nl,nk)
{

	#pragma acc kernels loop private(i,j,k)
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

    #pragma acc kernels loop private(i,j,k)
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

}



int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*D)[DIM2], (*tmp)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  D = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  tmp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));




  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B,C,D,tmp);
  else
    comp(A,B,C,D,tmp);



   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









