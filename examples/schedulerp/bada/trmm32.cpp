#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))




int ni = 1024;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int ni = atoi(argv[2]);
	int cpus = atoi(argv[3]);
	int z = 0;

	int N = ni;

	float alpha = 32412;

	omp_set_num_threads(cpus);

	int k,i,j,t;

	// Declare arrays on the stack
	float **A = new float*[N];
	for (i=0; i<N; i++)
	  A[i] = new float[N];

    float **A1 = new float*[N];
	for (i=0; i<N; i++)
	  A1[i] = new float[N];

    float **B = new float*[N];
	for (i=0; i<N; i++)
	  B[i] = new float[N];

    float **B1 = new float*[N];
	for (i=0; i<N; i++)
	  B1[i] = new float[N];

	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			//path[i][j] = ((float) (N-j)*j*(j+2) + 2) / N;
			A[i][j] = rand()/N;
			A1[i][j] =  A[i][j]; //  ((float) (N-j)*j*(j+2) + 2) / N;
            B[i][j] = rand()/N;
			B1[i][j] =  B[i][j]; //
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


  for (i = 1; i < ni; i++)
    for (j = 0; j < ni; j++)
      for (k = 0; k < i; k++)
        B[i][j] += alpha * A[i][k] * B[j][k];

}
else if(kind == 3){


  int t1, t2, t3, t4, t5;

 register int lbv, ubv;


}
else{

    //traco
    int c0,c1,c2,c3,c4,c5,c6,c8,i;



for (i = 1; i < ni; i++)
{
  {
  if (i >= 8 && ni >= i + 1)
    for (c0 = 0; c0 <= (i - 1) / 8; c0 += 1) {
#pragma omp parallel for
      for (c2 = 0; c2 < i / 8; c2 += 1)
        for (c6 = 8 * c2; c6 <= 8 * c2 + 7; c6 += 1) {
          if (c0 >= 1) {
            for (c8 = 8 * c0; c8 <= min(i - 1, 8 * c0 + 7); c8 += 1)
              B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
          } else
            for (c8 = 0; c8 <= 7; c8 += 1)
              B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
        }
      if (i >= 9)
        for (c2 = i / 8 + 1; c2 <= floord(ni - 1, 8); c2 += 1)
          for (c6 = 8 * c2; c6 <= min(ni - 1, 8 * c2 + 7); c6 += 1) {
            if (c0 >= 1) {
              for (c8 = 8 * c0; c8 <= min(i - 1, 8 * c0 + 7); c8 += 1)
                B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
            } else
              for (c8 = 0; c8 <= 7; c8 += 1)
                B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
          }
    }
  if (i == 8)
#pragma omp parallel for
    for (c6 = 8; c6 <= min(15, ni - 1); c6 += 1)
      for (c8 = 0; c8 <= 7; c8 += 1)
        B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
  if (ni >= i + 1)
    for (c0 = max(floord(i - 1, 8) + 1, 2); c0 <= min(floord(i - 1, 4) + 1, 2 * floord(i, 8) + 1); c0 += 1)
      for (c6 = -(i % 8) + i; c6 <= min(ni - 1, -(i % 8) + i + 7); c6 += 1)
        for (c8 = ((i + 7) % 8) - i + 8 * c0 - 7; c8 <= min(i - 1, ((i + 7) % 8) - i + 8 * c0); c8 += 1)
          B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
}

}

}



    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

    if(kind != 1){
      for (i = 1; i < ni; i++)
        for (j = 0; j < ni; j++)
          for (k = 0; k < i; k++)
            B[i][j] += alpha * A[i][k] * B[j][k];

        for (k = 0; k < N; k++)
        {
          for(i = 0; i < N; i++)
            for (j = 0; j < N; j++){
              if(A[i][j] != A1[i][j] || B[i][j] != B1[i][j])
                printf("Error!\n");
                exit(0);
              }
        }
    }


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
