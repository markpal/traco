#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#define M 512
double cos1[M][M+13];
double temp2d[M][M+23];
double block[M][M+43];
double sum2[M][M];



void init_array()
{
    int i, j;

    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            cos1[i][j] = (1+(i*j)%1024)/2.0;
            block[i][j] = (1+(i*j)%1024)/2.0;
        }
    }
}


void print_array()
{
    int i, j;

    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            fprintf(stdout, "%lf ", block[i][j]);
            if (j%80 == 79) fprintf(stdout, "\n");
        }
        fprintf(stdout, "\n");
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
double t_start, t_end;

int main(int argc, char *argv[]) {

	int i, j, k, l, m, n, o, t;

	init_array();

	omp_set_num_threads(2);


	t_start = rtclock();

    int c0,c1,c2,c3,c4,c6,c8,c10;

#pragma omp parallel for
for (c0 = 0; c0 <= (M - 1)/ 16; c0 += 1)
  for (c1 = 0; c1 <= (M - 1) / 16; c1 += 1)
    for (c2 = 16 * c0; c2 <= min(M - 1, 16 * c0 + 15); c2 += 1)
      for (c3 = 16 * c1; c3 <= min(16 * c1 + 15, M - 1); c3 += 1) {
        temp2d[c2][c3]=0.0;
        sum2[c2][c3]=0.0;
      }
if (M >= 33)
#pragma omp parallel for
  for (c2 = 0; c2 <= (M - 1) / 16; c2 += 1)
    if (M >= 33 && c2 >= 0)
      for (c0 = 0; c0 <= (M - 1) / 16; c0 += 1)
        for (c4 = 0; c4 <= (M - 1) / 16; c4 += 1)
          for (c6 = 16 * c0; c6 <= min(M - 1, 16 * c0 + 15); c6 += 1)
            for (c8 = 16 * c2; c8 <= min(16 * c2 + 15, M - 1); c8 += 1)
              for (c10 = 16 * c4; c10 <= min(M - 1, 16 * c4 + 15); c10 += 1) {
                if (c10 == 0 && c4 == 0 && c6 >= 16) {
                  temp2d[c6][c8]=temp2d[c6][c8]+block[c6][0]*cos1[c8][0];
                } else if (c0 == 0)
                  temp2d[c6][c8]=temp2d[c6][c8]+block[c6][c10]*cos1[c8][c10];
                sum2[c6][c8]=sum2[c6][c8]+cos1[c6][c10]*temp2d[c10][c8];
              }
#pragma omp parallel for
for (c0 = 0; c0 <= (M - 1)/ 16; c0 += 1)
  for (c1 = 0; c1 <= (M - 1) / 16; c1 += 1)
    for (c2 = 16 * c0; c2 <= min(M - 1, 16 * c0 + 15); c2 += 1)
      for (c3 = 16 * c1; c3 <= min(16 * c1 + 15, M - 1); c3 += 1)
        block[c2][c3]=(sum2[c2][c3]);

    t_end = rtclock();
    printf("%0.3lfs\n", t_end - t_start);


    return 0;
}
