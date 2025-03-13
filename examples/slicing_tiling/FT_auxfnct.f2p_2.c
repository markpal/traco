//#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))
#include <omp.h>




int N = 500;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;

int tilesize;
int tool;



void seq(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int k, i, j;

for(i = 1; i <= N1; i++){
  for(k = 1; k <= N2; k++){
    for(j = 1; j <= N3; j++){
      y[j][k][i]=y[j][k][i]*twiddle[j][k][i];
      x[j][k][i]=y[j][k][i];
    }
  }
}
}



void comp_tile(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int k, i, j, i_tile, q;

if(tool == 0)
{
int c0,c1,c2,c3,c4,c5;

if(tilesize==0)
{
int ub = floord(N1 - 1, 16);
#pragma omp parallel for shared(ub,N2,N3,N1,x,y,twiddle) private(c0,c1,c2,c3,c4,c5)
for (c0 = 0; c0 <= ub; c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
      for (c3 = 16 * c1 + 1; c3 <= min(N2, 16 * c1 + 16); c3 += 1)
        for (c4 = 16 * c2 + 1; c4 <= min(N3, 16 * c2 + 16); c4 += 1)
          for (c5 = 16 * c0 + 1; c5 <= min(N1, 16 * c0 + 16); c5 += 1) {
            y[c4][c3][c5]=y[c4][c3][c5]*twiddle[c4][c3][c5];
            x[c4][c3][c5]=y[c4][c3][c5];
          }



}
else
{
 int ub = floord(N1 - 1, 32);
#pragma omp parallel for shared(ub)
for (c0 = 0; c0 <= ub; c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 32); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 32); c2 += 1)
      for (c3 = 32 * c1 + 1; c3 <= min(N2, 32 * c1 + 32); c3 += 1)
        for (c4 = 32 * c2 + 1; c4 <= min(N3, 32 * c2 + 32); c4 += 1)
          for (c5 = 32 * c0 + 1; c5 <= min(N1, 32 * c0 + 32); c5 += 1) {
            y[c4][c3][c5]=y[c4][c3][c5]*twiddle[c4][c3][c5];
            x[c4][c3][c5]=y[c4][c3][c5];
          }

 }

}

else
{

  int t1, t2, t3, t4, t5, t6, t7;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

if(tilesize==0)
{

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  lbp=0;
  ubp=floord(N1,16);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N2,16);t2++) {
      for (t3=0;t3<=floord(N3,16);t3++) {
        for (t4=max(1,16*t2);t4<=min(N2,16*t2+15);t4++) {
          for (t5=max(1,16*t3);t5<=min(N3,16*t3+15);t5++) {
            lbv=max(1,16*t1);
            ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
            for (t7=lbv;t7<=ubv;t7++) {
              y[t5][t4][t7]=y[t5][t4][t7]*twiddle[t5][t4][t7];;
            }
            lbv=max(1,16*t1);
            ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
            for (t7=lbv;t7<=ubv;t7++) {
              x[t5][t4][t7]=y[t5][t4][t7];;
            }
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


/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  lbp=0;
  ubp=floord(N1,32);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N2,32);t2++) {
      for (t3=0;t3<=floord(N3,32);t3++) {
        for (t4=max(1,32*t2);t4<=min(N2,32*t2+31);t4++) {
          for (t5=max(1,32*t3);t5<=min(N3,32*t3+31);t5++) {
            lbv=max(1,32*t1);
            ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t7=lbv;t7<=ubv;t7++) {
              y[t5][t4][t7]=y[t5][t4][t7]*twiddle[t5][t4][t7];;
            }
            lbv=max(1,32*t1);
            ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t7=lbv;t7<=ubv;t7++) {
              x[t5][t4][t7]=y[t5][t4][t7];;
            }
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

  N1 = N2 = N3 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  if(argc > 3)
     tilesize = atoi(argv[3]);

  if(argc > 4)
     tool = atoi(argv[4]);

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

  if(tool == 2)
    seq(x, y, twiddle);
  else
    comp_tile(x, y, twiddle);

  gettimeofday(&f1, NULL);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}


