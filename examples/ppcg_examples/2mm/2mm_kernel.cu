#include "2mm_kernel.hu"
__global__ void kernel0(float *tmp, int DIM2, int NI, int NL, int NJ, int NK)
{
    int b0 = blockIdx.y, b1 = blockIdx.x;
    int t0 = threadIdx.y, t1 = threadIdx.x;

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NI; g1 += 8192)
      for (int g3 = 32 * b1; g3 < NJ; g3 += 8192) {
        if (NI >= t0 + g1 + 1)
          for (int c1 = t1; c1 <= min(31, NJ - g3 - 1); c1 += 16)
            tmp[(t0 + g1) * (DIM2) + g3 + c1] = (0);
        __syncthreads();
      }
}
__global__ void kernel1(float *tmp, int alpha, float *A, float *B, int DIM2, int NI, int NL, int NJ, int NK)
{
    int b0 = blockIdx.y, b1 = blockIdx.x;
    int t0 = threadIdx.y, t1 = threadIdx.x;
    float private_tmp[1][2];
    __shared__ float shared_A[32][32];

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NI; g1 += 8192)
      for (int g3 = 32 * b1; g3 < NJ; g3 += 8192) {
        if (NJ >= t1 + g3 + 1 && NI >= t0 + g1 + 1) {
          private_tmp[0][0] = tmp[(t0 + g1) * (DIM2) + (t1 + g3)];
          if (NJ >= t1 + g3 + 17)
            private_tmp[0][1] = tmp[(t0 + g1) * (DIM2) + (t1 + g3 + 16)];
        }
        for (int g9 = 0; g9 < NK; g9 += 32) {
          if (NI >= t0 + g1 + 1 && DIM2 >= g9 + 1)
            for (int c1 = t1; c1 <= min(DIM2 - g9 - 1, 31); c1 += 16)
              shared_A[t0][c1] = A[(t0 + g1) * (DIM2) + (g9 + c1)];
          __syncthreads();
          if (NJ >= t1 + g3 + 1 && NI >= t0 + g1 + 1)
            for (int c3 = 0; c3 <= min(31, NK - g9 - 1); c3 += 1) {
              private_tmp[0][0] += ((alpha * shared_A[t0][c3]) * B[(g9 + c3) * (DIM2) + t1 + g3]);
              if (NJ >= t1 + g3 + 17)
                private_tmp[0][1] += ((alpha * shared_A[t0][c3]) * B[(g9 + c3) * (DIM2) + t1 + g3 + 16]);
            }
          __syncthreads();
        }
        if (NJ >= t1 + g3 + 1 && NI >= t0 + g1 + 1) {
          tmp[(t0 + g1) * (DIM2) + (t1 + g3)] = private_tmp[0][0];
          if (NJ >= t1 + g3 + 17)
            tmp[(t0 + g1) * (DIM2) + (t1 + g3 + 16)] = private_tmp[0][1];
        }
        __syncthreads();
      }
}
__global__ void kernel2(int beta, float *D, int DIM2, int NI, int NL, int NJ, int NK)
{
    int b0 = blockIdx.y, b1 = blockIdx.x;
    int t0 = threadIdx.y, t1 = threadIdx.x;

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NI; g1 += 8192)
      for (int g3 = 32 * b1; g3 < NL; g3 += 8192) {
        if (NI >= t0 + g1 + 1)
          for (int c1 = t1; c1 <= min(31, NL - g3 - 1); c1 += 16)
            D[(t0 + g1) * (DIM2) + g3 + c1] *= beta;
        __syncthreads();
      }
}
__global__ void kernel3(float *tmp, float *C, float *D, int DIM2, int NI, int NL, int NJ, int NK)
{
    int b0 = blockIdx.y, b1 = blockIdx.x;
    int t0 = threadIdx.y, t1 = threadIdx.x;
    __shared__ float shared_tmp[32][32];
    __shared__ float shared_C[32][32];
    float private_D[1][2];

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NI; g1 += 8192)
      for (int g3 = 32 * b1; g3 < NL; g3 += 8192) {
        if (NL >= t1 + g3 + 1 && NI >= t0 + g1 + 1) {
          private_D[0][0] = D[(t0 + g1) * (DIM2) + (t1 + g3)];
          if (NL >= t1 + g3 + 17)
            private_D[0][1] = D[(t0 + g1) * (DIM2) + (t1 + g3 + 16)];
        }
        for (int g9 = 0; g9 < NJ; g9 += 32) {
          if (DIM2 >= g3 + 1 && NJ >= t0 + g9 + 1)
            for (int c1 = t1; c1 <= min(31, DIM2 - g3 - 1); c1 += 16)
              shared_C[t0][c1] = C[(t0 + g9) * (DIM2) + (g3 + c1)];
          if (NI >= t0 + g1 + 1 && DIM2 >= g9 + 1)
            for (int c1 = t1; c1 <= min(DIM2 - g9 - 1, 31); c1 += 16)
              shared_tmp[t0][c1] = tmp[(t0 + g1) * (DIM2) + (g9 + c1)];
          __syncthreads();
          if (NL >= t1 + g3 + 1 && NI >= t0 + g1 + 1)
            for (int c3 = 0; c3 <= min(31, NJ - g9 - 1); c3 += 1) {
              private_D[0][0] += (shared_tmp[t0][c3] * shared_C[c3][t1]);
              if (NL >= t1 + g3 + 17)
                private_D[0][1] += (shared_tmp[t0][c3] * shared_C[c3][t1 + 16]);
            }
          __syncthreads();
        }
        if (NL >= t1 + g3 + 1 && NI >= t0 + g1 + 1) {
          D[(t0 + g1) * (DIM2) + (t1 + g3)] = private_D[0][0];
          if (NL >= t1 + g3 + 17)
            D[(t0 + g1) * (DIM2) + (t1 + g3 + 16)] = private_D[0][1];
        }
        __syncthreads();
      }
}
