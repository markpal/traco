// See the Cormen book for details of the following algorithm
#include<stdio.h>
#include<limits.h>
#include <math.h>
#include <omp.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define ceild(n,d) ceil(((double)(n))/((double)(d)))


int N = 1500, DIM = 1502;
#include "mem.h"

#define pluto 2
#define pluto2 6
#define traco 3

int **points;

// A utility function to find distance between two points in a plane
double dist(int * p1, int * p2)
{
    return sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) +
                (p1[1] - p2[1])*(p1[1] - p2[1]));
}

// A utility function to find cost of a triangle. The cost is considered
// as perimeter (sum of lengths of all edges) of the triangle
double cost(int i, int j, int k)
{
    int* p1 = points[i];
    int* p2 = points[j];
    int *p3 = points[k];
    return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}




// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
double mcTDP(int kind)
{

    double** table = memd();


    int i, j, k, gap, q;

    /* m[i,j] = Minimum number of scalar multiplications needed
       to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where
       dimension of A[i] is p[i-1] x p[i] */

    double start = omp_get_wtime();


    // L is chain length.
    if(kind==-1){



    }


    if(kind==1){


   for (gap = 0; gap < N; gap++)
   {
      for (j = gap; j < N; j++)    // i = j - gap
      {
          if (gap < 2)
             table[j-gap][j] = 0.0;
          else
          {
              table[j-gap][j] = INT_MAX;
              for (k = j-gap+1; k < j; k++)
              {
                table[j-gap][j]  = MIN(table[j-gap][j], table[j-gap][k] + table[k][j] + cost(j-gap,j,k));

              }
          }
      }
   }
  }




    if(kind==pluto)  // sprawdzic bez maxfuse
    {
  int t1, t2, t3, t4, t5;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;


if (N >= 1) {
  for (t1=0;t1<=floord(N-1,8);t1++) {
    lbp=ceild(t1,2);
    ubp=min(floord(N-1,16),t1);
#pragma omp parallel for private(lbv,ubv,t3,t4,t5)
    for (t2=lbp;t2<=ubp;t2++) {
      if (t1 == t2) {
        for (t3=0;t3<=min(1,N-1);t3++) {
          for (t4=max(16*t1,t3);t4<=min(N-1,16*t1+15);t4++) {
            table[t4-t3][t4] = 0.0;;
          }
        }
      }
      for (t3=max(2,16*t1-16*t2);t3<=min(N-1,16*t1-16*t2+15);t3++) {
        for (t4=max(16*t2,t3);t4<=min(N-1,16*t2+15);t4++) {
          table[t4-t3][t4] = INT_MAX;
          for (t5=-t3+t4+1;t5<=t4-1;t5++) {
            table[t4-t3][t4] = MIN(table[t4-t3][t4], table[t4-t3][t5] + table[t5][t4] + cost(t4-t3,t4,t5));
          }
        }
      }
    }
  }
}


}


    if(kind==pluto2)  // sprawdzic bez maxfuse
    {
  int t1, t2, t3, t4, t5,t6;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

if (N >= 1) {
  lbp=0;
  ubp=floord(N-1,16);
#pragma omp parallel for private(lbv,ubv,t3,t4,t5,t6)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=t2;t3<=floord(N-1,16);t3++) {
      if (t2 == 0) {
        for (t4=0;t4<=min(1,N-1);t4++) {
          lbv=max(16*t3,t4);
          ubv=min(N-1,16*t3+15);
#pragma ivdep
#pragma vector always
          for (t5=lbv;t5<=ubv;t5++) {
            table[t5-t4][t5] = 0.0;;
          }
        }
      }
      for (t4=max(2,16*t2);t4<=min(N-1,16*t2+15);t4++) {
        lbv=max(16*t3,t4);
        ubv=min(N-1,16*t3+15);
#pragma ivdep
#pragma vector always
        for (t5=lbv;t5<=ubv;t5++) {
          table[t5-t4][t5] = INT_MAX;
        }
      }
    }
  }
  if (N >= 3) {
    for (t2=0;t2<=floord(N-1,8);t2++) {
      lbp=ceild(t2,2);
      ubp=min(floord(N-1,16),t2);
#pragma omp parallel for private(lbv,ubv,t4,t5,t6)
      for (t3=lbp;t3<=ubp;t3++) {
        for (t4=max(2,16*t2-16*t3);t4<=min(N-1,16*t2-16*t3+15);t4++) {
          for (t5=max(16*t3,t4);t5<=min(N-1,16*t3+15);t5++) {
            for (t6=-t4+t5+1;t6<=t5-1;t6++) {
              table[t5-t4][t5] = MIN(table[t5-t4][t5], table[t5-t4][t6] + table[t6][t5] + cost(t5-t4,t5,t6));
            }
          }
        }
      }
    }
  }
}



}


if(kind=traco)
{
 int c1,c3,c4,c5,c9,c11;

for( c1 = 0; c1 < N; c1 += 1)
  #pragma omp parallel for
  for( c3 = 0; c3 <= (N - c1 - 1) / 128; c3 += 1) {
    if (c1 >= 2) {
      for( c4 = 1; c4 <= 2; c4 += 1) {
        if (c4 == 2) {
          for( c5 = 0; c5 <= floord(c1 - 2, 16); c5 += 1)
            for( c9 = c1 + 128 * c3; c9 <= min(N - 1, c1 + 128 * c3 + 127); c9 += 1)
              for( c11 = -c1 + 16 * c5 + c9 + 1; c11 <= min(c9 - 1, -c1 + 16 * c5 + c9 + 16); c11 += 1)
                table[c9-c1][c9] = MIN(table[c9-c1][c9], table[c9-c1][c11] + table[c11][c9] + cost(c9-c1,c9,c11));
        } else
          for( c9 = c1 + 128 * c3; c9 <= min(N - 1, c1 + 128 * c3 + 127); c9 += 1)
            table[c9-c1][c9] = INT_MAX;
      }
    } else
      for( c9 = c1 + 128 * c3; c9 <= min(N - 1, c1 + 128 * c3 + 127); c9 += 1)
        table[c9-c1][c9] = 0.0;
  }




}




    double stop = omp_get_wtime();
    printf("%.4f\n",stop - start);

     return  table[0][N-1];
}

int main(int argc, char *argv[]){

    int num_proc=1, i;
    if(argc > 1)
        num_proc = atoi(argv[1]);

    omp_set_num_threads(num_proc);

    int kind=1;

    if(argc > 2)
        N = atoi(argv[2]);
    DIM = N+2;


    if(argc > 3)
        kind = atoi(argv[3]);



    points = (int **) malloc(DIM * sizeof(int*));

    for(i=0; i<DIM; i++)
        points[i] = (int *) malloc(2 * sizeof(int));



    mcTDP(kind);

    return 0;
}
