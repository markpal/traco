
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





void seq(float tmor[DIM1][DIM2], float qbnew[DIM1][DIM3][DIM2], float tmp[DIM1][DIM2]) {
int col, i, j;

for(col = 1; col <= N1; col++){
  i = 1;
  tmp[i][col]=tmor[i][col];
  for(i = 2; i <= N2; i++){
    for(j = 1; j <= N3; j++){
      tmp[i][col] = tmp[i][col] + qbnew[i-1][j][1]*tmor[j][col];
    }
  }
}




}

void comp32(float tmor[DIM1][DIM2], float qbnew[DIM1][DIM3][DIM2], float tmp[DIM1][DIM2]) {
int lx1= 0, c0, c2, c4, c6, c8, c10, i;
for (c0 = 0; c0 <= floord(N1 - 1, 32); c0 += 1) {
  for (c6 = 32 * c0 + 1; c6 <= min(N1, 32 * c0 + 32); c6 += 1) {
    i=1;
    tmp[i][c6]=tmor[i][c6];
  }
  for (c2 = 0; c2 <= floord(N2 - 2, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 32); c4 += 1)
      for (c6 = 32 * c4 + 1; c6 <= min(N3, 32 * c4 + 32); c6 += 1)
        for (c8 = 32 * c2 + 2; c8 <= min(N2, 32 * c2 + 33); c8 += 1)
          for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1)
            tmp[c8][c10]=tmp[c8][c10]+qbnew[c8-1][c6][1]*tmor[c6][c10];
}
}




void comp(float tmor[DIM1][DIM2], float qbnew[DIM1][DIM3][DIM2], float tmp[DIM1][DIM2]) {
int lx1= 0, c0, c2, c4, c6, c8, c10, i;

for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1) {
  for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1) {
    i=1;
    tmp[i][c6]=tmor[i][c6];
  }
  for (c2 = 0; c2 <= floord(N2 - 2, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c6 = 16 * c4 + 1; c6 <= min(N3, 16 * c4 + 16); c6 += 1)
        for (c8 = 16 * c2 + 2; c8 <= min(N2, 16 * c2 + 17); c8 += 1)
          for (c10 = 16 * c0 + 1; c10 <= min(N1, 16 * c0 + 16); c10 += 1)
            tmp[c8][c10]=tmp[c8][c10]+qbnew[c8-1][c6][1]*tmor[c6][c10];
}

}


void comp4(float tmor[DIM1][DIM2], float qbnew[DIM1][DIM3][DIM2], float tmp[DIM1][DIM2]) {
int lx1= 0, c0, c2, c4, c6, c8, c10, i;

for (c0 = 0; c0 <= floord(N1 - 1, 4); c0 += 1) {
  for (c6 = 4 * c0 + 1; c6 <= min(N1, 4 * c0 + 4); c6 += 1) {
    i=1;
    tmp[i][c6]=tmor[i][c6];
  }
  for (c2 = 0; c2 < floord(N2 + 2, 4); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 4); c4 += 1)
      for (c6 = 4 * c4 + 1; c6 <= min(N3, 4 * c4 + 4); c6 += 1)
        for (c8 = 4 * c2 + 2; c8 <= min(N2, 4 * c2 + 5); c8 += 1)
          for (c10 = 4 * c0 + 1; c10 <= min(N1, 4 * c0 + 4); c10 += 1)
            tmp[c8][c10]=tmp[c8][c10]+qbnew[c8-1][c6][1]*tmor[c6][c10];
}



}



void comp_pluto() {
/*
[Clan] Error: the input file is not a SCoP
	> A loop iterator was previously used as a parameter
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

  float (*tmor)[DIM2], (*tmp)[DIM2], (*qbnew)[DIM2][DIM3];

  tmor = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  tmp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  qbnew = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));


  printf("Ilosc procesorow: %i \n\n", tile_kind);
  omp_set_num_threads(tile_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tile_kind == 1)
    seq(tmor, qbnew, tmp);
  else if (tile_kind == 2)
         comp(tmor, qbnew, tmp);
       else
          comp_pluto();


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}



#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1) {
  if (N3 >= 2)
    for (c1 = 0; c1 <= floord(N2 - 2, 16); c1 += 1)
      if (c1 >= 0 && c0 >= 0 && N3 >= 2 && N2 >= 16 * c1 + 2) {
        for (c2 = 0; c2 <= (N3 - 1) / 16; c2 += 1)
          for (c3 = 16 * c0 + 1; c3 <= min(N1, 16 * c0 + 16); c3 += 1) {
            if (c2 == 0 && c1 == 0) {
              i=1;
              tmp[i][c3]=tmor[i][c3];
            }
            for (c4 = 16 * c1 + 2; c4 <= min(N2, 16 * c1 + 17); c4 += 1) {
              if (c2 == 0)
                tmp[c4][c3]=tmp[c4][c3]+qbnew[c4-1][1][1]*tmor[1][c3];
              for (c5 = max(16 * c2 + 1, 2); c5 <= min(N3, 16 * c2 + 16); c5 += 1)
                tmp[c4][c3]=tmp[c4][c3]+qbnew[c4-1][c5][1]*tmor[c5][c3];
            }
          }
      }
      }




