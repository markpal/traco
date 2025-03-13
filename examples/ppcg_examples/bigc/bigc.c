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
int NY, NX;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float q[DIM1], float p[DIM1], float r[DIM1], float s[DIM1]) {
int i,j,k, alpha=0;

#pragma scop
  for (i = 0; i < NY; i++)
    s[i] = 0;
  for (i = 0; i < NX; i++)
  {
      q[i] = 0;
      for (j = 0; j < NY; j++)
      {
	     s[j] = s[j] + r[i] * A[i][j];
         q[i] = q[i] + A[i][j] * p[j];
      }
  }
#pragma endscop
}






int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1,num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 2)
    N = atoi(argv[3]);



  NY = NX = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], *q, *p, *r, *s;

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  q = (float (*))malloc(DIM1 * sizeof(float));
  p = (float (*))malloc(DIM1 * sizeof(float));
  r = (float (*))malloc(DIM1 * sizeof(float));
  s = (float (*))malloc(DIM1 * sizeof(float));




  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  seq(A,q,p,r,s);

  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









