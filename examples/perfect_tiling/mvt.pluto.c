#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

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
// Filename...........benchmark/mvt.c
// Author.............Cedric Nugteren
// Last modified on...23-May-2012
//

#include "common.h"

// This is 'mvt', a matrix vector product and transpose kernel
int main(void) {
	int i,j;
	
	// Declare arrays on the stack
	float A[NX][NX];
	float x1[NX];
	float x2[NX];
	float y_1[NX];
	float y_2[NX];
	
	// Set the input data
	for (i=0; i<NX; i++) {
		x1[i] = ((float) i) / NX;
		x2[i] = ((float) i + 1) / NX;
		y_1[i] = ((float) i + 3) / NX;
		y_2[i] = ((float) i + 4) / NX;
		for (j=0; j<NX; j++) {
			A[i][j] = ((float) i*j) / NX;
		}
	}
	
	// Perform the computation

	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x1[i] = x1[i] + A[i][j] * y_1[j];
		}
	}
	#pragma endscop





  int t1, t2;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (NX >= 1) {
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=NX-1;t2++) {
      x1[t1]=x1[t1]+A[t1][t2]*y_1[t2];;
      x2[t1]=x2[t1]+A[t2][t1]*y_2[t2];;
    }
  }
}
/* End of CLooG code */

	#pragma scop
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x2[i] = x2[i] + A[j][i] * y_2[j];
		}
	}

	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

