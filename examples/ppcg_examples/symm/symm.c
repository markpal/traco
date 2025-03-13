#include<sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float acc[DIM1][DIM2]) {
int i,j,k, alpha=0, beta=0;

 #pragma scop
 if(NI > 3 && NJ > 3)
  for (i = 0; i < NI; i++)
    for (j = 0; j < NJ; j++)
      {
	acc[i][j] = 0;
	for (k = 0; k < j-1; k++)
	  {
	    C[k][j] += alpha * A[k][i] * B[i][j];
	    acc[i][j] += B[k][j] * A[k][i];
	  }
	C[i][j] = beta * C[i][j] + alpha * A[i][i] * B[i][j] + alpha * acc[i][j];
      }

  #pragma endscop

}








int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*acc)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  acc = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

   // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);


  seq(A,B,C,acc);

  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}









