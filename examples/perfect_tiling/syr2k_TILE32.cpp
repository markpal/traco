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
// Filename...........benchmark/syr2k.c
// Author.............Cedric Nugteren
// Last modified on...03-April-2012
//

int N = 1024;
int NI, NJ;

// This is 'syr2k', an algorithm for symmetric rank-2k operations
int main(int argc, char *argv[]) {
	int i,j,k;

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);
	NI = NJ = N;

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


double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

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
}
// traco
// -----------------------------------
else if(kind == 2){

int c0,c1,c2,c3,c4,c5;
for (int c0 = 0; c0 <= floord(NI - 1, 32); c0 += 1)
  for (int c1 = 0; c1 <= (NI - 1) / 32; c1 += 1)
    for (int c2 = 32 * c0; c2 <= min(NI - 1, 32 * c0 + 31); c2 += 1)
      for (int c3 = 32 * c1; c3 <= min(32 * c1 + 31, NI - 1); c3 += 1)
        C[c2][c3]*=beta;
for (int c0 = 0; c0 <= floord(NI - 1, 32); c0 += 1)
  for (int c1 = 0; c1 <= (NI - 1) / 32; c1 += 1)
    for (int c2 = 0; c2 <= floord(NJ - 1, 32); c2 += 1)
      for (int c3 = 32 * c0; c3 <= min(NI - 1, 32 * c0 + 31); c3 += 1)
        for (int c4 = 32 * c1; c4 <= min(32 * c1 + 31, NI - 1); c4 += 1)
          for (int c5 = 32 * c2; c5 <= min(32 * c2 + 31, NJ - 1); c5 += 1) {
            C[c3][c4]+=alpha*A[c3][c5]*B[c4][c5];
            C[c3][c4]+=alpha*B[c3][c5]*A[c4][c5];
          }
}

// pluto
// -----------------------------------
else if(kind == 3){


 //int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

 register int lbv, ubv;

/* Start of CLooG code */

  for (int t2=0;t2<=floord(NI-1,32);t2++) {
    for (int t3=0;t3<=floord(NI-1,32);t3++) {
      for (int t4=32*t2;t4<=min(NI-1,32*t2+31);t4++) {
        for (int t10=32*t3;t10<=min(NI-1,32*t3+31);t10++) {
          C[t4][t10]*=beta;
        }
      }
    }
  }
    for (int t2=0;t2<=floord(NI-1,32);t2++) {
      for (int t3=0;t3<=floord(NI-1,32);t3++) {
        for (int t4=0;t4<=floord(NJ-1,32);t4++) {
          for (int t5=32*t2;t5<=min(32*t2+31,NI-1);t5++) {
            for (int t6=32*t3;t6<=min(32*t3+31,NI-1);t6++) {
              for (int t7=32*t4;t7<=min(32*t4+31,NJ-1);t7++) {   //very amazing, changing order of arguments in 'min' slows the loop strongly
                C[t5][t6]+=alpha*A[t5][t7]*B[t6][t7];
                C[t5][t6]+=alpha*B[t5][t7]*A[t6][t7];
              }
            }
          }
        }


  }
}
}


	double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
