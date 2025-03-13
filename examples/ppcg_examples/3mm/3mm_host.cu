#include <assert.h>
#include "3mm_kernel.hu"
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
int NI, NJ, NL, NM, NK;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {
int i,j,k;

    #pragma scop
	for (i=0; i<NI; i++) {
		for (j=0; j<NJ; j++) {
			E[i][j] = 0;
			for (k=0; k<NK; k++) {
				E[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	#pragma endscop

    #pragma scop
	for (i=0; i<NJ; i++) {
		for (j=0; j<NL; j++) {
			F[i][j] = 0;
			for (k=0; k<NM; k++) {
				F[i][j] += C[i][k] * D[k][j];
			}
		}
	}
	#pragma endscop

if (NL >= 1 && NI >= 1)
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

    float *dev_G;
    float *dev_F;
    float *dev_E;
    
    cudaCheckReturn(cudaMalloc((void **) &dev_G, (NI) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_F, (NJ) * (DIM2) * sizeof(float)));
    cudaCheckReturn(cudaMalloc((void **) &dev_E, (NI) * (DIM2) * sizeof(float)));
    
cudaCheckReturn(cudaMemcpy(dev_G, G, (NI) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_F, F, (NJ) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
cudaCheckReturn(cudaMemcpy(dev_E, E, (NI) * (DIM2) * sizeof(float), cudaMemcpyHostToDevice));
    
    #define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
    {
      dim3 k0_dimBlock(16, 32);
      dim3 k0_dimGrid((8128 - NL >= 0) ? (floord(NL + 31, 32)) : (8160 - NL >= 0 && -8129 + NL >= 0) ? (255) : 256, (8160 - NI >= 0) ? (floord(NI + 31, 32)) : 256);
      kernel0 <<<k0_dimGrid, k0_dimBlock>>> (dev_G, dev_F, dev_E, DIM2, NI, NL, NJ);
      cudaCheckKernel();
    }
    
cudaCheckReturn(cudaMemcpy(G, dev_G, (NI) * (DIM2) * sizeof(float), cudaMemcpyDeviceToHost));
    
cudaCheckReturn(cudaFree(dev_G));
cudaCheckReturn(cudaFree(dev_F));
cudaCheckReturn(cudaFree(dev_E));
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

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*D)[DIM2], (*E)[DIM2], (*F)[DIM2], (*G)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  D = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  E = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  F = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  G = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);


    seq(A,B,C,D,E,F,G);

  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

