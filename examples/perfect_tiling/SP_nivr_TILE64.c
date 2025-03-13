#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 250;
int N1, N2, N3, N4, N5, DIM;
int DIM1;
int DIM2;
int DIM3;



void seq(float rhs[6][DIM1][DIM2][DIM3]) {
int k, i, j, r1,r2,r3,r4,r5,t1,t2,bt;

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      r1 = rhs[1][i][j][k];
      r2 = rhs[2][i][j][k];
      r3 = rhs[3][i][j][k];
      r4 = rhs[4][i][j][k];
      r5 = rhs[5][i][j][k];
      t1 = bt * r3;
      t2 = 0.5 * ( r4 + r5 );
      rhs[1][i][j][k] = -r2;
      rhs[2][i][j][k] =  r1;
      rhs[3][i][j][k] = bt * ( r4 - r5 );
      rhs[4][i][j][k] = -t1 + t2;
      rhs[5][i][j][k] =  t1 + t2;
    }
  }
}

}


void comp_pluto(float rhs[6][DIM1][DIM2][DIM3]) {

  int r1,r2,r3,r4,r5,t1,t2,bt;

  register int lbv, ubv, lb, ub, lb1, ub1, lb2, ub2;
  register int c1, c2, c3, c4, c5, c6;
#pragma scop
if ((((N1 >= 1) && (N2 >= 1)) && (N3 >= 1))) {
  for (c1 = 0; c1 <= floord(N1, 64); c1++) {
    for (c2 = 0; c2 <= floord(N2, 64); c2++) {
      for (c3 = 0; c3 <= floord(N3, 64); c3++) {
        for (c4 = max(1, (64 * c1)); c4 <= min(N1, ((64 * c1) + 63)); c4++) {
          for (c5 = max(1, (64 * c2)); c5 <= min(N2, ((64 * c2) + 63)); c5++) {
            for (c6 = max(1, (64 * c3)); c6 <= min(N3, ((64 * c3) + 63)); c6++) {
              r4 = rhs[4][c6][c5][c4];
              r5 = rhs[5][c6][c5][c4];
              r3 = rhs[3][c6][c5][c4];
              t2 = 0.5 * ( r4 + r5 );
              t1 = bt * r3;
              rhs[3][c6][c5][c4] = bt * ( r4 - r5 );
              rhs[4][c6][c5][c4] = -t1 + t2;
              rhs[5][c6][c5][c4] = t1 + t2;
              r1 = rhs[1][c6][c5][c4];
              r2 = rhs[2][c6][c5][c4];
              rhs[2][c6][c5][c4] = r1;
              rhs[1][c6][c5][c4] = -r2;
            }
          }
        }
      }
    }
  }
}
#pragma endscop

}


void comp_tile(float rhs[6][DIM1][DIM2][DIM3]) {
int c0,c1,c2,c3,c4,c5,c6,c7;
int r1,r2,r3,r4,r5,t1,t2,bt;

for (c0 = 0; c0 <= floord(N1 - 1, 64); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 64); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 64); c2 += 1)
      for (c3 = 64 * c1 + 1; c3 <= min(N2, 64 * c1 + 64); c3 += 1)
        for (c4 = 64 * c2 + 1; c4 <= min(N3, 64 * c2 + 64); c4 += 1)
          for (c5 = 64 * c0 + 1; c5 <= min(N1, 64 * c0 + 64); c5 += 1) {
            r1=rhs[1][c4][c3][c5];
            r2=rhs[2][c4][c3][c5];
            r3=rhs[3][c4][c3][c5];
            r4=rhs[4][c4][c3][c5];
            r5=rhs[5][c4][c3][c5];
            t1=bt*r3;
            t2=0.5*(r4+r5);
            rhs[1][c4][c3][c5]=-r2;
            rhs[2][c4][c3][c5]=r1;
            rhs[3][c4][c3][c5]=bt*(r4-r5);
            rhs[4][c4][c3][c5]=-t1+t2;
            rhs[5][c4][c3][c5]=t1+t2;
          }
}





int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);
  int kind = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N;

  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*rhs)[6][DIM2][DIM3];
  rhs= (float (*)[DIM1][DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 6 * sizeof(float));


  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // PETLA SEKWENCYJNA

  gettimeofday(&s1, NULL);

  switch(kind)
  {
      case 1 : seq(rhs); break;
      case 2 : comp_tile(rhs); break;
      case 3 : comp_pluto(rhs); break;
  }

  if(num_proc == 1)
    seq(rhs);
  else
    comp_tile(rhs);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}



