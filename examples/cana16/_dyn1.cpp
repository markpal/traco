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
    float **A = new float*[N+2];
    float **B = new float*[N+2];
    for (i=0; i<N+2; i++) {
	A[i] = new float[N+2];
	B[i] = new float[N+2];
    }
	// Set the input data
	//for (i=0; i<N+1; i++) {
	//		A[i] = ((float) i*i + 2) / N;
	//		B[i] = ((float) i*i + 2) / N;
    


double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){



for(i=0; i<=N; i++){
for(j=0; j<=N; j++){
  A[i][j] = A[i][j+1]; 
}
 B[i][N] = A[i+1][N]+A[i][N]; 
}


}
// pluto
// -----------------------------------
else if(kind == 3){



}else{

    //traco

int c0,c1,c2,c3;

for (c0 = 0; c0 <= floord(N, 16); c0 += 1)
  for (c1 = 0; c1 <= N / 16; c1 += 1)
    for (c2 = 16 * c0; c2 <= min(N, 16 * c0 + 15); c2 += 1) {
      if (16 * c1 + 15 >= N)
        B[c2][N]=A[c2+1][N]+A[c2][N];
      for (c3 = 16 * c1; c3 <= min(N + c0 - (-c0 + c2 + 14) / 15, 16 * c1 + 15); c3 += 1)
        A[c2][c3]=A[c2][c3+1];
      if (c2 >= 16 * c0 + 1 && 16 * c1 + 15 >= N)
        A[c2][N]=A[c2][N+1];
    }
}
    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
