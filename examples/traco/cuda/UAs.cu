#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

const long int N = 1000;  // Number of elements in arrays
const long int N1 = N;  // Number of elements in arrays
const long int N2 = N;  // Number of elements in arrays
const long int N3 = N;  // Number of elements in arrays

const int DIM_N = N + 2;





// Kernel that executes on the CUDA device
 __global__ void par( float (*wdtdr)[DIM_N], float *wxm1, float (*dxm1)[DIM_N], int N1, int N2, int DIM_N, int paczka)
 {



  	int idx = blockIdx.x;
    int t1, t2, t3;
    int lb = idx*paczka+1 ;
    int ub =  ((idx+1)*paczka < N1) ? (idx+1)*paczka : N1;


    if (N2 >= 1 && N3 >= 2) {
      for(t1 = lb; t1 <= ub; t1++) {
        for(t2 = 1; t2 <= N2; t2++) {
          //s1(t1,t2,1,22);
          wdtdr[t1][t2] = wdtdr[t1][t2] + wxm1[1]*dxm1[1][t1]*dxm1[1][t2];
          if (t2 <= N2 && N1 >= t1 && t1 >= 1 && t2 >= 1) {
            for(t3 = 2; t3 <= N3; t3++) {
             // s1(t1,t2,t3,22);
               wdtdr[t1][t2] = wdtdr[t1][t2] + wxm1[t3]*dxm1[t3][t1]*dxm1[t3][t2];
            }
          }

        }
      }
    }




}

 __global__ void seq( float (*wdtdr)[DIM_N], float *wxm1,  float (*dxm1)[DIM_N], int N1, int N2, int N3, int DIM_N)
{
	int i, j, ip;
	for(i=1; i<=N1; i++)
	 for(j=1; j<=N2; j++)
	  for(ip=1; ip<=N3; ip++)
	   wdtdr[i][j] = wdtdr[i][j] + wxm1[ip]*dxm1[ip][i]*dxm1[ip][j];


}




  	// main routine that executes on the host
int main(int argc, char **argv)
{
   	  float *wdtdr_h, *wdtdr_hs, *wdtdr_d;  // Pointer to host & device arrays

	  float *wxm1_h, *wxm1_d;  // Pointer to host & device arrays
	  float *dxm1_h, *dxm1_d;  // Pointer to host & device arrays



	  struct timeval s1, f1;
	  double  duration;


  	  size_t size =  DIM_N * DIM_N * sizeof(float);
	  int _size = DIM_N * DIM_N;

  	  wdtdr_h = (float *)malloc(size);        // Allocate array on host
	  wdtdr_hs = (float *)malloc(size);        // Allocate array on host
  	  wxm1_h = (float *)malloc(size);        // Allocate array on host
	  dxm1_h = (float *)malloc(size);        // Allocate array on host

	  // Initialize host array
  	  for (int i=0; i<_size; i++) wdtdr_h[i] = (float)i;
	  for (int i=0; i<_size; i++) wdtdr_hs[i] = (float)i;
  	  for (int i=0; i<_size; i++) wxm1_h[i] = (float)i;
	  for (int i=0; i<_size; i++) dxm1_h[i] = (float)i;

	  //  copy it to CUDA device
	  gettimeofday(&s1, NULL);

	  cudaMalloc((void **) &wdtdr_d, size);   // Allocate array on device
	  cudaMalloc((void **) &wxm1_d, size);   // Allocate array on device
   	  cudaMalloc((void **) &dxm1_d, size);   // Allocate array on device

          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas alloc: %2.6f seconds\n", duration);

	  gettimeofday(&s1, NULL);

	  cudaMemcpy(wdtdr_d, wdtdr_hs, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(wxm1_d, wxm1_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(dxm1_d, dxm1_h, size, cudaMemcpyHostToDevice);

          gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas copy: %2.6f seconds\n", duration);


	  // SEQ --------------------
          gettimeofday(&s1, NULL);
//          seq<<<1, 1>>>((float(*)[DIM_N])wdtdr_d, wxm1_d, (float(*)[DIM_N])dxm1_d, N1, N2, N3, DIM_N);
          cudaThreadSynchronize();
          gettimeofday(&f1, NULL);
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas sekw.: %2.6f seconds\n", duration);

  	  cudaMemcpy(wdtdr_hs, wdtdr_d, sizeof(float)*_size, cudaMemcpyDeviceToHost);

	  //------------------------

	  // PAR --------------------

      int block_size = 1;
  	  int n_blocks = atoi(argv[1]);  // CPU
	  int paczka = (int)ceil(N / n_blocks);
      // printf("\n*** %d \n", paczka);

	  cudaMemcpy(wdtdr_d, wdtdr_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(wxm1_d, wxm1_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(dxm1_d, dxm1_h, size, cudaMemcpyHostToDevice);

      gettimeofday(&s1, NULL);


      par<<< n_blocks, block_size >>> ((float(*)[DIM_N])wdtdr_d, wxm1_d, (float(*)[DIM_N])dxm1_d, N1, N2, DIM_N, paczka);
      cudaThreadSynchronize();
	  gettimeofday(&f1, NULL);


	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas par: %2.6f seconds\n", duration);

	  //------------------------

  	  // Retrieve result from device and store it in host array
      gettimeofday(&s1, NULL);

  	  cudaMemcpy(wdtdr_h, wdtdr_d, sizeof(float)*_size, cudaMemcpyDeviceToHost);

      gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas fetch: %2.6f seconds\n", duration);


	  for (int i=0; i<_size ; i++)
	  if (wdtdr_hs[i] != wdtdr_h[i])
          {
		printf("y %i %2.6f %2.6f\n", i, wdtdr_hs[i], wdtdr_h[i]);
	        printf("blad\n");
		exit(0);
	  }



  	  // Print results
  	  //for (int i=0; i<N; i++) printf("%d %f\n", i, a_h[i]);
  	  // Cleanup
  	  free(wdtdr_h); cudaFree(wdtdr_d);
	  free(wdtdr_hs);

	  free(wxm1_h); cudaFree(wxm1_d);
	  free(dxm1_h); cudaFree(dxm1_d);
}
