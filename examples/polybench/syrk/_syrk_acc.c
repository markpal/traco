// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float a[N][N];
float c[N][N];




void seq() {
int i,j,k, alpha=0, beta = 0;

   const int n = N;
   int NI = N;
   int NJ = N;
    #pragma acc data copy(c[0:n*n]) copyin(alpha, a[0:n*n], n, NI, NJ) private(i,j,k)
    {
	for (i=0; i<NI; i++) {
		for (j=0; j<NI; j++) {
			c[i][j] *= beta;
			for (k=0; k<NJ; k++) {
				c[i][j] += alpha * a[i][k] * a[j][k];

			}
		}
	}
    }


}







void comp() {
int alpha=0, beta = 0;
int i,j,k;


   const int n = N;
   int NI = N;
   int NJ = N;
    #pragma acc data copy(c[0:n*n]) copyin(alpha, a[0:n*n], n, NI, NJ) private(i,j,k)
    {
   #pragma acc kernels loop private(i,k,j)
	for (i=0; i<NI; i++) {
	    #pragma acc  loop
		for (j=0; j<NI; j++) {
			c[i][j] *= beta;
			 #pragma acc  loop
			for (k=0; k<NJ; k++) {
				c[i][j] += alpha * a[i][k] * a[j][k];

			}
		}
	}
    }

}



int main(int argc, char *argv[]) {


double start = omp_get_wtime();

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    //seq();

      comp();


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









