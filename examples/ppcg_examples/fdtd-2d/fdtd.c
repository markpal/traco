#include<sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK, TSTEPS;
int DIM1;
int DIM2;
int DIM3;





void seq(float ey[DIM1][DIM2], float ex[DIM1][DIM2], float hz[DIM1][DIM2]) {
int t,j,i;

    #pragma scop
	for (t=0; t<TSTEPS; t++) {
		for (j=0; j<NJ; j++) {
			ey[0][j] = t;
		}
		for (i=1; i<NI; i++) {
			for (j=0; j<NJ; j++) {
				ey[i][j] = ey[i][j] - 0.5*(hz[i][j] - hz[i-1][j]);
			}
		}
		for (i=0; i<NI; i++) {
			for (j=1; j<NJ; j++) {
				ex[i][j] = ex[i][j] - 0.5*(hz[i][j] - hz[i][j-1]);
			}
		}
		for (i=0; i<NI-1; i++) {
			for (j=0; j<NJ-1; j++) {
				hz[i][j] = hz[i][j] - 0.7*(ex[i][j+1] - ex[i][j] + ey[i+1][j] - ey[i][j]);
			}
		}
	}

   #pragma endscop

}



int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  TSTEPS = NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*ey)[DIM2], (*ex)[DIM2], (*hz)[DIM2];

  ey = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  ex = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  hz = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));


  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  gettimeofday(&s1, NULL);


    seq(ey,ex,hz);

  gettimeofday(&f1, NULL);

  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  printf("Czas: %2.3f seconds\n", duration);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









