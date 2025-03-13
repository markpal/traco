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

int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2][DIM3], float sum[DIM1][DIM2][DIM3], float C4[DIM1][DIM2]) {
int r,q,p,s;

int n = N;
 #pragma acc data copyout(sum[0:n*n*n]) copyin(A[0:n*n*n], C4[0:n*n],n) private(r,q,p,s)
 {
        for( r = 0; r< N; r++)  {
            for( q = 0; q< N; q++)  {
                for( p = 0; p< N; p++)  {
                    sum[r][q][p] = 0;
                    for( s = 0; s< N; s++)  {
                        sum[r][q][p] = sum[r][q][p] + A[r][q][s]*C4[s][p];
                    }
                }
                for( p = 0; p< N; p++)  {
                    A[r][q][p] = sum[r][q][p];
                }
            }
        }
 }

}







void comp(float A[DIM1][DIM2][DIM3], float sum[DIM1][DIM2][DIM3], float C4[DIM1][DIM2]) {
int r,q,p,s;
int c0, c1, c2, c3;

int n = N;
 #pragma acc data copyout(sum[0:n*n*n]) copyin(A[0:n*n*n], C4[0:n*n],n)
 {

 #pragma acc kernels loop  private(r,q,p,s)
        for( r = 0; r< N; r++)  {
            #pragma acc loop
            for( q = 0; q< N; q++)  {
            #pragma acc loop
                for( p = 0; p< N; p++)  {
                    sum[r][q][p] = 0;
                   #pragma acc loop
                    for( s = 0; s< N; s++)  {
                        sum[r][q][p] = sum[r][q][p] + A[r][q][s]*C4[s][p];
                    }
                }
                #pragma acc loop
                for( p = 0; p< N; p++)  {
                    A[r][q][p] = sum[r][q][p];
                }
            }
        }


 }
/*
#pragma omp parallel for
for (c0 = 0; c0 < N; c0 += 1) {
  for (c1 = 0; c1 < N; c1 += 1) {
    for (c2 = 0; c2 < N; c2 += 1) {
      sum[c0][c1][c2]=0;
    }
  }
}
#pragma omp parallel for
for (c0 = 0; c0 < N; c0 += 1) {
  for (c1 = 0; c1 < N; c1 += 1) {
    for (c2 = 0; c2 < N; c2 += 1) {
      for (c3 = 0; c3 < N; c3 += 1) {
        sum[c0][c1][c2]=sum[c0][c1][c2]+A[c0][c1][c3]*C4[c3][c2];
      }
    }
  }
}
#pragma omp parallel for
for (c0 = 0; c0 < N; c0 += 1) {
  for (c1 = 0; c1 < N; c1 += 1) {
    for (c2 = 0; c2 < N; c2 += 1) {
      A[c0][c1][c2]=sum[c0][c1][c2];
    }
  }
}
*/

}




int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2][DIM3], (*sum)[DIM2][DIM3], (*C4)[DIM2];

  A = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  sum = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  C4 = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));




  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,sum,C4);
  else if (tool_kind == 2)
    comp(A,sum,C4);
    else
      comp_pluto(A,sum,C4);


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









