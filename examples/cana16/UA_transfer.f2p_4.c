#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 200;
int N1, N2, N3, DIM;
int DIM1;
int DIM2;





void seq(float tmp[DIM1][DIM2], float tmor[DIM1][DIM2], float qbnew[DIM1][DIM2][2], float temp[DIM1][DIM2]) {
int col, j, i;

for(col = 2; col <= N1; col++){
  tmor[1][col]=tmor[1][col]+temp[1][col];
  for(j = 1; j <= N2; j++){
    for(i = 2; i <= N3; i++){
      tmor[j][col] = tmor[j][col] + qbnew[i-1][j][1] *temp[i][col];
    }
  }
}
}


void comp(float tmp[DIM1][DIM2], float tmor[DIM1][DIM2], float qbnew[DIM1][DIM2][2], float temp[DIM1][DIM2]) {

int col, j, i;
int c0, c2,c4,c6,c8,c10;
int UB = floord(N1 - 2, 16);
#pragma omp parallel for
for (c0 = 0; c0 <= UB; c0 += 1) {
  for (c6 = 16 * c0 + 2; c6 <= min(16 * c0 + 17, N1); c6 += 1)
    tmor[1][c6]=tmor[1][c6]+temp[1][c6];
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 2, 16); c4 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(16 * c2 + 16, N2); c6 += 1)
        for (c8 = 16 * c4 + 2; c8 <= min(16 * c4 + 17, N3); c8 += 1)
          for (c10 = 16 * c0 + 2; c10 <= min(16 * c0 + 17, N1); c10 += 1)
            tmor[c6][c10]=tmor[c6][c10]+qbnew[c8-1][c6][1]*temp[c8][c10];

/*

#pragma omp parallel for
for (c0 = 0; c0 <= UB; c0 += 1) {
  for (c6 = 16 * c0 + 2; c6 <= min(16 * c0 + 17, N1); c6 += 1)
    tmor[1][c6]=tmor[1][c6]+temp[1][c6];
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 2, 16); c4 += 1)
      for (c6 = 16 * c0 + 2; c6 <= min(16 * c0 + 17, N1); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(16 * c2 + 16, N2); c8 += 1)
          for (c10 = 16 * c4 + 2; c10 <= min(16 * c4 + 17, N3); c10 += 1)
            tmor[c8][c6]=tmor[c8][c6]+qbnew[c10-1][c8][1]*temp[c10][c6];
}
/*
for(col = 2; col <= N1; col++){
  tmor[1][col]=tmor[1][col]+temp[1][col];
  for(j = 1; j <= N2; j++){
    for(i = 2; i <= N3; i++){
      tmor[j][col] = tmor[j][col] + qbnew[i-1][j][1] *temp[i][col];
    }
  }
}
*/
}
}




int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  DIM = N1 = N2 = N3 = DIM1 = DIM2 = N;

  float (*tmp)[DIM2], (*tmor)[DIM2], (*qbnew)[DIM2][2], (*temp)[DIM2];
  tmp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  tmor = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  temp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  qbnew = (float (*)[DIM2][2])malloc(DIM1 * DIM2 * 2 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  if(num_proc==1)
    seq(tmp, tmor, qbnew, temp);
  else
   comp(tmp, tmor, qbnew, temp);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas sekwencyjny: %2.3f seconds\n", duration);


}


/*

#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1) {
  for (c6 = 16 * c0 + 2; c6 <= min(16 * c0 + 17, N1); c6 += 1)
    tmor[1][c6]=tmor[1][c6]+temp[1][c6];
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 2, 16); c4 += 1)
      for (c6 = 16 * c0 + 2; c6 <= min(16 * c0 + 17, N1); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(16 * c2 + 16, N2); c8 += 1)
          for (c10 = 16 * c4 + 2; c10 <= min(16 * c4 + 17, N3); c10 += 1)
            tmor[c8][c6]=tmor[c8][c6]+qbnew[c10-1][c8][1]*temp[c10][c6];
}



#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1) {
  for (c6 = 16 * c0 + 2; c6 <= min(16 * c0 + 17, N1); c6 += 1)
    tmor[1][c6]=tmor[1][c6]+temp[1][c6];
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 2, 16); c4 += 1)
      for (c6 = 16 * c2 + 1; c6 <= min(16 * c2 + 16, N2); c6 += 1)
        for (c8 = 16 * c4 + 2; c8 <= min(16 * c4 + 17, N3); c8 += 1)
          for (c10 = 16 * c0 + 2; c10 <= min(16 * c0 + 17, N1); c10 += 1)
            tmor[c6][c10]=tmor[c6][c10]+qbnew[c8-1][c6][1]*temp[c8][c10];
}

*/
