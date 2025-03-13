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

int TSTEPS = 10;
int N = 2048;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int i,j,t;

	// Declare arrays on the stack
	float **A = new float*[N];
	for (i=0; i<N; i++)
	  A[i] = new float[N];

	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			A[i][j] = ((float) i*i*(j+2) + 2) / N;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


	for (t=0; t<TSTEPS-1; t++) {
		for (i=1; i<=N-2; i++) {
			for (j=1; j<=N-2; j++) {
				A[i][j] = (A[i-1][j-1] + A[i-1][ j ] + A[i-1][j+1] + A[ i ][j-1] + A[ i ][ j ] + A[ i ][j+1] + A[i+1][j-1] + A[i+1][ j ] + A[i+1][j+1])/9.0;
			}
		}
	}
}
// pluto
// -----------------------------------
else if(kind == 3){


  int t1, t2, t3, t4, t5, t6;

 register int lbv, ubv;

/* Start of CLooG code */
if ((N >= 3) && (TSTEPS >= 2)) {
  for (t1=0;t1<=floord(TSTEPS-2,32);t1++) {
    for (t2=t1;t2<=min(floord(TSTEPS+N-4,32),floord(32*t1+N+29,32));t2++) {
      for (t3=max(ceild(64*t2-N-28,32),t1+t2);t3<=min(min(min(min(floord(TSTEPS+N-4,16),floord(32*t1+N+29,16)),floord(64*t2+N+59,32)),floord(32*t1+32*t2+N+60,32)),floord(32*t2+TSTEPS+N+27,32));t3++) {
        for (t4=max(max(max(32*t1,32*t2-N+2),16*t3-N+2),-32*t2+32*t3-N-29);t4<=min(min(min(min(TSTEPS-2,32*t1+31),32*t2+30),16*t3+14),-32*t2+32*t3+30);t4++) {
          for (t5=max(max(32*t2,t4+1),32*t3-t4-N+2);t5<=min(min(32*t2+31,32*t3-t4+30),t4+N-2);t5++) {
            for (t6=max(32*t3,t4+t5+1);t6<=min(32*t3+31,t4+t5+N-2);t6++) {
              A[-t4+t5][-t4-t5+t6]=(A[-t4+t5-1][-t4-t5+t6-1]+A[-t4+t5-1][-t4-t5+t6]+A[-t4+t5-1][-t4-t5+t6+1]+A[-t4+t5][-t4-t5+t6-1]+A[-t4+t5][-t4-t5+t6]+A[-t4+t5][-t4-t5+t6+1]+A[-t4+t5+1][-t4-t5+t6-1]+A[-t4+t5+1][-t4-t5+t6]+A[-t4+t5+1][-t4-t5+t6+1])/9.0;;
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
/* End of CLooG code */
}else{ //traco

int c0,c1,c2,c3,c4,c5;

/*
#pragma omp parallel for
for (c0 = 0; c0 < TSTEPS - 1; c0 += 1)
  for (c1 = 0; c1 <= floord(N - 3, 32); c1 += 1)
    for (c2 = 0; c2 <= (N - 3) / 32; c2 += 1)
      for (c4 = 32 * c1 + 1; c4 <= min(N - 2, 32 * c1 + 32); c4 += 1) {
        for (c5 = max(1, 32 * c1 + 32 * c2 - c4 + 2); c5 <= 32 * c2; c5 += 1)
          A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
        if (N >= 32 * c2 + 35) {
          for (c5 = 32 * c2 + 1; c5 <= 32 * c1 + 32 * c2 - c4 + 33; c5 += 1)
            A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
        } else
          for (c5 = 32 * c2 + 1; c5 < N - 1; c5 += 1)
            A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
      }
      */


for (c0 = 0; c0 <= floord(TSTEPS - 2, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(N - 3, 32); c1 += 1)
    for (c2 = 0; c2 <= (N - 3) / 32; c2 += 1)
      if (N >= 32 * c2 + 35) {
        for (c3 = 32 * c0; c3 <= min(32 * c0 + 15, TSTEPS - 2); c3 += 1)
          for (c4 = 32 * c1 + 1; c4 <= min(min(64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 + 32, 32 * c1 + 32), N - 2); c4 += 1) {
            for (c5 = max(64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 - c4 + 2, 1); c5 <= 32 * c1 + 32 * c2 - c4 + 1; c5 += 1)
              A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
            for (c5 = max(1, 32 * c1 + 32 * c2 - c4 + 2); c5 <= 64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 - c4 + 33; c5 += 1)
              A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
          }
        for (c3 = 32 * c0 + 16; c3 <= min(min(32 * c0 + 31, 32 * c0 + 16 * c2 + 15), TSTEPS - 2); c3 += 1)
          for (c4 = 32 * c1 + 1; c4 <= min(min(64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 + 32, 32 * c1 + 32), N - 2); c4 += 1)
            for (c5 = max(64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 - c4 + 2, 1); c5 <= 64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 - c4 + 33; c5 += 1)
              A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
      } else
        for (c3 = 32 * c0; c3 <= min(TSTEPS - 2, 32 * c0 + 31); c3 += 1)
          for (c4 = 32 * c1 + 1; c4 <= min(N - 2, 32 * c1 + 32); c4 += 1) {
            for (c5 = max(64 * c0 + 32 * c1 + 32 * c2 - 2 * c3 - c4 + 2, 1); c5 <= 32 * c1 + 32 * c2 - c4 + 1; c5 += 1)
              A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
            for (c5 = max(1, 32 * c1 + 32 * c2 - c4 + 2); c5 <= 32 * c2; c5 += 1)
              A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
            for (c5 = 32 * c2 + 1; c5 < N - 1; c5 += 1)
              A[c4][c5]=(A[c4-1][c5-1]+A[c4-1][c5]+A[c4-1][c5+1]+A[c4][c5-1]+A[c4][c5]+A[c4][c5+1]+A[c4+1][c5-1]+A[c4+1][c5]+A[c4+1][c5+1])/9.0;
          }


}
    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
