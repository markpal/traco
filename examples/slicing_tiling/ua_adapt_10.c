#include<omp.h>
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
int lx1= 0, c0, c2, c4, c6, c8, c10;


if(tool == 0)
{
int c0,c2,c6,c10,c8;

if(tilesize==0)
{
int ub = floord(N1 - 1, 16);
#pragma omp parallel for
for (c0 = 0; c0 <= ub; c0 += 1) {
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
}
else
{


int ub = floord(N1 - 1, 32);
#pragma omp parallel for
for (c0 = 0; c0 <= ub; c0 += 1) {
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
      for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1) {
        y[c6][1][c10]=x1[c6][1][c10];
        y[c6][2][c10]=0;
      }
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 32); c4 += 1)
      for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
        for (c8 = 32 * c4 + 1; c8 <= min(N3, 32 * c4 + 32); c8 += 1)
          for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1)
            y[c6][2][c10]=y[c6][2][c10]+map2[c8]*x1[c6][c8][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
      for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
        for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1) {
          y[c6][3][c10]=x1[c6][lx1][c10];
          y[c6][4][c10]=0;
        }
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N4 - 1, 32); c4 += 1)
      for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
        for (c8 = 32 * c4 + 1; c8 <= min(N4, 32 * c4 + 32); c8 += 1)
          for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1)
            y[c6][4][c10]=y[c6][4][c10]+map4[c8]*x2[c6][c8][c10];
  if (N3 >= 1)
    for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
      for (c6 = 32 * c2 + 1; c6 <= min(N2, 32 * c2 + 32); c6 += 1)
        for (c10 = 32 * c0 + 1; c10 <= min(N1, 32 * c0 + 32); c10 += 1)
          y[c6][lx1][c10]=x2[c6][lx1][c10];
}

}}

else{

if(tilesize==0)
{
  int t1, t2, t3, t4, t5, t6, t7, t8, t9;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1)) {
  lbp=0;
  ubp=floord(N1,16);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N2,16);t2++) {
      for (t5=max(1,16*t2);t5<=min(N2,16*t2+15);t5++) {
        lbv=max(1,16*t1);
        ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][4][t9]=0;;
        }
      }
      if (N4 >= 1) {
        for (t4=0;t4<=floord(N4,16);t4++) {
          for (t5=max(1,16*t2);t5<=min(N2,16*t2+15);t5++) {
            for (t7=max(1,16*t4);t7<=min(N4,16*t4+15);t7++) {
              lbv=max(1,16*t1);
              ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
              for (t9=lbv;t9<=ubv;t9++) {
                y[t5][4][t9]=y[t5][4][t9]+map4[t7]*x2[t5][t7][t9];;
              }
            }
          }
        }
      }
      for (t5=max(1,16*t2);t5<=min(N2,16*t2+15);t5++) {
        lbv=max(1,16*t1);
        ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][2][t9]=0;;
          y[t5][3][t9]=x1[t5][lx1][t9];;
        }
      }
      if (N3 >= 1) {
        for (t4=0;t4<=floord(N3,16);t4++) {
          for (t5=max(1,16*t2);t5<=min(N2,16*t2+15);t5++) {
            for (t7=max(1,16*t4);t7<=min(N3,16*t4+15);t7++) {
              lbv=max(1,16*t1);
              ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
              for (t9=lbv;t9<=ubv;t9++) {
                y[t5][2][t9]=y[t5][2][t9]+map2[t7]*x1[t5][t7][t9];;
              }
            }
          }
        }
      }
      for (t5=max(1,16*t2);t5<=min(N2,16*t2+15);t5++) {
        lbv=max(1,16*t1);
        ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][1][t9]=x1[t5][1][t9];;
        }
        lbv=max(1,16*t1);
        ubv=min(N1,16*t1+15);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][lx1][t9]=x2[t5][lx1][t9];;
        }
      }
    }
  }
}
/* End of CLooG code */

}

else
{
 int t1, t2, t3, t4, t5, t6, t7, t8, t9;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1)) {
  lbp=0;
  ubp=floord(N1,32);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N2,32);t2++) {
      for (t5=max(1,32*t2);t5<=min(N2,32*t2+31);t5++) {
        lbv=max(1,32*t1);
        ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][4][t9]=0;;
        }
      }
      if (N4 >= 1) {
        for (t4=0;t4<=floord(N4,32);t4++) {
          for (t5=max(1,32*t2);t5<=min(N2,32*t2+31);t5++) {
            for (t7=max(1,32*t4);t7<=min(N4,32*t4+31);t7++) {
              lbv=max(1,32*t1);
              ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
              for (t9=lbv;t9<=ubv;t9++) {
                y[t5][4][t9]=y[t5][4][t9]+map4[t7]*x2[t5][t7][t9];;
              }
            }
          }
        }
      }
      for (t5=max(1,32*t2);t5<=min(N2,32*t2+31);t5++) {
        lbv=max(1,32*t1);
        ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][2][t9]=0;;
          y[t5][3][t9]=x1[t5][lx1][t9];;
        }
      }
      if (N3 >= 1) {
        for (t4=0;t4<=floord(N3,32);t4++) {
          for (t5=max(1,32*t2);t5<=min(N2,32*t2+31);t5++) {
            for (t7=max(1,32*t4);t7<=min(N3,32*t4+31);t7++) {
              lbv=max(1,32*t1);
              ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
              for (t9=lbv;t9<=ubv;t9++) {
                y[t5][2][t9]=y[t5][2][t9]+map2[t7]*x1[t5][t7][t9];;
              }
            }
          }
        }
      }
      for (t5=max(1,32*t2);t5<=min(N2,32*t2+31);t5++) {
        lbv=max(1,32*t1);
        ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][1][t9]=x1[t5][1][t9];;
        }
        lbv=max(1,32*t1);
        ubv=min(N1,32*t1+31);
#pragma ivdep
#pragma vector always
        for (t9=lbv;t9<=ubv;t9++) {
          y[t5][lx1][t9]=x2[t5][lx1][t9];;
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

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  if(argc > 3)
     tilesize = atoi(argv[3]);

  if(argc > 4)
     tool = atoi(argv[4]);

  float (*y)[6][DIM2], (*x1)[DIM3][DIM2], (*x2)[DIM3][DIM2], *map2, *map4;

  y = (float (*)[6][DIM2])malloc(DIM1 * DIM2 * 6 * sizeof(float));
  x1 = (float (*)[DIM3][DIM2])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  x2 = (float (*)[DIM3][DIM2])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  map2 = (float (*))malloc(DIM3 * sizeof(float));
  map4 = (float (*))malloc(DIM3 * sizeof(float));



  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool == 2)
    seq(y, x1, x2, map2, map4);
  else
    comp(y, x1, x2, map2, map4);

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}



