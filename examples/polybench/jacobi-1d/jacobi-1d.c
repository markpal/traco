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
int TSTEPS;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1], float B[DIM1]) {
int i,t;

#pragma scop
  for (t = 0; t < TSTEPS; t++)
    {
      for (i = 1; i < N - 1; i++)
	B[i] = 0.33333 * (A[i-1] + A[i] + A[i + 1]);
      for (i = 1; i < N - 1; i++)
	A[i] = B[i];
    }
#pragma endscop

}







void comp(float A[DIM1], float B[DIM1]) {
int c0, c3;


for (c0 = 0; c0 < 2 * TSTEPS; c0 += 1)
  if (c0 % 2 == 0) {
#pragma omp parallel for
    for (c3 = 1; c3 < N - 1; c3 += 1)
      A[c3]=B[c3];
  } else
#pragma omp parallel for
    for (c3 = 1; c3 < N - 1; c3 += 1)
      B[c3]=0.33333*(A[c3-1]+A[c3]+A[c3+1]);



}

void comp_pluto(float A[DIM1], float B[DIM1]) {

  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N >= 3) && (TSTEPS >= 1)) {
  B[1]=0.33333*(A[1 -1]+A[1]+A[1 +1]);;
  for (t1=2;t1<=min(N-2,3*TSTEPS-2);t1++) {
    if ((2*t1+1)%3 == 0) {
      B[1]=0.33333*(A[1 -1]+A[1]+A[1 +1]);;
    }
    lbp=ceild(2*t1+2,3);
    ubp=t1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      B[-2*t1+3*t2]=0.33333*(A[-2*t1+3*t2-1]+A[-2*t1+3*t2]+A[-2*t1+3*t2+1]);;
      A[-2*t1+3*t2-1]=B[-2*t1+3*t2-1];;
    }
  }
  if (N == 3) {
    for (t1=2;t1<=3*TSTEPS-2;t1++) {
      if ((2*t1+1)%3 == 0) {
        B[1]=0.33333*(A[1 -1]+A[1]+A[1 +1]);;
      }
      if ((2*t1+2)%3 == 0) {
        A[1]=B[1];;
      }
    }
  }
  for (t1=3*TSTEPS-1;t1<=N-2;t1++) {
    lbp=t1-TSTEPS+1;
    ubp=t1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      B[-2*t1+3*t2]=0.33333*(A[-2*t1+3*t2-1]+A[-2*t1+3*t2]+A[-2*t1+3*t2+1]);;
      A[-2*t1+3*t2-1]=B[-2*t1+3*t2-1];;
    }
  }
  if (N >= 4) {
    for (t1=N-1;t1<=3*TSTEPS-2;t1++) {
      if ((2*t1+1)%3 == 0) {
        B[1]=0.33333*(A[1 -1]+A[1]+A[1 +1]);;
      }
      lbp=ceild(2*t1+2,3);
      ubp=floord(2*t1+N-2,3);
#pragma omp parallel for private(lbv,ubv)
      for (t2=lbp;t2<=ubp;t2++) {
        B[-2*t1+3*t2]=0.33333*(A[-2*t1+3*t2-1]+A[-2*t1+3*t2]+A[-2*t1+3*t2+1]);;
        A[-2*t1+3*t2-1]=B[-2*t1+3*t2-1];;
      }
      if ((2*t1+N+2)%3 == 0) {
        A[N-2]=B[N-2];;
      }
    }
  }
  for (t1=max(N-1,3*TSTEPS-1);t1<=3*TSTEPS+N-5;t1++) {
    lbp=t1-TSTEPS+1;
    ubp=floord(2*t1+N-2,3);
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      B[-2*t1+3*t2]=0.33333*(A[-2*t1+3*t2-1]+A[-2*t1+3*t2]+A[-2*t1+3*t2+1]);;
      A[-2*t1+3*t2-1]=B[-2*t1+3*t2-1];;
    }
    if ((2*t1+N+2)%3 == 0) {
      A[N-2]=B[N-2];;
    }
  }
  A[N-2]=B[N-2];;
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


  TSTEPS = N*10;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float *A, *B;

  A = (float (*))malloc(DIM1 * sizeof(float));
  B = (float (*))malloc(DIM1 * sizeof(float));


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









