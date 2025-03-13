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
 __global__ void par(float (*rho_i)[DIM_N][DIM_N], float (*u)[6][DIM_N][DIM_N], float (*square)[DIM_N][DIM_N], float (*vs)[DIM_N][DIM_N], float (*us)[DIM_N][DIM_N], float (*ws)[DIM_N][DIM_N], float (*qs)[DIM_N][DIM_N], int paczka)
{
      int idx = blockIdx.x;
      int t1,t2,t3;
      int lb = idx*paczka+1;
      int ub =  ((idx+1)*paczka < N1) ? (idx+1)*paczka : N1;
      float rho_inv;

   // lb--; ub--;
   if(lb==1) lb = 0;

    if (N2 >= 0 && N3 >= 0) {
      for(t1 = lb; t1 <= ub; t1++) {
        for(t2 = 0; t2 <= N2; t2++) {
          for(t3 = 0; t3 <= N3; t3++) {
            rho_inv = 1.0/u[1][t3][t2][t1];
         //   if (t1 >= 0 && t3 >= 0 && t2 >= 0 && N3 >= t3 && N1 >= t1 && N2 >= t2) {
              rho_i[t3][t2][t1] = rho_inv;
          //  }
          //  if (t1 >= 0 && t3 >= 0 && t2 >= 0 && N3 >= t3 && N1 >= t1 && N2 >= t2) {
              us[t3][t2][t1] = u[2][t3][t2][t1] * rho_inv;
          //  }
          //  if (t1 >= 0 && t3 >= 0 && t2 >= 0 && N3 >= t3 && N1 >= t1 && N2 >= t2) {
              vs[t3][t2][t1] = u[3][t3][t2][t1] * rho_inv;
          //  }
         //   if (t1 >= 0 && t3 >= 0 && t2 >= 0 && N3 >= t3 && N1 >= t1 && N2 >= t2) {
               ws[t3][t2][t1] = u[4][t3][t2][t1] * rho_inv;
         //   }
         //   if (t1 >= 0 && t3 >= 0 && t2 >= 0 && N3 >= t3 && N1 >= t1 && N2 >= t2) {
               square[t3][t2][t1] = 0.5* ( u[2][t3][t2][t1]*u[2][t3][t2][t1] + u[3][t3][t2][t1]*u[3][t3][t2][t1] + u[4][t3][t2][t1]*u[4][t3][t2][t1] ) * rho_inv;

          //  }
       //     if (t1 >= 0 && t3 >= 0 && t2 >= 0 && N3 >= t3 && N1 >= t1 && N2 >= t2) {
              qs[t3][t2][t1] = square[t3][t2][t1] * rho_inv;
         //   }
          }

          }
        }
      }

}



__global__ void seq(float (*rho_i)[DIM_N][DIM_N], float (*u)[6][DIM_N][DIM_N], float (*square)[DIM_N][DIM_N], float (*vs)[DIM_N][DIM_N], float (*us)[DIM_N][DIM_N], float (*ws)[DIM_N][DIM_N], float (*qs)[DIM_N][DIM_N])
{
	int k, i, j;
	float rho_inv;


    for(k = 0; k <= N1; k++){
      for(j = 0; j <= N2; j++){
        for(i = 0; i <= N3; i++){
          rho_inv = 1.0/u[1][i][j][k];
          rho_i[i][j][k] = rho_inv;
          us[i][j][k] = u[2][i][j][k] * rho_inv;
          vs[i][j][k] = u[3][i][j][k] * rho_inv;
          ws[i][j][k] = u[4][i][j][k] * rho_inv;
          square[i][j][k]     = 0.5* ( u[2][i][j][k]*u[2][i][j][k] + u[3][i][j][k]*u[3][i][j][k] + u[4][i][j][k]*u[4][i][j][k] ) * rho_inv;
          qs[i][j][k] = square[i][j][k] * rho_inv;
        }
      }
    }

}



int main(int argc, char **argv)
{
    float *rho_i_h, *rho_i_d;  // Pointer to host & device arrays
    float *rho_i_hs, *rho_i_ds;  // Pointer to host & device arrays

    float *u_h, *u_d;  // Pointer to host & device arrays

    float *us_h, *us_d;  // Pointer to host & device arrays
    float *us_hs, *us_ds;  // Pointer to host & device arrays

    float *vs_h, *vs_d;  // Pointer to host & device arrays
    float *vs_hs, *vs_ds;  // Pointer to host & device arrays

    float *ws_h, *ws_d;  // Pointer to host & device arrays
    float *ws_hs, *ws_ds;  // Pointer to host & device arrays

    float *qs_h, *qs_d;  // Pointer to host & device arrays
    float *qs_hs, *qs_ds;  // Pointer to host & device arrays

    float *square_h, *square_d;  // Pointer to host & device arrays
    float *square_hs, *square_ds;  // Pointer to host & device arrays


    struct timeval s1, f1;
	double  duration;

  	size_t size =  DIM_N * DIM_N * DIM_N * sizeof(float);
	int _size = DIM_N * DIM_N * DIM_N;

  	rho_i_h = (float *)malloc(size);        // Allocate array on host
  	rho_i_hs = (float *)malloc(size);        // Allocate array on host
  	us_h = (float *)malloc(size);
  	us_hs = (float *)malloc(size);
  	vs_h = (float *)malloc(size);
  	vs_hs = (float *)malloc(size);
  	ws_h = (float *)malloc(size);
  	ws_hs = (float *)malloc(size);
  	qs_h = (float *)malloc(size);
  	qs_hs = (float *)malloc(size);
  	square_h = (float *)malloc(size);
  	square_hs = (float *)malloc(size);

  	u_h = (float *)malloc(size*6);

	// Initialize host array
  	for (int i=0; i<_size*6; i++) u_h[i] = (float)i;
  	for (int i=0; i<_size; i++) qs_h[i] = (float)i;
  	for (int i=0; i<_size; i++) qs_hs[i] = (float)i;

	//  cudaMalloc((void **) &pdiff_ds, size);   // Allocate array on device
	cudaMalloc((void **) &rho_i_ds, size);   // Allocate array on device
	cudaMalloc((void **) &us_ds, size);   // Allocate array on device
    cudaMalloc((void **) &vs_ds, size);   // Allocate array on device
    cudaMalloc((void **) &ws_ds, size);   // Allocate array on device
    cudaMalloc((void **) &qs_ds, size);   // Allocate array on device
    cudaMalloc((void **) &square_ds, size);   // Allocate array on device

    //cudaMemcpy(rms_ds, rms_hs, sizeof(float)*6, cudaMemcpyHostToDevice);
    cudaMemcpy(qs_ds, qs_hs, size, cudaMemcpyHostToDevice);


	//  copy it to CUDA device
	gettimeofday(&s1, NULL);
	cudaMalloc((void **) &rho_i_d, size);   // Allocate array on device
	cudaMalloc((void **) &us_d, size);   // Allocate array on device
    cudaMalloc((void **) &vs_d, size);   // Allocate array on device
    cudaMalloc((void **) &ws_d, size);   // Allocate array on device
    cudaMalloc((void **) &qs_d, size);   // Allocate array on device
    cudaMalloc((void **) &square_d, size);   // Allocate array on device
    cudaMalloc((void **) &u_d, 6*size);   // Allocate array on device
    gettimeofday(&f1, NULL);
  	// Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas alloc: %2.6f seconds", duration);

    cudaMemcpy(qs_d, qs_h, size, cudaMemcpyHostToDevice);
    gettimeofday(&s1, NULL);
  	cudaMemcpy(u_d, u_h, size*6, cudaMemcpyHostToDevice);

	//cudaMemcpy(rhs_d, rhs_h, size, cudaMemcpyHostToDevice);

    gettimeofday(&f1, NULL);
  	 // Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("\nCzas send: %2.6f seconds\n", duration);

      // SEQ --------------------
    gettimeofday(&s1, NULL);
//    seq<<<1, 1>>>((float(*)[DIM_N][DIM_N])rho_i_ds, (float(*)[6][DIM_N][DIM_N])u_d, (float(*)[DIM_N][DIM_N])square_ds, (float(*)[DIM_N][DIM_N])vs_ds, (float(*)[DIM_N][DIM_N])us_ds, (float(*)[DIM_N][DIM_N])ws_ds, (float(*)[DIM_N][DIM_N])qs_ds);
    cudaThreadSynchronize();
    gettimeofday(&f1, NULL);

	// cudaMemcpy(pdiff_hs, pdiff_ds, sizeof(int)*_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(rho_i_hs, rho_i_ds, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(square_hs, square_ds, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(vs_hs, vs_ds, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(us_hs, us_ds, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ws_hs, ws_ds, size, cudaMemcpyDeviceToHost);
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
    par<<< n_blocks, block_size >>> ((float(*)[DIM_N][DIM_N])rho_i_d, (float(*)[6][DIM_N][DIM_N])u_d, (float(*)[DIM_N][DIM_N])square_d, (float(*)[DIM_N][DIM_N])vs_d, (float(*)[DIM_N][DIM_N])us_d, (float(*)[DIM_N][DIM_N])ws_d, (float(*)[DIM_N][DIM_N])qs_d, paczka);
    cudaThreadSynchronize();
    gettimeofday(&f1, NULL);


	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas par: %2.6f seconds\n", duration);

    //------------------------

	//------------------------

  	// Retrieve result from device and store it in host array
    gettimeofday(&s1, NULL);
    //cudaMemcpy(x_h, x_d, sizeof(int)*size, cudaMemcpyDeviceToHost);
	//cudaMemcpy(pdiff_h, pdiff_d, sizeof(int)*_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(rho_i_h, rho_i_d, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(square_h, square_d, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(vs_h, vs_d, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(us_h, us_d, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ws_h, ws_d, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(qs_h, qs_d, size, cudaMemcpyDeviceToHost);


	//cudaMemcpy(wdtdr_h, wdtdr_d, sizeof(int)*N, cudaMemcpyDeviceToHost);
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





