#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define MAX(x,y)    ((x) > (y)? (x) : (y))

int N = 5000;

int can_pair(int *input, int a, int b){
   return ((((input[a] + input[b]) == 3) && (a < b - 1))) ? 1 : 0;
}

int main(int argc, char *argv[])
{
    /*int num_proc=1;
    num_proc = atoi(argv[1]);
    int kind;

    if(argc > 2)
        N = atoi(argv[2]);



    if(argc > 3)
        kind = atoi(argv[3]);
*/

    int DIM = 2*N+2;
    int i,j,k,c=0;
    double start, end;


    float (*S)[DIM];
    S = (float (*)[DIM])malloc(DIM * DIM * sizeof(float));
    int *RNA;
    RNA = (int (*))malloc(DIM * sizeof(float));


    start = omp_get_wtime();

    for (i = N-1; i >= 0; i--) {
     for (j = i+1; j < N; j++) {
      for (k = 0; k < j-i; k++) {
         S[i][j] = MAX(S[i][k+i] + S[k+i+1][j], S[i][j]); // s0
      }
      S[i][j] = MAX(S[i][j], S[i+1][j-1] +can_pair(RNA, i, j));
     }
    }

    end = omp_get_wtime();
	printf("%.6f\n%i", end - start,c);

    return 0;


}

