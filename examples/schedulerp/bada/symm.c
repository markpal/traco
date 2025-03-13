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





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float acc[DIM1][DIM2]) {
int i,j,k, alpha=0, beta=0;

 #pragma scop
 if(NI > 3 && NJ > 3)
  for (i = 0; i < NI; i++)
    for (j = 0; j < NJ; j++)
      {
	acc[i][j] = 0;
	for (k = 0; k < j-1; k++)
	  {
	    C[k][j] += alpha * A[k][i] * B[i][j];
	    acc[i][j] += B[k][j] * A[k][i];
	  }
	C[i][j] = beta * C[i][j] + alpha * A[i][i] * B[i][j] + alpha * acc[i][j];
      }

  #pragma endscop

}







void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float acc[DIM1][DIM2]){

int c0,c1,c2,c4,alpha=0,beta=0;

/*
if (NJ >= 4 && NI >= 4)
#pragma omp parallel for
  for (c0 = 0; c0 < NI; c0 += 1)
    for (c1 = 0; c1 < NJ; c1 += 1) {
      if (c1 >= 0 && NJ >= c1 + 1 && c0 >= 0 && NI >= c0 + 1 && NJ >= 4 && NI >= 4) {
        acc[c0][c1]=0;
        C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
      }

      if (c1 == 2 && c0 == 0) {

        if (NI >= 4 && NJ >= 4)
          for (c0 = 0; c0 < NI; c0 += 1)
            C[0][2]+=alpha*A[0][c0]*B[c0][2];


        if (NI >= 4 && NJ >= 4)
          for (c0 = 0; c0 < NI; c0 += 1) {
            acc[c0][2]=0;
            if (c0 == 0)
              C[-1][2]+=alpha*A[-1][0]*B[0][2];
            acc[c0][2]+=B[-1][2]*A[-1][c0];
            C[c0][2]=beta*C[c0][2]+alpha*A[c0][c0]*B[c0][2]+alpha*acc[c0][2];
          }

      } else if (c1 >= 3) {
        if (c0 == 0)

          if (NJ >= c1 + 1 && NJ >= 4 && NI >= 4 && c1 >= 2)
            for (c0 = 0; c0 < NI; c0 += 1)
              C[0][c1]+=alpha*A[0][c0]*B[c0][c1];


        if (c0 >= 0 && NI >= 4 && c1 >= 3 && NJ >= c1 + 1 && NI >= c0 + 1)
          for (c4 = 0; c4 < c1 - 1; c4 += 1)
            acc[c0][c1]+=B[c4][c1]*A[c4][c0];

        if (c0 == 0)

          if (NJ >= c1 + 1 && NJ >= 4 && NI >= 4 && c1 >= 2)
            for (c0 = 0; c0 < NI; c0 += 1) {
              for (c4 = 0; c4 < c1 - 1; c4 += 1)
                acc[c0][c1]=0;
              if (c1 >= c0 + 2)
                C[-1][c1]+=alpha*A[-1][c0]*B[c0][c1];
              acc[c0][c1]+=B[-1][c1]*A[-1][c0];
              for (c4 = 0; c4 < c1 - 1; c4 += 1)
                C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
            }

      }
      if (c0 == 0)
        for (c2 = 1; c2 < c1 - 1; c2 += 1)

          if (NJ >= c1 + 1 && NJ >= 4 && NI >= 4 && c2 + 1 >= 0 && c1 >= c2 + 2 && c1 >= 2)
            for (c0 = 0; c0 < NI; c0 += 1)
              if (c2 + c0 >= 0) {
                if (c2 + 1 == 0)
                  for (c4 = 0; c4 < c1 - 1; c4 += 1)
                    acc[c0][c1]=0;
                if (c2 >= 0) {
                  C[c2][c1]+=alpha*A[c2][c0]*B[c0][c1];
                } else
                  acc[c0][c1]+=B[-1][c1]*A[-1][c0];
                if (c2 + 1 == 0)
                  C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
              } else
                C[-1][c1]+=alpha*A[-1][0]*B[0][c1];

    }
*/

if (NJ >= 4 && NI >= 4)
#pragma omp parallel for
  for (c0 = 0; c0 < NI; c0 += 1)
    for (c1 = 0; c1 < NJ; c1 += 1) {
      if (c1 >= 0 && NJ >= c1 + 1 && c0 >= 0 && NI >= c0 + 1 && NJ >= 4 && NI >= 4) {
        acc[c0][c1]=0;
        C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
      }

      if (c1 >= 2) {
        if (c1 >= 3)

          if (c0 >= 0 && NI >= 4 && c1 >= 3 && NJ >= c1 + 1 && NI >= c0 + 1)
            for (c4 = 0; c4 < c1 - 1; c4 += 1)
              acc[c0][c1]+=B[c4][c1]*A[c4][c0];


        if (NI >= 4 && NJ >= c1 + 1 && c1 >= 2 && NI >= c0 + 1 && c0 >= 0 && NJ >= 4) {
          for (c4 = 0; c4 < c1 - 1; c4 += 1)
            acc[c0][c1]=0;
          if (c1 >= c0 + 2)
            C[-1][c1]+=alpha*A[-1][c0]*B[c0][c1];
          acc[c0][c1]+=B[-1][c1]*A[-1][c0];
          for (c4 = 0; c4 < c1 - 1; c4 += 1)
            C[c0][c1]=beta*C[c0][c1]+alpha*A[c0][c0]*B[c0][c1]+alpha*acc[c0][c1];
        }

      }
    }


}

void comp_pluto(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float acc[DIM1][DIM2]) {
  int alpha=0,beta=0;

  int t1, t2, t3, t4, t5;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if ((NI >= 4) && (NJ >= 4)) {
  lbp=0;
  ubp=NI-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NJ-1;t3++) {
      acc[t2][t3]=0;;
    }
  }
  lbp=0;
  ubp=1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t3=0;t3<=NI-1;t3++) {
      C[t3][t2]=beta*C[t3][t2]+alpha*A[t3][t3]*B[t3][t2]+alpha*acc[t3][t2];;
    }
  }
  acc[0][2]+=B[0][2]*A[0][0];;
  C[0][2]+=alpha*A[0][0]*B[0][2];;
  C[0][2]=beta*C[0][2]+alpha*A[0][0]*B[0][2]+alpha*acc[0][2];;
  for (t4=3;t4<=NI+1;t4++) {
    C[0][2]+=alpha*A[0][t4-2]*B[t4-2][2];;
  }
  for (t3=1;t3<=NI-1;t3++) {
    acc[t3][2]+=B[0][2]*A[0][t3];;
    C[t3][2]=beta*C[t3][2]+alpha*A[t3][t3]*B[t3][2]+alpha*acc[t3][2];;
  }
  lbp=3;
  ubp=min(NI,NJ-1);
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t4=0;t4<=t2-2;t4++) {
      acc[0][t2]+=B[t4][t2]*A[t4][0];;
    }
    C[0][t2]+=alpha*A[0][0]*B[0][t2];;
    C[0][t2]=beta*C[0][t2]+alpha*A[0][0]*B[0][t2]+alpha*acc[0][t2];;
    for (t4=t2+1;t4<=t2+NI-1;t4++) {
      C[0][t2]+=alpha*A[0][-t2+t4]*B[-t2+t4][t2];;
    }
    for (t3=1;t3<=t2-2;t3++) {
      for (t4=0;t4<=t2-2;t4++) {
        acc[t3][t2]+=B[t4][t2]*A[t4][t3];;
      }
      for (t4=t2;t4<=t2+t3-1;t4++) {
        C[t3][t2]+=alpha*A[t3][-t2+t4]*B[-t2+t4][t2];;
      }
      C[t3][t2]+=alpha*A[t3][t3]*B[t3][t2];;
      C[t3][t2]=beta*C[t3][t2]+alpha*A[t3][t3]*B[t3][t2]+alpha*acc[t3][t2];;
      for (t4=t2+t3+1;t4<=t2+NI-1;t4++) {
        C[t3][t2]+=alpha*A[t3][-t2+t4]*B[-t2+t4][t2];;
      }
    }
    for (t3=t2-1;t3<=NI-1;t3++) {
      for (t4=0;t4<=t2-2;t4++) {
        acc[t3][t2]+=B[t4][t2]*A[t4][t3];;
      }
      C[t3][t2]=beta*C[t3][t2]+alpha*A[t3][t3]*B[t3][t2]+alpha*acc[t3][t2];;
    }
  }
  if (NI <= NJ-2) {
    for (t4=0;t4<=NI-1;t4++) {
      acc[0][NI+1]+=B[t4][NI+1]*A[t4][0];;
    }
    C[0][NI+1]+=alpha*A[0][0]*B[0][NI+1];;
    C[0][NI+1]=beta*C[0][NI+1]+alpha*A[0][0]*B[0][NI+1]+alpha*acc[0][NI+1];;
    for (t4=NI+2;t4<=2*NI;t4++) {
      C[0][NI+1]+=alpha*A[0][t4-NI-1]*B[t4-NI-1][NI+1];;
    }
    for (t3=1;t3<=NI-2;t3++) {
      for (t4=0;t4<=NI-1;t4++) {
        acc[t3][NI+1]+=B[t4][NI+1]*A[t4][t3];;
      }
      for (t4=NI+1;t4<=t3+NI;t4++) {
        C[t3][NI+1]+=alpha*A[t3][t4-NI-1]*B[t4-NI-1][NI+1];;
      }
      C[t3][NI+1]+=alpha*A[t3][t3]*B[t3][NI+1];;
      C[t3][NI+1]=beta*C[t3][NI+1]+alpha*A[t3][t3]*B[t3][NI+1]+alpha*acc[t3][NI+1];;
      for (t4=t3+NI+2;t4<=2*NI;t4++) {
        C[t3][NI+1]+=alpha*A[t3][t4-NI-1]*B[t4-NI-1][NI+1];;
      }
    }
    for (t4=0;t4<=NI-1;t4++) {
      acc[NI-1][NI+1]+=B[t4][NI+1]*A[t4][NI-1];;
    }
    for (t4=NI+1;t4<=2*NI-1;t4++) {
      C[NI-1][NI+1]+=alpha*A[NI-1][t4-NI-1]*B[t4-NI-1][NI+1];;
    }
    C[NI-1][NI+1]+=alpha*A[NI-1][NI-1]*B[NI-1][NI+1];;
    C[NI-1][NI+1]=beta*C[NI-1][NI+1]+alpha*A[NI-1][NI-1]*B[NI-1][NI+1]+alpha*acc[NI-1][NI+1];;
  }
  lbp=NI+2;
  ubp=NJ-1;
#pragma omp parallel for private(lbv,ubv)
  for (t2=lbp;t2<=ubp;t2++) {
    for (t4=0;t4<=t2-2;t4++) {
      acc[0][t2]+=B[t4][t2]*A[t4][0];;
    }
    C[0][t2]+=alpha*A[0][0]*B[0][t2];;
    C[0][t2]=beta*C[0][t2]+alpha*A[0][0]*B[0][t2]+alpha*acc[0][t2];;
    for (t4=t2+1;t4<=t2+NI-1;t4++) {
      C[0][t2]+=alpha*A[0][-t2+t4]*B[-t2+t4][t2];;
    }
    for (t3=1;t3<=NI-2;t3++) {
      for (t4=0;t4<=t2-2;t4++) {
        acc[t3][t2]+=B[t4][t2]*A[t4][t3];;
      }
      for (t4=t2;t4<=t2+t3-1;t4++) {
        C[t3][t2]+=alpha*A[t3][-t2+t4]*B[-t2+t4][t2];;
      }
      C[t3][t2]+=alpha*A[t3][t3]*B[t3][t2];;
      C[t3][t2]=beta*C[t3][t2]+alpha*A[t3][t3]*B[t3][t2]+alpha*acc[t3][t2];;
      for (t4=t2+t3+1;t4<=t2+NI-1;t4++) {
        C[t3][t2]+=alpha*A[t3][-t2+t4]*B[-t2+t4][t2];;
      }
    }
    for (t4=0;t4<=t2-2;t4++) {
      acc[NI-1][t2]+=B[t4][t2]*A[t4][NI-1];;
    }
    for (t4=t2;t4<=t2+NI-2;t4++) {
      C[NI-1][t2]+=alpha*A[NI-1][-t2+t4]*B[-t2+t4][t2];;
    }
    C[NI-1][t2]+=alpha*A[NI-1][NI-1]*B[NI-1][t2];;
    C[NI-1][t2]=beta*C[NI-1][t2]+alpha*A[NI-1][NI-1]*B[NI-1][t2]+alpha*acc[NI-1][t2];;
    for (t3=NI;t3<=t2-2;t3++) {
      for (t4=t2;t4<=t2+NI-1;t4++) {
        C[t3][t2]+=alpha*A[t3][-t2+t4]*B[-t2+t4][t2];;
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

  NK = NI = NJ = NL = NM = N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*A)[DIM2], (*B)[DIM2], (*C)[DIM2], (*acc)[DIM2];

  A = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  B = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  C = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));
  acc = (float (*)[DIM2])malloc(DIM1 * DIM2 * sizeof(float));

  //printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tool_kind == 1)
    seq(A,B,C,acc);
  else if (tool_kind == 2){
         comp(A,B,C,acc);
   }
       else{
          comp_pluto(A,B,C,acc);
   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}









