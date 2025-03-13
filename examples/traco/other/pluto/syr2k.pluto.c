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
// Filename...........benchmark/syr2k.c
// Author.............Cedric Nugteren
// Last modified on...03-April-2012
//

#include "common.h"
#include "looplib_a.h"


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





  int t1, t2, t3, t4, t5;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (NI >= 1) {
  lbp=0;
  ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NI-1;t3++) {
      C[t2][t3]*=beta;;
    }
  }
  if (NJ >= 1) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=0;t3<=NI-1;t3++) {
        for (t4=0;t4<=NJ-1;t4++) {
          C[t2][t3]+=alpha*A[t2][t4]*B[t3][t4];;
          C[t2][t3]+=alpha*B[t2][t4]*A[t3][t4];;
        }
      }
    }
  }
}
/* End of CLooG code */

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
