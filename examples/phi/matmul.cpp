#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))






int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);
	int M = N;
	int mp = M / 2;
    int K = N;
	int cpus = atoi(argv[3]);
    int z = 0;
	omp_set_num_threads(cpus);

	int k,l,i,j,t,loop=N,n=N;

	// Declare arrays on the stack
	double **A = new double*[N+1];
	double **B = new double*[N+1];
	double **C = new double*[N+1];


	for (i=0; i<N+1; i++){
	  A[i] = new double[N+1];
	  B[i] = new double[N+1];
	  C[i] = new double[N+1];
    }


	// Set the input data
	for (i=0; i<N+1; i++) {
		for (j=0; j<N+1; j++) {
			A[i][j] = 0.001*(i+1)*j;
			B[i][j] = 0.001*(i+1)*j;
			C[i][j] = 0.001*(i+1)*j;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

 for(i=0; i<M; i++)
   for(j=0; j<N; j++)
     for(k=0; k<K; k++)
       C[i][j] += A[i][k] * B[k][j];

       printf("---\n");

}

else{

    //traco
omp_set_nested(1);
int c0,c1,c2,c3,c4,c5,c6,c7,c8,c10,c12,c9,c11;
int UB = floord(N - 1, 32);


#pragma omp parallel sections
{
#pragma omp section
{
#pragma offload target(mic) in(A:length(N*N),B:length(N*N)) out(C:length(mp*N))
#pragma omp parallel for
for (c0 = 0; c0 <= (mp - 1)/32; c0 += 1)
  for (c1 = 0; c1 <= floord(N - 1, 32); c1 += 1)
    for (c2 = 0; c2 <= floord(K - 1, 32); c2 += 1)
      for (c3 = 32 * c0; c3 <= min(M - 1, 32 * c0 + 31); c3 += 1)
        for (c5 = 32 * c2; c5 <= min(K - 1, 32 * c2 + 31); c5 += 1)
          for (c4 = 32 * c1; c4 <= min(N - 1, 32 * c1 + 31); c4 += 1)
            C[c3][c4]+=A[c3][c5]*B[c5][c4];
}
#pragma omp section
{
#pragma omp parallel for
for (c0 = mp/32; c0 <= (M - 1)/32; c0 += 1)
  for (c1 = 0; c1 <= floord(N - 1, 32); c1 += 1)
    for (c2 = 0; c2 <= floord(K - 1, 32); c2 += 1)
      for (c3 = 32 * c0; c3 <= min(M - 1, 32 * c0 + 31); c3 += 1)
        for (c5 = 32 * c2; c5 <= min(K - 1, 32 * c2 + 31); c5 += 1)
          for (c4 = 32 * c1; c4 <= min(N - 1, 32 * c1 + 31); c4 += 1)
            C[c3][c4]+=A[c3][c5]*B[c5][c4];
}
}
}
    double end1 = omp_get_wtime();
	printf("%.3f\n", end1 - start);


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
