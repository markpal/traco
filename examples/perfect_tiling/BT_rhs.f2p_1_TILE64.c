#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define TILE_SIZE 50

int N = 300;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float u[6][DIM1][DIM2][DIM3], float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3]) {
int k,j,i,rho_inv;

for(k = 0; k <= N1; k++){
  for(j = 0; j <= N2; j++){
    for(i = 0; i <= N3; i++){
      rho_inv = 1.0/u[1][i][j][k];
      rho_i[i][j][k] = rho_inv;
      us[i][j][k] = u[2][i][j][k] * rho_inv;
      vs[i][j][k] = u[3][i][j][k] * rho_inv;
      ws[i][j][k] = u[4][i][j][k] * rho_inv;
      square[i][j][k]     = 0.5* ( u[2][i][j][k]*u[2][i][j][k] + u[3][i][j][k]*u[3][i][j][k] + u[4][i][j][k]*u[4][i][j][k] ) * rho_inv;
      qs[i][j][k] = square[i][j][k] * rho_inv;
    }
  }
}

}


void comp_tile(float u[6][DIM1][DIM2][DIM3], float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3]) {
int rho_inv;
  register int c0, c1, c2, c3, c4, c5;
for (c0 = 0; c0 <= floord(N1, 64); c0 += 1)
  for (c1 = 0; c1 <= floord(N2, 64); c1 += 1)
    for (c2 = 0; c2 <= floord(N3, 64); c2 += 1)
      for (c3 = 64 * c1; c3 <= min(N2, 64 * c1 + 63); c3 += 1)
        for (c4 = 64 * c2; c4 <= min(N3, 64 * c2 + 63); c4 += 1)
          for (c5 = 64 * c0; c5 <= min(N1, 64 * c0 + 63); c5 += 1) {
            rho_inv=1.0/u[1][c4][c3][c5];
            rho_i[c4][c3][c5]=rho_inv;
            us[c4][c3][c5]=u[2][c4][c3][c5]*rho_inv;
            vs[c4][c3][c5]=u[3][c4][c3][c5]*rho_inv;
            ws[c4][c3][c5]=u[4][c4][c3][c5]*rho_inv;
            square[c4][c3][c5]=0.5*(u[2][c4][c3][c5]*u[2][c4][c3][c5]+u[3][c4][c3][c5]*u[3][c4][c3][c5]+u[4][c4][c3][c5]*u[4][c4][c3][c5])*rho_inv;
            qs[c4][c3][c5]=square[c4][c3][c5]*rho_inv;
          }

}

void comp_pluto(float u[6][DIM1][DIM2][DIM3], float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3]) {
  register int lbv, ubv, lb, ub, lb1, ub1, lb2, ub2;
  register int c0, c1, c2, c3, c4, c5;
  int rho_inv;

#pragma scop
if ((((N1 >= 0) && (N2 >= 0)) && (N3 >= 0))) {
  for (c0 = 0; c0 <= floord(N1, 64); c0++) {
    for (c1 = 0; c1 <= floord(N2, 64); c1++) {
      for (c2 = 0; c2 <= floord(N3, 64); c2++) {
        for (c3 = (64 * c0); c3 <= min(N1, ((64 * c0) + 63)); c3++) {
          for (c4 = (64 * c1); c4 <= min(N2, ((64 * c1) + 63)); c4++) {
            for (c5 = (64 * c2); c5 <= min(N3, ((64 * c2) + 63)); c5++) {
              rho_inv = 1.0/u[1][c5][c4][c3];
              square[c5][c4][c3] = 0.5* ( u[2][c5][c4][c3]*u[2][c5][c4][c3] + u[3][c5][c4][c3]*u[3][c5][c4][c3] + u[4][c5][c4][c3]*u[4][c5][c4][c3] ) * rho_inv;
              qs[c5][c4][c3] = square[c5][c4][c3] * rho_inv;
              ws[c5][c4][c3] = u[4][c5][c4][c3] * rho_inv;
              vs[c5][c4][c3] = u[3][c5][c4][c3] * rho_inv;
              us[c5][c4][c3] = u[2][c5][c4][c3] * rho_inv;
              rho_i[c5][c4][c3] = rho_inv;
            }
          }
        }
      }
    }
  }
}
#pragma endscop
}




int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);
  int kind = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*u)[6][DIM2][DIM3], (*square)[DIM2][DIM3], (*qs)[DIM2][DIM3], (*ws)[DIM2][DIM3], (*vs)[DIM2][DIM3], (*us)[DIM2][DIM3], (*rho_i)[DIM2][DIM3];

  us = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  vs = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  ws = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  square = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  qs = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  rho_i = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[6][DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 6 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  switch(kind)
  {
      case 1 : seq(u, us, vs, ws, qs, square, rho_i); break;
      case 2 : comp_tile(u, us, vs, ws, qs, square, rho_i); break;
      case 3 : comp_pluto(u, us, vs, ws, qs, square, rho_i); break;
  }

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("%2.3f\n", duration);




}


