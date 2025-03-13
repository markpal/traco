#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#include<openacc.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float a[DIM1][DIM2]) {
int i,j,p;

#pragma acc data copyinout(a[0:n*n]) copyin(N) private(p,i,j)
{
    for (p=0; p<N; p++) {
        for (i=p+1; i<N; i++)   {
            a[p][i] = a[p][i]/a[p][p];
        }
        for(i=p+1; i<N; i++)    {
            for (j=p+1; j<N; j++)   {
                a[i][j] = a[i][j] - a[i][p]*a[p][j];
            }
        }
    }
}


}







void comp(float a[DIM1][DIM2]) {
int c0, c3, c5;
int i,j,p;
// rk aproximated only

/*
for (c0 = 0; c0 < 2 * N - 2; c0 += 1) {
  if (2 * floord(c0 - 1, 2) + 1 == c0) {
#pragma omp parallel for
    for (c3 = (c0 + 1) / 2; c3 < N; c3 += 1)
      for (c5 = (c0 + 1) / 2; c5 < N; c5 += 1)
        a[(c0-1)/2][c3]=a[(c0-1)/2][c3]/a[(c0-1)/2][(c0-1)/2];
  } else if (c0 == 0 && N >= 3) {
#pragma omp parallel for
    for (c3 = 1; c3 < N; c3 += 1) {
      a[c3][-1]=a[c3][-1]-a[c3][0]*a[0][-1];
      for (c5 = max(1, -c3 + 3); c5 < N; c5 += 1)
        a[c3][c5]=a[c3][c5]-a[c3][0]*a[0][c5];
    }
  } else if (c0 >= 2) {
#pragma omp parallel for
    for (c3 = (c0 + 2) / 2; c3 < N; c3 += 1)
      a[c3][-1]=a[c3][-1]-a[c3][c0/2]*a[c0/2][-1];
  } else
    a[1][-1]=a[1][-1]-a[1][0]*a[0][-1];
  if (c0 >= 1)
#pragma omp parallel for
    for (c3 = c0 + 1; c3 < N; c3 += 1)
      for (c5 = c0 + 1; c5 < N; c5 += 1)
        a[c3][c5]=a[c3][c5]-a[c3][c0]*a[c0][c5];
}
*/
#pragma acc data copyinout(a[0:n*n]) copyin(N,p)
{
    #pragma acc loop
    for (p=0; p<N; p++) {
#pragma acc kernels loop private(i)
        for (i=p+1; i<N; i++)   {
            a[p][i] = a[p][i]/a[p][p];
        }
#pragma acc kernels loop private(i,j)
        for(i=p+1; i<N; i++)    {
            #pragma acc loop
            for (j=p+1; j<N; j++)   {
                a[i][j] = a[i][j] - a[i][p]*a[p][j];
            }
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









