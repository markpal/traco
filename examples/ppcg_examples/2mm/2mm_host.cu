#include <assert.h>
#include "2mm_kernel.hu"
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include<sys/time.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;

if ((NJ >= 1 && NI >= 1) || (NL >= 1 && NI >= 1))
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

    float *dev_tmp;
    float *dev_A;
    float *dev_C;
    float *dev_B;
    float *dev_D;
    
    cudaCheckReturn(cudaMalloc((void **) &dev_tmp, (NI) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_A, (NI) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_C, (NJ) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_B, (NK) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_D, (NI) * (DIM2) * sizeof(float)));
    
cudaCheckReturn(cudaMemcpy(dev_tmp, tmp, (NI) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_A, A, (NI) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_C, C, (NJ) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_B, B, (NK) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_D, D, (NI) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
    
    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    {
      if (NJ >= 1) {
        {
          dim3 k0_dimBlock(16, 32);
          dim3 k0_dimGrid((8128 - NJ >= 0) ? ((NJ + 31) / 32) : (-8129 + NJ >= 0 && 8160 - NJ >= 0) ? (255) : 256, (8128 - NI >= 0) ? ((NI + 31) / 32) : (-8129 + NI >= 0 && 8160 - NI >= 0) ? (255) : 256);
          kernel0 <<<k0_dimGrid, k0_dimBlock>>> (dev_tmp, DIM2, NI, NL, NJ, NK);
          cudaCheckKernel();
        }
        
        if (NK >= 1)
          {
            dim3 k1_dimBlock(16, 32);
            dim3 k1_dimGrid((8128 - NJ >= 0) ? ((NJ + 31) / 32) : (-8129 + NJ >= 0 && 8160 - NJ >= 0) ? (255) : 256, (8128 - NI >= 0) ? ((NI + 31) / 32) : (-8129 + NI >= 0 && 8160 - NI >= 0) ? (255) : 256);
            kernel1 <<<k1_dimGrid, k1_dimBlock>>> (dev_tmp, alpha, dev_A, dev_B, DIM2, NI, NL, NJ, NK);
            cudaCheckKernel();
          }
          
      }
      if (NL >= 1) {
        {
          dim3 k2_dimBlock(16, 32);
          dim3 k2_dimGrid((8128 - NL >= 0) ? ((NL + 31) / 32) : (-8129 + NL >= 0 && 8160 - NL >= 0) ? (255) : 256, (8128 - NI >= 0) ? ((NI + 31) / 32) : (-8129 + NI >= 0 && 8160 - NI >= 0) ? (255) : 256);
          kernel2 <<<k2_dimGrid, k2_dimBlock>>> (beta, dev_D, DIM2, NI, NL, NJ, NK);
          cudaCheckKernel();
        }
        
        if (NJ >= 1)
          {
            dim3 k3_dimBlock(16, 32);
            dim3 k3_dimGrid((8128 - NL >= 0) ? ((NL + 31) / 32) : (-8129 + NL >= 0 && 8160 - NL >= 0) ? (255) : 256, (8128 - NI >= 0) ? ((NI + 31) / 32) : (-8129 + NI >= 0 && 8160 - NI >= 0) ? (255) : 256);
            kernel3 <<<k3_dimGrid, k3_dimBlock>>> (dev_tmp, dev_C, dev_D, DIM2, NI, NL, NJ, NK);
            cudaCheckKernel();
          }
          
      }
    }
cudaCheckReturn(cudaMemcpy(tmp, dev_tmp, (NI) * (DIM2) * sizeof(float), cudaMemcpyDeviceToHost));
cudaCheckReturn(cudaMemcpy(D, dev_D, (NI) * (DIM2) * sizeof(float), cudaMemcpyDeviceToHost));
    
cudaCheckReturn(cudaFree(dev_tmp));
cudaCheckReturn(cudaFree(dev_A));
cudaCheckReturn(cudaFree(dev_C));
cudaCheckReturn(cudaFree(dev_B));
cudaCheckReturn(cudaFree(dev_D));
  }

}




int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*D)[DIM2], (*tmp)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  D = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  tmp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

    seq(A,B,C,D,tmp);


  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);


  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









