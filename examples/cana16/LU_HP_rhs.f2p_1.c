#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 50;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;

#define TILE_SIZE 5





void seq(float rsd[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3]) {
int k, m, i, j,tmp;

   for(k = 1; k <= N1; k += 1)
      for(j = 1; j <= N2; j += 1)
         for(i = 1; i <= N3; i += 1) {
            for(m = 1; m <= 5; m += 1)
               rsd[m][i][j][k] = -frct[m][i][j][k];
            tmp = 1.0/u[1][i][j][k];
            rho_i[i][j][k] = tmp;
            qs[i][j][k] = 0.5*(u[2][i][j][k]*u[2][i][j][k]+u[3][i][j][k]*u[3][i][j][k]+u[4][i][j][k]*u[4][i][j][k])*tmp;
         }
}


void comp(float rsd[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3]) {
int k, m, i, j,tmp;
int c0, c2, c4, c8, c10, c12, c14;
int UB = floord(N1 - 1, 16);
/*
#pragma omp parallel for private(k,i,j,m, tmp)
   for(k = 1; k <= N1; k += 1)
      for(j = 1; j <= N2; j += 1)
         for(i = 1; i <= N3; i += 1) {
            for(m = 1; m <= 5; m += 1)
               rsd[m][i][j][k] = -frct[m][i][j][k];
            tmp = 1.0/u[1][i][j][k];
            rho_i[i][j][k] = tmp;
            qs[i][j][k] = 0.5*(u[2][i][j][k]*u[2][i][j][k]+u[3][i][j][k]*u[3][i][j][k]+u[4][i][j][k]*u[4][i][j][k])*tmp;
         }

#pragma omp parallel for
for (c0 = 0; c0 < N1; c0 += 1)
  for (c2 = 0; c2 < N2; c2 += 1)
    for (c4 = 0; c4 < N3; c4 += 1) {
      for (c6 = 0; c6 <= 4; c6 += 1)
        rsd[c6+1][c4+1][c2+1][c0+1]=-frct[c6+1][c4+1][c2+1][c0+1];
      tmp[c4+1][c2+1][c0+1]=1.0/u[1][c4+1][c2+1][c0+1];
      rho_c4+1[c4+1][c2+1][c0+1]=tmp[c4+1][c2+1][c0+1];
      qs[c4+1][c2+1][c0+1]=0.5*(u[2][c4+1][c2+1][c0+1]*u[2][c4+1][c2+1][c0+1]+u[3][c4+1][c2+1][c0+1]*u[3][c4+1][c2+1][c0+1]+u[4][c4+1][c2+1][c0+1]*u[4][c4+1][c2+1][c0+1])*tmp[c4+1][c2+1][c0+1];
    }



*/

#pragma omp parallel for private(tmp)
for (c0 = 0; c0 <= UB; c0 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1) {
      for (c8 = 16 * c0 + 1; c8 <= min(16 * c0 + 16, N1); c8 += 1)
        for (c10 = 16 * c2 + 1; c10 <= min(16 * c2 + 16, N2); c10 += 1)
          for (c12 = 16 * c4 + 1; c12 <= min(16 * c4 + 16, N3); c12 += 1)
            for (c14 = 1; c14 <= 5; c14 += 1)
              rsd[c14][c12][c10][c8]=-frct[c14][c12][c10][c8];
      for (c8 = 16 * c0 + 1; c8 <= min(16 * c0 + 16, N1); c8 += 1)
        for (c10 = 16 * c2 + 1; c10 <= min(16 * c2 + 16, N2); c10 += 1)
          for (c12 = 16 * c4 + 1; c12 <= min(16 * c4 + 16, N3); c12 += 1) {
            tmp=1.0/u[1][c12][c10][c8];
            rho_i[c12][c10][c8]=tmp;
            qs[c12][c10][c8]=0.5*(u[2][c12][c10][c8]*u[2][c12][c10][c8]+u[3][c12][c10][c8]*u[3][c12][c10][c8]+u[4][c12][c10][c8]*u[4][c12][c10][c8])*tmp;
          }
    }

  /*  #pragma omp parallel for  private(tmp)
for (c0 = 0; c0 <= UB; c0 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1) {
        for (c10 = 16 * c2 + 1; c10 <= min(16 * c2 + 16, N2); c10 += 1)
          for (c12 = 16 * c4 + 1; c12 <= min(16 * c4 + 16, N3); c12 += 1)
            for (c14 = 1; c14 <= 5; c14 += 1)
             for (c8 = 16 * c0 + 1; c8 <= min(16 * c0 + 16, N1); c8 += 1)
              rsd[c14][c12][c10][c8]=-frct[c14][c12][c10][c8];

        for (c10 = 16 * c2 + 1; c10 <= min(16 * c2 + 16, N2); c10 += 1)
          for (c12 = 16 * c4 + 1; c12 <= min(16 * c4 + 16, N3); c12 += 1)
             for (c8 = 16 * c0 + 1; c8 <= min(16 * c0 + 16, N1); c8 += 1) {
            tmp=1.0/u[1][c12][c10][c8];
            rho_i[c12][c10][c8]=tmp;
            qs[c12][c10][c8]=0.5*(u[2][c12][c10][c8]*u[2][c12][c10][c8]+u[3][c12][c10][c8]*u[3][c12][c10][c8]+u[4][c12][c10][c8]*u[4][c12][c10][c8])*tmp;
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

  N1 = N2 = N3 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*frct)[6][DIM2][DIM3], (*rsd)[6][DIM2][DIM3], (*u)[6][DIM2][DIM3], (*qs)[DIM2][DIM3], (*rho_i)[DIM2][DIM3];
  rho_i = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  qs = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[DIM1][DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 6 * sizeof(float));
  rsd = (float (*)[DIM1][DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 6 * sizeof(float));
  frct = (float (*)[DIM1][DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 6 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // PETLA SEKWENCYJNA

  gettimeofday(&s1, NULL);

  if(num_proc == 1)
    seq(rsd, u, rho_i, qs, frct);
  else
    comp(rsd, u, rho_i, qs, frct);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}



