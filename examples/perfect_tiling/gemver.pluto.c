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
// Filename...........benchmark/gemver.c
// Author.............Cedric Nugteren
// Last modified on...04-April-2012
//

#include "common.h"

// This is 'gemver', a general matrix vector multiplication and matrix addition kernel
int main(void) {
	int i,j;
	
	// Declare arrays on the stack
	float A[NX][NX];
	float u1[NX];
	float u2[NX];
	float v1[NX];
	float v2[NX];
	float w[NX];
	float x[NX];
	float y[NX];
	float z[NX];
	
	// Set the constants
	int alpha = 43532;
	int beta = 12313;
	
	// Set the input data
	for (i=0; i<NX; i++) {
		u1[i] = i;
		u2[i] = (i+1)/NX/2.0;
		v1[i] = (i+1)/NX/4.0;
		v2[i] = (i+1)/NX/6.0;
		w[i] = 0.0;
		x[i] = 0.0;
		y[i] = (i+1)/NX/8.0;
		z[i] = (i+1)/NX/9.0;
		for (j=0; j<NX; j++) {
			A[i][j] = ((float) i*j) / NX;
		}
	}
	
	// Perform the computation
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];
		}
	}
	#pragma endscop

	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x[i] = x[i] + beta * A[j][i] * y[j];
		}
	}
	#pragma endscop

	for (i=0; i<NX; i++) {
		x[i] = x[i] + z[i];
	}
	#pragma endscop







  int t1, t2, t3, t4;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (NX >= 1) {
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NX-1;t3++) {
      A[t3][t2]=A[t3][t2]+u1[t3]*v1[t2]+u2[t3]*v2[t2];;
      x[t2]=x[t2]+beta*A[t3][t2]*y[t3];;
    }
  }
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    x[t2]=x[t2]+z[t2];;
  }
  lbp=0;
  ubp=NX-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NX-1;t3++) {
      w[t2]=w[t2]+alpha*A[t2][t3]*x[t3];;
    }
  }
}
/* End of CLooG code */

	#pragma scop
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x[i] = x[i] + beta * A[j][i] * y[j];
		}
	}

	#pragma scop
	for (i=0; i<NX; i++) {
		x[i] = x[i] + z[i];
	}

	#pragma scop
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			w[i] = w[i] +  alpha * A[i][j] * x[j];
		}
	}

	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

