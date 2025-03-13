#include "atax_kernel.hu"
__global__ void kernel0(float *tmp, int DIM2, int NX, int NY)
{
    int b0 = blockIdx.x;
    int t0 = threadIdx.x;

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    for (int g1 = 32 * b0; g1 < NX; g1 += 1048576) {
      if (NX >= t0 + g1 + 1)
        tmp[t0 + g1] = (0);
      __syncthreads();
    }
}
__global__ void kernel1(float *A, float *tmp, float *x, int DIM2, int NX, int NY)
{
    int b0 = blockIdx.x;
    int t0 = threadIdx.x;
    __shared__ float shared_A[32][32];
    float private_tmp[1];
    __shared__ float shared_x[32];

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NX; g1 += 1048576) {
      if (NX >= t0 + g1 + 1)
        private_tmp[0] = tmp[t0 + g1];
      for (int g5 = 0; g5 < NY; g5 += 32) {
        if (NY >= t0 + g5 + 1)
          shared_x[t0] = x[t0 + g5];
        if (DIM2 >= t0 + g5 + 1)
          for (int c0 = 0; c0 <= min(31, NX - g1 - 1); c0 += 1)
            shared_A[c0][t0] = A[(g1 + c0) * (DIM2) + (t0 + g5)];
        __syncthreads();
        if (NX >= t0 + g1 + 1)
          for (int c2 = 0; c2 <= min(31, NY - g5 - 1); c2 += 1)
            private_tmp[0] = (private_tmp[0] + (shared_A[t0][c2] * shared_x[c2]));
        __syncthreads();
      }
      if (NX >= t0 + g1 + 1)
        tmp[t0 + g1] = private_tmp[0];
      __syncthreads();
    }
}
__global__ void kernel2(float *y, int DIM2, int NX, int NY)
{
    int b0 = blockIdx.x;
    int t0 = threadIdx.x;

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    for (int g1 = 32 * b0; g1 < NY; g1 += 1048576) {
      if (NY >= t0 + g1 + 1)
        y[t0 + g1] = (0);
      __syncthreads();
    }
}
__global__ void kernel3(float *y, float *A, float *tmp, int DIM2, int NX, int NY)
{
    int b0 = blockIdx.x;
    int t0 = threadIdx.x;
    float private_y[1];
    __shared__ float shared_tmp[32];

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NY; g1 += 1048576) {
      if (NY >= t0 + g1 + 1)
        private_y[0] = y[t0 + g1];
      for (int g5 = 0; g5 < NX; g5 += 32) {
        if (NX >= t0 + g5 + 1)
          shared_tmp[t0] = tmp[t0 + g5];
        __syncthreads();
        if (NY >= t0 + g1 + 1)
          for (int c2 = 0; c2 <= min(31, NX - g5 - 1); c2 += 1)
            private_y[0] = (private_y[0] + (A[(g5 + c2) * (DIM2) + t0 + g1] * shared_tmp[c2]));
        __syncthreads();
      }
      if (NY >= t0 + g1 + 1)
        y[t0 + g1] = private_y[0];
      __syncthreads();
    }
}
