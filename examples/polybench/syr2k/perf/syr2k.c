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
// Filename...........benchmark/syr2k.c
// Author.............Cedric Nugteren
// Last modified on...03-April-2012
//

#include "common.h"

// This is 'syr2k', an algorithm for symmetric rank-2k operations
int main(void) {
	int i,j,k;
	
	// Declare arrays on the stack
//	float A[NI][NJ];
	//float B[NI][NJ];
	//float C[NI][NI];
	float **A = new float*[NI];
	float **B = new float*[NI];
	float **C = new float*[NI];
	for (i=0; i<NI; i++)
	  A[i] = new float[NI];
	for (i=0; i<NI; i++)
	  B[i] = new float[NI];
	for (i=0; i<NI; i++)
	  C[i] = new float[NI];

	
	// Set the constants
	int alpha = 32412;
	int beta = 2123;
	
	// Set the input data
	for (i=0; i<NI; i++) {
		for (j=0; j<NJ; j++) {
			A[i][j] = ((float) i*j) / NI;
			B[i][j] = ((float) i*j) / NI;
		}
	}
	for (i=0; i<NI; i++) {
		for (j=0; j<NI; j++) {
			C[i][j] = ((float) i*j) / NI;
		}
	}
	
	// Perform the computation (C := alpha*A*B' + alpha*B*A' + beta*C)
	/*for (i=0; i<NI; i++) {
		for (j=0; j<NI; j++) {
			C[i][j] *= beta;
			for (k=0; k<NJ; k++) {
				C[i][j] += alpha * A[i][k] * B[j][k];
				C[i][j] += alpha * B[i][k] * A[j][k];
			}
		}
	}
*/
double start = omp_get_wtime();
//	if(0){
  for (i = 0; i < NI; i++)
    for (j = 0; j < NI; j++)
      C[i][j] *= beta;
  for (i = 0; i < NI; i++)
    for (j = 0; j < NI; j++)
      for (k = 0; k < NJ; k++)
	{
	  C[i][j] += alpha * A[i][k] * B[j][k];
	  C[i][j] += alpha * B[i][k] * A[j][k];
	}


	double end = omp_get_wtime();
	printf("diff = %.16g\n", end - start);
start = omp_get_wtime();
int c0,c1,c2,c3,c4,c5;
for (int c0 = 0; c0 <= floord(NI - 1, 16); c0 += 1)
  for (int c1 = 0; c1 <= (NI - 1) / 16; c1 += 1)
    for (int c2 = 16 * c0; c2 <= min(NI - 1, 16 * c0 + 15); c2 += 1)
      for (int c3 = 16 * c1; c3 <= min(16 * c1 + 15, NI - 1); c3 += 1)
        C[c2][c3]*=beta;


for (int c0 = 0; c0 <= floord(NI - 1, 16); c0 += 1)
  for (int c1 = 0; c1 <= (NI - 1) / 16; c1 += 1)
    for (int c2 = 0; c2 <= floord(NJ - 1, 16); c2 += 1)
      for (int c3 = 16 * c0; c3 <= min(NI - 1, 16 * c0 + 15); c3 += 1)
        for (int c4 = 16 * c1; c4 <= min(16 * c1 + 15, NI - 1); c4 += 1)
          for (int c5 = 16 * c2; c5 <= min(16 * c2 + 15, NJ - 1); c5 += 1) {
            C[c3][c4]+=alpha*A[c3][c5]*B[c4][c5];
            C[c3][c4]+=alpha*B[c3][c5]*A[c4][c5];
          }

          






	end = omp_get_wtime();
	printf("diff = %.16g\n", end - start);
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
