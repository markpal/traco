#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define TILE_SIZE 30

int N = 500;
int N1, N2, N3, DIM;
int DIM1;
int DIM2;





void seq(float wdtdr[DIM1][DIM2], float wxm1[DIM1], float dxm1[DIM1][DIM2]) {
int ip, j, i;

    for(i = 1; i <= N1; i++){
      for(j = 1; j <= N2; j++){
        for(ip = 1; ip <= N3; ip++){
          wdtdr[i][j] = wdtdr[i][j] + wxm1[ip]*dxm1[ip][i]*dxm1[ip][j];
        }
      }
    }
}


void comp(float wdtdr[DIM1][DIM2], float wxm1[DIM1], float dxm1[DIM1][DIM2]) {
int ip, j, i;

    #pragma omp parallel for private(i,j,ip)
    for(i = 1; i <= N1; i++){
      for(j = 1; j <= N2; j++){
        for(ip = 1; ip <= N3; ip++){
          wdtdr[i][j] = wdtdr[i][j] + wxm1[ip]*dxm1[ip][i]*dxm1[ip][j];
        }
      }
    }

}

void comp_tile(float wdtdr[DIM1][DIM2], float wxm1[DIM1], float dxm1[DIM1][DIM2]) {
int ip, j, i, i_tile,j_tile,ip_tile;

  int t1, t2, t3, t4, t5, t6;

 register int lbv, ubv, lbv2, ubv2;



int c0, c1, c2, c3, c4, c5;

for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
          for (c5 = 16 * c2 + 1; c5 <= min(N3, 16 * c2 + 16); c5 += 1)
      for (c3 = 16 * c0 + 1; c3 <= min(N1, 16 * c0 + 16); c3 += 1)
        for (c4 = 16 * c1 + 1; c4 <= min(N2, 16 * c1 + 16); c4 += 1)
            wdtdr[c3][c4]=wdtdr[c3][c4]+wxm1[c5]*dxm1[c5][c3]*dxm1[c5][c4];




}





int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  DIM = N1 = N2 = N3 = DIM1 = DIM2 = N;

  float (*dxm1)[DIM2], (*wxm1), (*wdtdr)[DIM2];
  wdtdr = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  wxm1 = (float (*))malloc(DIM1 * sizeof(float));
  dxm1 = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  if(num_proc==1)
    seq(wdtdr, wxm1, dxm1);
  else
    comp_tile(wdtdr, wxm1, dxm1);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas sekwencyjny: %2.3f seconds\n", duration);


}


