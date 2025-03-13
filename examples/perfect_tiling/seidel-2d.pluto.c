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
// Filename...........benchmark/seidel-2d.c
// Author.............Cedric Nugteren
// Last modified on...05-April-2012
//

#include "common.h"

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(void) {
	int i,j,t;
	
	// Declare arrays on the stack
	float A[N][N];
	
	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			A[i][j] = ((float) i*i*(j+2) + 2) / N;
		}
	}
	
	// Perform the computation



  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N >= 3) && (TSTEPS >= 2)) {
  for (t1=1;t1<=2*TSTEPS+N-6;t1++) {
    lbp=max(ceild(t1+1,2),t1-TSTEPS+2);
    ubp=min(floord(t1+N-2,2),t1);
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=t1+1;t3<=t1+N-2;t3++) {
        A[-t1+2*t2][-t1+t3]=(A[-t1+2*t2-1][-t1+t3-1]+A[-t1+2*t2-1][-t1+t3]+A[-t1+2*t2-1][-t1+t3+1]+A[-t1+2*t2][-t1+t3-1]+A[-t1+2*t2][-t1+t3]+A[-t1+2*t2][-t1+t3+1]+A[-t1+2*t2+1][-t1+t3-1]+A[-t1+2*t2+1][-t1+t3]+A[-t1+2*t2+1][-t1+t3+1])/9.0;;
      }
    }
  }
}
/* End of CLooG code */
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
