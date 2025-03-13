#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK, TSTEPS;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2]) {
int i,j,k,t, alpha=0;

#pragma scop
for (t=0; t<TSTEPS; t++) {
 for (i=1; i<N-1; i++) {
  for (j=1; j<N-1; j++) {
   if (i < N-1 && j < N-1) {
    B[i][j] = 0.2 * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);
   }
  }
 }
 for (i=1; i<N-1; i++) {
  for (j=1; j<N-1; j++) {
   A[i][j] = B[i][j];
   }
  }
}
#pragma endscop

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2]) {

int c0, c2, c3;
for (c0 = 0; c0 < 2 * TSTEPS; c0 += 1){
if(c0%2==1)
#pragma omp parallel
 for (c2 = 1; c2 < N - 1; c2 += 1)
  for (c3 = 1; c3 < N - 1; c3 += 1)
    B[c2][c3] = 0.2 * (A[c2][c3] + A[c2][c3-1] + A[c2][1+c3] + A[1+c2][c3] + A[c2-1][c3]);
else
#pragma omp parallel
   for (c2 = 1; c2 < N - 1; c2 += 1)
    for (c3 = 1; c3 < N - 1; c3 += 1)
      A[c2][c3] = B[c2][c3];
}

}

void comp_pluto(float A[DIM1][DIM2], float B[DIM1][DIM2]) {

  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N >= 3) && (TSTEPS >= 1)) {
  for (t3=1;t3<=N-2;t3++) {
    B[1][t3]=0.2*(A[1][t3]+A[1][t3-1]+A[1][1+t3]+A[1+1][t3]+A[1 -1][t3]);;
  }
  for (t1=2;t1<=min(N-2,3*TSTEPS-2);t1++) {
    if ((2*t1+1)%3 == 0) {
      for (t3=ceild(2*t1+1,3);t3<=floord(2*t1+3*N-8,3);t3++) {
        B[1][(-2*t1+3*t3+2)/3]=0.2*(A[1][(-2*t1+3*t3+2)/3]+A[1][(-2*t1+3*t3+2)/3 -1]+A[1][1+(-2*t1+3*t3+2)/3]+A[1+1][(-2*t1+3*t3+2)/3]+A[1 -1][(-2*t1+3*t3+2)/3]);;
      }
    }
    lbp=ceild(2*t1+2,3);
    ubp=t1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      B[-2*t1+3*t2][1]=0.2*(A[-2*t1+3*t2][1]+A[-2*t1+3*t2][1 -1]+A[-2*t1+3*t2][1+1]+A[1+-2*t1+3*t2][1]+A[-2*t1+3*t2-1][1]);;
      for (t3=2*t1-2*t2+2;t3<=2*t1-2*t2+N-2;t3++) {
        B[-2*t1+3*t2][-2*t1+2*t2+t3]=0.2*(A[-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2][-2*t1+2*t2+t3-1]+A[-2*t1+3*t2][1+-2*t1+2*t2+t3]+A[1+-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2-1][-2*t1+2*t2+t3]);;
        A[-2*t1+3*t2-1][-2*t1+2*t2+t3-1]=B[-2*t1+3*t2-1][-2*t1+2*t2+t3-1];;
      }
      A[-2*t1+3*t2-1][N-2]=B[-2*t1+3*t2-1][N-2];;
    }
  }
  if (N == 3) {
    for (t1=2;t1<=3*TSTEPS-2;t1++) {
      if ((2*t1+1)%3 == 0) {
        B[1][1]=0.2*(A[1][1]+A[1][1 -1]+A[1][1+1]+A[1+1][1]+A[1 -1][1]);;
      }
      if ((2*t1+2)%3 == 0) {
        A[1][1]=B[1][1];;
      }
    }
  }
  for (t1=3*TSTEPS-1;t1<=N-2;t1++) {
    lbp=t1-TSTEPS+1;
    ubp=t1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      B[-2*t1+3*t2][1]=0.2*(A[-2*t1+3*t2][1]+A[-2*t1+3*t2][1 -1]+A[-2*t1+3*t2][1+1]+A[1+-2*t1+3*t2][1]+A[-2*t1+3*t2-1][1]);;
      for (t3=2*t1-2*t2+2;t3<=2*t1-2*t2+N-2;t3++) {
        B[-2*t1+3*t2][-2*t1+2*t2+t3]=0.2*(A[-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2][-2*t1+2*t2+t3-1]+A[-2*t1+3*t2][1+-2*t1+2*t2+t3]+A[1+-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2-1][-2*t1+2*t2+t3]);;
        A[-2*t1+3*t2-1][-2*t1+2*t2+t3-1]=B[-2*t1+3*t2-1][-2*t1+2*t2+t3-1];;
      }
      A[-2*t1+3*t2-1][N-2]=B[-2*t1+3*t2-1][N-2];;
    }
  }
  if (N >= 4) {
    for (t1=N-1;t1<=3*TSTEPS-2;t1++) {
      if ((2*t1+1)%3 == 0) {
        for (t3=ceild(2*t1+1,3);t3<=floord(2*t1+3*N-8,3);t3++) {
          B[1][(-2*t1+3*t3+2)/3]=0.2*(A[1][(-2*t1+3*t3+2)/3]+A[1][(-2*t1+3*t3+2)/3 -1]+A[1][1+(-2*t1+3*t3+2)/3]+A[1+1][(-2*t1+3*t3+2)/3]+A[1 -1][(-2*t1+3*t3+2)/3]);;
        }
      }
      lbp=ceild(2*t1+2,3);
      ubp=floord(2*t1+N-2,3);
#pragma omp parallel for private(lbv,ubv)
      for (t2=lbp;t2<=ubp;t2++) {
        B[-2*t1+3*t2][1]=0.2*(A[-2*t1+3*t2][1]+A[-2*t1+3*t2][1 -1]+A[-2*t1+3*t2][1+1]+A[1+-2*t1+3*t2][1]+A[-2*t1+3*t2-1][1]);;
        for (t3=2*t1-2*t2+2;t3<=2*t1-2*t2+N-2;t3++) {
          B[-2*t1+3*t2][-2*t1+2*t2+t3]=0.2*(A[-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2][-2*t1+2*t2+t3-1]+A[-2*t1+3*t2][1+-2*t1+2*t2+t3]+A[1+-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2-1][-2*t1+2*t2+t3]);;
          A[-2*t1+3*t2-1][-2*t1+2*t2+t3-1]=B[-2*t1+3*t2-1][-2*t1+2*t2+t3-1];;
        }
        A[-2*t1+3*t2-1][N-2]=B[-2*t1+3*t2-1][N-2];;
      }
      if ((2*t1+N+2)%3 == 0) {
        for (t3=ceild(2*t1-2*N+8,3);t3<=floord(2*t1+N-1,3);t3++) {
          A[N-2][(-2*t1+3*t3+2*N-5)/3]=B[N-2][(-2*t1+3*t3+2*N-5)/3];;
        }
      }
    }
  }
  for (t1=max(N-1,3*TSTEPS-1);t1<=3*TSTEPS+N-5;t1++) {
    lbp=t1-TSTEPS+1;
    ubp=floord(2*t1+N-2,3);
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      B[-2*t1+3*t2][1]=0.2*(A[-2*t1+3*t2][1]+A[-2*t1+3*t2][1 -1]+A[-2*t1+3*t2][1+1]+A[1+-2*t1+3*t2][1]+A[-2*t1+3*t2-1][1]);;
      for (t3=2*t1-2*t2+2;t3<=2*t1-2*t2+N-2;t3++) {
        B[-2*t1+3*t2][-2*t1+2*t2+t3]=0.2*(A[-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2][-2*t1+2*t2+t3-1]+A[-2*t1+3*t2][1+-2*t1+2*t2+t3]+A[1+-2*t1+3*t2][-2*t1+2*t2+t3]+A[-2*t1+3*t2-1][-2*t1+2*t2+t3]);;
        A[-2*t1+3*t2-1][-2*t1+2*t2+t3-1]=B[-2*t1+3*t2-1][-2*t1+2*t2+t3-1];;
      }
      A[-2*t1+3*t2-1][N-2]=B[-2*t1+3*t2-1][N-2];;
    }
    if ((2*t1+N+2)%3 == 0) {
      for (t3=ceild(2*t1-2*N+8,3);t3<=floord(2*t1+N-1,3);t3++) {
        A[N-2][(-2*t1+3*t3+2*N-5)/3]=B[N-2][(-2*t1+3*t3+2*N-5)/3];;
      }
    }
  }
  for (t3=2*TSTEPS;t3<=2*TSTEPS+N-3;t3++) {
    A[N-2][t3-2*TSTEPS+1]=B[N-2][t3-2*TSTEPS+1];;
  }
}
/* End of CLooG code */

}


int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);


  TSTEPS = N;

  TSTEPS = NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));



 // printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B);
  else if (tool_kind == 2){
         comp(A,B);
   }
       else{
          comp_pluto(A,B);
   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









