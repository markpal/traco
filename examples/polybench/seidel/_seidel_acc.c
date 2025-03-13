// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float a[N][N];




void seq() {
int t,i,j;
int n = N;
int T = N;

#pragma acc data copy(a[0:n*n]) copyin(n,T) private(t,i,j)
{
    for (t=0; t<=T-1; t++)  {
        for (i=1; i<=N-2; i++)  {
            for (j=1; j<=N-2; j++)  {
                a[i][j] = (a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] + a[i][j-1] + a[i][j] + a[i][j+1]+ a[i+1][j-1] + a[i+1][j] + a[i+1][j+1])/9.0;
            }
        }
    }
}

}







void comp() {
int c0,c1,c3;
int n = N;
int T = N;

#pragma acc data copyinout(A[0:n*n]) copyin(n,T,c0)
{
    if (N >= 4)
    #pragma acc loop
  for (c0 = 0; c0 < 3 * N + 2 * T - 10; c0 += 1){
#pragma acc kernels loop  private(c1,c3)
    for (c1 = max(0, -2 * N + (N + c0) / 2 + 5); c1 <= min(c0 / 2, T - 1); c1 += 1){
        #pragma acc loop
      for (c3 = max(-N - c1 + (N + c0) / 2 + 3, 1); c3 <= min(-c1 + c0 / 2 + 1, N - 2); c3 += 1){
        a[c3][c0-2*c1-2*c3+3]=(a[c3-1][c0-2*c1-2*c3+3-1]+a[c3-1][c0-2*c1-2*c3+3]+a[c3-1][c0-2*c1-2*c3+3+1]+a[c3][c0-2*c1-2*c3+3-1]+a[c3][c0-2*c1-2*c3+3]+a[c3][c0-2*c1-2*c3+3+1]+a[c3+1][c0-2*c1-2*c3+3-1]+a[c3+1][c0-2*c1-2*c3+3]+a[c3+1][c0-2*c1-2*c3+3+1])/9.0;
      }}}
}

}



int main(int argc, char *argv[]) {



  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();
   // seq();

    comp();

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









