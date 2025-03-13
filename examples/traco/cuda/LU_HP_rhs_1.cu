#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

#define N 256

const long int N1 = N;  // Number of elements in arrays
const long int N2 = N;  // Number of elements in arrays
const long int N3 = N;  // Number of elements in arrays

const int DIM_N = N + 2;


// Kernel that executes on the CUDA device
 __global__ void par(float (*rho_i)[DIM_N][DIM_N], float (*u)[6][DIM_N][DIM_N], float (*rsd)[6][DIM_N][DIM_N], float (*frct)[6][DIM_N][DIM_N], float (*qs)[DIM_N][DIM_N], int paczka)
{
      int idx = blockIdx.x;
      int k, m, i, j;
      float tmp;
      int lb = idx*paczka+1;
      int ub =  ((idx+1)*paczka < N1) ? (idx+1)*paczka : N1;


   for(k = lb; k <= ub; k += 1)
      for(j = 1; j <= N2; j += 1)
         for(i = 1; i <= N3; i += 1) {
            for(m = 1; m <= 5; m += 1)
               rsd[m][i][j][k] = -frct[m][i][j][k];
            tmp = 1.0/u[1][i][j][k];
            rho_i[i][j][k] = tmp;
            qs[i][j][k] = 0.5*(u[2][i][j][k]*u[2][i][j][k]+u[3][i][j][k]*u[3][i][j][k]+u[4][i][j][k]*u[4][i][j][k])*tmp;
         }

}



__global__ void seq(float (*rho_i)[DIM_N][DIM_N], float (*u)[6][DIM_N][DIM_N], float (*rsd)[6][DIM_N][DIM_N], float (*frct)[6][DIM_N][DIM_N], float (*qs)[DIM_N][DIM_N])
{
	int k, i, j, m;
	float tmp;


   for(k = 1; k <= N1; k += 1)
      for(j = 1; j <= N2; j += 1)
         for(i = 1; i <= N3; i += 1) {
            for(m = 1; m <= 5; m += 1)
               rsd[m][i][j][k] = -frct[m][i][j][k];
            tmp = 1.0/u[1][i][j][k];
            rho_i[i][j][k] = tmp;
            qs[i][j][k] = 0.5*(u[2][i][j][k]*u[2][i][j][k]+u[3][i][j][k]*u[3][i][j][k]+u[4][i][j][k]*u[4][i][j][k])*tmp;
         }

}



int main(int argc, char **argv)
{
    float *rho_i_h, *rho_i_d;  // Pointer to host & device arrays
    float *rho_i_hs, *rho_i_ds;  // Pointer to host & device arrays

    float *u_h, *u_d;  // Pointer to host & device arrays

    float *rsd_h, *rsd_d;  // Pointer to host & device arrays
    float *rsd_hs, *rsd_ds;  // Pointer to host & device arrays

    float *frct_h, *frct_d;  // Pointer to host & device arrays

    float *qs_h, *qs_d;  // Pointer to host & device arrays
    float *qs_hs, *qs_ds;  // Pointer to host & device arrays



    struct timeval s1, f1;
	double  duration;

  	size_t size =  DIM_N * DIM_N * DIM_N * sizeof(float);
	int _size = DIM_N * DIM_N * DIM_N;

  	rho_i_h = (float *)malloc(size);        // Allocate array on host
  	rho_i_hs = (float *)malloc(size);        // Allocate array on host
  	qs_h = (float *)malloc(size);
  	qs_hs = (float *)malloc(size);

  	u_h = (float *)malloc(size*6);
  	rsd_h = (float *)malloc(size*6);
  	rsd_hs = (float *)malloc(size*6);
  	frct_h = (float *)malloc(size*6);

	// Initialize host array
  	for (int i=0; i<_size*6; i++) u_h[i] = (float)i;
  	for (int i=0; i<_size*6; i++) frct_h[i] = (float)i;
  	for (int i=0; i<_size*6; i++) rsd_h[i] = (float)i;
  	for (int i=0; i<_size*6; i++) rsd_hs[i] = (float)i;
  	for (int i=0; i<_size; i++) qs_h[i] = (float)i;
  	for (int i=0; i<_size; i++) qs_hs[i] = (float)i;

	//  cudaMalloc((void **) &pdiff_ds, size);   // Allocate array on device
	cudaMalloc((void **) &rho_i_ds, size);   // Allocate array on device
	cudaMalloc((void **) &rsd_ds, size*6);   // Allocate array on device
    cudaMalloc((void **) &qs_ds, size);   // Allocate array on device


    //cudaMemcpy(rms_ds, rms_hs, sizeof(float)*6, cudaMemcpyHostToDevice);
    //cudaMemcpy(qs_ds, qs_hs, size, cudaMemcpyHostToDevice);


	//  copy it to CUDA device
	gettimeofday(&s1, NULL);
	cudaMalloc((void **) &rho_i_d, size);   // Allocate array on device
    cudaMalloc((void **) &qs_d, size);   // Allocate array on device
    cudaMalloc((void **) &u_d, 6*size);   // Allocate array on device
    cudaMalloc((void **) &frct_d, 6*size);   // Allocate array on device
    cudaMalloc((void **) &rsd_d, 6*size);   // Allocate array on device
    gettimeofday(&f1, NULL);
  	// Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas alloc: %2.6f seconds", duration);


    gettimeofday(&s1, NULL);
  	cudaMemcpy(u_d, u_h, size*6, cudaMemcpyHostToDevice);
  	cudaMemcpy(frct_d, frct_h, size*6, cudaMemcpyHostToDevice);
    gettimeofday(&f1, NULL);

  	 // Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("\nCzas send: %2.6f seconds\n", duration);

      // SEQ --------------------
    gettimeofday(&s1, NULL);
    seq<<<1, 1>>>((float(*)[DIM_N][DIM_N])rho_i_ds, (float(*)[6][DIM_N][DIM_N])u_d, (float(*)[6][DIM_N][DIM_N])rsd_ds, (float(*)[6][DIM_N][DIM_N])frct_d, (float(*)[DIM_N][DIM_N])qs_ds);
    cudaThreadSynchronize();
    gettimeofday(&f1, NULL);

	// cudaMemcpy(pdiff_hs, pdiff_ds, sizeof(int)*_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(rho_i_hs, rho_i_ds, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(rsd_hs, rsd_ds, size*6, cudaMemcpyDeviceToHost);
	cudaMemcpy(qs_hs, qs_ds, size, cudaMemcpyDeviceToHost);


	// printf("%i %2.6f %2.6f\n", 0, tm2_hs[0], tm2_h[0]);
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas sekw.: %2.6f seconds\n", duration);

	//------------------------

	// PAR --------------------

    int block_size = 1;
  	int n_blocks = atoi(argv[1]);  // CPU
	int paczka = (int)ceil(N1 / n_blocks);
printf("%i", paczka);

    gettimeofday(&s1, NULL);
    par<<< n_blocks, block_size >>> ((float(*)[DIM_N][DIM_N])rho_i_d, (float(*)[6][DIM_N][DIM_N])u_d, (float(*)[6][DIM_N][DIM_N])rsd_d, (float(*)[6][DIM_N][DIM_N])frct_d, (float(*)[DIM_N][DIM_N])qs_d, paczka);
    cudaThreadSynchronize();
    gettimeofday(&f1, NULL);


	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas par: %2.6f seconds\n", duration);

    //------------------------

	//------------------------

  	// Retrieve result from device and store it in host array
    gettimeofday(&s1, NULL);
	cudaMemcpy(rho_i_h, rho_i_d, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(rsd_h, rsd_d, size*6, cudaMemcpyDeviceToHost);
	cudaMemcpy(qs_h, qs_d, size, cudaMemcpyDeviceToHost);
	gettimeofday(&f1, NULL);
  	// Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas fetch: %2.6f seconds\n", duration);


	for (int i=0; i<_size ; i++)
          if (qs_hs[i] != qs_h[i])
          {
            printf("%i %f %f\n", i, qs_hs[i], qs_h[i]);
            printf("blad\n");
            exit(0);
          }

    return 0;
}





