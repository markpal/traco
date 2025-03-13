// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float A[N][N];
float B[N][N];
float C[N][N];
float D[N][N];
float E[N][N];
float F[N][N];
float G[N][N];


int main(int argc, char *argv[]) {

      int i,j,k;

   double start = omp_get_wtime();


   const int n = N;
   int ni =  N;
   int nj =  N;
   int nl =  N;
   int nk =  N;
   int nm = N;

 #pragma acc data copy(E[0:n*n],F[0:n*n],G[0:n*n]) copyin(A[0:n*n],B[0:n*n],C[0:n*n],D[0:n*n],n,ni,nj,nl,nk,nm)
  {

    #pragma acc kernels loop
        for (i=0; i<ni; i++) {
            #pragma acc loop
            for (j=0; j<nj; j++) {
                E[i][j] = 0;
                #pragma acc loop
                for (k=0; k<nk; k++) {
                    E[i][j] += A[i][k] * B[k][j];
                }
            }
        }


        #pragma acc kernels loop
        for (i=0; i<nj; i++) {
            #pragma acc loop
            for (j=0; j<nl; j++) {
                F[i][j] = 0;
                #pragma acc loop
                for (k=0; k<nm; k++) {
                    F[i][j] += C[i][k] * D[k][j];
                }
            }
        }


        #pragma acc kernels loop
        for (i=0; i<ni; i++) {
            #pragma acc loop
            for (j=0; j<nl; j++) {
                G[i][j] = 0;
                #pragma acc loop
                for (k=0; k<nj; k++) {
                    G[i][j] += E[i][k] * F[k][j];
                }
            }
        }
  }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

