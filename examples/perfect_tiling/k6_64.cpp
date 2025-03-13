#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

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


int N = 1024;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int k,l,i,j,t,loop=N,n=N;

	// Declare arrays on the stack
	float **b = new float*[N];
	for (i=0; i<N; i++)
	  b[i] = new float[N];
    float *w = new float[N];

	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			b[i][j] = ((float) i*i*(j+2) + 2) / N;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


    for ( l=1 ; l<=loop ; l++ ) {
        for ( i=1 ; i<n ; i++ ) {
            for ( k=0 ; k<i ; k++ ) {
                w[i] += b[k][i] * w[(i-k)-1];
            }
        }
    }
}
// pluto
// -----------------------------------
else if(kind == 3){



}else{

    //traco

int c0,c1,c2,c3,c4,c5;

for (c0 = 0; c0 <= floord(loop - 1, 64); c0 += 1)
  for (c1 = 0; c1 <= floord(n - 2, 64); c1 += 1)
    for (c2 = 0; c2 <= c1; c2 += 1)
      if (c1 >= c2 + 1) {
        for (c5 = 64 * c2; c5 <= 64 * c2 + 63; c5 += 1)
          w[64*c1+1]+=b[c5][64*c1+1]*w[(64*c1+1-c5)-1];
      } else
        for (c3 = 64 * c0 + 1; c3 <= min(loop, 64 * c0 + 64); c3 += 1)
          for (c4 = 64 * c1 + 1; c4 <= min(n - 1, 64 * c1 + 64); c4 += 1) {
            if (c3 + c4 >= 64 * c0 + 64 * c1 + 3)
              for (c5 = 0; c5 < 64 * c1; c5 += 1)
                w[c4]+=b[c5][c4]*w[(c4-c5)-1];
            for (c5 = 64 * c1; c5 < c4; c5 += 1)
              w[c4]+=b[c5][c4]*w[(c4-c5)-1];
          }


}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
