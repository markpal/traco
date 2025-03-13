#include<omp.h>
#include<stdio.h>
#include<openacc.h>


#define N 1024

float A[N][N];
float q[N];
float p[N];
float r[N];
float s[N];

/*



   int n = N;
   int ny = n;
   int nx = n;

 #pragma acc data copy(s[0:n],q[0:n]) copyin(A[0:n*n], r[0:n], p[0:n],n,ny,nx)
 {
  for (i = 0; i < ny; i++)
    s[i] = 0;
  for (i = 0; i < nx; i++)
  {
      q[i] = 0;
      for (j = 0; j < ny; j++)
      {
	     s[j] = s[j] + r[i] * A[i][j];
         q[i] = q[i] + A[i][j] * p[j];
      }
  }
 }
*/









int main(int argc, char *argv[]) {
int i,j,k, alpha=0, c0, c1, c2,t1,t2;


  double start = omp_get_wtime();

  const int n = N;
  int NY = n;
  int NX = n;

 #pragma acc data copy(s[0:n],q[0:n]) copyin(A[0:n*n], r[0:n], p[0:n],n,NY,NX)
 {

// SCC

  #pragma acc kernels loop
  for (i = 0; i < NY; i++){
    s[i] = 0;
  }


  #pragma acc kernels loop
  for(t2 = 0; t2 <= NY-1; t2++) {
       #pragma acc loop
      for(t1 = 0; t1 <= NX-1; t1++) {
        s[t2]=s[t2]+r[t1]*A[t1][t2];
      }
  }

// IND loop
#pragma acc kernels loop
for(t1 = 0; t1 <= NX-2; t1++) {
  q[t1]=0;
}
if (NX >= 1 && NY >= 1) {
  q[NX-1]=0;
}
if (NX == 1) {
     #pragma acc kernels loop
  for(t2 = 0; t2 <= NY-1; t2++) {
    s[t2]=s[t2]+r[0]*A[0][t2];
  }
}
if (NX >= 2 && NY <= 0) {
  q[NX-1]=0;
}
 #pragma acc kernels loop
for (c0 = 0; c0 < NX; c0 += 1) {
    #pragma acc loop
  for (c1 = 0; c1 < NY; c1 += 1) {
    q[c0]=q[c0]+A[c0][c1]*p[c1];
  }
}

 }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}









