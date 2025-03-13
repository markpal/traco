#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 200;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {
int k, iz, i, j;

#pragma scop
    for(k = 1; k <= N1; k++){
      for(iz = 1; iz <= N2; iz++){
        for(j = 1; j <= N3; j++){
          for(i = 1; i <= N4; i++){
            r[i][j][iz] = r[i][j][iz]+u[i][j][k]*wdtdr[k][iz];
          }
        }
      }
    }
#pragma endscop
}


void comp_traco(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {
int c0,c1,c2,c3,c4,c5,c6,c7;

for (c0 = 0; c0 <= floord(N1 - 1, 64); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 64); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 64); c2 += 1)
      for (c3 = 0; c3 <= floord(N4 - 1, 64); c3 += 1)
        for (c4 = 64 * c0 + 1; c4 <= min(N1, 64 * c0 + 64); c4 += 1)
          for (c5 = 64 * c2 + 1; c5 <= min(N3, 64 * c2 + 64); c5 += 1)
            for (c6 = 64 * c3 + 1; c6 <= min(N4, 64 * c3 + 64); c6 += 1)
              for (c7 = 64 * c1 + 1; c7 <= min(N2, 64 * c1 + 64); c7 += 1)
                r[c6][c5][c7]=r[c6][c5][c7]+u[c6][c5][c4]*wdtdr[c4][c7];

// issf loop.c --tiling3 --permute
}



void comp_pluto(float u[DIM1][DIM2][DIM3], float wdtdr[DIM1][DIM2], float r[DIM1][DIM2][DIM3]) {

  int t1, t2, t3, t4, t5, t6, t7, t8;

 register int lbv, ubv;

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1) && (N4 >= 1)) {
  for (t1=0;t1<=floord(N2,64);t1++) {
    for (t2=0;t2<=floord(N3,64);t2++) {
      for (t3=0;t3<=floord(N4,64);t3++) {
        for (t4=0;t4<=floord(N1,64);t4++) {
          for (t5=max(1,64*t2);t5<=min(N3,64*t2+63);t5++) {
            for (t6=max(1,64*t3);t6<=min(N4,64*t3+63);t6++) {
              for (t7=max(1,64*t4);t7<=min(N1,64*t4+63);t7++) {
                lbv=max(1,64*t1);
                ubv=min(N2,64*t1+63);
#pragma ivdep
#pragma vector always
                for (t8=lbv;t8<=ubv;t8++) {
                  r[t6][t5][t8]=r[t6][t5][t8]+u[t6][t5][t7]*wdtdr[t7][t8];;
                }
              }
            }
          }
        }
      }
    }
  }
}

/* End of CLooG code */

}




int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  int kind = atoi(argv[1]);

  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*u)[DIM2][DIM3], (*wdtdr)[DIM2], (*r)[DIM2][DIM3];
  wdtdr = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  r = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));

  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  //printf("Ilosc procesorow: %i \n\n", num_proc);
  //omp_set_num_threads(1);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);

  switch(kind)
  {
      case 1 : seq(u, wdtdr, r); break;
      case 2 : comp_traco(u, wdtdr, r); break;
      case 3 : comp_pluto(u, wdtdr, r); break;
  }


  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("%2.3f\n", duration);




}


