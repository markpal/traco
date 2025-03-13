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
// Filename...........benchmark/mvt.c
// Author.............Cedric Nugteren
// Last modified on...23-May-2012
//

int NX = 4000;


// This is 'mvt', a matrix vector product and transpose kernel
int main(int argc, char *argv[]) {
	int i,j;

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);
	NX = N;

	// Declare arrays on the stack
	float **A = new float*[NX];

	for (i=0; i<NX; i++)
	  A[i] = new float[NX];
	float *x1 = new float[NX];
	float *x2 = new float[NX];
	float *y_1 = new float[NX];
	float *y_2 = new float[NX];

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

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x1[i] = x1[i] + A[i][j] * y_1[j];
		}
	}
	for (i=0; i<NX; i++) {
		for (j=0; j<NX; j++) {
			x2[i] = x2[i] + A[j][i] * y_2[j];
		}
	}
}
// traco
// -----------------------------------
else if(kind == 2){

int c0,c1,c2,c3,c4,c5;

for (int c0 = 0; c0 <= floord(NX - 1, 16); c0 += 1)
  for (int c1 = 0; c1 <= (NX - 1) / 16; c1 += 1)
    for (int c2 = 16 * c0; c2 <= min(NX - 1, 16 * c0 + 15); c2 += 1)
      for (int c3 = 16 * c1; c3 <= min(16 * c1 + 15, NX - 1); c3 += 1) {
        x1[c2]=x1[c2]+A[c2][c3]*y_1[c3];
        x2[c2]=x2[c2]+A[c3][c2]*y_2[c3];
      }

}
// pluto
// -----------------------------------
else if(kind == 3){

  int t1, t2, t3, t4;

 register int lbv, ubv;

/* Start of CLooG code */
if (NX >= 1) {
  for (t1=0;t1<=floord(NX-1,16);t1++) {
    for (t2=0;t2<=floord(NX-1,16);t2++) {
      for (t3=16*t1;t3<=min(NX-1,16*t1+15);t3++) {
        for (t4=16*t2;t4<=min(NX-1,16*t2+15);t4++) {
          x1[t3]=x1[t3]+A[t3][t4]*y_1[t4];;
          x2[t3]=x2[t3]+A[t4][t3]*y_2[t4];;
        }
      }
    }
  }
}
/* End of CLooG code */

}

	double end = omp_get_wtime();
	printf("%.3f\n", end - start);


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

