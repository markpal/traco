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

#include "/home/marek/issf/examples/traco/other/cetus/common.h"
#include "/home/marek/issf/examples/traco/other/cetus/looplib_a.h"


// This is 'syr2k', an algorithm for symmetric rank-2k operations
int main(void) {
	int i,j,k;

	// Declare arrays on the stack
	float **A = ReserveMemoryandClear(NI, NJ);
	float **B = ReserveMemoryandClear(NI, NJ);
	float **C = ReserveMemoryandClear(NI, NI);

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

	for (i=0; i<NI; i++) {
		for (j=0; j<NI; j++) {
			C[i][j] *= beta;
			for (k=0; k<NJ; k++) {
				C[i][j] += alpha * A[i][k] * B[j][k];
				C[i][j] += alpha * B[i][k] * A[j][k];
			}
		}
	}


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
