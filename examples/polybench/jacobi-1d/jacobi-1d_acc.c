// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float A[N];
float B[N];



/*
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


*/


int main(int argc, char *argv[]) {

  int i,j;
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   const int n = N;
   int TSTEPS = N;


   double start = omp_get_wtime();

    #pragma acc data copy(A[0:n],B[0:n]) copyin(n, TSTEPS)
    {
     int c0, c3;
    #pragma acc loop
    for (c0 = 0; c0 < 2 * TSTEPS; c0 += 1)
      if (c0 % 2 == 0) {
    #pragma acc kernels loop private(c3)
        for (c3 = 1; c3 < n - 1; c3 += 1){
          A[c3]=B[c3];
        }
      } else
    #pragma acc kernels loop private(c3)
        for (c3 = 1; c3 < n - 1; c3 += 1){
          B[c3]=0.33333*(A[c3-1]+A[c3]+A[c3+1]);
        }



        /*
 #pragma acc data copy(A[0:n],B[0:n]) copyin(n,TSTEPS,i,j)
{


  for (t = 0; t < TSTEPS; t++)
    {
      for (i = 1; i < n - 1; i++)
	B[i] = 0.33333 * (A[i-1] + A[i] + A[i + 1]);
      for (i = 1; i < n - 1; i++)
	A[i] = B[i];
    }
    }
*/



    }


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









