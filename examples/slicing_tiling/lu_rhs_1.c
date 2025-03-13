#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))
#include <omp.h>

int N = 100;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;


int tilesize;
int tool;



void seq(float rsd[6][DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3]) {
int tmp=0,k,i,j,z;

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      for(z = 1; z <= 5; z++){
        rsd[z][i][j][k] = - frct[z][i][j][k];
      }
      tmp = 1.0 / u[1][i][j][k];

      rho_i[i][j][k] = tmp;

      qs[i][j][k] = (u[2][i][j][k] * u[2][i][j][k] + u[3][i][j][k] * u[3][i][j][k] + u[4][i][j][k] * u[4][i][j][k])  * tmp * 0.5;
    }
  }
}

}




void comp(float rsd[6][DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3]) {
int tmp= 0, c0, c2, c4, c6, c8, c10, c12, c14;


if(tool == 0)
{


if(tilesize==0)
{
int ub = floord(N1 - 1, 16);
#pragma omp parallel for private(tmp)
for (c0 = 0; c0 <= ub; c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c8 = 16 * c0 + 1; c8 <= min(N1, 16 * c0 + 16); c8 += 1)
        for (c10 = 16 * c2 + 1; c10 <= min(N2, 16 * c2 + 16); c10 += 1)
          for (c12 = 16 * c4 + 1; c12 <= min(N3, 16 * c4 + 16); c12 += 1)
            for (c14 = 1; c14 <= 5; c14 += 1)
              rsd[c14][c12][c10][c8]=-frct[c14][c12][c10][c8];
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c8 = 16 * c0 + 1; c8 <= min(N1, 16 * c0 + 16); c8 += 1)
        for (c10 = 16 * c2 + 1; c10 <= min(N2, 16 * c2 + 16); c10 += 1)
          for (c12 = 16 * c4 + 1; c12 <= min(N3, 16 * c4 + 16); c12 += 1) {
            tmp=1.0/u[1][c12][c10][c8];
            rho_i[c12][c10][c8]=tmp;
            qs[c12][c10][c8]=(u[2][c12][c10][c8]*u[2][c12][c10][c8]+u[3][c12][c10][c8]*u[3][c12][c10][c8]+u[4][c12][c10][c8]*u[4][c12][c10][c8])*tmp*0.5;
          }
}
}
else
{
int ub = floord(N1 - 1, 32);
#pragma omp parallel for private(tmp)
for (c0 = 0; c0 <= ub; c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 32); c4 += 1)
      for (c8 = 32 * c0 + 1; c8 <= min(N1, 32 * c0 + 32); c8 += 1)
        for (c10 = 32 * c2 + 1; c10 <= min(N2, 32 * c2 + 32); c10 += 1)
          for (c12 = 32 * c4 + 1; c12 <= min(N3, 32 * c4 + 32); c12 += 1)
            for (c14 = 1; c14 <= 5; c14 += 1)
              rsd[c14][c12][c10][c8]=-frct[c14][c12][c10][c8];
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 32); c4 += 1)
      for (c8 = 32 * c0 + 1; c8 <= min(N1, 32 * c0 + 32); c8 += 1)
        for (c10 = 32 * c2 + 1; c10 <= min(N2, 32 * c2 + 32); c10 += 1)
          for (c12 = 32 * c4 + 1; c12 <= min(N3, 32 * c4 + 32); c12 += 1) {
            tmp=1.0/u[1][c12][c10][c8];
            rho_i[c12][c10][c8]=tmp;
            qs[c12][c10][c8]=(u[2][c12][c10][c8]*u[2][c12][c10][c8]+u[3][c12][c10][c8]*u[3][c12][c10][c8]+u[4][c12][c10][c8]*u[4][c12][c10][c8])*tmp*0.5;
          }
}

}
}
else{
if(tilesize==0)
{


  int t1, t2, t3, t4, t5, t6, t7, t8, tmp =0;

 register int lbv, ubv;


/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  for (t1=1;t1<=N1;t1++) {
    for (t2=1;t2<=N2;t2++) {
      for (t3=0;t3<=floord(N3,16);t3++) {
        for (t5=max(1,16*t3);t5<=min(N3,16*t3+15);t5++) {
          tmp=1.0/u[1][t5][t2][t1];;
          qs[t5][t2][t1]=(u[2][t5][t2][t1]*u[2][t5][t2][t1]+u[3][t5][t2][t1]*u[3][t5][t2][t1]+u[4][t5][t2][t1]*u[4][t5][t2][t1])*tmp*0.5;;
          rho_i[t5][t2][t1]=tmp;;
          lbv=1;
          ubv=5;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            rsd[t6][t5][t2][t1]=-frct[t6][t5][t2][t1];;
          }
        }
      }
    }
  }
}
/* End of CLooG code */

}
else
{
  int t1, t2, t3, t4, t5, t6, t7, t8;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  for (t1=1;t1<=N1;t1++) {
    for (t2=1;t2<=N2;t2++) {
      for (t3=0;t3<=floord(N3,32);t3++) {
        for (t5=max(1,32*t3);t5<=min(N3,32*t3+31);t5++) {
          tmp=1.0/u[1][t5][t2][t1];;
          qs[t5][t2][t1]=(u[2][t5][t2][t1]*u[2][t5][t2][t1]+u[3][t5][t2][t1]*u[3][t5][t2][t1]+u[4][t5][t2][t1]*u[4][t5][t2][t1])*tmp*0.5;;
          rho_i[t5][t2][t1]=tmp;;
          lbv=1;
          ubv=5;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            rsd[t6][t5][t2][t1]=-frct[t6][t5][t2][t1];;
          }
        }
      }
    }
  }
}
/* End of CLooG code */

}
}
}





int main(int argc, char *argv[]) {

  // number of processors
  int num_proc=1;
  num_proc = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  if(argc > 3)
     tilesize = atoi(argv[3]);

  if(argc > 4)
     tool = atoi(argv[4]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*rsd)[DIM1][DIM2][DIM3], (*frct)[DIM1][DIM2][DIM3], (*u)[DIM1][DIM2][DIM3], (*rho_i)[DIM2][DIM3], (*qs)[DIM2][DIM3];

  rsd = (float (*)[DIM1][DIM2][DIM3])malloc(6 * DIM1 * DIM2 * DIM3 * sizeof(float));
  frct = (float (*)[DIM1][DIM2][DIM3])malloc(6 * DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[DIM1][DIM2][DIM3])malloc(6 * DIM1 * DIM2 * DIM3 * sizeof(float));
  rho_i = (float (*)[DIM2][DIM3])malloc( DIM1 * DIM2 * DIM3 * sizeof(float));
  qs = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));

  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool== 2)
    seq(rsd, frct, u, rho_i, qs);
  else
     comp(rsd, frct, u, rho_i, qs);



   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}



