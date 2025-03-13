//
// This file is part of the Bones source-to-source compiler examples. The C-code
// is largely identical in terms of functionality and variable naming to the code
// found in PolyBench/C version 3.2. For more information on PolyBench/C or Bones
// please use the contact information below.
//
// == More information on PolyBench/C
// Contact............Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
// Web address........http://polybench.sourceforge.net/
// 
// == More information on Bones
// Contact............Cedric Nugteren <c.nugteren@tue.nl>
// Web address........http://parse.ele.tue.nl/bones/
//
// == File information
// Filename...........benchmark/seidel-2d.c
// Author.............Cedric Nugteren
// Last modified on...05-April-2012
//

#include "common.h"

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(void) {
	int i,j,t;
	
	// Declare arrays on the stack
	float **A = new float*[N];
	for (i=0; i<N; i++)
	  A[i] = new float[N];
	printf("diff");
	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			A[i][j] = ((float) i*i*(j+2) + 2) / N;
		}
	}
	
	// Perform the computation
	#pragma scop
	double start = omp_get_wtime();
	for (t=0; t<TSTEPS-1; t++) {
		for (i=1; i<=N-2; i++) {
			for (j=1; j<=N-2; j++) {
				A[i][j] = (A[i-1][j-1] + A[i-1][ j ] + A[i-1][j+1] + A[ i ][j-1] + A[ i ][ j ] + A[ i ][j+1] + A[i+1][j-1] + A[i+1][ j ] + A[i+1][j+1])/9.0;
			}
		}
	}
	double end = omp_get_wtime();
	printf("diff = %.16g\n", end - start);

start = omp_get_wtime();

if(1){

  int t1, t2, t3, t4, t5, t6;

 register int lbv, ubv;

/* Start of CLooG code */
if ((N >= 3) && (TSTEPS >= 2)) {
  for (t1=0;t1<=floord(TSTEPS-2,16);t1++) {
    for (t2=t1;t2<=min(floord(TSTEPS+N-4,16),floord(16*t1+N+13,16));t2++) {
      for (t3=max(ceild(32*t2-N-12,16),t1+t2);t3<=min(min(min(min(floord(TSTEPS+N-4,8),floord(16*t1+N+13,8)),floord(32*t2+N+27,16)),floord(16*t1+16*t2+N+28,16)),floord(16*t2+TSTEPS+N+11,16));t3++) {
        for (t4=max(max(max(16*t1,16*t2-N+2),8*t3-N+2),-16*t2+16*t3-N-13);t4<=min(min(min(min(TSTEPS-2,16*t1+15),16*t2+14),8*t3+6),-16*t2+16*t3+14);t4++) {
          for (t5=max(max(16*t2,t4+1),16*t3-t4-N+2);t5<=min(min(16*t2+15,16*t3-t4+14),t4+N-2);t5++) {
            for (t6=max(16*t3,t4+t5+1);t6<=min(16*t3+15,t4+t5+N-2);t6++) {
              A[-t4+t5][-t4-t5+t6]=(A[-t4+t5-1][-t4-t5+t6-1]+A[-t4+t5-1][-t4-t5+t6]+A[-t4+t5-1][-t4-t5+t6+1]+A[-t4+t5][-t4-t5+t6-1]+A[-t4+t5][-t4-t5+t6]+A[-t4+t5][-t4-t5+t6+1]+A[-t4+t5+1][-t4-t5+t6-1]+A[-t4+t5+1][-t4-t5+t6]+A[-t4+t5+1][-t4-t5+t6+1])/9.0;;
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
}else{
for (int c0 = 0; c0 < TSTEPS - 1; c0 += 1)
  for (int c1 = 0; c1 <= floord(N - 3, 32); c1 += 1)
    for (int c2 = 0; c2 <= (N - 3) / 32; c2 += 1)
      for (int c4 = 32 * c1 + 1; c4 <= min(N - 2, 32 * c1 + 32); c4 += 1) {
        for (int c5 = max(32 * c1 + 32 * c2 - c4 + 2, 1); c5 <= min(N - 2, 32 * c1 + 32 * c2 - c4 + 33); c5 += 1)
          A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
        if (32 * c2 + 34 >= N)
          for (int c5 = 32 * c1 + 32 * c2 - c4 + 34; c5 < N - 1; c5 += 1)
            A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
      }
}
end = omp_get_wtime();
	printf("diff = %.16g\n", end - start);

	#pragma endscop
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
