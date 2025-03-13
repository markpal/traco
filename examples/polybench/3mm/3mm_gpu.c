#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#include<openacc.h>

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





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {
int i,j,k;

   int n = N;
   int ni = n;
   int nj = n;
   int nl = n;
   int nk = n;
   int nm = n;


  #pragma acc data copyinout(tmp[0:n*n],E[0:n*n],F[0:n*n],G[0:n*n]) copyin(alpha, A[0:n*n], B[0:n*n], C[0:n*n], D[0:n*n], n,ni,nj,nl,nk,nm)
  {

    for (i=0; i<ni; i++) {
    		for (j=0; j<nj; j++) {
    			E[i][j] = 0;
      			for (k=0; k<nk; k++) {
      				E[i][j] += A[i][k] * B[k][j];
    			}
  		}
	}


	for (i=0; i<nj; i++) {
    		for (j=0; j<nl; j++) {
    			F[i][j] = 0;
      			for (k=0; k<nm; k++) {
      				F[i][j] += C[i][k] * D[k][j];
    			}
  		}
	}


	for (i=0; i<ni; i++) {
    		for (j=0; j<nl; j++) {
    			G[i][j] = 0;
      			for (k=0; k<nj; k++) {
      				G[i][j] += E[i][k] * F[k][j];
    			}
  		}
	}
  }

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {
int i,j,k;


   int n = N;
   int ni = n;
   int nj = n;
   int nl = n;
   int nk = n;
   int nm = n;


  #pragma acc data copyinout(tmp[0:n*n],E[0:n*n],F[0:n*n],G[0:n*n]) copyin(alpha, A[0:n*n], B[0:n*n], C[0:n*n], D[0:n*n], n,ni,nj,nl,nk,nm)
  {

    #pragma acc kernels loop  private(i,j,k)
        for (i=0; i<ni; i++) {
            #pragma acc loop
            for (j=0; j<nj; j++) {
                E[i][j] = 0;
                #pragma acc loop
                for (k=0; k<nk; k++) {
                    E[i][j] += A[i][k] * B[k][j];
                }
            }
        }


        #pragma acc kernels loop  private(i,j,k)
        for (i=0; i<nj; i++) {
            #pragma acc loop
            for (j=0; j<nl; j++) {
                F[i][j] = 0;
                #pragma acc loop
                for (k=0; k<nm; k++) {
                    F[i][j] += C[i][k] * D[k][j];
                }
            }
        }


        #pragma acc kernels loop  private(i,j,k)
        for (i=0; i<ni; i++) {
            #pragma acc loop
            for (j=0; j<nl; j++) {
                G[i][j] = 0;
                #pragma acc loop
                for (k=0; k<nj; k++) {
                    G[i][j] += E[i][k] * F[k][j];
                }
            }
        }
  }


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

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*D)[DIM2], (*E)[DIM2], (*F)[DIM2], (*G)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  D = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  E = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  F = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  G = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B,C,D,E,F,G);
  else if (tool_kind == 2){
     comp(A,B,C,D,E,F,G);
   }
    else{
       comp_pluto(A,B,C,D,E,F,G);
   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

