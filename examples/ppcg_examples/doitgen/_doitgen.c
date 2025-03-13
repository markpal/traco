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

int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2][DIM3], float sum[DIM1][DIM2][DIM3], float C4[DIM1][DIM2]) {
int r,q,p,s;

#pragma scop
        for( r = 0; r< N; r++)  {
            for( q = 0; q< N; q++)  {
                for( p = 0; p< N; p++)  {
                    sum[r][q][p] = 0;
                    for( s = 0; s< N; s++)  {
                        sum[r][q][p] = sum[r][q][p] + A[r][q][s]*C4[s][p];
                    }
                }
                for( p = 0; p< N; p++)  {
                    A[r][q][p] = sum[r][q][p];
                }
            }
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

  N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2][DIM3], (*sum)[DIM2][DIM3], (*C4)[DIM2];

  A = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  sum = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  C4 = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));




  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    seq(A,sum,C4);


  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);


  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









