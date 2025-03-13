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
// Filename...........benchmark/symm.c
// Author.............Cedric Nugteren
// Last modified on...23-May-2012
//

#include "common.h"
#include "looplib_a.h"


// This is 'symm', a symmetric matrix multiplication kernel
int main(void) {
	int i,j,k;
	float acc[100];
	float bij;

	// Declare arrays on the stack
	float **A = ReserveMemoryandClear(NJ, NJ);
	float **B = ReserveMemoryandClear(NI, NJ);
	float **C = ReserveMemoryandClear(NI, NJ);

	// Set the constants
	float alpha = 32412;
	float beta = 2123;

	// Set the input data
	for (i=0; i<NI; i++) {
		for (j=0; j<NJ; j++) {
			C[i][j] = ((float) i*j) / NI;
			B[i][j] = ((float) i*j) / NI;
		}
	}
	for (i=0; i<NJ; i++) {
		for (j=0; j<NJ; j++) {
			A[i][j] = ((float) i*j) / NI;
		}
	}










  int t1, t2, t3, t4, t5;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((NI >= 1) && (NJ >= 1)) {
  for (t1=0;t1<=min(1,NJ-1);t1++) {
    for (t2=0;t2<=NI-1;t2++) {
      bij=B[t2][t1];;
      acc[t1]=0;;
      C[t2][t1]=beta*C[t2][t1]+alpha*A[t2][t2]*bij+alpha*acc[t1];;
    }
  }
  if (NJ >= 3) {
    for (t2=0;t2<=NI-1;t2++) {
      bij=B[t2][2];;
      C[0][2]+=alpha*A[0][t2]*bij;;
      acc[2]=0;;
      acc[2]+=B[0][2]*A[0][t2];;
      C[t2][2]=beta*C[t2][2]+alpha*A[t2][t2]*bij+alpha*acc[2];;
    }
  }
  for (t1=3;t1<=NJ-1;t1++) {
    for (t2=0;t2<=NI-1;t2++) {
      bij=B[t2][t1];;
      C[0][t1]+=alpha*A[0][t2]*bij;;
      acc[t1]=0;;
      acc[t1]+=B[0][t1]*A[0][t2];;
      for (t3=1;t3<=t1-2;t3++) {
        C[t3][t1]+=alpha*A[t3][t2]*bij;;
        acc[t1]+=B[t3][t1]*A[t3][t2];;
      }
      C[t2][t1]=beta*C[t2][t1]+alpha*A[t2][t2]*bij+alpha*acc[t1];;
    }
  }
}
/* End of CLooG code */

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

