#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <sys/time.h>

#include "common.h"

// Kernel that executes on the CUDA device
 __global__ void par1(float (*sum_tang)[MAXGRID][MAXGRID], float (*diff)[MAXGRID][MAXGRID][LENGTH], int MAXGRID, int LENGTH,  int paczka)
{
  	  int idx = blockIdx.x;
      int lb = idx*paczka;
      int ub =  ((idx+1)*paczka < MAXGRID-1) ? (idx+1)*paczka : MAXGRID-1;
      int i,j,cnt;
	  float sum;

      for (j=lb; j<=ub; j++) {
			for (i=0; i<=MAXGRID-1; i++) {
				sum = sum_tang[j][i];
				for (cnt=0; cnt<=LENGTH-1; cnt++) {
					diff[j][i][cnt] = sum;
				}
			}
       }


}


 __global__ void par2(float (*mean)[MAXGRID][MAXGRID], float (*sum_diff)[MAXGRID][MAXGRID][LENGTH], float (*diff)[MAXGRID][MAXGRID][LENGTH], int MAXGRID, int LENGTH,  int paczka)
{
  	  int idx = blockIdx.x;
      int lb = idx*paczka;
      int ub =  ((idx+1)*paczka < MAXGRID-1) ? (idx+1)*paczka : MAXGRID-1;
      int i,j,cnt;
	  float sum;

      for (j=lb; j<=ub; j++) {
		for (i=j; i<=MAXGRID-1; i++) {
			sum_diff[j][i][0] = diff[j][i][0];
			for (cnt=1; cnt<=LENGTH-1; cnt++) {
                sum_diff[j][i][cnt] = sum_diff[j][i][cnt-1] + diff[j][i][cnt];
            }
			mean[j][i] = sum_diff[j][i][LENGTH-1];
        }
      }
}


 __global__ void par3(float (*path)[MAXGRID][MAXGRID], float (*mean)[MAXGRID][MAXGRID], int MAXGRID, int paczka)
{
  	  int idx = blockIdx.x;
      int lb = idx*paczka;
      int ub =  ((idx+1)*paczka < MAXGRID-1) ? (idx+1)*paczka : MAXGRID-1;
      int i,j,cnt;
	  float sum;


      for (i=lb; i<=ub; i++) {
			path[0][i] = mean[0][i];
      }

      __synchtreads();

      for (j=lb; j<=ub; j++) {
			for (i=j; i<=MAXGRID-1; i++) {
				path[j][i] = path[j-1][i-1] + mean[j][i];
			}
       }
}




 __global__ void seq(float (*sum_tang)[MAXGRID][MAXGRID], float (*sum_diff)[MAXGRID][MAXGRID][LENGTH], float (*diff)[MAXGRID][MAXGRID][LENGTH], float (*path)[MAXGRID][MAXGRID], float (*mean)[MAXGRID][MAXGRID], int MAXGRID, int LENGTH, int ITER, int paczka)
{

	for (t=0; t<ITER; t++) {
		for (j=0; j<=MAXGRID-1; j++) {
			for (i=0; i<=MAXGRID-1; i++) {
				sum = sum_tang[j][i];
				for (cnt=0; cnt<=LENGTH-1; cnt++) {
					diff[j][i][cnt] = sum;
				}
			}
		}
		for (j=0; j<=MAXGRID-1; j++) {
			for (i=j; i<=MAXGRID-1; i++) {
				sum_diff[j][i][0] = diff[j][i][0];
				for (cnt=1; cnt<=LENGTH-1; cnt++) {
					sum_diff[j][i][cnt] = sum_diff[j][i][cnt-1] + diff[j][i][cnt];
				}
				mean[j][i] = sum_diff[j][i][LENGTH-1];
			}
		}

		for (i=0; i<=MAXGRID-1; i++) {
			path[0][i] = mean[0][i];
		}

		for (j=1; j<=MAXGRID-1; j++) {
			for (i=j; i<=MAXGRID-1; i++) {
				path[j][i] = path[j-1][i-1] + mean[j][i];
			}
		}
	}
}

  	// main routine that executes on the host
int main(int argc, char **argv)
{
  	  float *sum_tang_h, *sum_tang_d;  // Pointer to host & device arrays
  	  float *sum_diff_h, *sum_diff_d;  // Pointer to host & device arrays
  	  float *sum_diff_hs, *sum_diff_ds;  // Pointer to host & device arrays
      float *diff_h, *diff_d;  // Pointer to host & device arrays
  	  float *diff_hs, *diff_ds;  // Pointer to host & device arrays
  	  float *mean_h, *mean_d;  // Pointer to host & device arrays
   	  float *mean_hs, *mean_ds;  // Pointer to host & device arrays
   	  float *path_h, *path_d;  // Pointer to host & device arrays
   	  float *path_hs, *path_ds;  // Pointer to host & device arrays

	  struct timeval s1, f1;
	  double  duration;

  	  size_t size =  MAXGRID * MAXGRID * LENGTH * sizeof(float);
	  int _size = MAXGRID * MAXGRID * LENGTH;

  	  size_t size2 =  MAXGRID * LENGTH * sizeof(float);
	  int _size2 = MAXGRID * LENGTH;

  	  sum_tang_h = (float *)malloc(size2);        // Allocate array on host
	  sum_diff_h = (float *)malloc(size);        // Allocate array on host
  	  sum_diff_hs = (float *)malloc(size);        // Allocate array on host
  	  diff_h = (float *)malloc(size);        // Allocate array on host
  	  diff_hs = (float *)malloc(size);        // Allocate array on host
  	  mean_h = (float *)malloc(size2);        // Allocate array on host
  	  mean_hs = (float *)malloc(size2);        // Allocate array on host
      path_h = (float *)malloc(size2);        // Allocate array on host
  	  path_hs = (float *)malloc(size2);        // Allocate array on host

      // Set the input data
        for (i=0; i<MAXGRID; i++) {
            for (j=0; j<MAXGRID; j++) {
                sum_tang_h[i][j] = (float)((i+1)*(j+1));
                mean_h[i][j] = ((float) i-j) / MAXGRID;
                path_h[i][j] = ((float) i*(j-1)) / MAXGRID;
            }
        }

	  cudaMalloc((void **) &sum_diff_ds, size);   // Allocate array on device
	  cudaMalloc((void **) &diff_ds, size);   // Allocate array on device
	  cudaMalloc((void **) &mean_ds, size2);   // Allocate array on device
	  cudaMalloc((void **) &path_ds, size2);   // Allocate array on device

	  cudaMemcpy(sum_diff_ds, sum_diff_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(diff_ds, diff_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(mean_ds, mean_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(path_ds, path_h, size, cudaMemcpyHostToDevice);

	  //  copy it to CUDA device
	  gettimeofday(&s1, NULL);

	  cudaMalloc((void **) &sum_diff_d, size);   // Allocate array on device
	  cudaMalloc((void **) &sum_tang_d, size2);   // Allocate array on device
	  cudaMalloc((void **) &diff_d, size);   // Allocate array on device
	  cudaMalloc((void **) &mean_d, size2);   // Allocate array on device
	  cudaMalloc((void **) &path_d, size2);   // Allocate array on device

      gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas alloc: %2.6f seconds\n", duration);

	  gettimeofday(&s1, NULL);
  	  cudaMemcpy(sum_tang_d, sum_tang_h, size, cudaMemcpyHostToDevice);
	  cudaMemcpy(mean_d, mean_h, size2, cudaMemcpyHostToDevice);
      cudaMemcpy(path_d, path_h, size2, cudaMemcpyHostToDevice);

      gettimeofday(&f1, NULL);
  	  // Do calculation on device:
	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas copy: %2.6f seconds\n", duration);


	  // SEQ --------------------
      gettimeofday(&s1, NULL);
      seq<<<1, 1>>>((float(*)[MAXGRID][MAXGRID])sum_tang_d, (float(*)[MAXGRID][MAXGRID][LENGTH])sum_diff_ds, (float(*)[MAXGRID][MAXGRID][LENGTH])diff_ds, (float(*)[MAXGRID][MAXGRID])path_ds,  (float(*)[MAXGRID][MAXGRID])mean_ds, MAXGRID, LENGTH, ITER, paczka)
      cudaThreadSynchronize();
      gettimeofday(&f1, NULL);

	  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
	  printf("Czas sekw.: %2.6f seconds\n", duration);

  	  cudaMemcpy(diff_hs, diff_ds, sizeof(float)*size, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(sum_diff_hs, sum_diff_ds, sizeof(float)*size, cudaMemcpyDeviceToHost);
      cudaMemcpy(mean_hs, mean_ds, sizeof(float)*size2, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(mean_hs, mean_ds, sizeof(float)*size2, cudaMemcpyDeviceToHost);
	  cudaFree(diff_ds);
	  cudaFree(sum_diff_ds);
	  cudaFree(mean_ds);
	  cudaFree(path_ds);

	  //------------------------

	  // PAR --------------------

      int block_size = 1;
  	  int n_blocks = atoi(argv[1]);  // CPU
	  int paczka = (int)ceil(N / n_blocks);
         // printf("\n*** %d \n", paczka);

      gettimeofday(&s1, NULL);
	  for (t=0; t<ITER; t++) {
        par1<<< n_blocks, block_size >>> ((float(*)[MAXGRID][MAXGRID])sum_tang_d, (float(*)[MAXGRID][MAXGRID][LENGTH])diff_d, MAXGRID, LENGTH, paczka);
        cudaThreadSynchronize();
        par2<<< n_blocks, block_size >>> ((float(*)[MAXGRID][MAXGRID])mean_d, (float(*)[MAXGRID][MAXGRID][LENGTH])sum_diff_d, (float(*)[MAXGRID][MAXGRID][LENGTH])diff_d, MAXGRID, LENGTH, paczka);
        cudaThreadSynchronize();
        par3<<< n_blocks, block_size >>> ((float(*)[MAXGRID][MAXGRID])path_d, (float(*)[MAXGRID][MAXGRID])mean_d, MAXGRID, paczka);
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
      cudaMemcpy(diff_h, diff_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(sum_diff_h, sum_diff_d, sizeof(float)*size, cudaMemcpyDeviceToHost);
      cudaMemcpy(mean_h, mean_d, sizeof(float)*size2, cudaMemcpyDeviceToHost);
  	  cudaMemcpy(mean_h, mean_d, sizeof(float)*size2, cudaMemcpyDeviceToHost);
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
      cudaFree(diff_d);
      cudaFree(sum_tang_d);
	  cudaFree(sum_diff_d);
	  cudaFree(mean_d);
	  cudaFree(path_d);

      free(diff_h);
      free(sum_tang_h);
	  free(sum_diff_h);
	  free(mean_h);
	  free(path_h);

}
