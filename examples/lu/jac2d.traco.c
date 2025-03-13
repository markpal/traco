#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <omp.h>
#include <assert.h>

#define N 200
#define T 100

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#pragma declarations
double a[N][N];
double b[N][N];
double a1[N][N];
double b1[N][N];

#pragma enddeclarations


#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif



void init_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            a[i][j] = ((double)j)/N;
            a1[i][j] = ((double)j)/N;
        }
    }
}


double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}
#define __PLACE_TO_INSERT_FORWARD_DECLARATIONS

int main(int argc, char *argv[])
{
    int t, i, j;
    double t_start, t_end;

    init_array();


#pragma scop
    for (t=0; t<T; t++) {
        for (i=2; i<N-1; i++) {
            for (j=2; j<N-1; j++) {
                b1[i][j]= 0.2*(a1[i][j]+a1[i][j-1]+a1[i][1+j]+a1[1+i][j]+a1[i-1][j]);
            }
        }
        for (i=2; i<N-1; i++) {
            for (j=2; j<N-1; j++)   {
                a1[i][j]=b1[i][j];
            }
        }
    }
#pragma endscop

int t1, c3, c5, t3, t5;
    t_start = rtclock();


  int num_proc=1;
  num_proc = atoi(argv[1]);



    omp_set_num_threads(num_proc);


if (N >= 4)
  for (t1 = 0; t1 < T; t1 += 1) {
    if (t1 >= 1) {
      if (N >= 4 && T >= t1 + 1 && t1 >= 0) {
        if (t1 >= 1) {
          #pragma omp parallel for
          for (c3 = 2; c3 < N - 1; c3 += 1) {
            if (c3 == 2) {
              b[2][2]=0.2*(a[2][2]+a[2][2-1]+a[2][1+2]+a[1+2][2]+a[2-1][2]);
            }
            for (c5 = max(2, -2 * c3 + 7); c5 < N - 1; c5 += 1) {
              b[c3][c5]=0.2*(a[c3][c5]+a[c3][c5-1]+a[c3][1+c5]+a[1+c3][c5]+a[c3-1][c5]);
            }
          }
          if (N == 4) {
            b[2][2]=0.2*(a[2][2]+a[2][2-1]+a[2][1+2]+a[1+2][2]+a[2-1][2]);
          }
        } else{
          b[2][2]=0.2*(a[2][2]+a[2][2-1]+a[2][1+2]+a[1+2][2]+a[2-1][2]);
       }
      }
    } else
      for (t3 = 2; t3 < N - 1; t3 += 1)
        for (t5 = 2; t5 < N - 1; t5 += 1)
          if (T >= 1 && t5 >= 2 && N >= t5 + 2 && t3 >= 2 && N >= t3 + 2) {
            b[t3][t5]=0.2*(a[t3][t5]+a[t3][t5-1]+a[t3][1+t5]+a[1+t3][t5]+a[t3-1][t5]);
          }
    if (T >= t1 + 1 && t1 >= 0) {
      #pragma omp parallel for
      for (c3 = 2; c3 < N - 1; c3 += 1) {
        for (c5 = 2; c5 < N - 1; c5 += 1) {
          a[c3][c5]=b[c3][c5];
        }
      }
    }
  }


for(i=0; i<N; i++)
for(j=0; j<N; j++)
if(!(isnan(a[i][j]) && isnan(a1[i][j]))){
 if(a[i][j] != a1[i][j]) {
   printf("Error %i %i %f %f\n", i, j, a[i][j], a1[i][j]);
   exit(0);
 }
 if(b[i][j] != b1[i][j]) {
   printf("Error %i %i %f %f\n", i, j, b[i][j], b1[i][j]);
   exit(0);
 }
}




    t_end = rtclock();
    printf("%0.6lfs\n", t_end - t_start);


    return 0;
}
