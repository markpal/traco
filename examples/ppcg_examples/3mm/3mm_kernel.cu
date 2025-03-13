#include "3mm_kernel.hu"
__global__ void kernel0(float *G, float *F, float *E, int DIM2, int NI, int NL, int NJ)
{
    int b0 = blockIdx.y, b1 = blockIdx.x;
    int t0 = threadIdx.y, t1 = threadIdx.x;
    float private_G[1][2];
    __shared__ float shared_F[32][32];

    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    #define min(x,y)    ((x) < (y) ? (x) : (y))
    for (int g1 = 32 * b0; g1 < NI; g1 += 8192)
      for (int g3 = 32 * b1; g3 < NL; g3 += 8192) {
        if (NJ >= 1)
          if (NL >= t1 + g3 + 1 && NI >= t0 + g1 + 1) {
            private_G[0][0] = G[(t0 + g1) * (DIM2) + (t1 + g3)];
            if (NL >= t1 + g3 + 17)
              private_G[0][1] = G[(t0 + g1) * (DIM2) + (t1 + g3 + 16)];
          }
        for (int g9 = 0; g9 <= (NJ >= 1 ? NJ - 1 : 0); g9 += 32) {
          if (NJ >= g9 + 1)
            if (DIM2 >= g3 + 1 && NJ >= t0 + g9 + 1)
              for (int c1 = t1; c1 <= min(31, DIM2 - g3 - 1); c1 += 16)
                shared_F[t0][c1] = F[(t0 + g9) * (DIM2) + (g3 + c1)];
          __syncthreads();
          if (g9 == 0 && NI >= t0 + g1 + 1 && NL >= t1 + g3 + 1) {
            private_G[0][0] = (0);
            if (NL >= t1 + g3 + 17)
              private_G[0][1] = (0);
          }
          if (NI >= t0 + g1 + 1 && NL >= t1 + g3 + 1)
            for (int c3 = 0; c3 <= min(31, NJ - g9 - 1); c3 += 1) {
              private_G[0][0] += (E[(t0 + g1) * (DIM2) + g9 + c3] * shared_F[c3][t1]);
              if (NL >= t1 + g3 + 17)
                private_G[0][1] += (E[(t0 + g1) * (DIM2) + g9 + c3] * shared_F[c3][t1 + 16]);
            }
          __syncthreads();
        }
        if (NL >= t1 + g3 + 1 && NI >= t0 + g1 + 1) {
          G[(t0 + g1) * (DIM2) + (t1 + g3)] = private_G[0][0];
          if (NL >= t1 + g3 + 17)
            G[(t0 + g1) * (DIM2) + (t1 + g3 + 16)] = private_G[0][1];
        }
        __syncthreads();
      }
}
