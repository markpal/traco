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





void seq(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {
int i,j,k;

    #pragma scop
	for (i=0; i<NI; i++) {
		for (j=0; j<NJ; j++) {
			E[i][j] = 0;
			for (k=0; k<NK; k++) {
				E[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	#pragma endscop

    #pragma scop
	for (i=0; i<NJ; i++) {
		for (j=0; j<NL; j++) {
			F[i][j] = 0;
			for (k=0; k<NM; k++) {
				F[i][j] += C[i][k] * D[k][j];
			}
		}
	}
	#pragma endscop

    #pragma scop
	for (i=0; i<NI; i++) {
		for (j=0; j<NL; j++) {
			G[i][j] = 0;
			for (k=0; k<NJ; k++) {
				G[i][j] += E[i][k] * F[k][j];
			}
		}
	}
	#pragma endscop

}


void comp(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {

int c0, c1, c2, c3, c4, c5;

for (c0 = 0; c0 <= floord(NI - 1, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(NJ - 1, 32); c1 += 1) {
    for (c2 = 0; c2 <= floord(NK - 1, 32); c2 += 1)
      for (c3 = 32 * c0; c3 <= min(NI - 1, 32 * c0 + 31); c3 += 1) {
        for (c4 = 32 * c2; c4 <= min(NK - 1, 32 * c2 + 31); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NJ >= c4 + 1)
            E[c3][c4]=0;
          for (c5 = 32 * c1; c5 <= min(NJ - 1, 32 * c1 + 31); c5 += 1)
            E[c3][c5]+=A[c3][c4]*B[c4][c5];
        }
        if (c2 == 0) {
          for (c4 = max(32, 32 * c1); c4 <= min(min(NJ - 1, NK - 1), 32 * c1 + 31); c4 += 1)
            E[c3][c4]=0;
          for (c4 = max(32 * c1, NK); c4 <= min(NJ - 1, 32 * c1 + 31); c4 += 1)
            E[c3][c4]=0;
        }
      }
    if (NK <= 0)
      for (c3 = 32 * c0; c3 <= min(NI - 1, 32 * c0 + 31); c3 += 1)
        for (c4 = 32 * c1; c4 <= min(NJ - 1, 32 * c1 + 31); c4 += 1)
          E[c3][c4]=0;
  }

for (c0 = 0; c0 <= floord(NJ - 1, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(NL - 1, 32); c1 += 1) {
    for (c2 = 0; c2 <= floord(NM - 1, 32); c2 += 1)
      for (c3 = 32 * c0; c3 <= min(NJ - 1, 32 * c0 + 31); c3 += 1) {
        for (c4 = 32 * c2; c4 <= min(NM - 1, 32 * c2 + 31); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NL >= c4 + 1)
            F[c3][c4]=0;
          for (c5 = 32 * c1; c5 <= min(NL - 1, 32 * c1 + 31); c5 += 1)
            F[c3][c5]+=C[c3][c4]*D[c4][c5];
        }
        if (c2 == 0) {
          for (c4 = max(32, 32 * c1); c4 <= min(min(NL - 1, NM - 1), 32 * c1 + 31); c4 += 1)
            F[c3][c4]=0;
          for (c4 = max(32 * c1, NM); c4 <= min(NL - 1, 32 * c1 + 31); c4 += 1)
            F[c3][c4]=0;
        }
      }
    if (NM <= 0)
      for (c3 = 32 * c0; c3 <= min(NJ - 1, 32 * c0 + 31); c3 += 1)
        for (c4 = 32 * c1; c4 <= min(NL - 1, 32 * c1 + 31); c4 += 1)
          F[c3][c4]=0;
  }


for (c0 = 0; c0 <= floord(NI - 1, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(NL - 1, 32); c1 += 1) {
    for (c2 = 0; c2 <= floord(NJ - 1, 32); c2 += 1)
      for (c3 = 32 * c0; c3 <= min(NI - 1, 32 * c0 + 31); c3 += 1) {
        for (c4 = 32 * c2; c4 <= min(NJ - 1, 32 * c2 + 31); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NL >= c4 + 1)
            G[c3][c4]=0;
          for (c5 = 32 * c1; c5 <= min(NL - 1, 32 * c1 + 31); c5 += 1)
            G[c3][c5]+=E[c3][c4]*F[c4][c5];
        }
        if (c2 == 0) {
          for (c4 = max(32, 32 * c1); c4 <= min(min(NL - 1, NJ - 1), 32 * c1 + 31); c4 += 1)
            G[c3][c4]=0;
          for (c4 = max(32 * c1, NJ); c4 <= min(NL - 1, 32 * c1 + 31); c4 += 1)
            G[c3][c4]=0;
        }
      }
    if (NJ <= 0)
      for (c3 = 32 * c0; c3 <= min(NI - 1, 32 * c0 + 31); c3 += 1)
        for (c4 = 32 * c1; c4 <= min(NL - 1, 32 * c1 + 31); c4 += 1)
          G[c3][c4]=0;
  }



}

void comp_pluto(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {

  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17;

 register int lbv, ubv;
/* Start of CLooG code */
if ((NI >= 0) && (NJ >= 0) && (NL >= 1)) {
  for (t2=0;t2<=floord(NI+NJ-1,32);t2++) {
    for (t3=0;t3<=floord(NL-1,32);t3++) {
      for (t4=32*t2;t4<=min(min(NI-1,NJ-1),32*t2+31);t4++) {
        lbv=32*t3;
        ubv=min(NL-1,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          F[t4][t17]=0;;
          G[t4][t17]=0;;
        }
      }
      for (t4=max(NI,32*t2);t4<=min(NJ-1,32*t2+31);t4++) {
        lbv=32*t3;
        ubv=min(NL-1,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          F[t4][t17]=0;;
        }
      }
      for (t4=max(NJ,32*t2);t4<=min(NI-1,32*t2+31);t4++) {
        lbv=32*t3;
        ubv=min(NL-1,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          G[t4][t17]=0;;
        }
      }
    }
  }
}
if ((NI <= -1) && (NL >= 1)) {
  for (t2=0;t2<=floord(NJ-1,32);t2++) {
    for (t3=0;t3<=floord(NL-1,32);t3++) {
      for (t4=32*t2;t4<=min(NJ-1,32*t2+31);t4++) {
        lbv=32*t3;
        ubv=min(NL-1,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          F[t4][t17]=0;;
        }
      }
    }
  }
}
if ((NJ <= -1) && (NL >= 1)) {
  for (t2=0;t2<=floord(NI-1,32);t2++) {
    for (t3=0;t3<=floord(NL-1,32);t3++) {
      for (t4=32*t2;t4<=min(NI-1,32*t2+31);t4++) {
        lbv=32*t3;
        ubv=min(NL-1,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          G[t4][t17]=0;;
        }
      }
    }
  }
}
if ((NL >= 1) && (NM >= 1)) {
  for (t2=0;t2<=floord(NJ-1,32);t2++) {
    for (t3=0;t3<=floord(NL-1,32);t3++) {
      for (t5=0;t5<=floord(NM-1,32);t5++) {
        for (t6=32*t2;t6<=min(NJ-1,32*t2+31);t6++) {
          for (t8=32*t5;t8<=min(NM-1,32*t5+31);t8++) {
            lbv=32*t3;
            ubv=min(NL-1,32*t3+31);
#pragma ivdep
#pragma vector always
            for (t17=lbv;t17<=ubv;t17++) {
              F[t6][t17]+=C[t6][t8]*D[t8][t17];;
            }
          }
        }
      }
    }
  }
}
if (NJ >= 1) {
  for (t2=0;t2<=floord(NI-1,32);t2++) {
    for (t3=0;t3<=floord(NJ-1,32);t3++) {
      for (t4=32*t2;t4<=min(NI-1,32*t2+31);t4++) {
        lbv=32*t3;
        ubv=min(NJ-1,32*t3+31);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          E[t4][t17]=0;;
        }
      }
    }
  }
}
if (NJ >= 1) {
  for (t2=0;t2<=floord(NI-1,32);t2++) {
    for (t3=0;t3<=floord(NJ-1,32);t3++) {
      if (NK >= 1) {
        for (t5=0;t5<=floord(NK-1,32);t5++) {
          for (t6=32*t2;t6<=min(NI-1,32*t2+31);t6++) {
            for (t7=32*t3;t7<=min(NJ-1,32*t3+31);t7++) {
              for (t9=32*t5;t9<=min(NK-1,32*t5+31);t9++) {
                E[t6][t7]+=A[t6][t9]*B[t9][t7];;
              }
            }
          }
        }
      }
      if (NL >= 1) {
        for (t5=0;t5<=floord(NL-1,32);t5++) {
          for (t6=32*t2;t6<=min(NI-1,32*t2+31);t6++) {
            for (t7=32*t3;t7<=min(NJ-1,32*t3+31);t7++) {
              lbv=32*t5;
              ubv=min(NL-1,32*t5+31);
#pragma ivdep
#pragma vector always
              for (t17=lbv;t17<=ubv;t17++) {
                G[t6][t17]+=E[t6][t7]*F[t7][t17];;
              }
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */


}


void comp4(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {

int c0, c1, c2, c3, c4, c5;


for (c0 = 0; c0 <= floord(NI - 1, 4); c0 += 1)
  for (c1 = 0; c1 <= floord(NJ - 1, 4); c1 += 1) {
    for (c2 = 0; c2 <= floord(NK - 1, 4); c2 += 1)
      for (c3 = 4 * c0; c3 <= min(NI - 1, 4 * c0 + 3); c3 += 1) {
        for (c4 = 4 * c2; c4 <= min(NK - 1, 4 * c2 + 3); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NJ >= c4 + 1)
            E[c3][c4]=0;
          for (c5 = 4 * c1; c5 <= min(NJ - 1, 4 * c1 + 3); c5 += 1)
            E[c3][c5]+=A[c3][c4]*B[c4][c5];
        }
        if (c2 == 0) {
          for (c4 = max(4, 4 * c1); c4 <= min(min(NJ - 1, NK - 1), 4 * c1 + 3); c4 += 1)
            E[c3][c4]=0;
          for (c4 = max(4 * c1, NK); c4 <= min(NJ - 1, 4 * c1 + 3); c4 += 1)
            E[c3][c4]=0;
        }
      }
    if (NK <= 0)
      for (c3 = 4 * c0; c3 <= min(NI - 1, 4 * c0 + 3); c3 += 1)
        for (c4 = 4 * c1; c4 <= min(NJ - 1, 4 * c1 + 3); c4 += 1)
          E[c3][c4]=0;
  }



for (c0 = 0; c0 <= floord(NJ - 1, 4); c0 += 1)
  for (c1 = 0; c1 <= floord(NL - 1, 4); c1 += 1) {
    for (c2 = 0; c2 <= floord(NM - 1, 4); c2 += 1)
      for (c3 = 4 * c0; c3 <= min(NJ - 1, 4 * c0 + 3); c3 += 1) {
        for (c4 = 4 * c2; c4 <= min(NM - 1, 4 * c2 + 3); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NL >= c4 + 1)
            F[c3][c4]=0;
          for (c5 = 4 * c1; c5 <= min(NL - 1, 4 * c1 + 3); c5 += 1)
            F[c3][c5]=F[c3][c5]+C[c3][c4]*D[c4][c5];
        }
        if (c2 == 0) {
          for (c4 = max(4, 4 * c1); c4 <= min(min(NL - 1, NM - 1), 4 * c1 + 3); c4 += 1)
            F[c3][c4]=0;
          for (c4 = max(4 * c1, NM); c4 <= min(NL - 1, 4 * c1 + 3); c4 += 1)
            F[c3][c4]=0;
        }
      }
    if (NM <= 0)
      for (c3 = 4 * c0; c3 <= min(NJ - 1, 4 * c0 + 3); c3 += 1)
        for (c4 = 4 * c1; c4 <= min(NL - 1, 4 * c1 + 3); c4 += 1)
          F[c3][c4]=0;
  }


for (c0 = 0; c0 <= floord(NI - 1, 4); c0 += 1)
  for (c1 = 0; c1 <= floord(NL - 1, 4); c1 += 1) {
    for (c2 = 0; c2 <= floord(NJ - 1, 4); c2 += 1)
      for (c3 = 4 * c0; c3 <= min(NI - 1, 4 * c0 + 3); c3 += 1) {
        for (c4 = 4 * c2; c4 <= min(NJ - 1, 4 * c2 + 3); c4 += 1) {
          if (c2 == 0 && c1 == 0 && NL >= c4 + 1)
            G[c3][c4]=0;
          for (c5 = 4 * c1; c5 <= min(NL - 1, 4 * c1 + 3); c5 += 1)
            G[c3][c5]+=E[c3][c4]*F[c4][c5];
        }
        if (c2 == 0) {
          for (c4 = max(4, 4 * c1); c4 <= min(min(NL - 1, NJ - 1), 4 * c1 + 3); c4 += 1)
            G[c3][c4]=0;
          for (c4 = max(4 * c1, NJ); c4 <= min(NL - 1, 4 * c1 + 3); c4 += 1)
            G[c3][c4]=0;
        }
      }
    if (NJ <= 0)
      for (c3 = 4 * c0; c3 <= min(NI - 1, 4 * c0 + 3); c3 += 1)
        for (c4 = 4 * c1; c4 <= min(NL - 1, 4 * c1 + 3); c4 += 1)
          G[c3][c4]=0;
  }





}

void comp_pluto4(float A[DIM1][DIM2], float B[DIM1][DIM2], float C[DIM1][DIM2], float D[DIM1][DIM2], float E[DIM1][DIM2], float F[DIM1][DIM2], float G[DIM1][DIM2]) {
  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17;

 register int lbv, ubv;

/* Start of CLooG code */
if ((NI >= 0) && (NJ >= 0) && (NL >= 1)) {
  for (t2=0;t2<=floord(NI+NJ-1,4);t2++) {
    for (t3=0;t3<=floord(NL-1,4);t3++) {
      for (t4=4*t2;t4<=min(min(NI-1,NJ-1),4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NL-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          F[t4][t17]=0;;
          G[t4][t17]=0;;
        }
      }
      for (t4=max(NI,4*t2);t4<=min(NJ-1,4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NL-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          F[t4][t17]=0;;
        }
      }
      for (t4=max(NJ,4*t2);t4<=min(NI-1,4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NL-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          G[t4][t17]=0;;
        }
      }
    }
  }
}
if ((NI <= -1) && (NL >= 1)) {
  for (t2=0;t2<=floord(NJ-1,4);t2++) {
    for (t3=0;t3<=floord(NL-1,4);t3++) {
      for (t4=4*t2;t4<=min(NJ-1,4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NL-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          F[t4][t17]=0;;
        }
      }
    }
  }
}
if ((NJ <= -1) && (NL >= 1)) {
  for (t2=0;t2<=floord(NI-1,4);t2++) {
    for (t3=0;t3<=floord(NL-1,4);t3++) {
      for (t4=4*t2;t4<=min(NI-1,4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NL-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          G[t4][t17]=0;;
        }
      }
    }
  }
}
if ((NL >= 1) && (NM >= 1)) {
  for (t2=0;t2<=floord(NJ-1,4);t2++) {
    for (t3=0;t3<=floord(NL-1,4);t3++) {
      for (t5=0;t5<=floord(NM-1,4);t5++) {
        for (t6=4*t2;t6<=min(NJ-1,4*t2+3);t6++) {
          for (t8=4*t5;t8<=min(NM-1,4*t5+3);t8++) {
            lbv=4*t3;
            ubv=min(NL-1,4*t3+3);
#pragma ivdep
#pragma vector always
            for (t17=lbv;t17<=ubv;t17++) {
              F[t6][t17]+=C[t6][t8]*D[t8][t17];;
            }
          }
        }
      }
    }
  }
}
if (NJ >= 1) {
  for (t2=0;t2<=floord(NI-1,4);t2++) {
    for (t3=0;t3<=floord(NJ-1,4);t3++) {
      for (t4=4*t2;t4<=min(NI-1,4*t2+3);t4++) {
        lbv=4*t3;
        ubv=min(NJ-1,4*t3+3);
#pragma ivdep
#pragma vector always
        for (t17=lbv;t17<=ubv;t17++) {
          E[t4][t17]=0;;
        }
      }
    }
  }
}
if (NJ >= 1) {
  for (t2=0;t2<=floord(NI-1,4);t2++) {
    for (t3=0;t3<=floord(NJ-1,4);t3++) {
      if (NK >= 1) {
        for (t5=0;t5<=floord(NK-1,4);t5++) {
          for (t6=4*t2;t6<=min(NI-1,4*t2+3);t6++) {
            for (t7=4*t3;t7<=min(NJ-1,4*t3+3);t7++) {
              for (t9=4*t5;t9<=min(NK-1,4*t5+3);t9++) {
                E[t6][t7]+=A[t6][t9]*B[t9][t7];;
              }
            }
          }
        }
      }
      if (NL >= 1) {
        for (t5=0;t5<=floord(NL-1,4);t5++) {
          for (t6=4*t2;t6<=min(NI-1,4*t2+3);t6++) {
            for (t7=4*t3;t7<=min(NJ-1,4*t3+3);t7++) {
              lbv=4*t5;
              ubv=min(NL-1,4*t5+3);
#pragma ivdep
#pragma vector always
              for (t17=lbv;t17<=ubv;t17++) {
                G[t6][t17]+=E[t6][t7]*F[t7][t17];;
              }
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
}


int main(int argc, char *argv[]) {

  // number of processors
  int tile_kind=1, BL=0;
  tile_kind = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  if(argc > 3)
    BL = atoi(argv[3]);

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



  printf("Ilosc procesorow: %i \n\n", tile_kind);
  omp_set_num_threads(tile_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tile_kind == 1)
    seq(A,B,C,D,E,F,G);
  else if (tile_kind == 2){
         if(BL==0)
         comp(A,B,C,D,E,F,G);
         else
         comp4(A,B,C,D,E,F,G);
   }
       else{
          if(BL==0)
          comp_pluto(A,B,C,D,E,F,G);
          else
          comp_pluto4(A,B,C,D,E,F,G);
   }

   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}
