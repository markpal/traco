#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

#define N 512
const int N1 = N;
const int N2 = N;
const int N3 = N;

const int DIM_N = N + 2;


// Kernel that executes on the CUDA device
 __global__ void par(float (*tmp)[DIM_N], float (*tmor)[DIM_N], float (*qbnew)[DIM_N][2], int paczka)
{
  	  int idx = blockIdx.x;
      int t1, t2, t3, i;
      int lb = idx*paczka+1;
      int ub =  ((idx+1)*paczka < N1) ? (idx+1)*paczka : N1;


      if (N2 >= 2 && N3 >= 2) {
      for(t1 = lb; t1 <= ub; t1++){
        for(t2 = 2; t2 <= N2; t2++) {
          tmp[t2][t1] = tmp[t2][t1] + qbnew[t2-1][1][1]*tmor[1][t1];
          if (N2 >= t2 && N1 >= t1 && t2 >= 2 && t1 >= 1) {
            for(t3 = 2; t3 <= N3; t3++) {
              tmp[t2][t1] = tmp[t2][t1] + qbnew[t2-1][t3][1]*tmor[t3][t1];
            }
          }

        }
      }
    }

    for(t1 = lb; t1 <= ub; t1++) {
      i=1;
      if (t1 >= 1 && N1 >= t1) {
        tmp[i][t1]=tmor[i][t1];
     }

   }


}




 __global__ void seq(float (*tmp)[DIM_N], float (*tmor)[DIM_N], float (*qbnew)[DIM_N][2])
{
	int col, i, j;


    for(col = 1; col <= N1; col++){
      i = 1;
      tmp[i][col]=tmor[i][col];
      for(i = 2; i <= N2; i++){
        for(j = 1; j <= N3; j++){
          tmp[i][col] = tmp[i][col] + qbnew[i-1][j][1]*tmor[j][col];
        }
      }
    }


}






int main(int argc, char **argv)
{
  	float *tmp_h, *tmp_d;  // Pointer to host & device arrays
   	float *tmp_hs, *tmp_ds;  // Pointer to host & device arrays

    float *qbnew_h, *qbnew_d;  // Pointer to host & device arrays
    float *tmor_h, *tmor_d;  // Pointer to host & device arrays

	struct timeval s1, f1;
	double  duration;

  	size_t size =  DIM_N * DIM_N * sizeof(float);
	int _size = DIM_N * DIM_N ;

    tmp_h = (float *)malloc(size);        // Allocate array on host
	tmp_hs = (float *)malloc(size);        // Allocate array on host
  	tmor_h = (float *)malloc(size);        // Allocate array on host
  	qbnew_h = (float *)malloc(size*2);        // Allocate array on host

  	for (int i=0; i<_size; i++) tmp_h[i] = (float)i;
	for (int i=0; i<_size; i++) tmp_hs[i] = (float)i;
	for (int i=0; i<_size; i++) tmor_h[i] = (float)i;
	for (int i=0; i<_size; i++) qbnew_h[i] = (float)i;

	cudaMalloc((void **) &tmp_ds, size);   // Allocate array on device

	cudaMemcpy(tmp_ds, tmp_hs, size, cudaMemcpyHostToDevice);

//  copy it to CUDA device
	gettimeofday(&s1, NULL);

	cudaMalloc((void **) &tmp_d, size);
	cudaMalloc((void **) &tmor_d, size);   // Allocate array on device
    cudaMalloc((void **) &qbnew_d, size*2);   // Allocate array on device

    gettimeofday(&f1, NULL);
  	// Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas alloc: %2.6f seconds", duration);

    gettimeofday(&s1, NULL);

  	cudaMemcpy(tmp_d, tmp_h, size, cudaMemcpyHostToDevice);
	cudaMemcpy(tmor_d, tmor_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(qbnew_d, qbnew_h, size*2, cudaMemcpyHostToDevice);

    gettimeofday(&f1, NULL);
  	// Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas send: %2.6f seconds\n", duration);

	gettimeofday(&s1, NULL);
//    seq<<<1, 1>>>((float(*)[DIM_N])tmp_ds, (float(*)[DIM_N])tmor_d, (float(*)[DIM_N][2])qbnew_d);
    cudaThreadSynchronize();
    gettimeofday(&f1, NULL);

    cudaMemcpy(tmp_hs, tmp_ds, size, cudaMemcpyDeviceToHost);

    duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas sekw.: %2.6f seconds\n", duration);

	// PAR --------------------

    int block_size = 1;
  	int n_blocks = atoi(argv[1]);  // CPU
	int paczka = (int)ceil(N1 / n_blocks);


    gettimeofday(&s1, NULL);
	par<<< n_blocks, block_size >>> ((float(*)[DIM_N])tmp_d, (float(*)[DIM_N])tmor_d, (float(*)[DIM_N][2])qbnew_d, paczka);
    cudaThreadSynchronize();
    gettimeofday(&f1, NULL);

    duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas par: %2.6f seconds\n", duration);

	//------------------------
    // Retrieve result from device and store it in host array
    gettimeofday(&s1, NULL);
	cudaMemcpy(tmp_h, tmp_d, size, cudaMemcpyDeviceToHost);
    gettimeofday(&f1, NULL);
  	// Do calculation on device:
	duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	printf("Czas fetch: %2.6f seconds\n", duration);

    for (int i=0; i<_size ; i++)
	  if (tmp_hs[i] != tmp_h[i])
          {
		printf("%i %f %f\n", i, tmp_hs[i], tmp_h[i]);
	        printf("blad\n");
		exit(0);
	  }

	  // Cleanup
  	  free(tmp_h); cudaFree(tmp_d);
	  free(tmp_hs); cudaFree(tmp_ds);
      free(tmor_h); cudaFree(tmor_d);
	  free(qbnew_h); cudaFree(qbnew_d);

    return 0;
}
