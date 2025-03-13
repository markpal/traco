// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o doitgen.exe _doitgen_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>


#define N 128

float A[N][N][N];
float sum[N][N][N];
float C4[N][N];





int main(int argc, char *argv[]) {

   int r,q,p,s;


  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

   const int n = N;

     #pragma acc data copy(sum[0:n*n*n],A[0:n*n*n]) copyin(C4[0:n*n],n,r,q,p,s)
     {

     #pragma acc kernels loop private(r,q,p,s)
            for( r = 0; r< n; r++)  {
                #pragma acc loop
                for( q = 0; q< n; q++)  {
                #pragma acc loop
                    for( p = 0; p< n; p++)  {
                        sum[r][q][p] = 0;
                       #pragma acc loop
                        for( s = 0; s< n; s++)  {
                            sum[r][q][p] = sum[r][q][p] + A[r][q][s]*C4[s][p];
                        }
                    }
                    #pragma acc loop
                    for( p = 0; p< n; p++)  {
                        A[r][q][p] = sum[r][q][p];
                    }
                }
            }


     }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









