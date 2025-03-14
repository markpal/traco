#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

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


	t_start = rtclock();


#pragma scop
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++) {
            temp2d[i][j] = 0.0;
            for (k = 0; k < M; k++)
                temp2d[i][j] = temp2d[i][j] + block[i][k] * cos1[j][k];
        }

    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++) {
            sum2[i][j] = 0.0;
            for (k = 0; k < M; k++)
                sum2[i][j] = sum2[i][j] + cos1[i][k] * temp2d[k][j];
            block[i][j] = (sum2[i][j]);
        }
#pragma endscop

    t_end = rtclock();
    printf("%0.3lfs\n", t_end - t_start);


    return 0;
}
