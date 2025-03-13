#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 7000;

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

int t1,t3,c3,c1;

omp_set_num_threads(1);
    start = omp_get_wtime();


for (t1 = 0; t1 < N - 1; t1 += 1)
  for (t3 = t1 + 1; t3 < N; t3 += 1) {
    if (N >= t3 + 1 && t3 >= t1 + 1 && t1 >= 0) {
      S[t1][t3] = max(S[t1][t3], S[t1+1][t3-1] +can_pair(RNA, t1, t3));
    }
    if (t1 >= 0) {
      #pragma omp parallel for
      for (c1 = t1; c1 <= min(min(t3 - 1, N - t3 + t1 - 1), t1 + 1); c1 += 1) {
        if (c1 == t1 + 1) {
          for (c3 = t3 + 1; c3 < N; c3 += 1) {
             S[t1+1][c3] = max(S[t1+1][t3-t1-1+t1+1] + S[t3-t1-1+t1+1+1][c3], S[t1+1][c3]);
          }
        } else
          S[t1][t3] = max(S[t1][0+t1] + S[0+t1+1][t3], S[t1][t3]);

      }
    }
    if (t1 == 0 && t3 >= 2)
      if (t3 >= 1 && N >= t3 + 1) {

           S[0][t3] = max(S[0][t3-1] + S[t3][t3], S[0][t3]); // s0

        if (t3 >= 2) {
          #pragma omp parallel for
          for (c3 = t3 + 1; c3 < N; c3 += 1) {
            S[0][c3]=S[0][t3-1+0]+S[t3-1+0+1][c3]+S[0][c3];
               S[0][c3] = max(S[0][t3-1] + S[t3][c3], S[0][c3]); // s0

          }
        }
      }
  }



    end = omp_get_wtime();
	printf("%.6f\n%i", end - start,c);

    return 0;


}

