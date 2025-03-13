#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

int N = 200;
int N1, N2, N3, DIM;
int DIM1;
int DIM2;





void seq(float tmp[DIM1][DIM2], float tmor[DIM1][DIM2], float qbnew[DIM1][DIM2][2]) {
int col, j, i;

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


void comp(float tmp[DIM1][DIM2], float tmor[DIM1][DIM2], float qbnew[DIM1][DIM2][2]) {
int col, j, i;

    #pragma omp parallel for private(i,j,col)
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




int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  DIM = N1 = N2 = N3 = DIM1 = DIM2 = N;

  float (*tmp)[DIM2], (*tmor)[DIM2], (*qbnew)[DIM2][2];
  tmp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  tmor = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  qbnew = (float (*)[DIM2][2])malloc(DIM1 * DIM2 * 2 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  if(num_proc==1)
    seq(tmp, tmor, qbnew);
  else
   comp(tmp, tmor, qbnew);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas sekwencyjny: %2.3f seconds\n", duration);


}
