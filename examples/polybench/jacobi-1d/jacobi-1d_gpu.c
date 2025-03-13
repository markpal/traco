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
int TSTEPS;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1], float B[DIM1]) {
int i,t;


#pragma acc data copyinout(A[0:N],B[0:N]) copyin(N,TSTEPS) private(t,i)
{


  for (t = 0; t < TSTEPS; t++)
    {
      for (i = 1; i < N - 1; i++)
	B[i] = 0.33333 * (A[i-1] + A[i] + A[i + 1]);
      for (i = 1; i < N - 1; i++)
	A[i] = B[i];
    }

}

}







void comp(float A[DIM1], float B[DIM1]) {


#pragma acc data copyinout(A[0:N*N],B[0:N*N]) copyin(N,TSTEPS)
{
 int c0, c3;
#pragma acc loop
for (c0 = 0; c0 < 2 * TSTEPS; c0 += 1)
  if (c0 % 2 == 0) {
#pragma acc kernels loop private(c3)
    for (c3 = 1; c3 < N - 1; c3 += 1)
      A[c3]=B[c3];
  } else
#pragma acc kernels loop private(c3)
    for (c3 = 1; c3 < N - 1; c3 += 1)
      B[c3]=0.33333*(A[c3-1]+A[c3]+A[c3+1]);
}
}






int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);


  TSTEPS = N*10;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float *A, *B;

  A = (float (*))malloc(DIM1 * sizeof(float));
  B = (float (*))malloc(DIM1 * sizeof(float));


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









