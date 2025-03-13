// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float ey[N][N];
float ex[N][N];
float hz[N][N];


void seq(float ey[DIM1][DIM2], float ex[DIM1][DIM2], float hz[DIM1][DIM2]) {
int t,j,i;
const int n = N+1;
int NI = N;
int NJ = N;
int TSTEPS = N;

    #pragma acc data copy(ey[0:n*n],ex[0:n*n], hz[0:n*n]) copyin(NI,NJ,TSTEPS,t,i,j,n)
    {

	for (t=0; t<TSTEPS; t++) {
		for (j=0; j<NJ; j++) {
			ey[0][j] = t;
		}
		for (i=1; i<NI; i++) {
			for (j=0; j<NJ; j++) {
				ey[i][j] = ey[i][j] - 0.5*(hz[i][j] - hz[i-1][j]);
			}
		}
		for (i=0; i<NI; i++) {
			for (j=1; j<NJ; j++) {
				ex[i][j] = ex[i][j] - 0.5*(hz[i][j] - hz[i][j-1]);
			}
		}
		for (i=0; i<NI-1; i++) {
			for (j=0; j<NJ-1; j++) {
				hz[i][j] = hz[i][j] - 0.7*(ex[i][j+1] - ex[i][j] + ey[i+1][j] - ey[i][j]);
			}
		}
	}

    }


}







void comp(float ey[DIM1][DIM2], float ex[DIM1][DIM2], float hz[DIM1][DIM2]) {
int t,i,j;
const int n = N+1;
int NI = N;
int NJ = N;
int TSTEPS = N;

#pragma acc data copy(ey[0:n*n],ex[0:n*n], hz[0:n*n]) copyin(NI,NJ,TSTEPS,t,i,j,n) create(i,j)
{

    #pragma acc loop
	for (t=0; t<TSTEPS; t++) {
    #pragma acc kernels loop private(i,j)
		for (i=0; i<NJ; i++) {
			ey[0][i] = t;
		}

        #pragma acc kernels loop private(i,j)
		for (i=1; i<NI; i++) {
		    #pragma acc loop
			for (j=0; j<NJ; j++) {
				ey[i][j] = ey[i][j] - 0.5*(hz[i][j] - hz[i-1][j]);
			}
		}

        #pragma acc kernels loop private(i,j)
		for (i=0; i<NI; i++) {
		    #pragma acc loop
			for (j=1; j<NJ; j++) {
				ex[i][j] = ex[i][j] - 0.5*(hz[i][j] - hz[i][j-1]);
			}
		}

        #pragma acc kernels loop private(i,j)
		for (i=0; i<NI-1; i++) {
		    #pragma acc loop
			for (j=0; j<NJ-1; j++) {
				hz[i][j] = hz[i][j] - 0.7*(ex[i][j+1] - ex[i][j] + ey[i+1][j] - ey[i][j]);
			}
		}

	}

}
}


int main(int argc, char *argv[]) {


   double start = omp_get_wtime();

   comp(); //seq();


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









