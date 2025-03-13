#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 2000;

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
    int i,j,k,c=0;
    double start, end;

    int DIM = 2*N+2;
    float (*S)[DIM];
    S = (float (*)[DIM])malloc(DIM * DIM * sizeof(float));
    int *RNA;
    RNA = (int (*))malloc(DIM * sizeof(float));

int c1,c2,c3,c4,c5,c6,c7,c8,c9,c11,t2,t4,t5,t7,t9;


    start = omp_get_wtime();

if (N >= 2) {
  for (t2=ceild(-N-29,32);t2<=0;t2++) {
    for (t4=max(0,-t2-1);t4<=floord(N-1,32);t4++) {
      for (t5=max(max(32*t2,-N+2),-32*t4-30);t5<=min(0,32*t2+31);t5++) {
        for (t7=max(32*t4,-t5+1);t7<=min(N-1,32*t4+31);t7++) {
          for (t9=0;t9<=t5+t7-1;t9++) {
            S[-t5][t7] = max(S[-t5][t9+-t5] + S[t9+-t5+1][t7], S[-t5][t7]);;
          }
          S[-t5][t7] = max(S[-t5][t7], S[-t5+1][t7-1] +can_pair(RNA, -t5, t7));;
        }
      }
    }
  }
}



    end = omp_get_wtime();
	printf("%.6f\n%i", end - start,c);

    return 0;


}

