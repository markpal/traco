#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 100;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {
int k, iz, i, j;

#pragma scop
    for(k = 1; k <= N1; k++){
      for(iz = 1; iz <= N2; iz++){
        for(j = 1; j <= N3; j++){
          for(i = 1; i <= N4; i++){
            r[i][j][iz] = r[i][j][iz]+u[i][j][k]*wdtdr[k][iz];
          }
        }
      }
    }
#pragma endscop
}


void comp(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {
int c0,c1,c2,c3,c4,c5,c6,c7,c8;
{

int UB = min(floord(N2 - 1, 16) + 1, floord(N4 - 1, 16));
int UB2 = floord(N2 - 1, 16);

if (N1 >= 1)
#pragma omp parallel for
  for (c1 = 0; c1 <= UB; c1 += 1)
    for (c2 = 0; c2 <= min(floord(N2 - 1, 16), floord(N3 - 1, 16) + 1); c2 += 1)
      for (c3 = 0; c3 <= min((N4 - 1) / 16 + 1, floord(N3 - 1, 16)); c3 += 1)
          for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
            for (c4 = 16 * c0 + 1; c4 <= min(16 * c0 + 16, N1); c4 += 1)
              for (c5 = 16 * c3 + 1; c5 <= min(min(N4 + 16, N3), 16 * c3 + 16); c5 += 1)
                for (c6 = 16 * c1 + 1; c6 <= min(min(N2 + 16, 16 * c1 + 16), N4); c6 += 1)
                  for (c7 = 16 * c2 + 1; c7 <= min(min(N3 + 16, N2), 16 * c2 + 16); c7 += 1)
                    r[c6][c5][c7]=r[c6][c5][c7]+u[c6][c5][c4]*wdtdr[c4][c7];


/*


#pragma omp parallel for
  for (c1 = 0; c1 <= UB2; c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
      for (c3 = 0; c3 <= floord(N4 - 1, 16); c3 += 1)
         for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
            for (c4 = 16 * c0 + 1; c4 <= min(16 * c0 + 16, N1); c4 += 1)
              for (c5 = 16 * c1 + 1; c5 <= min(16 * c1 + 16, N2); c5 += 1)
                for (c6 = 16 * c2 + 1; c6 <= min(16 * c2 + 16, N3); c6 += 1)
                  for (c7 = 16 * c3 + 1; c7 <= min(16 * c3 + 16, N4); c7 += 1)
                    r[c7][c6][c5]=r[c7][c6][c5]+u[c7][c6][c4]*wdtdr[c4][c5];


#pragma omp parallel for
    for(k = 1; k <= N1; k++){
          for(i = 1; i <= N4; i++){
            for(j = 1; j <= N3; j++){
              for(iz = 1; iz <= N2; iz++){
              r[i][j][iz] = r[i][j][iz]+u[i][j][k]*wdtdr[k][iz];
          }
        }
      }
    }
*/
}




int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*u)[DIM2][DIM3], (*wdtdr)[DIM2], (*r)[DIM2][DIM3];
  wdtdr = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  r = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(1);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  if(num_proc == 1)
    seq(u, wdtdr, r);
  else
    comp(u, wdtdr, r);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas sekwencyjny: %2.3f seconds\n", duration);




}


