#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 1024;
int DIM;
int NI, NJ, NL, NM, NK;
int DIM1;
int DIM2;
int DIM3;





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;

    #pragma scop
	for (i=0; i<NI; i++) {
     for (j=0; j<NJ; j++) {
      tmp[i][j] = 0;
      for (k=0; k<NK; k++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
     }
    }

  	for (i=0; i<NI; i++) {
     for (j=0; j<NL; j++) {
      D[i][j] *= beta;
       for (k=0; k<NJ; k++) {
         D[i][j] += tmp[i][k] * C[k][j];
      }
    }
   }
   #pragma endscop

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {
int i,j,k, alpha=0, beta = 0;
#pragma omp parallel for private(i,k,j)
	for (i=0; i<NI; i++) {
     for (j=0; j<NJ; j++) {
      tmp[i][j] = 0;
      for (k=0; k<NK; k++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
     }
    }

#pragma omp parallel for private(i,k,j)
  	for (i=0; i<NI; i++) {
     for (j=0; j<NL; j++) {
      D[i][j] *= beta;
       for (k=0; k<NJ; k++) {
         D[i][j] += tmp[i][k] * C[k][j];
      }
    }
   }



}

void comp_pluto(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {

  int t1, t2, t3, t4, t5, alpha=0, beta = 0;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (NI >= 1) {
  if ((NJ >= NL+1) && (NL >= 1)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=0;t3<=NL-1;t3++) {
        D[t2][t3]*=beta;;
        tmp[t2][t3]=0;;
      }
      for (t3=NL;t3<=NJ-1;t3++) {
        tmp[t2][t3]=0;;
      }
    }
  }
  if ((NJ >= 1) && (NJ <= NL-1)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=0;t3<=NJ-1;t3++) {
        D[t2][t3]*=beta;;
        tmp[t2][t3]=0;;
      }
      for (t3=NJ;t3<=NL-1;t3++) {
        D[t2][t3]*=beta;;
      }
    }
  }
  if ((NJ >= 1) && (NJ == NL)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=0;t3<=NJ-1;t3++) {
        D[t2][t3]*=beta;;
        tmp[t2][t3]=0;;
      }
    }
  }
  if ((NJ >= 1) && (NL <= 0)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=0;t3<=NJ-1;t3++) {
        tmp[t2][t3]=0;;
      }
    }
  }
  if ((NJ <= 0) && (NL >= 1)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=0;t3<=NL-1;t3++) {
        D[t2][t3]*=beta;;
      }
    }
  }
  if ((NJ >= 1) && (NK >= 1) && (NL >= 1)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t4=0;t4<=NK-1;t4++) {
        for (t5=0;t5<=NJ-1;t5++) {
          tmp[t2][t5]+=alpha*A[t2][t4]*B[t4][t5];;
        }
      }
      for (t4=0;t4<=NL-1;t4++) {
        for (t5=0;t5<=NJ-1;t5++) {
          D[t2][t4]+=tmp[t2][t5]*C[t5][t4];;
        }
      }
    }
  }
  if ((NJ >= 1) && (NK >= 1) && (NL <= 0)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t4=0;t4<=NK-1;t4++) {
        for (t5=0;t5<=NJ-1;t5++) {
          tmp[t2][t5]+=alpha*A[t2][t4]*B[t4][t5];;
        }
      }
    }
  }
  if ((NJ >= 1) && (NK <= 0) && (NL >= 1)) {
    lbp=0;
    ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t4=0;t4<=NL-1;t4++) {
        for (t5=0;t5<=NJ-1;t5++) {
          D[t2][t4]+=tmp[t2][t5]*C[t5][t4];;
        }
      }
    }
  }
}
/* End of CLooG code */
}


void comp_pluto4(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float tmp[DIM1][DIM2]) {

}


int main(int argc, char *argv[]) {

  // number of processors
  int tool_kind=1, num_proc=1;

  tool_kind = atoi(argv[1]);
  num_proc = atoi(argv[2]);

  if(argc > 3)
    N = atoi(argv[3]);

  NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*D)[DIM2], (*tmp)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  D = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  tmp = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));




  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B,C,D,tmp);
  else if (tool_kind == 2)
    comp(A,B,C,D,tmp);
    else
      comp_pluto(A,B,C,D,tmp);


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}









