#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))
#include <omp.h>

int N = 200;
int N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, DIM;
int DIM1;
int DIM2;
int DIM3;


int tilesize;
int tool;


void seq(float u[DIM1][DIM3][DIM2], float z[DIM1][DIM3][DIM2]) {
int i1, i2, i3, d1=0, d2=0, d3=0, t1=0, t2=0, t3=0;

for(i3 = N1; i3 <= N2; i3++){
  for(i2 = N3; i2 <= N4; i2++){
    for(i1 = N5; i1 <= N6; i1++){
      u[2*i1-d1][2*i2-d2][2*i3-d3]=u[2*i1-d1][2*i2-d2][2*i3-d3] +z[i1][i2][i3];
    }
    for(i1 = 1; i1 <= N7; i1++){
      u[2*i1-t1][2*i2-d2][2*i3-d3]=u[2*i1-t1][2*i2-d2][2*i3-d3] +0.5*(z[i1+1][i2][i3]+z[i1][i2][i3]);
    }
  }
  for(i2 = 1; i2 <= N8; i2++){
    for(i1 = N9; i1 <= N10; i1++){
      u[2*i1-d1][2*i2-t2][2*i3-d3]=u[2*i1-d1][2*i2-t2][2*i3-d3] +0.5*(z[i1][i2+1][i3]+z[i1][i2][i3]);
    }
    for(i1 = 1; i1 <= N11; i1++){
      u[2*i1-t1][2*i2-t2][2*i3-d3]=u[2*i1-t1][2*i2-t2][2*i3-d3] +0.25*(z[i1+1][i2+1][i3]+z[i1+1][i2][i3] +z[i1][i2+1][i3]+z[i1][i2][i3]);
    }
  }
}

}

void comp(float u[DIM1][DIM3][DIM2], float z[DIM1][DIM3][DIM2]) {
int i1, i2, i3, d1=0, d2=0, d3=0, t1=0, t2=0, t3=0;
int c0, c2, c4, c6, c8, c10;

if(tool == 0){

 if(tilesize==0)
{
int ub = floord(-N1 + N2, 16);
register int lbv, ubv;
if (N8 >= 1 && N11 >= 1) {
#pragma omp parallel for private(lbv,ubv)
  for (c0 = 0; c0 <= ub; c0 += 1) {
    for (c2 = 0; c2 <= floord(N4 - N3, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N6 - N5, 16); c4 += 1)
        for (c6 = N3 + 16 * c2; c6 <= min(N4, N3 + 16 * c2 + 15); c6 += 1)
          for (c8 = N5 + 16 * c4; c8 <= min(N6, N5 + 16 * c4 + 15); c8 += 1){
          lbv = N1 + 16 * c0;
          ubv = min(N2, N1 + 16 * c0 + 15);
             for (c10 = lbv; c10 <= ubv; c10 += 1)
              u[2*c8-d1][2*c6-d2][2*c10-d3]=u[2*c8-d1][2*c6-d2][2*c10-d3]+z[c8][c6][c10];
          }
    for (c2 = 0; c2 <= floord(N4 - N3, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
        for (c6 = N3 + 16 * c2; c6 <= min(N4, N3 + 16 * c2 + 15); c6 += 1)
          for (c8 = 16 * c4 + 1; c8 <= min(N7, 16 * c4 + 16); c8 += 1){
          lbv = N1 + 16 * c0;
          ubv = min(N2, N1 + 16 * c0 + 15);
             for (c10 = lbv; c10 <= ubv; c10 += 1)
              u[2*c8-t1][2*c6-d2][2*c10-d3]=u[2*c8-t1][2*c6-d2][2*c10-d3]+0.5*(z[c8+1][c6][c10]+z[c8][c6][c10]);
}
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 16); c4 += 1)
        for (c6 = 16 * c2 + 1; c6 <= min(N8, 16 * c2 + 16); c6 += 1)
          for (c8 = N9 + 16 * c4; c8 <= min(N10, N9 + 16 * c4 + 15); c8 += 1){
          lbv = N1 + 16 * c0;
          ubv = min(N2, N1 + 16 * c0 + 15);
             for (c10 = lbv; c10 <= ubv; c10 += 1)


              u[2*c8-d1][2*c6-t2][2*c10-d3]=u[2*c8-d1][2*c6-t2][2*c10-d3]+0.5*(z[c8][c6+1][c10]+z[c8][c6][c10]);
}
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N11 - 1, 16); c4 += 1)
        for (c6 = 16 * c2 + 1; c6 <= min(N8, 16 * c2 + 16); c6 += 1)
          for (c8 = 16 * c4 + 1; c8 <= min(N11, 16 * c4 + 16); c8 += 1){
          lbv = N1 + 16 * c0;
          ubv = min(N2, N1 + 16 * c0 + 15);
             for (c10 = lbv; c10 <= ubv; c10 += 1)
              u[2*c8-t1][2*c6-t2][2*c10-d3]=u[2*c8-t1][2*c6-t2][2*c10-d3]+0.25*(z[c8+1][c6+1][c10]+z[c8+1][c6][c10]+z[c8][c6+1][c10]+z[c8][c6][c10]);
}

      for (c2 = (N8 - 1) / 16 + 1; c2 <= floord(-N3 + N4, 16); c2 += 1)
        for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
          for (c6 = N3 + 16 * c2; c6 <= min(N3 + 16 * c2 + 15, N4); c6 += 1)
            for (c8 = N5 + 16 * c4; c8 <= min(N6, N5 + 16 * c4 + 15); c8 += 1)
              for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
                u[2*c8-d1][2*c6-d2][2*c10-d3]=u[2*c8-d1][2*c6-d2][2*c10-d3]+z[c8][c6][c10];
        for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
          for (c6 = N3 + 16 * c2; c6 <= min(N3 + 16 * c2 + 15, N4); c6 += 1)
            for (c8 = 16 * c4 + 1; c8 <= min(N7, 16 * c4 + 16); c8 += 1)
              for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
                u[2*c8-t1][2*c6-d2][2*c10-d3]=u[2*c8-t1][2*c6-d2][2*c10-d3]+0.5*(z[c8+1][c6][c10]+z[c8][c6][c10]);
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 16); c4 += 1)
        for (c6 = 16 * c2 + 1; c6 <= min(N8, 16 * c2 + 16); c6 += 1)
          for (c8 = N9 + 16 * c4; c8 <= min(N10, N9 + 16 * c4 + 15); c8 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
              u[2*c8-d1][2*c6-t2][2*c10-d3]=u[2*c8-d1][2*c6-t2][2*c10-d3]+0.5*(z[c8][c6+1][c10]+z[c8][c6][c10]);
  }


  }
}

else
{
int ub = floord(-N1 + N2, 32);
register int lbv, ubv;
if (N8 >= 1 && N11 >= 1) {
#pragma omp parallel for private(lbv,ubv)
  for (c0 = 0; c0 <= ub; c0 += 1) {
    for (c2 = 0; c2 <= floord(N4 - N3, 32); c2 += 1)
      for (c4 = 0; c4 <= floord(N6 - N5, 32); c4 += 1)
        for (c6 = N3 + 32 * c2; c6 <= min(N4, N3 + 32 * c2 + 31); c6 += 1)
          for (c8 = N5 + 32 * c4; c8 <= min(N6, N5 + 32 * c4 + 31); c8 += 1){
lbv = N1 + 32 * c0;
ubv = min(N2, N1 + 32 * c0 + 31);
            for (c10 = lbv; c10 <= ubv; c10 += 1)
              u[2*c8-d1][2*c6-d2][2*c10-d3]=u[2*c8-d1][2*c6-d2][2*c10-d3]+z[c8][c6][c10];
}
    for (c2 = 0; c2 <= floord(N4 - N3, 32); c2 += 1)
      for (c4 = 0; c4 <= floord(N7 - 1, 32); c4 += 1)
        for (c6 = N3 + 32 * c2; c6 <= min(N4, N3 + 32 * c2 + 31); c6 += 1)
          for (c8 = 32 * c4 + 1; c8 <= min(N7, 32 * c4 + 32); c8 += 1){
lbv = N1 + 32 * c0;
ubv = min(N2, N1 + 32 * c0 + 31);
            for (c10 = lbv; c10 <= ubv; c10 += 1)
              u[2*c8-t1][2*c6-d2][2*c10-d3]=u[2*c8-t1][2*c6-d2][2*c10-d3]+0.5*(z[c8+1][c6][c10]+z[c8][c6][c10]);
}
    for (c2 = 0; c2 <= floord(N8 - 1, 32); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 32); c4 += 1)
        for (c6 = 32 * c2 + 1; c6 <= min(N8, 32 * c2 + 32); c6 += 1)
          for (c8 = N9 + 32 * c4; c8 <= min(N10, N9 + 32 * c4 + 31); c8 += 1){
lbv = N1 + 32 * c0;
ubv = min(N2, N1 + 32 * c0 + 31);
            for (c10 = lbv; c10 <= ubv; c10 += 1)
              u[2*c8-d1][2*c6-t2][2*c10-d3]=u[2*c8-d1][2*c6-t2][2*c10-d3]+0.5*(z[c8][c6+1][c10]+z[c8][c6][c10]);
}
    for (c2 = 0; c2 <= floord(N8 - 1, 32); c2 += 1)
      for (c4 = 0; c4 <= floord(N11 - 1, 32); c4 += 1)
        for (c6 = 32 * c2 + 1; c6 <= min(N8, 32 * c2 + 32); c6 += 1)
          for (c8 = 32 * c4 + 1; c8 <= min(N11, 32 * c4 + 32); c8 += 1){
lbv = N1 + 32 * c0;
ubv = min(N2, N1 + 32 * c0 + 31);
            for (c10 = lbv; c10 <= ubv; c10+= 1)
              u[2*c8-t1][2*c6-t2][2*c10-d3]=u[2*c8-t1][2*c6-t2][2*c10-d3]+0.25*(z[c8+1][c6+1][c10]+z[c8+1][c6][c10]+z[c8][c6+1][c10]+z[c8][c6][c10]);
}

     for (c2 = (N8 - 1) / 32 + 1; c2 <= floord(-N3 + N4, 32); c2 += 1)
        for (c4 = 0; c4 <= floord(-N5 + N6, 32); c4 += 1)
          for (c6 = N3 + 32 * c2; c6 <= min(N3 + 32 * c2 + 31, N4); c6 += 1)
            for (c8 = N5 + 32 * c4; c8 <= min(N6, N5 + 32 * c4 + 31); c8 += 1)
              for (c10 = N1 + 32 * c0; c10 <= min(N2, N1 + 32 * c0 + 31); c10 += 1)
                u[2*c8-d1][2*c6-d2][2*c10-d3]=u[2*c8-d1][2*c6-d2][2*c10-d3]+z[c8][c6][c10];
        for (c4 = 0; c4 <= floord(N7 - 1, 32); c4 += 1)
          for (c6 = N3 + 32 * c2; c6 <= min(N3 + 32 * c2 + 31, N4); c6 += 1)
            for (c8 = 32 * c4 + 1; c8 <= min(N7, 32 * c4 + 32); c8 += 1)
              for (c10 = N1 + 32 * c0; c10 <= min(N2, N1 + 32 * c0 + 31); c10 += 1)
                u[2*c8-t1][2*c6-d2][2*c10-d3]=u[2*c8-t1][2*c6-d2][2*c10-d3]+0.5*(z[c8+1][c6][c10]+z[c8][c6][c10]);
    for (c2 = 0; c2 <= floord(N8 - 1, 32); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 32); c4 += 1)
        for (c6 = 32 * c2 + 1; c6 <= min(N8, 32 * c2 + 32); c6 += 1)
          for (c8 = N9 + 32 * c4; c8 <= min(N10, N9 + 32 * c4 + 31); c8 += 1)
            for (c10 = N1 + 32 * c0; c10 <= min(N2, N1 + 32 * c0 + 31); c10 += 1)
              u[2*c8-d1][2*c6-t2][2*c10-d3]=u[2*c8-d1][2*c6-t2][2*c10-d3]+0.5*(z[c8][c6+1][c10]+z[c8][c6][c10]);



  }



}
}
}
else
{


if(tilesize==0)
{


  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N10 >= N9+1) && (N11 >= 2) && (N2 >= N1+1) && (N4 >= N3+1) && (N6 >= N5+1) && (N7 >= 2) && (N8 >= 2)) {
  lbp=ceild(N1-15,16);
  ubp=floord(N2,16);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t3=ceild(N3-15,16);t3<=floord(N4,16);t3++) {
      for (t6=ceild(N5-15,16);t6<=floord(N6,16);t6++) {
        for (t8=max(N3,16*t3);t8<=min(N4,16*t3+15);t8++) {
          for (t11=max(N5,16*t6);t11<=min(N6,16*t6+15);t11++) {
            lbv=max(N1,16*t1);
            ubv=min(N2,16*t1+15);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-d1][2*t8-d2][2*t12-d3]=u[2*t11-d1][2*t8-d2][2*t12-d3]+z[t11][t8][t12];;
            }
          }
        }
      }
      for (t6=0;t6<=floord(N7,16);t6++) {
        for (t8=max(N3,16*t3);t8<=min(N4,16*t3+15);t8++) {
          for (t11=max(1,16*t6);t11<=min(N7,16*t6+15);t11++) {
            lbv=max(N1,16*t1);
            ubv=min(N2,16*t1+15);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-t1][2*t8-d2][2*t12-d3]=u[2*t11-t1][2*t8-d2][2*t12-d3]+0.5*(z[t11+1][t8][t12]+z[t11][t8][t12]);;
            }
          }
        }
      }
    }
    for (t3=0;t3<=floord(N8,16);t3++) {
      for (t6=ceild(N9-15,16);t6<=floord(N10,16);t6++) {
        for (t8=max(1,16*t3);t8<=min(N8,16*t3+15);t8++) {
          for (t11=max(N9,16*t6);t11<=min(N10,16*t6+15);t11++) {
            lbv=max(N1,16*t1);
            ubv=min(N2,16*t1+15);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-d1][2*t8-t2][2*t12-d3]=u[2*t11-d1][2*t8-t2][2*t12-d3]+0.5*(z[t11][t8+1][t12]+z[t11][t8][t12]);;
            }
          }
        }
      }
      for (t6=0;t6<=floord(N11,16);t6++) {
        for (t8=max(1,16*t3);t8<=min(N8,16*t3+15);t8++) {
          for (t11=max(1,16*t6);t11<=min(N11,16*t6+15);t11++) {
            lbv=max(N1,16*t1);
            ubv=min(N2,16*t1+15);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-t1][2*t8-t2][2*t12-d3]=u[2*t11-t1][2*t8-t2][2*t12-d3]+0.25*(z[t11+1][t8+1][t12]+z[t11+1][t8][t12]+z[t11][t8+1][t12]+z[t11][t8][t12]);;
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
}
else{

  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N10 >= N9+1) && (N11 >= 2) && (N2 >= N1+1) && (N4 >= N3+1) && (N6 >= N5+1) && (N7 >= 2) && (N8 >= 2)) {
  lbp=ceild(N1-31,32);
  ubp=floord(N2,32);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t3=ceild(N3-31,32);t3<=floord(N4,32);t3++) {
      for (t6=ceild(N5-31,32);t6<=floord(N6,32);t6++) {
        for (t8=max(N3,32*t3);t8<=min(N4,32*t3+31);t8++) {
          for (t11=max(N5,32*t6);t11<=min(N6,32*t6+31);t11++) {
            lbv=max(N1,32*t1);
            ubv=min(N2,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-d1][2*t8-d2][2*t12-d3]=u[2*t11-d1][2*t8-d2][2*t12-d3]+z[t11][t8][t12];;
            }
          }
        }
      }
      for (t6=0;t6<=floord(N7,32);t6++) {
        for (t8=max(N3,32*t3);t8<=min(N4,32*t3+31);t8++) {
          for (t11=max(1,32*t6);t11<=min(N7,32*t6+31);t11++) {
            lbv=max(N1,32*t1);
            ubv=min(N2,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-t1][2*t8-d2][2*t12-d3]=u[2*t11-t1][2*t8-d2][2*t12-d3]+0.5*(z[t11+1][t8][t12]+z[t11][t8][t12]);;
            }
          }
        }
      }
    }
    for (t3=0;t3<=floord(N8,32);t3++) {
      for (t6=ceild(N9-31,32);t6<=floord(N10,32);t6++) {
        for (t8=max(1,32*t3);t8<=min(N8,32*t3+31);t8++) {
          for (t11=max(N9,32*t6);t11<=min(N10,32*t6+31);t11++) {
            lbv=max(N1,32*t1);
            ubv=min(N2,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-d1][2*t8-t2][2*t12-d3]=u[2*t11-d1][2*t8-t2][2*t12-d3]+0.5*(z[t11][t8+1][t12]+z[t11][t8][t12]);;
            }
          }
        }
      }
      for (t6=0;t6<=floord(N11,32);t6++) {
        for (t8=max(1,32*t3);t8<=min(N8,32*t3+31);t8++) {
          for (t11=max(1,32*t6);t11<=min(N11,32*t6+31);t11++) {
            lbv=max(N1,32*t1);
            ubv=min(N2,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t12=lbv;t12<=ubv;t12++) {
              u[2*t11-t1][2*t8-t2][2*t12-d3]=u[2*t11-t1][2*t8-t2][2*t12-d3]+0.25*(z[t11+1][t8+1][t12]+z[t11+1][t8][t12]+z[t11][t8+1][t12]+z[t11][t8][t12]);;
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

  if(argc > 3)
     tilesize = atoi(argv[3]);

  if(argc > 4)
     tool = atoi(argv[4]);

  N1 = N5 = N3 =N9 =  1;
  N2 = N4 =N6 = N7 = N8 = N10 = N11= N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*z)[DIM2][DIM3], (*u)[DIM2][DIM3];

  u = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 8 * sizeof(float));
  z = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));



  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool == 2)
    seq(u, z);
  else
    comp(u, z);



   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}
