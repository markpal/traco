#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

#include "common.h"

// Kernel that executes on the CUDA device
 __global__ void par1(float (*A)[N][N], float (*B)[N][N], int N, int paczka)
{
  	  int idx = blockIdx.x;
      int lb = idx*paczka+1;
      int ub =  ((idx+1)*paczka < N-1) ? (idx+1)*paczka : N-1;
      int i,j;


      for (i=lb; i<ub; i++) {
			for (j=1; j<N-1; j++) {
				B[i][j] = 0.2 * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);
			}
	   }


}

 __global__ void par2(float (*A)[N][N], float (*B)[N][N], int N, int paczka)
{
  	  int idx = blockIdx.x;
      int lb = idx*paczka+1;
      int ub =  ((idx+1)*paczka < N-1) ? (idx+1)*paczka : N-1;
      int i,j;


	  for (i=lb; i<ub; i++) {
			for (j=1; j<N-1; j++) {
				A[i][j] = B[i][j];
			}
      }


}



 __global__ void seq(float (*A)[N][N], float (*B)[N][N], int N, int TSTEPS, int paczka)
{
    int i,j,t;

	for (t=0; t<TSTEPS; t++) {
		for (i=1; i<N-1; i++) {
			for (j=1; j<N-1; j++) {
				B[i][j] = 0.2 * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);
			}
		}
		for (i=1; i<N-1; i++) {
			for (j=1; j<N-1; j++) {
				A[i][j] = B[i][j];
			}
		}
	}
}

  	// main routine that executes on the host
int main(int argc, char **argv)
{
  	  int t;

  	  float *A_h, *A_d;  // Pointer to host & device arrays
  	  float *B_h, *B_d;  // Pointer to host & device arrays
  	  float *A_hs, *A_ds;  // Pointer to host & device arrays
  	  float *B_hs, *B_ds;  // Pointer to host & device arrays

	  struct timeval s1, f1;
	  double  duration;

  	  size_t size =  N * N * sizeof(float);
	  int _size = N * N * LENGTH;


  	  A_h = (float *)malloc(size);        // Allocate array on host
  	  A_hs = (float *)malloc(size);        // Allocate array on host
  	  B_h = (float *)malloc(size);        // Allocate array on host
  	  B_hs = (float *)malloc(size);        // Allocate array on host

        // Set the input data
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                A_h[i][j] = ((float) i*(j+2) + 2) / N;
                B_h[i][j] = ((float) i*(j+3) + 3) / N;
            }
        }

	  cudaMalloc((void **) &A_ds, size);   // Allocate array on device
	  cudaMalloc((void **) &B_ds, size);   // Allocate array on device

	  cudaMemcpy(A_ds, A_h, size, cudaMemcpyHostToDevice);

	  //  copy it to CUDA device
	  gettimeofday(&s1, NULL);

	  cudaMalloc((void **) &A_d, size);   // Allocate array on device
	  cudaMalloc((void **) &B_d, size);   // Allocate array on device

      gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas alloc: %2.6f seconds\n", duration);

	  gettimeofday(&s1, NULL);
  	  cudaMemcpy(A_d, A_h, size, cudaMemcpyHostToDevice);
      gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas copy: %2.6f seconds\n", duration);


	  // SEQ --------------------
      gettimeofday(&s1, NULL);
      seq<<<1, 1>>>((float(*)[N][N])A_ds, (float(*)[N][N]B_ds, N, TSTEPS, paczka)
      cudaThreadSynchronize();
      gettimeofday(&f1, NULL);

	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas sekw.: %2.6f seconds\n", duration);

  	  cudaMemcpy(A_hs, A_ds, sizeof(float)*size, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(B_hs, B_ds, sizeof(float)*size, cudaMemcpyDeviceToHost);

	  cudaFree(A_ds);
	  cudaFree(B_ds);


	  //------------------------

	  // PAR --------------------

      int block_size = 1;
  	  int n_blocks = atoi(argv[1]);  // CPU
	  int paczka = (int)ceil(N / n_blocks);
         // printf("\n*** %d \n", paczka);

      gettimeofday(&s1, NULL);
	  for (t=0; t<ITER; t++) {
        par1<<< n_blocks, block_size >>>((float(*)[N][N])A_d, (float(*)[N][N]B_d, N, paczka);
        cudaThreadSynchronize();
        par1<<< n_blocks, block_size >>>((float(*)[N][N])A_d, (float(*)[N][N]B_d, N, paczka);
        cudaThreadSynchronize();
	  }
	  cudaThreadSynchronize();
      gettimeofday(&f1, NULL);


	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas par: %2.6f seconds\n", duration);

	  //------------------------

  	  // Retrieve result from device and store it in host array
      gettimeofday(&s1, NULL);
      //cudaMemcpy(x_h, x_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
      cudaMemcpy(A_h, A_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(B_h, B_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
	  //cudaMemcpy(twiddle_h, twiddle_d, sizeof(float)*N, cudaMemcpyDeviceToHost);
      gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas fetch: %2.6f seconds\n", duration);

/*
	  for (int i=0; i<_size ; i++)
	  if (y_hs[i] != y_h[i])
          {
		printf("%i %2.6f %2.6f\n", i, y_hs[i], y_h[i]);
	        printf("blad\n");
		exit(0);
	  }
*/

  	  // Print results
  	  //for (int i=0; i<N; i++) printf("%d %f\n", i, a_h[i]);
  	  // Cleanup
      cudaFree(A_d);
      cudaFree(B_d);

      free(A_h);
      free(B_h);


}
