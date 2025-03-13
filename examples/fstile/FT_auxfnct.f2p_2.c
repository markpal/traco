#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define TILE_SIZE 20


int N = 200;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int k, i, j;

#pragma scop
for(i = 1; i <= N1; i++){
  for(k = 1; k <= N2; k++){
    for(j = 1; j <= N3; j++){
      y[j][k][i]=y[j][k][i]*twiddle[j][k][i];
      x[j][k][i]=y[j][k][i];
    }
  }
}
#pragma endscop
}




void comp_tile(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int ii,jj,kk,c0,c1,c2,c3,c4,c5;
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
      for (c3 = 16 * c0 + 1; c3 <= min(N1, 16 * c0 + 16); c3 += 1)
        for (c4 = 16 * c1 + 1; c4 <= min(N2, 16 * c1 + 16); c4 += 1)
          for (c5 = 16 * c2 + 1; c5 <= min(N3, 16 * c2 + 16); c5 += 1) {
            y[c5][c4][c3]=y[c5][c4][c3]*twiddle[c5][c4][c3];
            x[c5][c4][c3]=y[c5][c4][c3];
          }




}

void fs_tile(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int ii,jj,kk,c0,c1,c2,c3,c4,c5;
#pragma omp parallel for
for (c0 = 0; c0 <= (N1 - 1)/16; c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
      for (c3 = 16 * c1 + 1; c3 <= min(N2, 16 * c1 + 16); c3 += 1)
        for (c4 = 16 * c2 + 1; c4 <= min(N3, 16 * c2 + 16); c4 += 1)
          for (c5 = 16 * c0 + 1; c5 <= min(N1, 16 * c0 + 16); c5 += 1) {
            y[c4][c3][c5]=y[c4][c3][c5]*twiddle[c4][c3][c5];
            x[c4][c3][c5]=y[c4][c3][c5];
          }




}
void fs(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int ii,jj,kk,c0,c1,c2,c3,c4,c5;

for (c0 = 0; c0 <= 1; c0 += 1)
#pragma omp parallel for
  for (c1 = 1; c1 <= N1; c1 += 1)
    for (c3 = 1; c3 <= N2; c3 += 1)
      for (c5 = 1; c5 <= N3; c5 += 1)
        if (c0 == 1) {
          x[c5][c3][c1]=y[c5][c3][c1];
        } else
          y[c5][c3][c1]=y[c5][c3][c1]*twiddle[c5][c3][c1];
}

int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*y)[DIM2][DIM3], (*x)[DIM2][DIM3], (*twiddle)[DIM2][DIM3];
  x = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  y = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  twiddle = (float (*)[DIM1][DIM2])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // PETLA SEKWENCYJNA

  gettimeofday(&s1, NULL);

  if(num_proc == 1)
    seq(x, y, twiddle);
  else if(num_proc == 2)
    comp_tile(x, y, twiddle);
    else if(num_proc == 3)
      fs_tile(x, y, twiddle);
      else
        fs(x, y, twiddle);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}


