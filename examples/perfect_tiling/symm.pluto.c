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

// This is 'symm', a symmetric matrix multiplication kernel
int main(void) {
	int i,j,k;
	float acc[1];
	float bij;
	
	// Declare arrays on the stack
	float A[NJ][NJ];
	float B[NI][NJ];
	float C[NI][NJ];
	
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
	
	// Perform the computation (C := alpha*A*B + beta*C, with A symmetric)






  int t1, t2, t3, t4, t5;

 register int lbv, ubv;

/* Start of CLooG code */
if ((NI >= 1) && (NJ >= 1)) {
  if (NJ >= 4) {
    for (t1=0;t1<=NI-1;t1++) {
      for (t2=0;t2<=1;t2++) {
        bij=B[t1][t2];;
        acc[0]=0;;
        C[t1][t2]=beta*C[t1][t2]+alpha*A[t1][t1]*bij+alpha*acc[0];;
      }
      bij=B[t1][2];;
      C[0][2]+=alpha*A[0][t1]*bij;;
      acc[0]=0;;
      acc[0]+=B[0][2]*A[0][t1];;
      C[t1][2]=beta*C[t1][2]+alpha*A[t1][t1]*bij+alpha*acc[0];;
      for (t2=3;t2<=NJ-1;t2++) {
        bij=B[t1][t2];;
        C[0][t2]+=alpha*A[0][t1]*bij;;
        acc[0]=0;;
        acc[0]+=B[0][t2]*A[0][t1];;
        for (t3=1;t3<=t2-2;t3++) {
          C[t3][t2]+=alpha*A[t3][t1]*bij;;
          acc[0]+=B[t3][t2]*A[t3][t1];;
        }
        C[t1][t2]=beta*C[t1][t2]+alpha*A[t1][t1]*bij+alpha*acc[0];;
      }
    }
  }
  if (NJ == 3) {
    for (t1=0;t1<=NI-1;t1++) {
      for (t2=0;t2<=1;t2++) {
        bij=B[t1][t2];;
        acc[0]=0;;
        C[t1][t2]=beta*C[t1][t2]+alpha*A[t1][t1]*bij+alpha*acc[0];;
      }
      bij=B[t1][2];;
      C[0][2]+=alpha*A[0][t1]*bij;;
      acc[0]=0;;
      acc[0]+=B[0][2]*A[0][t1];;
      C[t1][2]=beta*C[t1][2]+alpha*A[t1][t1]*bij+alpha*acc[0];;
    }
  }
  if (NJ <= 2) {
    for (t1=0;t1<=NI-1;t1++) {
      for (t2=0;t2<=NJ-1;t2++) {
        bij=B[t1][t2];;
        acc[0]=0;;
        C[t1][t2]=beta*C[t1][t2]+alpha*A[t1][t1]*bij+alpha*acc[0];;
      }
    }
  }
}
/* End of CLooG code */
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

