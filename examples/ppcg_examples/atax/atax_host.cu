#include <assert.h>
#include "atax_kernel.hu"
#include<sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NY, NX;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int i,j,k, alpha=0;

if (NY >= 1 || NX >= 1)
  {
#define cudaCheckReturn(ret) \
  do { \
    cudaError_t cudaCheckReturn_e = (ret); \
    if (cudaCheckReturn_e != cudaSuccess) { \
      fprintf(stderr, "CUDA error: %s\n", cudaGetErrorString(cudaCheckReturn_e)); \
      fflush(stderr); \
    } \
    assert(cudaCheckReturn_e == cudaSuccess); \
  } while(0)
#define cudaCheckKernel() \
  do { \
    cudaCheckReturn(cudaGetLastError()); \
  } while(0)

    float *dev_y;
    float *dev_A;
    float *dev_tmp;
    float *dev_x;
    
    cudaCheckReturn(cudaMalloc((void **) &dev_y, (NY) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_A, (NX) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_tmp, (NX) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_x, (NY) * sizeof(float)));
    
cudaCheckReturn(cudaMemcpy(dev_A, A, (NX) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_x, x, (NY) * sizeof(float), cudaMemcpyHostToDevice));
    
    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    {
      if (NX >= 1) {
        {
          dim3 k0_dimBlock(32);
          dim3 k0_dimGrid((1048512 - NX >= 0) ? ((NX + 31) / 32) : (-1048513 + NX >= 0 && 1048544 - NX >= 0) ? (32767) : 32768);
          kernel0 <<<k0_dimGrid, k0_dimBlock>>> (dev_tmp, DIM2, NX, NY);
          cudaCheckKernel();
        }
        
        if (NY >= 1)
          {
            dim3 k1_dimBlock(32);
            dim3 k1_dimGrid((1048512 - NX >= 0) ? ((NX + 31) / 32) : (-1048513 + NX >= 0 && 1048544 - NX >= 0) ? (32767) : 32768);
            kernel1 <<<k1_dimGrid, k1_dimBlock>>> (dev_A, dev_tmp, dev_x, DIM2, NX, NY);
            cudaCheckKernel();
          }
          
      }
      if (NY >= 1) {
        {
          dim3 k2_dimBlock(32);
          dim3 k2_dimGrid((1048512 - NY >= 0) ? ((NY + 31) / 32) : (-1048513 + NY >= 0 && 1048544 - NY >= 0) ? (32767) : 32768);
          kernel2 <<<k2_dimGrid, k2_dimBlock>>> (dev_y, DIM2, NX, NY);
          cudaCheckKernel();
        }
        
        if (NX >= 1)
          {
            dim3 k3_dimBlock(32);
            dim3 k3_dimGrid((1048512 - NY >= 0) ? ((NY + 31) / 32) : (-1048513 + NY >= 0 && 1048544 - NY >= 0) ? (32767) : 32768);
            kernel3 <<<k3_dimGrid, k3_dimBlock>>> (dev_y, dev_A, dev_tmp, DIM2, NX, NY);
            cudaCheckKernel();
          }
          
      }
    }
cudaCheckReturn(cudaMemcpy(y, dev_y, (NY) * sizeof(float), cudaMemcpyDeviceToHost));
cudaCheckReturn(cudaMemcpy(tmp, dev_tmp, (NX) * sizeof(float), cudaMemcpyDeviceToHost));
    
cudaCheckReturn(cudaFree(dev_y));
cudaCheckReturn(cudaFree(dev_A));
cudaCheckReturn(cudaFree(dev_tmp));
cudaCheckReturn(cudaFree(dev_x));
  }

}





int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NY = NX = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], *x, *y, *tmp;

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  x = (float (*))malloc(DIM1 * sizeof(float));
  y = (float (*))malloc(DIM1 * sizeof(float));
  tmp = (float (*))malloc(DIM1 * sizeof(float));


  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

    seq(A,y,tmp,x);

  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);
  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









