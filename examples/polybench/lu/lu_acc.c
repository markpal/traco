// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float a[N][N];




int main(int argc, char *argv[]) {

    int p,j,i;
    const int n = N;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

    #pragma acc data copy(a[0:n*n]) copyin(p,i,n)
    {
        #pragma acc loop
        for (p=0; p<n; p++) {
    #pragma acc kernels loop private(i)
            for (i=p+1; i<n; i++)   {
                a[p][i] = a[p][i]/a[p][p];
            }
    #pragma acc kernels loop private(i,j)
            for(i=p+1; i<n; i++)    {
                #pragma acc loop
                for (j=p+1; j<n; j++)   {
                    a[i][j] = a[i][j] - a[i][p]*a[p][j];
                }
            }
        }
    }

/*
    #pragma acc data copy(a[0:n*n]) copyin(p,i,n)
    {
        for (p=0; p<n; p++) {
            for (i=p+1; i<n; i++)   {
                a[p][i] = a[p][i]/a[p][p];
            }
            for(i=p+1; i<n; i++)    {
                for (j=p+1; j<n; j++)   {
                    a[i][j] = a[i][j] - a[i][p]*a[p][j];
                }
            }
        }
    }
*/

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









