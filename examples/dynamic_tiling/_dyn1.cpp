#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))



int N = 2048;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int k,l,i,j,t,loop=N,n=N;

	// Declare arrays on the stack
	/*float **A = new float*[N+1];
	float **B = new float*[N+1];
	for (i=0; i<N; i++){
	  A[i] = new float[N+1];
	  B[i] = new float[N+1];
	}
	*/
    float *A = new float[N+1];
    float *B = new float[N+1];

	// Set the input data
	for (i=0; i<N+1; i++) {
			A[i] = ((float) i*i + 2) / N;
			B[i] = ((float) i*i + 2) / N;
    }


double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


for(i = 0; i < N; i++){
    for(j = 0; j < N; j++) {
        A[j] = A[j] + B[i];
        if(i == j)
            B[i+1] = A[j];
    }
}

}
// pluto
// -----------------------------------
else if(kind == 3){



}else{

    //traco

int c0,c1,c2,c3;

for (c0 = 0; c0 <= floord(N - 1, 32); c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 32; c1 += 1)
    for (c2 = 32 * c0; c2 <= min(N - 1, 32 * c0 + 31); c2 += 1) {
      if (c1 == c0 && c2 >= 32 * c0 + 1)
        for (c3 = 0; c3 < 32 * c0; c3 += 1)
          A[c3]=A[c3]+B[c2];
      for (c3 = 32 * c1; c3 <= min(32 * c1 + 31, N - 1); c3 += 1) {
        if (c2 == 32 * c0 && c0 >= c1 + 2) {
          A[c3]=A[c3]+B[32*c0];
        } else if (32 * c1 + 32 >= c2)
          A[c3]=A[c3]+B[c2];
        B[c2+1]=A[c3];
      }
    }
}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
