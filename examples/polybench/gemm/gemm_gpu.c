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





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;


  #pragma acc data copyinout(C[0:n*n]) copyin(alpha, beta, A[0:n*n], B[0:n*n], NI,NJ,NK)
  {

	for (i=0; i<NI; i++) {
     for (j=0; j<NJ; j++) {
      C[i][j] *= beta;
      for (k=0; k<NK; k++) {
       C[i][j] += alpha * A[i][k] * B[k][j];
      }
     }
    }
  }


}




void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;


  #pragma acc data copyinout(C[0:n*n]) copyin(alpha, beta, A[0:n*n], B[0:n*n], NI,NJ,NK)
  {
    #pragma omp kernels loop private(i,j,k)
	for (i=0; i<NI; i++) {
     for (j=0; j<NJ; j++) {
      C[i][j] *= beta;
      for (k=0; k<NK; k++) {
       C[i][j] += alpha * A[i][k] * B[k][j];
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

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));



  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B,C);
  else if (tool_kind == 2){

         comp(A,B,C);

   }
       else{

          comp_pluto(A,B,C);

   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









