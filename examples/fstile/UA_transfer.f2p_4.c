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
int c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c11;
/*
if (N2 >= 1)
  for (c0 = 0; c0 <= floord(N3 - 2, 16); c0 += 1)
#pragma omp parallel for
    for (c1 = 0; c1 <= (N1 - 2)/16; c1 += 1)
      if (c0 >= 1) {
        if (N2 >= 2) {
          for (c3 = 0; c3 <= (N2 - 1) / 16; c3 += 1)
            for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(16 * c3 + 16, N2); c9 += 1)
                for (c11 = 16 * c0 + 2; c11 <= min(N3, 16 * c0 + 17); c11 += 1)
                  tmor[c9][c7]=tmor[c9][c7]+qbnew[c11-1][c9][1]*temp[c11][c7];
        } else
          for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
            if (c0 >= 2) {
              for (c11 = 16 * c0 + 2; c11 <= min(N3, 16 * c0 + 17); c11 += 1)
                tmor[1][c7]=tmor[1][c7]+qbnew[c11-1][1][1]*temp[c11][c7];
            } else
              for (c11 = 18; c11 <= min(33, N3); c11 += 1)
                tmor[1][c7]=tmor[1][c7]+qbnew[c11-1][1][1]*temp[c11][c7];
      } else {
        for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
          tmor[1][c7]=tmor[1][c7]+temp[1][c7];
        if (N3 >= 3 && N2 >= 2)
          for (c3 = 0; c3 <= (N2 - 1) / 16; c3 += 1)
            for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(16 * c3 + 16, N2); c9 += 1)
                for (c11 = 2; c11 <= min(17, N3); c11 += 1)
                  tmor[c9][c7]=tmor[c9][c7]+qbnew[c11-1][c9][1]*temp[c11][c7];
      }
*/

if (N3 >= 18 && N1 >= 18)
  for (c0 = 0; c0 <= min((N1 - 2) / 16, (N3 - 2) / 16); c0 += 1)
    if (c0 >= 1) {
//#pragma omp parallel for
      for (c3 = 0; c3 <= min((N1 - 1) / 16, ((N2 - 1)/16)); c3 += 1)
        for (c5 = 0; c5 <= min(floord(N2 - 2, 16), (N3 - 2) / 16); c5 += 1)
          for (c7 = 16 * c3 + 1; c7 <= min(16 * c3 + 16, N2); c7 += 1)
            for (c9 = 16 * c5 + 2; c9 <= min(N3, 16 * c5 + 17); c9 += 1)
              for (c11 = 16 * c0 + 2; c11 <= min(16 * c0 + 17, N1); c11 += 1)
                tmor[c7][c11]=tmor[c7][c11]+qbnew[c9-1][c7][1]*temp[c9][c11];
    } else
//#pragma omp parallel for
      for (c3 = 0; c3 <= min(((N2 - 1)/16), (N1 - 1) / 16); c3 += 1)
        for (c5 = 0; c5 <= min((N3 - 2) / 16, floord(N2 - 2, 16)); c5 += 1)
          for (c7 = 16 * c3 + 1; c7 <= min(N2, 16 * c3 + 16); c7 += 1)
            for (c9 = 16 * c5 + 2; c9 <= min(16 * c5 + 17, N3); c9 += 1)
              for (c11 = 2; c11 <= 17; c11 += 1)
                tmor[c7][c11]=tmor[c7][c11]+qbnew[c9-1][c7][1]*temp[c9][c11];


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
