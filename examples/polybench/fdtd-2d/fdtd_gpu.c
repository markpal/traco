#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include<openacc.h>


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK, TSTEPS;
int DIM1;
int DIM2;
int DIM3;





void seq(float ey[DIM1][DIM2], float ex[DIM1][DIM2], float hz[DIM1][DIM2]) {
int t,j,i;
int n = N;
    #pragma acc data copyinout(ey[0:n*n],ex[0:n*n], hz[0:n*n]) copyin(NI,NJ,TSTEPS,t,i,j)
    {

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

    }


}







void comp(float ey[DIM1][DIM2], float ex[DIM1][DIM2], float hz[DIM1][DIM2]) {
int t,i,j;

    #pragma acc data copyinout(ey[0:n*n],ex[0:n*n], hz[0:n*n]) copyin(NI,NJ,TSTEPS,t,i,j)
{

#pragma acc loop
	for (t=0; t<TSTEPS; t++) {
#pragma acc kernels loop private(i,j)
		for (i=0; i<NJ; i++) {
			ey[0][i] = t;
		}

#pragma acc kernels loop private(i,j)
		for (i=1; i<NI; i++) {
		    #pragma acc loop
			for (j=0; j<NJ; j++) {
				ey[i][j] = ey[i][j] - 0.5*(hz[i][j] - hz[i-1][j]);
			}
		}

#pragma acc kernels loop private(i,j)
		for (i=0; i<NI; i++) {
		    #pragma acc loop
			for (j=1; j<NJ; j++) {
				ex[i][j] = ex[i][j] - 0.5*(hz[i][j] - hz[i][j-1]);
			}
		}

#pragma acc kernels loop private(i,j)
		for (i=0; i<NI-1; i++) {
		    #pragma acc loop
			for (j=0; j<NJ-1; j++) {
				hz[i][j] = hz[i][j] - 0.7*(ex[i][j+1] - ex[i][j] + ey[i+1][j] - ey[i][j]);
			}
		}

	}

}
}

void comp_pluto(float ey[DIM1][DIM2], float ex[DIM1][DIM2], float hz[DIM1][DIM2]) {



  int t1, t2, t3;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((NJ >= 1) && (TSTEPS >= 1)) {
  if ((NI >= 2) && (NJ >= 2)) {
    ey[0][0]=0;;
    for (t3=1;t3<=NJ-1;t3++) {
      ey[0][t3]=0;;
      ex[0][t3]=ex[0][t3]-0.5*(hz[0][t3]-hz[0][t3-1]);;
    }
  }
  if ((NI >= 2) && (NJ == 1)) {
    ey[0][0]=0;;
  }
  if ((NI == 1) && (NJ >= 2)) {
    for (t1=0;t1<=2*TSTEPS-2;t1++) {
      if (t1%2 == 0) {
        ey[0][0]=t1/2;;
        for (t3=ceild(t1+2,2);t3<=floord(t1+2*NJ-2,2);t3++) {
          ey[0][(-t1+2*t3)/2]=t1/2;;
          ex[0][(-t1+2*t3)/2]=ex[0][(-t1+2*t3)/2]-0.5*(hz[0][(-t1+2*t3)/2]-hz[0][(-t1+2*t3)/2 -1]);;
        }
      }
    }
  }
  if ((NI <= 0) && (NJ >= 2)) {
    for (t1=0;t1<=2*TSTEPS-2;t1++) {
      if (t1%2 == 0) {
        for (t3=ceild(t1,2);t3<=floord(t1+2*NJ-2,2);t3++) {
          ey[0][(-t1+2*t3)/2]=t1/2;;
        }
      }
    }
  }
  if ((NI <= 1) && (NJ == 1)) {
    for (t1=0;t1<=2*TSTEPS-2;t1++) {
      if (t1%2 == 0) {
        ey[0][0]=t1/2;;
      }
    }
  }
  if ((NI >= 2) && (NJ >= 2)) {
    for (t1=1;t1<=2*TSTEPS-2;t1++) {
      if (t1%2 == 0) {
        ey[0][0]=t1/2;;
        for (t3=ceild(t1+2,2);t3<=floord(t1+2*NJ-2,2);t3++) {
          ey[0][(-t1+2*t3)/2]=t1/2;;
          ex[0][(-t1+2*t3)/2]=ex[0][(-t1+2*t3)/2]-0.5*(hz[0][(-t1+2*t3)/2]-hz[0][(-t1+2*t3)/2 -1]);;
        }
      }
      lbp=ceild(t1+1,2);
      ubp=min(floord(t1+NI-1,2),t1);
#pragma omp parallel for private(lbv,ubv)
      for (t2=lbp;t2<=ubp;t2++) {
        ey[-t1+2*t2][0]=ey[-t1+2*t2][0]-0.5*(hz[-t1+2*t2][0]-hz[-t1+2*t2-1][0]);;
        for (t3=t1-t2+1;t3<=t1-t2+NJ-1;t3++) {
          ey[-t1+2*t2][-t1+t2+t3]=ey[-t1+2*t2][-t1+t2+t3]-0.5*(hz[-t1+2*t2][-t1+t2+t3]-hz[-t1+2*t2-1][-t1+t2+t3]);;
          ex[-t1+2*t2][-t1+t2+t3]=ex[-t1+2*t2][-t1+t2+t3]-0.5*(hz[-t1+2*t2][-t1+t2+t3]-hz[-t1+2*t2][-t1+t2+t3-1]);;
          hz[-t1+2*t2-1][-t1+t2+t3-1]=hz[-t1+2*t2-1][-t1+t2+t3-1]-0.7*(ex[-t1+2*t2-1][-t1+t2+t3-1 +1]-ex[-t1+2*t2-1][-t1+t2+t3-1]+ey[-t1+2*t2-1 +1][-t1+t2+t3-1]-ey[-t1+2*t2-1][-t1+t2+t3-1]);;
        }
      }
    }
  }
  if ((NI >= 2) && (NJ == 1)) {
    for (t1=1;t1<=2*TSTEPS-2;t1++) {
      if (t1%2 == 0) {
        ey[0][0]=t1/2;;
      }
      lbp=ceild(t1+1,2);
      ubp=min(floord(t1+NI-1,2),t1);
#pragma omp parallel for private(lbv,ubv)
      for (t2=lbp;t2<=ubp;t2++) {
        ey[-t1+2*t2][0]=ey[-t1+2*t2][0]-0.5*(hz[-t1+2*t2][0]-hz[-t1+2*t2-1][0]);;
      }
    }
  }
  if (NJ >= 2) {
    for (t1=2*TSTEPS-1;t1<=2*TSTEPS+NI-3;t1++) {
      lbp=t1-TSTEPS+1;
      ubp=min(floord(t1+NI-1,2),t1);
#pragma omp parallel for private(lbv,ubv)
      for (t2=lbp;t2<=ubp;t2++) {
        ey[-t1+2*t2][0]=ey[-t1+2*t2][0]-0.5*(hz[-t1+2*t2][0]-hz[-t1+2*t2-1][0]);;
        for (t3=t1-t2+1;t3<=t1-t2+NJ-1;t3++) {
          ey[-t1+2*t2][-t1+t2+t3]=ey[-t1+2*t2][-t1+t2+t3]-0.5*(hz[-t1+2*t2][-t1+t2+t3]-hz[-t1+2*t2-1][-t1+t2+t3]);;
          ex[-t1+2*t2][-t1+t2+t3]=ex[-t1+2*t2][-t1+t2+t3]-0.5*(hz[-t1+2*t2][-t1+t2+t3]-hz[-t1+2*t2][-t1+t2+t3-1]);;
          hz[-t1+2*t2-1][-t1+t2+t3-1]=hz[-t1+2*t2-1][-t1+t2+t3-1]-0.7*(ex[-t1+2*t2-1][-t1+t2+t3-1 +1]-ex[-t1+2*t2-1][-t1+t2+t3-1]+ey[-t1+2*t2-1 +1][-t1+t2+t3-1]-ey[-t1+2*t2-1][-t1+t2+t3-1]);;
        }
      }
    }
  }
  if (NJ == 1) {
    for (t1=2*TSTEPS-1;t1<=2*TSTEPS+NI-3;t1++) {
      lbp=t1-TSTEPS+1;
      ubp=min(floord(t1+NI-1,2),t1);
#pragma omp parallel for private(lbv,ubv)
      for (t2=lbp;t2<=ubp;t2++) {
        ey[-t1+2*t2][0]=ey[-t1+2*t2][0]-0.5*(hz[-t1+2*t2][0]-hz[-t1+2*t2-1][0]);;
      }
    }
  }
}
/* End of CLooG code */
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


  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(ey,ex,hz);
  else if (tool_kind == 2)
    comp(ey,ex,hz);
    else
      comp_pluto(ey,ex,hz);


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









