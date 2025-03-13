#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

const long int N = 2048;  // Number of elements in arrays
const long int N1 = N;  // Number of elements in arrays
const long int N2 = N;  // Number of elements in arrays
const long int N3 = 10;  // Number of elements in arrays
const long int N4 = 10;  // Number of elements in arrays

const int DIM_N = N + 2;

// Kernel that executes on the CUDA device
 __global__ void par(float (*tm2)[DIM_N][DIM_N], float (*u)[DIM_N][DIM_N], float (*wdtdr)[DIM_N], int N1, int N2, int N3, int N4, int DIM_N, int paczka)
{
  	  int idx = blockIdx.x;
          int t1, t3, t4, t2;
          int lb = idx*paczka+1;
          int ub =  ((idx+1)*paczka < N1) ? (idx+1)*paczka : N1;


if (N3 >= 1 && N2 >= 2 && N4 >= 1) {
  for(t1 = lb; t1 <= ub; t1++) {
    for(t3 = 1; t3 <= N3; t3++) {
      for(t4 = 1; t4 <= N4; t4++) {
        //s1(t1,1,t3,t4,24);
        tm2[t4][t3][t1] =  tm2[t4][t3][t1] + u[t4][1][t3] * wdtdr[1][t3];
        if (t1 >= 1 && t4 >= 1 && t4 <= N4 && t3 >= 1 && t3 <= N3 && N1 >= t1) {
          for(t2 = 2; t2 <= N2; t2++) {
           // s1(t1,t2,t3,t4,24);
            tm2[t4][t3][t1] =  tm2[t4][t3][t1] + u[t4][t2][t3] * wdtdr[t2][t3];
          }
        }

      }
    }
  }
}


}




 __global__ void seq(float (*tm2)[DIM_N][DIM_N], float (*u)[DIM_N][DIM_N], float (*wdtdr)[DIM_N], int N1, int N2, int N3, int N4, int DIM_N)
{
	int i,j, k, iz;
	for(iz=1; iz<=N1; iz++)
	  for(k=1; k<=N2; k++)
        for(j=1; j<=N3; j++)
		   for(i=1; i<=N4; i++)
           {
			//   tm2[i*DIM_N*DIM_N + j*DIM_N + iz] = 7;
			   //tm2[0] = (float)8;

			   tm2[i][j][iz] =  tm2[i][j][iz] + u[i][k][j] * wdtdr[k][j];
	       }
	  //     tm2[0] = (float)8;
	     //  tm2[1] = (float)8;
}

  	// main routine that executes on the host
int main(int argc, char **argv)
{
  	  float *tm2_h, *tm2_d;  // Pointer to host & device arrays
   	  float *tm2_hs, *tm2_ds;  // Pointer to host & device arrays

	  float *u_h, *u_d;  // Pointer to host & device arrays
	  float *wdtdr_h, *wdtdr_d;  // Pointer to host & device arrays



	  struct timeval s1, f1;
	  double  duration;

  	  size_t size =  DIM_N * DIM_N * N3 *N4 * sizeof(float);
	  int _size = DIM_N * DIM_N * N3 *N4;


  	  tm2_h = (float *)malloc(size);        // Allocate array on host
	  u_h = (float *)malloc(size);        // Allocate array on host
  	  tm2_hs = (float *)malloc(size);        // Allocate array on host
	  wdtdr_h = (float *)malloc(size);        // Allocate array on host

	  // Initialize host array
  	  for (int i=0; i<_size; i++) tm2_h[i] = (float)i;
	  for (int i=0; i<_size; i++) tm2_hs[i] = (float)i;
	  for (int i=0; i<_size; i++) u_h[i] = (float)i;
	  for (int i=0; i<_size; i++) wdtdr_h[i] = (float)i;

	  cudaMalloc((void **) &tm2_ds, size);   // Allocate array on device

	  cudaMemcpy(tm2_ds, tm2_hs, size, cudaMemcpyHostToDevice);

	  //  copy it to CUDA device
	  gettimeofday(&s1, NULL);

	 cudaMalloc((void **) &tm2_d, size);   // Allocate array on device
	 cudaMalloc((void **) &u_d, size);   // Allocate array on device
	 cudaMalloc((void **) &wdtdr_d, size);   // Allocate array on device

         gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas alloc: %2.6f seconds\n", duration);

    gettimeofday(&s1, NULL);
  	  cudaMemcpy(tm2_d, tm2_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(u_d, u_h, size, cudaMemcpyHostToDevice);
          cudaMemcpy(wdtdr_d, wdtdr_h, size, cudaMemcpyHostToDevice);

          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas send: %2.6f seconds\n", duration);


	  // SEQ --------------------
          gettimeofday(&s1, NULL);
//          seq<<<1, 1>>>((float(*)[DIM_N][DIM_N])tm2_ds, (float(*)[DIM_N][DIM_N])u_d, (float(*)[DIM_N])wdtdr_d, N1, N2, N3, N4, DIM_N);
          cudaThreadSynchronize();
          gettimeofday(&f1, NULL);

	  cudaMemcpy(tm2_hs, tm2_ds, sizeof(float)*_size, cudaMemcpyDeviceToHost);
	 // printf("%i %2.6f %2.6f\n", 0, tm2_hs[0], tm2_h[0]);
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas sekw.: %2.6f seconds\n", duration);

	  //exit(0);
	  //------------------------

	  // PAR --------------------

          int block_size = 1;
  	  int n_blocks = atoi(argv[1]);  // CPU
	  int paczka = (int)ceil(N / n_blocks);
         // printf("\n*** %d \n", paczka);

          gettimeofday(&s1, NULL);
		par<<< n_blocks, block_size >>> ((float(*)[DIM_N][DIM_N])tm2_d, (float(*)[DIM_N][DIM_N])u_d, (float(*)[DIM_N])wdtdr_d, N1, N2, N3, N4, DIM_N, paczka);
          cudaThreadSynchronize();
          gettimeofday(&f1, NULL);


	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas par: %2.6f seconds\n", duration);

	  //------------------------

  	  // Retrieve result from device and store it in host array
          gettimeofday(&s1, NULL);
          //cudaMemcpy(x_h, x_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
	  cudaMemcpy(tm2_h, tm2_d, sizeof(float)*_size, cudaMemcpyDeviceToHost);
	  //cudaMemcpy(wdtdr_h, wdtdr_d, sizeof(float)*N, cudaMemcpyDeviceToHost);
          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas fetch: %2.6f seconds\n", duration);


	  for (int i=0; i<_size ; i++)
	  if (tm2_hs[i] != tm2_h[i])
          {
		printf("%i %2.6f %2.6f\n", i, tm2_hs[i], tm2_h[i]);
	        printf("blad\n");
		exit(0);
	  }


  	  // Print results
  	  //for (int i=0; i<N; i++) printf("%d %f\n", i, a_h[i]);
  	  // Cleanup
  	  free(tm2_h); cudaFree(tm2_d);
	  free(u_h); cudaFree(u_d);
          free(wdtdr_h); cudaFree(wdtdr_d);
	  free(tm2_hs); cudaFree(tm2_ds);
}
