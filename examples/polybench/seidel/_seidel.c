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
int T;
int DIM1;
int DIM2;
int DIM3;





void seq(float a[DIM1][DIM2]) {
int t,i,j;

#pragma scop
    for (t=0; t<=T-1; t++)  {
        for (i=1; i<=N-2; i++)  {
            for (j=1; j<=N-2; j++)  {
                a[i][j] = (a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] + a[i][j-1] + a[i][j] + a[i][j+1]+ a[i+1][j-1] + a[i+1][j] + a[i+1][j+1])/9.0;
            }
        }
    }
#pragma endscop

}







void comp(float a[DIM1][DIM2]) {
int c0,c1,c3;

if (N >= 4)
  for (c0 = 0; c0 < 3 * N + 2 * T - 10; c0 += 1)
#pragma omp parallel for
    for (c1 = max(0, -2 * N + (N + c0) / 2 + 5); c1 <= min(c0 / 2, T - 1); c1 += 1)
      for (c3 = max(-N - c1 + (N + c0) / 2 + 3, 1); c3 <= min(-c1 + c0 / 2 + 1, N - 2); c3 += 1)
        a[c3][c0-2*c1-2*c3+3]=(a[c3-1][c0-2*c1-2*c3+3-1]+a[c3-1][c0-2*c1-2*c3+3]+a[c3-1][c0-2*c1-2*c3+3+1]+a[c3][c0-2*c1-2*c3+3-1]+a[c3][c0-2*c1-2*c3+3]+a[c3][c0-2*c1-2*c3+3+1]+a[c3+1][c0-2*c1-2*c3+3-1]+a[c3+1][c0-2*c1-2*c3+3]+a[c3+1][c0-2*c1-2*c3+3+1])/9.0;

}

void comp_pluto(float a[DIM1][DIM2]) {
  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((N >= 3) && (T >= 1)) {
  for (t1=1;t1<=2*T+N-4;t1++) {
    lbp=max(ceild(t1+1,2),t1-T+1);
    ubp=min(floord(t1+N-2,2),t1);
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=t1+1;t3<=t1+N-2;t3++) {
        a[-t1+2*t2][-t1+t3]=(a[-t1+2*t2-1][-t1+t3-1]+a[-t1+2*t2-1][-t1+t3]+a[-t1+2*t2-1][-t1+t3+1]+a[-t1+2*t2][-t1+t3-1]+a[-t1+2*t2][-t1+t3]+a[-t1+2*t2][-t1+t3+1]+a[-t1+2*t2+1][-t1+t3-1]+a[-t1+2*t2+1][-t1+t3]+a[-t1+2*t2+1][-t1+t3+1])/9.0;;
      }
    }
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

  T = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A);
  else if (tool_kind == 2)
    comp(A);
    else
      comp_pluto(A);


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









