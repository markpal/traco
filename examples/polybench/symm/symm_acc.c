// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 1024


float A[N][N];
float B[N][N];
float C[N][N];
float acc[N][N];

void seq() {
int i,j,k, alpha=0, beta=0;


    const int  n = N;
   int NI = N;
   int NJ = N;

 #pragma acc data copy(C[0:n*n], acc[0:n*n]) copyin(alpha, A[0:n*n], B[0:n*n], n, NI, NJ, alpha,beta) private(i,j,k)
 {
 if(NI > 3 && NJ > 3)
   for (i = 0; i < NI; i++)
    for (j = 0; j < NJ; j++)
      {
	acc[i][j] = 0;
	for (k = 0; k < j-1; k++)
	  {
	    C[k][j] += alpha * A[k][i] * B[i][j];
	    acc[i][j] += B[k][j] * A[k][i];
	  }
	C[i][j] = beta * C[i][j] + alpha * A[i][i] * B[i][j] + alpha * acc[i][j];
      }
 }



}





void comp(){

int c0,c1,c2,c4,alpha=0,beta=0;


   int NI = N;
   int NJ = N;


 #pragma acc data copy(C[0:n*n], acc[0:n*n]) copyin(alpha, A[0:n*n], B[0:n*n], n, NI, NJ, alpha,beta)
 {
if (NJ >= 4 && NI >= 4)
  #pragma acc kernerls loop private(c0,c1,c4)
  for (c0 = 0; c0 < NI; c0 += 1){
  #pragma acc loop
    for (c1 = 0; c1 < NJ; c1 += 1) {
      if (c1 >= 0 && NJ >= c1 + 1 && c0 >= 0 && NI >= c0 + 1 && NJ >= 4 && NI >= 4) {
        acc[c0][c1]=0;
        C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
      }

      if (c1 >= 2) {
        if (c1 >= 3)

          if (c0 >= 0 && NI >= 4 && c1 >= 3 && NJ >= c1 + 1 && NI >= c0 + 1)
           #pragma acc loop
            for (c4 = 0; c4 < c1 - 1; c4 += 1){
              acc[c0][c1]+=B[c4][c1]*A[c4][c0];
            }


        if (NI >= 4 && NJ >= c1 + 1 && c1 >= 2 && NI >= c0 + 1 && c0 >= 0 && NJ >= 4) {
          #pragma acc loop
          for (c4 = 0; c4 < c1 - 1; c4 += 1){
            acc[c0][c1]=0;
          }
          if (c1 >= c0 + 2)
            C[-1][c1]+=alpha*A[-1][c0]*B[c0][c1];
          acc[c0][c1]+=B[-1][c1]*A[-1][c0];
           #pragma acc loop
          for (c4 = 0; c4 < c1 - 1; c4 += 1){
            C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
           }
        }
      }
      }
    }
 }

}



int main(int argc, char *argv[]) {


   double start = omp_get_wtime();


 //   seq();

         comp();

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}









