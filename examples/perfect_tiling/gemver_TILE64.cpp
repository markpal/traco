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
// Filename...........benchmark/gemver.c
// Author.............Cedric Nugteren
// Last modified on...04-April-2012
//

int NX = 1000;

// This is 'gemver', a general matrix vector multiplication and matrix addition kernel
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);
	NX = N;

	int i,j;

	// Declare arrays on the stack
	float **A = new float*[NX];
	for (i=0; i<NX; i++)
	  A[i] = new float[NX];
	float *u1 = new float[NX];
	float *u2 = new float[NX];
	float *v1 = new float[NX];
	float *v2 = new float[NX];
	float *w = new float[NX];
	float *x= new float[NX];
	float *y = new float[NX];
	float *z = new float[NX];

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


double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];
		}
	}
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x[i] = x[i] + beta * A[j][i] * y[j];
		}
	}
	for (i=0; i<NX; i++) {
		x[i] = x[i] + z[i];
	}
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			w[i] = w[i] +  alpha * A[i][j] * x[j];
		}
	}
}
// traco
// -----------------------------------
else if(kind == 2){

int c0,c1,c2,c3,c4,c5;
for (c0 = 0; c0 <= floord(NX - 1, 64); c0 += 1)
  for (c1 = 0; c1 <= (NX - 1) / 64; c1 += 1)
    for (c2 = 64 * c0; c2 <= min(NX - 1, 64 * c0 + 63); c2 += 1)
      for (c3 = 64 * c1; c3 <= min(64 * c1 + 63, NX - 1); c3 += 1)
        A[c2][c3]=A[c2][c3]+u1[c2]*v1[c3]+u2[c2]*v2[c3];


for (c0 = 0; c0 <= floord(NX - 1, 64); c0 += 1)
  for (c1 = 0; c1 <= (NX - 1) / 64; c1 += 1)
    for (c2 = 64 * c1; c2 <= min(NX - 1, 64 * c1 + 63); c2 += 1)
      for (c3 = 64 * c0; c3 <= min(64 * c0 + 63, NX - 1); c3 += 1)
        x[c3]=x[c3]+beta*A[c2][c3]*y[c2];



	for (i=0; i<NX; i++) {
		x[i] = x[i] + z[i];
	}


for (c0 = 0; c0 <= floord(NX - 1, 64); c0 += 1)
  for (c1 = 0; c1 <= (NX - 1) / 64; c1 += 1)
    for (c2 = 64 * c1; c2 <= min(NX - 1, 64 * c1 + 63); c2 += 1)
      for (c3 = 64 * c0; c3 <= min(64 * c0 + 63, NX - 1); c3 += 1)
        w[c3]=w[c3]+alpha*A[c3][c2]*x[c2];

/* End of CLooG code */
}
// pluto
// -----------------------------------
else if(kind == 3){

int t1, t2, t3, t4, t5, t6, t7, t8;

 register int lbv, ubv;

/* Start of CLooG code */
if (NX >= 1) {
  for (t2=0;t2<=floord(NX-1,64);t2++) {
    for (t3=0;t3<=floord(NX-1,64);t3++) {
      for (t4=64*t3;t4<=min(NX-1,64*t3+63);t4++) {
        lbv=64*t2;
        ubv=min(NX-1,64*t2+63);
#pragma ivdep
#pragma vector always
        for (t8=lbv;t8<=ubv;t8++) {
          A[t4][t8]=A[t4][t8]+u1[t4]*v1[t8]+u2[t4]*v2[t8];;
        }
        lbv=64*t2;
        ubv=min(NX-1,64*t2+63);
#pragma ivdep
#pragma vector always
        for (t8=lbv;t8<=ubv;t8++) {
          x[t8]=x[t8]+beta*A[t4][t8]*y[t4];;
        }
      }
    }
  }
  lbv=0;
  ubv=NX-1;
#pragma ivdep
#pragma vector always
  for (t2=lbv;t2<=ubv;t2++) {
    x[t2]=x[t2]+z[t2];;
  }
  for (t2=0;t2<=floord(NX-1,64);t2++) {
    for (t3=0;t3<=floord(NX-1,64);t3++) {
      for (t4=64*t2;t4<=min(NX-1,64*t2+63);t4++) {
        for (t5=64*t3;t5<=min(NX-1,64*t3+63);t5++) {
          w[t4]=w[t4]+alpha*A[t4][t5]*x[t5];;
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

/*
	for (int c0 = 0; c0 <= floord(NX - 1, 64); c0 += 1)
	  for (int c1 = 0; c1 <= (NX - 1) / 64; c1 += 1)
	    for (int c2 = 64 * c0; c2 <= min(NX - 1, 64 * c0 + 63); c2 += 1)
	      for (int c3 = 64 * c1; c3 <= min(64 * c1 + 63, NX - 1); c3 += 1)
		A[c2][c3]=A[c2][c3]+u1[c2]*v1[c3]+u2[c2]*v2[c3];

	for (int c0 = 0; c0 <= floord(NX - 1, 64); c0 += 1)
	  for (int c1 = 0; c1 <= (NX - 1) / 64; c1 += 1)
	    for (int c2 = 64 * c0; c2 <= min(NX - 1, 64 * c0 + 63); c2 += 1)
	      for (int c3 = 64 * c1; c3 <= min(64 * c1 + 63, NX - 1); c3 += 1)
		x[c2]=x[c2]+beta*A[c3][c2]*y[c3];


	for (i=0; i<NX; i++) {
		x[i] = x[i] + z[i];
	}


	for (int c0 = 0; c0 <= floord(NX - 1, 64); c0 += 1)
	  for (int c1 = 0; c1 <= (NX - 1) / 64; c1 += 1)
	    for (int c2 = 64 * c0; c2 <= min(NX - 1, 64 * c0 + 63); c2 += 1)
	      for (int c3 = 64 * c1; c3 <= min(64 * c1 + 63, NX - 1); c3 += 1)
		w[c2]=w[c2]+alpha*A[c2][c3]*x[c3];





*/
