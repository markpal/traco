#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 500;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;



void seq(float u[6][DIM1][DIM2][2], float phi1[DIM1][DIM2], float phi2[DIM1][DIM2]) {
int k=1,ki1=1,ki2=1,i,j,c2;

for(j = N1; j <= N2; j++){
  for(i = N3; i <= N4; i++){
    k = ki1;
    phi1[i][j] = c2*(  u[5][i][j][k] - 0.50 * (  u[2][i][j][k] * 2 + u[3][i][j][k] * 2 + u[4][i][j][k] * 2 ) / u[1][i][j][k] );
    k = ki2;
    phi2[i][j] = c2*(  u[5][i][j][k] - 0.50 * (  u[2][i][j][k] * 2 + u[3][i][j][k] * 2 + u[4][i][j][k] * 2 ) / u[1][i][j][k] );
  }
}

}


void comp(float u[6][DIM1][DIM2][DIM3], float phi1[DIM1][DIM2][DIM3], float phi2[DIM1][DIM2][DIM3]) {

}


void comp_tile(float u[6][DIM1][DIM2][2], float phi1[DIM1][DIM2], float phi2[DIM1][DIM2]) {
int k=1,ki1=1,ki2=1;
int c0,c1,c2,c3,gg2;

#pragma omp parallel for
for (c0 = 0; c0 <= floord(-N1 + N2, 256); c0 += 1)
  for (c1 = 0; c1 <= floord(-N3 + N4, 256); c1 += 1)
     for (c3 = N3 + 256 * c1; c3 <= min(N3 + 256 * c1 + 255, N4); c3 += 1)
    for (c2 = N1 + 256 * c0; c2 <= min(N2, N1 + 256 * c0 + 255); c2 += 1)
       {
        k=ki1;
        phi1[c3][c2]=gg2*(u[5][c3][c2][k]-0.50*(u[2][c3][c2][k]*2+u[3][c3][c2][k]*2+u[4][c3][c2][k]*2)/u[1][c3][c2][k]);
        k=ki2;
        phi2[c3][c2]=gg2*(u[5][c3][c2][k]-0.50*(u[2][c3][c2][k]*2+u[3][c3][c2][k]*2+u[4][c3][c2][k]*2)/u[1][c3][c2][k]);
      }
/*
#pragma omp parallel for
for (c0 = 0; c0 <= floord(-N1 + N2, 256); c0 += 1)
  for (c1 = 0; c1 <= floord(-N3 + N4, 256); c1 += 1)
    for (c2 = N1 + 256 * c0; c2 <= min(N2, N1 + 256 * c0 + 255); c2 += 1)
      for (c3 = N3 + 256 * c1; c3 <= min(N3 + 256 * c1 + 255, N4); c3 += 1) {
        k=ki1;
        phi1[c3][c2]=gg2*(u[5][c3][c2][k]-0.50*(u[2][c3][c2][k]*2+u[3][c3][c2][k]*2+u[4][c3][c2][k]*2)/u[1][c3][c2][k]);
        k=ki2;
        phi2[c3][c2]=gg2*(u[5][c3][c2][k]-0.50*(u[2][c3][c2][k]*2+u[3][c3][c2][k]*2+u[4][c3][c2][k]*2)/u[1][c3][c2][k]);
      }

#pragma omp parallel for
  for(i = N3; i <= N4; i++){
for(j = N1; j <= N2; j++){

    k = ki1;
    phi1[i][j] = c2*(  u[5][i][j][k] - 0.50 * (  u[2][i][j][k] * 2 + u[3][i][j][k] * 2 + u[4][i][j][k] * 2 ) / u[1][i][j][k] );
    k = ki2;
    phi2[i][j] = c2*(  u[5][i][j][k] - 0.50 * (  u[2][i][j][k] * 2 + u[3][i][j][k] * 2 + u[4][i][j][k] * 2 ) / u[1][i][j][k] );
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

  N1 = N3 = 1;
  N2 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*u)[6][DIM2][DIM3], (*phi1)[DIM2], (*phi2)[DIM2];
  phi1 = (float (*)[DIM2])malloc(DIM1 * DIM2  * sizeof(float));
  phi2 = (float (*)[DIM2])malloc(DIM1 * DIM2  * sizeof(float));
  u = (float (*)[DIM1][DIM2][2])malloc(DIM1 * DIM2 * 2 * 6 * sizeof(float));


  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // PETLA SEKWENCYJNA

  gettimeofday(&s1, NULL);

  if(num_proc == 1)
    seq(u, phi1, phi2);
  else
    comp_tile(u, phi1, phi2);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}



