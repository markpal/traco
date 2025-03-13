#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define MAX(x,y)    ((x) > (y)? (x) : (y))

int N = 500;

int can_pair(int *input, int a, int b){
   return ((((input[a] + input[b]) == 3) && (a < b - 1))) ? 1 : 0;
}

int main(int argc, char *argv[])
{
    int num_proc=1;
    num_proc = atoi(argv[1]);
    int kind;

    if(argc > 2)
        N = atoi(argv[2]);

    int DIM = 2*N+2;

    if(argc > 3)
        kind = atoi(argv[3]);

    int i,j,k;
    double start, end;


    float (*S)[DIM];
    S = (float (*)[DIM])malloc(DIM * DIM * sizeof(float));
    int *RNA;
    RNA = (int (*))malloc(DIM * sizeof(float));

int z = 0;
    start = omp_get_wtime();

    for (i = 0; i <= N-1; i++) {
     for (j = N-i; j < N; j++) {
      for (k = 0; k < j-N+i+1; k++) {
     z++;//   z++; //S[N-i-1][j] = S[N-i-1][k+N-i-1] + S[k+N-i][j] + S[N-i-1][j];
      }
      for (k = 0; k <= 0; k++) {
  z++;   // S[N-i-1][j] = S[N-i-1][j] + S[N-i][j-1];
      }
     }
    }
	printf("%.6f\n%i\n", end - start,z) ;
	z=0;
int c1,c3,c4,c7,c9,c10,c11,c5;


for (c1 = 0; c1 <= floord(N - 1, 16); c1 += 1)
  for (c3 = 0; c3 <= min(floord(N - 2, 16), c1); c3 += 1) {
    for (c5 = 0; c5 <= c3; c5 += 1)
      for (c7 = max(16 * c1, 16 * c3 + 1); c7 <= min(N - 1, 16 * c1 + 15); c7 += 1)
        for (c11 = 16 * c5; c11 <= min(16 * c3, 16 * c5 + 15); c11 += 1)
   z++;//       S[N-c7-1][N+16*c3-c7]=S[N-c7-1][c11+N-c7-1]+S[c11+N-c7][N+16*c3-c7]+S[N-c7-1][N+16*c3-c7];
    for (c7 = max(16 * c3 + 1, 16 * c1); c7 <= min(N - 1, 16 * c1 + 30); c7 += 1)
      for (c9 = max(N - 16 * c1 + 16 * c3 - 15, N + 16 * c3 - c7); c9 <= min(N + 16 * c3 - c7 + 15, N - 1); c9 += 1)
        for (c10 = max(0, N + 16 * c3 - c7 - c9 + 1); c10 <= min(1, c1 - (-c1 + c7 + 14) / 15 + 2); c10 += 1)
          if (c10 == 1) {
       z++;//      S[N-c7-1][c9]=S[N-c7-1][c9]+S[N-c7][c9-1];
          } else {
            if (c7 + c9 == N + 1 && c3 == 0 && c7 >= 16 * c1 + 1)
         z++;//      S[N-c7-1][N-c7+1]=S[N-c7-1][0+N-c7-1]+S[0+N-c7][N-c7+1]+S[N-c7-1][N-c7+1];
            for (c11 = max(max(N + 16 * c3 - c7 - c9 + 2, 16 * c3), 16 * c1 + 16 * c3 - c7 + 1); c11 <= -N + c7 + c9; c11 += 1)
         z++;//      S[N-c7-1][c9]=S[N-c7-1][c11+N-c7-1]+S[c11+N-c7][c9]+S[N-c7-1][c9];
          }
  }
    end = omp_get_wtime();
	printf("%.6f\n%i\n", end - start,z) ;

    return 0;


}

