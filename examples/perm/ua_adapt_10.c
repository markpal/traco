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




void seq(float y[DIM1][6][DIM2], float x1[DIM1][DIM3][DIM2], float x2[DIM1][DIM3][DIM2], float map2[DIM3], float map4[DIM3]) {
int iz, ix, ip, lx1=0;

for(iz = 1; iz <= N1; iz++){
  for(ix = 1; ix <= N2; ix++){
    y[ix][1][iz]=x1[ix][1][iz];
    y[ix][2][iz]=0;
    for(ip = 1; ip <= N3; ip++){
      y[ix][2][iz]=y[ix][2][iz]+map2[ip]*x1[ix][ip][iz];
    }
    y[ix][3][iz]=x1[ix][lx1][iz];
    y[ix][4][iz]=0;
    for(ip = 1; ip <= N4; ip++){
      y[ix][4][iz]=y[ix][4][iz]+map4[ip]*x2[ix][ip][iz];
    }
    y[ix][lx1][iz]=x2[ix][lx1][iz];
  }
}

}

void comp(float y[DIM1][6][DIM2], float x1[DIM1][DIM3][DIM2], float x2[DIM1][DIM3][DIM2], float map2[DIM3], float map4[DIM3]) {
int lx1= 0, c0, c2, c4, c6, c8, c10, c1,c3,c5,c7,c9

int UB = floord(N1 - 1, 16);

// Tiling with permutation
#pragma omp parallel for
for (c0 = 0; c0 <= UB; c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
      for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1) {
        y[c6][1][c10]=x1[c6][1][c10];
        y[c6][2][c10]=0;
      }
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
        for (c8 = 16 * c4 + 1; c8 <= min(N3, 16 * c4 + 16); c8 += 1)
          for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1)
            y[c6][2][c10]=y[c6][2][c10]+map2[c8]*x1[c6][c8][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
        for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1) {
          y[c6][3][c10]=x1[c6][lx1][c10];
          y[c6][4][c10]=0;
        }
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
        for (c8 = 16 * c4 + 1; c8 <= min(N4, 16 * c4 + 16); c8 += 1)
          for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1)
            y[c6][4][c10]=y[c6][4][c10]+map4[c8]*x2[c6][c8][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
        for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1)
          y[c6][lx1][c10]=x2[c6][lx1][c10];
}


/*
// Tiling without permutation
#pragma omp parallel for
for (c1 = 0; c1 <= UB; c1 += 1)
  for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
    if (N3 >= 1) {
      if (N3 >= 17)
        for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
          for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1) {
            y[c9][1][c7]=x1[c9][1][c7];
            y[c9][2][c7]=0;
          }
      for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
        for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1) {
          if (N3 <= 16) {
            y[c9][1][c7]=x1[c9][1][c7];
            y[c9][2][c7]=0;
          }
          y[c9][3][c7]=x1[c9][lx1][c7];
          y[c9][4][c7]=0;
          y[c9][lx1][c7]=x2[c9][lx1][c7];
        }
    } else
      for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
        for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1) {
          y[c9][1][c7]=x1[c9][1][c7];
          y[c9][2][c7]=0;
        }
    for (c5 = 0; c5 <= floord(N3 - 1, 16); c5 += 1)
      for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
        for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
          for (c11 = 16 * c5 + 1; c11 <= min(N3, 16 * c5 + 16); c11 += 1)
            y[c9][2][c7]=y[c9][2][c7]+map2[c11]*x1[c9][c11][c7];
    if (N3 >= 1)
      for (c5 = 0; c5 <= floord(N4 - 1, 16); c5 += 1)
        for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
          for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
            for (c11 = 16 * c5 + 1; c11 <= min(N4, 16 * c5 + 16); c11 += 1)
              y[c9][4][c7]=y[c9][4][c7]+map4[c11]*x2[c9][c11][c7];
  }
*/





}



int main(int argc, char *argv[]) {

  // number of processors
  int tile_kind=1;
  tile_kind = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*y)[6][DIM2], (*x1)[DIM3][DIM2], (*x2)[DIM3][DIM2], *map2, *map4;

  y = (float (*)[6][DIM2])malloc(DIM1 * DIM2 * 6 * sizeof(float));
  x1 = (float (*)[DIM3][DIM2])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  x2 = (float (*)[DIM3][DIM2])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  map2 = (float (*))malloc(DIM3 * sizeof(float));
  map4 = (float (*))malloc(DIM3 * sizeof(float));



  printf("Ilosc procesorow: %i \n\n", tile_kind);
  omp_set_num_threads(tile_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tile_kind == 1)
    seq(y, x1, x2, map2, map4);
  else
      comp(y, x1, x2, map2, map4);

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}




