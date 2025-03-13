// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define NX 128

float A[NX][NX];
float u1[NX];
float u2[NX];
float v1[NX];
float v2[NX];
float w[NX];
float x[NX];
float y[NX];
float z[NX];

// This is 'gemver', a general matrix vector multiplication and matrix addition kernel
int main(int argc, char *argv[]) {
	int i,j;

    // Set the constants
	int alpha = 43532;
	int beta = 12313;

	// Set the input data
	for (i=0; i<NX; i++) {
		u1[i] = i;
		u2[i] = (i+1)/NX/2.0;
		v1[i] = (i+1)/NX/4.0;
		v2[i] = (i+1)/NX/6.0;
		w[i] = 0.0;
		x[i] = 0.0;
		y[i] = (i+1)/NX/8.0;
		z[i] = (i+1)/NX/9.0;
		for (j=0; j<NX; j++) {
			A[i][j] = ((float) i*j) / NX;
		}
	}

	double start = omp_get_wtime();

    int nx = NX;
    int n = NX;
    #pragma acc data copy(A[0:n*n],i,j,x[0:n],w[0:n]) copyin(y[0:n], z[0:n], u1[0:n], v1[0:n], u2[0:n], v2[0:n],nx,n,beta,alpha) create(i,j)
    {
#pragma acc kernels loop private(i,j)
	for (i=0; i<nx; i++) {
	     #pragma acc loop
    		for (j=0; j<nx; j++) {
    			A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];
  		}
	}

#pragma acc kernels loop private(i,j)
	for (i=0; i<nx; i++) {
	     #pragma acc loop
    		for (j=0; j<nx; j++) {
    			x[i] = x[i] + beta * A[j][i] * y[j];
  		}
	}
#pragma acc kernels loop private(i,j)
	for (i=0; i<nx; i++) {
  		x[i] = x[i] + z[i];
	}
#pragma acc kernels loop private(i,j)
	for (i=0; i<nx; i++) {
	       #pragma acc loop
    		for (j=0; j<nx; j++) {
    			w[i] = w[i] +  alpha * A[i][j] * x[j];
  		}
	}
    }



	double end = omp_get_wtime();
	printf("%.2f\n", end - start);



	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

