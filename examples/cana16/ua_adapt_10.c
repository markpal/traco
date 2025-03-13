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

void comp32(float y[DIM1][6][DIM2], float x1[DIM1][DIM3][DIM2], float x2[DIM1][DIM3][DIM2], float map2[DIM3], float map4[DIM3]) {
int lx1= 0, c0, c2, c4, c6, c8, c10;

for (c0 = 0; c0 <= floord(N1 - 1, 32); c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
      for (c8 = 32 * c0 + 1; c8 <= min(N1, 32 * c0 + 32); c8 += 1) {
        y[c6][1][c8]=x1[c6][1][c8];
        y[c6][2][c8]=0;
      }
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 32); c4 += 1)
      for (c6 = 32 * c4 + 1; c6 <= min(N3, 32 * c4 + 32); c6 += 1)
        for (c8 = 32 * c2 + 1; c8 <= min(N2, 32 * c2 + 32); c8 += 1)
          for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1)
            y[c8][2][c10]=y[c8][2][c10]+map2[c6]*x1[c8][c6][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
      for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
        for (c8 = 32 * c0 + 1; c8 <= min(N1, 32 * c0 + 32); c8 += 1) {
          y[c6][3][c8]=x1[c6][lx1][c8];
          y[c6][4][c8]=0;
        }
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N4 - 1, 32); c4 += 1)
      for (c6 = 32 * c4 + 1; c6 <= min(N4, 32 * c4 + 32); c6 += 1)
        for (c8 = 32 * c2 + 1; c8 <= min(N2, 32 * c2 + 32); c8 += 1)
          for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1)
            y[c8][4][c10]=y[c8][4][c10]+map4[c6]*x2[c8][c6][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
      for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
        for (c8 = 32 * c0 + 1; c8 <= min(N1, 32 * c0 + 32); c8 += 1)
          y[c6][lx1][c8]=x2[c6][lx1][c8];
}

}

void comp4(float y[DIM1][6][DIM2], float x1[DIM1][DIM3][DIM2], float x2[DIM1][DIM3][DIM2], float map2[DIM3], float map4[DIM3]) {
int lx1= 0, c0, c2, c4, c6, c8, c10;
for (c0 = 0; c0 <= floord(N1 - 1, 4); c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 4); c2 += 1)
    for (c6 = 4 * c2 + 1; c6 <= min(N2, 4 * c2 + 4); c6 += 1)
      for (c8 = 4 * c0 + 1; c8 <= min(N1, 4 * c0 + 4); c8 += 1) {
        y[c6][1][c8]=x1[c6][1][c8];
        y[c6][2][c8]=0;
      }
  for (c2 = 0; c2 <= floord(N2 - 1, 4); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 4); c4 += 1)
      for (c6 = 4 * c4 + 1; c6 <= min(N3, 4 * c4 + 4); c6 += 1)
        for (c8 = 4 * c2 + 1; c8 <= min(N2, 4 * c2 + 4); c8 += 1)
          for (c10 = 4 * c0 + 1; c10 <= min(N1, 4 * c0 + 4); c10 += 1)
            y[c8][2][c10]=y[c8][2][c10]+map2[c6]*x1[c8][c6][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 4); c2 += 1)
      for (c6 = 4 * c2 + 1; c6 <= min(N2, 4 * c2 + 4); c6 += 1)
        for (c8 = 4 * c0 + 1; c8 <= min(N1, 4 * c0 + 4); c8 += 1) {
          y[c6][3][c8]=x1[c6][lx1][c8];
          y[c6][4][c8]=0;
        }
  for (c2 = 0; c2 <= floord(N2 - 1, 4); c2 += 1)
    for (c4 = 0; c4 <= floord(N4 - 1, 4); c4 += 1)
      for (c6 = 4 * c4 + 1; c6 <= min(N4, 4 * c4 + 4); c6 += 1)
        for (c8 = 4 * c2 + 1; c8 <= min(N2, 4 * c2 + 4); c8 += 1)
          for (c10 = 4 * c0 + 1; c10 <= min(N1, 4 * c0 + 4); c10 += 1)
            y[c8][4][c10]=y[c8][4][c10]+map4[c6]*x2[c8][c6][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 4); c2 += 1)
      for (c6 = 4 * c2 + 1; c6 <= min(N2, 4 * c2 + 4); c6 += 1)
        for (c8 = 4 * c0 + 1; c8 <= min(N1, 4 * c0 + 4); c8 += 1)
          y[c6][lx1][c8]=x2[c6][lx1][c8];
}



}


void comp(float y[DIM1][6][DIM2], float x1[DIM1][DIM3][DIM2], float x2[DIM1][DIM3][DIM2], float map2[DIM3], float map4[DIM3]) {
int lx1= 0, c0, c2, c4, c6, c8, c10;

int UB = floord(N1 - 1, 16);


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

#pragma omp parallel for
for (c0 = 0; c0 <= UB; c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
      for (c8 = 16 * c0 + 1; c8 <= min(N1, 16 * c0 + 16); c8 += 1) {
        y[c6][1][c8]=x1[c6][1][c8];
        y[c6][2][c8]=0;
      }
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c6 = 16 * c4 + 1; c6 <= min(N3, 16 * c4 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1)
            y[c8][2][c10]=y[c8][2][c10]+map2[c6]*x1[c8][c6][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
        for (c8 = 16 * c0 + 1; c8 <= min(N1, 16 * c0 + 16); c8 += 1) {
          y[c6][3][c8]=x1[c6][lx1][c8];
          y[c6][4][c8]=0;
        }
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
      for (c6 = 16 * c4 + 1; c6 <= min(N4, 16 * c4 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1)
            y[c8][4][c10]=y[c8][4][c10]+map4[c6]*x2[c8][c6][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
        for (c8 = 16 * c0 + 1; c8 <= min(N1, 16 * c0 + 16); c8 += 1)
          y[c6][lx1][c8]=x2[c6][lx1][c8];
}



#pragma omp parallel for
for (c0 = 1; c0 <= N1; c0 += 1)
  for (c1 = 1; c1 <= N2; c1 += 1) {
    if (lx1 == 1 && c0 >= 1 && N1 >= c0 && c1 >= 1 && N2 >= c1) {
      y[c1][1][c0]=x1[c1][1][c0];
      y[c1][lx1][c0]=x2[c1][lx1][c0];
    }

      if (c0 >= 1 && N1 >= c0 && c1 >= 1 && N2 >= c1 && N3 >= 1) {
        y[c1][2][c0]=0;
        for (c4 = 1; c4 <= N3; c4 += 1)
          y[c1][2][c0]=y[c1][2][c0]+map2[c4]*x1[c1][c4][c0];
        if (lx1 == 2)
          y[c1][lx1][c0]=x2[c1][lx1][c0];
      } else if (lx1 == 2 && N3 <= 0 && c1 >= 1 && N2 >= c1 && c0 >= 1 && N1 >= c0) {
        y[c1][2][c0]=0;
        y[c1][lx1][c0]=x2[c1][lx1][c0];
      }


    if (lx1 == 3 && c0 >= 1 && N1 >= c0 && c1 >= 1 && N2 >= c1) {
      y[c1][3][c0]=x1[c1][lx1][c0];
      y[c1][lx1][c0]=x2[c1][lx1][c0];
    }

    if (c0 >= 1 && N1 >= c0 && c1 >= 1 && N2 >= c1 && N4 >= 1) {
          y[c1][4][c0]=0;
          for (c4 = 1; c4 <= N4; c4 += 1)
            y[c1][4][c0]=y[c1][4][c0]+map4[c4]*x2[c1][c4][c0];
          if (lx1 == 4)
            y[c1][lx1][c0]=x2[c1][lx1][c0];
        } else if (lx1 == 4 && N4 <= 0 && c1 >= 1 && N2 >= c1 && c0 >= 1 && N1 >= c0) {
          y[c1][4][c0]=0;
          y[c1][lx1][c0]=x2[c1][lx1][c0];
        }


    }
/*
#pragma omp parallel for
for(ix = 1; ix <= N2; ix++){
for(iz = 1; iz <= N1; iz++){
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




