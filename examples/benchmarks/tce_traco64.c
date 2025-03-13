#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


#include <assert.h>

#define N 55
double A[N][N][N][N];
double T1[N][N][N][N];
double T2[N][N][N][N];
double T3[N][N][N][N];
double B[N][N][N][N];
double C1[N][N];
double C2[N][N];
double C3[N][N];
double C4[N][N];
void init_array()
{
    int i,j,k,l;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                for (l=0; l<N; l++) {
                    A[i][j][k][l] = 1 + ((double)k)/N;
                }
            }
        }
    }
}

void init()
{
    init_array();
}

void print_array()
{
    int i, j, k, l;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                for (l=0; l<N; l++) {
                    fprintf(stdout, "%lf ", B[i][j][k][l]);
                }
            }
        }
    }

    fprintf(stdout, "\n");
}


void print_results()
{
    print_array();

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

int main()
{
    int a, q, r, s, p, b, c, d;

    init_array();

    t_start = rtclock();
    int c0, c2, c4, c6, c8, c10, c12, c14, c16, c18;

#pragma scop

#pragma omp parallel for
for (c0 = 0; c0 <= (N - 1) / 64; c0 += 1)
  for (c2 = 0; c2 <= (N - 1) / 64; c2 += 1)
    for (c4 = 0; c4 <= (N - 1) / 64; c4 += 1)
      for (c6 = 0; c6 <= (N - 1) / 64; c6 += 1)
        for (c8 = 0; c8 <= (N - 1) / 64; c8 += 1)
          for (c10 = 64 * c0; c10 <= min(N - 1, 64 * c0 + 63); c10 += 1)
            for (c12 = 64 * c2; c12 <= min(64 * c2 + 63, N - 1); c12 += 1)
              for (c14 = 64 * c4; c14 <= min(N - 1, 64 * c4 + 63); c14 += 1)
                for (c16 = 64 * c8; c16 <= min(N - 1, 64 * c8 + 63); c16 += 1)
                  for (c18 = 64 * c6; c18 <= min(64 * c6 + 63, N - 1); c18 += 1) {
                    T1[c10][c12][c14][c18]=T1[c10][c12][c14][c18]+A[c16][c12][c14][c18]*C4[c16][c10];
                    T2[c10][c12][c14][c18]=T2[c10][c12][c14][c18]+T1[c10][c16][c14][c18]*C3[c16][c12];
                    T3[c10][c12][c14][c18]=T3[c10][c12][c14][c18]+T2[c10][c12][c16][c18]*C2[c16][c14];
                    B[c10][c12][c14][c18]=B[c10][c12][c14][c18]+T3[c10][c12][c14][c16]*C1[c16][c18];
                  }
#pragma endscop

t_end = rtclock();
    printf("%0.3lfs\n", t_end - t_start);

    return 0;
}
