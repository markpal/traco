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
int NY, NX;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int i,j,k, alpha=0;


   int n = N;
   int ny = n;
   int nx = n;

 #pragma acc data copyout(tmp[0:n],y[0:n]) copyin(A[0:n*n], x[0:n],n,ny,nx) private(i,j)
 {
  for (i = 0; i < NY; i++)
    y[i] = 0;
  for (i = 0; i < NX; i++)
    {
      tmp[i] = 0;
      for (j = 0; j < NY; j++)
	tmp[i] = tmp[i] + A[i][j] * x[j];
      for (j = 0; j < NY; j++)
	y[j] = y[j] + A[i][j] * tmp[i];
    }
 }

}







void comp(float A[DIM1][DIM2], float y[DIM1], float tmp[DIM1], float x[DIM1]) {
int c0,c2,c0_0,i;
/*{
  if (NY >= 1)
#pragma omp parallel for
    for (c0 = 0; c0 < NX; c0 += 1) {
      {
        if (NX >= c0 + 1 && NY >= c0 + 1)
          for (c0_0 = 0; c0_0 < c0; c0_0 += 1)
            y[c0_0]=0;
        if (c0 >= 0 && NX >= c0 + 1 && NY >= 1) {
          for (c2 = 0; c2 < NY; c2 += 1) {
            if (c2 == c0)
              y[c0]=0;
            tmp[c0]=0;
          }
          tmp[c0]=tmp[c0]+A[c0][-1]*x[-1];
          y[-1]=y[-1]+A[c0][-1]*tmp[c0];
        }
        if (NY >= c0 + 1 && c0 >= 0)
          for (c0_0 = c0 + 1; c0_0 < NX; c0_0 += 1)
            y[c0_0]=0;
      }

      if (c0 == 0)

        for (c0 = 0; c0 < NX; c0 += 1) {
          for (c2 = 0; c2 < NY; c2 += 1)
            tmp[c0]=tmp[c0]+A[c0][c2]*x[c2];
          for (c2 = 0; c2 < NY; c2 += 1)
            y[c2]=y[c2]+A[c0][c2]*tmp[c0];
        }

    }
  if (NX >= 1)
    for (c0 = NX; c0 < NY; c0 += 1)

      {
        if (NY >= c0 + 1) {
          for (c0_0 = 0; c0_0 < min(c0, NX); c0_0 += 1)
            y[c0_0]=0;
          if (NX >= 1 && c0 >= NX)
            y[-1]=y[-1]+A[c0][-1]*tmp[c0];
        }
        if (c0 >= 0 && NX >= c0 + 1 && NY >= 1) {
          for (c2 = 0; c2 < NY; c2 += 1) {
            if (c2 == c0)
              y[c0]=0;
            tmp[c0]=0;
          }
          y[-1]=y[-1]+A[c0][-1]*tmp[c0];
        }
        if (NY >= c0 + 1 && c0 >= 0)
          for (c0_0 = c0 + 1; c0_0 < NX; c0_0 += 1)
            y[c0_0]=0;
      }

}
*/
 #pragma acc data copyout(tmp[0:n],y[0:n]) copyin(A[0:n*n], x[0:n],n,ny,nx) private(i,j)
 {
#pragma acc kernels loop private(i)
  for (i = 0; i < NY; i++)
    y[i] = 0;
if (NY >= 1)
#pragma acc kernels loop private(c0,c2)
  for (c0 = 0; c0 < NX; c0 += 1) {
    if (c0 >= 0 && NX >= c0 + 1 && NY >= 1) {
      #pragma acc loop
      for (c2 = 0; c2 < NY; c2 += 1)
        tmp[c0]=0;
      tmp[c0]=tmp[c0]+A[c0][-1]*x[-1];
      y[-1]=y[-1]+A[c0][-1]*tmp[c0];
    }

    if (c0 == 0)
      #pragma acc loop
      for (c0 = 0; c0 < NX; c0 += 1) {
        #pragma acc loop
        for (c2 = 0; c2 < NY; c2 += 1)
          tmp[c0]=tmp[c0]+A[c0][c2]*x[c2];
        #pragma acc loop
        for (c2 = 0; c2 < NY; c2 += 1)
          y[c2]=y[c2]+A[c0][c2]*tmp[c0];
      }

  }

 }



}




int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NY = NX = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], *x, *y, *tmp;

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  x = (float (*))malloc(DIM1 * sizeof(float));
  y = (float (*))malloc(DIM1 * sizeof(float));
  tmp = (float (*))malloc(DIM1 * sizeof(float));




  printf("Ilosc procesorow: %i \n\n", tool_kind);
  omp_set_num_threads(tool_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,y,tmp,x);
  else if (tool_kind == 2){
          comp(A,y,tmp,x);
   }
       else{
          comp_pluto(A,y,tmp,x);

   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









