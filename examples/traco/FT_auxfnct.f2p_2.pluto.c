#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define TILE_SIZE 20


int N = 200;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int k, i, j;




  int t1, t2, t3, t4, t5, t6, t7;

 register int lbv, ubv;

/* Start of CLooG code */
if ((N1 >= 1) && (N2 >= 1) && (N3 >= 1)) {
  for (t1=0;t1<=floord(N1,32);t1++) {
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




void comp_tile(float x[DIM1][DIM2][DIM3], float y[DIM1][DIM2][DIM3], float twiddle[DIM1][DIM2][DIM3]) {
int ii,jj,kk,c0,c1,c2;
for(ii= 1; ii<= N1; ii+=16){ 
for(kk= 1; kk<= N2; kk+=16){
for(jj= 1; jj<= N3; jj+=16){
for (c0 = ii; c0 <= min(N1, ii + 15); c0 += 1){  
  for (c1 = kk; c1 <= min(N2, kk + 15); c1 += 1)
    for (c2 = jj; c2 <= min(N3, jj + 15); c2 += 1) {
y[c2][c1][c0]=y[c2][c1][c0]*twiddle[c2][c1][c0];
x[c2][c1][c0]=y[c2][c1][c0];
    }
}}
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

  if(num_proc == 1)
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


