// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024

float A[N][N];
float x1[N];
float x2[N];
float y_1[N];
float y_2[N];


/*
int i,j,k, alpha=0;

#pragma acc data copyinout(x1[0:n],x2[0:n]) copyin(alpha, A[0:n*n], y_1[0:n], y_2[0:n],N,NX) private(i,j)
{

	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x1[i] = x1[i] + A[i][j] * y_1[j];
		}
	}
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x2[i] = x2[i] + A[j][i] * y_2[j];
		}
	}
}

*/





int main(int argc, char *argv[]) {


int i,j,k, alpha=0;
const int n = N;
int NX = N;


  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();


#pragma acc data copy(x1[0:n],x2[0:n]) copyin(A[0:n*n], y_1[0:n], y_2[0:n],NX,n)
{
    #pragama acc kernels loop private(i,j)
	for (i=0; i<NX; i++) {
	    #pragma acc loop
		for (j=0; j<NX; j++) {
			x1[i] = x1[i] + A[i][j] * y_1[j];
            x2[i] = x2[i] + A[j][i] * y_2[j];
		}
	}

}
/*
#pragma acc data copy(x1[0:n],x2[0:n]) copyin(alpha, A[0:n*n], y_1[0:n], y_2[0:n],n,NX) private(i,j)
{

	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x1[i] = x1[i] + A[i][j] * y_1[j];
		}
	}
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x2[i] = x2[i] + A[j][i] * y_2[j];
		}
	}
}
*/

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}









