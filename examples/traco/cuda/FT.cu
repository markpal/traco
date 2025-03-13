#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

const long int N = 200;  // Number of elements in arrays
const long int N1 = N;  // Number of elements in arrays
const long int N2 = N;  // Number of elements in arrays
const long int N3 = N;  // Number of elements in arrays

const int DIM_N = N + 2;

// Kernel that executes on the CUDA device
 __global__ void par(float (*x)[DIM_N][DIM_N], float (*y)[DIM_N][DIM_N], float (*twiddle)[DIM_N][DIM_N], int N1, int N2, int N3, int DIM_N, int paczka)
{
  	  int idx = blockIdx.x;
          int t1, t2, t3;
          int lb = idx*paczka+1;
          int ub =  ((idx+1)*paczka < N1) ? (idx+1)*paczka : N1;

	if (N3 >= 1 && N2 >= 1) {
	  for(t1 = lb; t1 <= ub; t1++) {
	
	      for(t3 = 1; t3 <= N3; t3++) {
	          for(t2 = 1; t2 <= N2; t2++) {
		y[t2][t3][t1] = y[t2][t3][t1] + twiddle[t2][t3][t1];
		if (t3 >= 1 && N3 >= t3 && t2 >= 1 && N2 >= t2 && t1 >= 1 && N1 >= t1) {
		  y[t2][t3][t1] = x[t2][t3][t1];
		}

	      }
	    }
	  }
	}


}

 __global__ void seq(float (*x)[DIM_N][DIM_N], float (*y)[DIM_N][DIM_N], float (*twiddle)[DIM_N][DIM_N], int N1, int N2, int N3, int DIM_N)
{
	int i,j, k;
	for(i=1; i<=N1; i++)
          for(k=1; k<=N2; k++)
	  for(j=1; j<=N3; j++)

              {
		   y[j][k][i] = y[j][k][i] + twiddle[j][k][i];
		   y[j][k][i] = x[j][k][i];
	      }
}

  	// main routine that executes on the host
int main(int argc, char **argv)
{
  	  float *y_h, *y_d;  // Pointer to host & device arrays
   	  float *y_hs, *y_ds;  // Pointer to host & device arrays
   	  float *x_hs, *x_ds;  // Pointer to host & device arrays

	  float *x_h, *x_d;  // Pointer to host & device arrays
	  float *twiddle_h, *twiddle_d;  // Pointer to host & device arrays

	  struct timeval s1, f1;
	  double  duration;

  	  size_t size =  DIM_N * DIM_N * DIM_N * sizeof(float);
	  int _size = DIM_N * DIM_N * DIM_N;

  	  y_h = (float *)malloc(size);        // Allocate array on host
	  x_h = (float *)malloc(size);        // Allocate array on host
  	  y_hs = (float *)malloc(size);        // Allocate array on host
  	  x_hs = (float *)malloc(size);        // Allocate array on host
	  twiddle_h = (float *)malloc(size);        // Allocate array on host

	  // Initialize host array
  	  for (int i=0; i<_size; i++) x_h[i] = (float)i;

	  cudaMalloc((void **) &y_ds, size);   // Allocate array on device
	  cudaMalloc((void **) &x_ds, size);   // Allocate array on device

	  cudaMemcpy(y_ds, y_h, size, cudaMemcpyHostToDevice);
	  	  cudaMemcpy(x_ds, x_h, size, cudaMemcpyHostToDevice);

	  //  copy it to CUDA device
	  gettimeofday(&s1, NULL);

	  cudaMalloc((void **) &x_d, size);   // Allocate array on device
	  cudaMalloc((void **) &y_d, size);   // Allocate array on device
	  cudaMalloc((void **) &twiddle_d, size);   // Allocate array on device

          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas alloc: %2.6f seconds\n", duration);

	  gettimeofday(&s1, NULL);
  	  cudaMemcpy(x_d, x_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(y_d, y_h, size, cudaMemcpyHostToDevice);
          cudaMemcpy(twiddle_d, twiddle_h, size, cudaMemcpyHostToDevice);

          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas copy: %2.6f seconds\n", duration);


	  // SEQ --------------------
          gettimeofday(&s1, NULL);
          seq<<<1, 1>>>((float(*)[DIM_N][DIM_N])x_ds, (float(*)[DIM_N][DIM_N])y_ds, (float(*)[DIM_N][DIM_N])twiddle_d, N1, N2, N3, DIM_N);
          cudaThreadSynchronize();
          gettimeofday(&f1, NULL);
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas sekw.: %2.6f seconds\n", duration);

  	  cudaMemcpy(y_hs, y_ds, sizeof(float)*size, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(x_hs, x_ds, sizeof(float)*size, cudaMemcpyDeviceToHost);
	  cudaFree(x_ds);
	  
	  //------------------------

	  // PAR --------------------

          int block_size = 1;
  	  int n_blocks = atoi(argv[1]);  // CPU
	  int paczka = (int)ceil(N / n_blocks);
         // printf("\n*** %d \n", paczka);

          gettimeofday(&s1, NULL);
	  par<<< n_blocks, block_size >>> ((float(*)[DIM_N][DIM_N])x_d, (float(*)[DIM_N][DIM_N])y_d, (float(*)[DIM_N][DIM_N])twiddle_d, N1, N2, N3, DIM_N, paczka);
          cudaThreadSynchronize();
          gettimeofday(&f1, NULL);


	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas par: %2.6f seconds\n", duration);

	  //------------------------

  	  // Retrieve result from device and store it in host array
          gettimeofday(&s1, NULL);
          //cudaMemcpy(x_h, x_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
	  cudaMemcpy(y_h, y_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
	  //cudaMemcpy(twiddle_h, twiddle_d, sizeof(float)*N, cudaMemcpyDeviceToHost);
          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas fetch: %2.6f seconds\n", duration);


	  for (int i=0; i<_size ; i++)
	  if (y_hs[i] != y_h[i])
          {
		printf("%i %2.6f %2.6f\n", i, y_hs[i], y_h[i]);
	        printf("blad\n");
		exit(0);
	  }


  	  // Print results
  	  //for (int i=0; i<N; i++) printf("%d %f\n", i, a_h[i]);
  	  // Cleanup
  	  free(x_h); cudaFree(x_d);
	  free(y_h); cudaFree(y_d);
          free(twiddle_h); cudaFree(twiddle_d);
	  free(y_hs);
}
