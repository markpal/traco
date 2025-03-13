#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

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

/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if (N >= 1) {
  lbp=0;
  ubp=floord(N-1,32);
#pragma omp parallel for private(lbv,ubv,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N-1,32);t2++) {
      for (t4=0;t4<=floord(N-1,32);t4++) {
        for (t5=0;t5<=floord(N-1,32);t5++) {
          for (t8=0;t8<=floord(N-1,32);t8++) {
            for (t9=32*t1;t9<=min(N-1,32*t1+31);t9++) {
              for (t11=32*t4;t11<=min(N-1,32*t4+31);t11++) {
                for (t12=32*t5;t12<=min(N-1,32*t5+31);t12++) {
                  for (t15=32*t8;t15<=min(N-1,32*t8+31);t15++) {
                    lbv=32*t2;
                    ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
                    for (t16=lbv;t16<=ubv;t16++) {
                      T1[t9][t11][t12][t16] = T1[t9][t11][t12][t16] + A[t15][t11][t12][t16]*C4[t15][t9];;
                    }
                  }
                }
              }
            }
          }
          for (t8=0;t8<=floord(N-1,32);t8++) {
            for (t9=32*t1;t9<=min(N-1,32*t1+31);t9++) {
              for (t11=32*t4;t11<=min(N-1,32*t4+31);t11++) {
                for (t12=32*t5;t12<=min(N-1,32*t5+31);t12++) {
                  for (t15=32*t8;t15<=min(N-1,32*t8+31);t15++) {
                    lbv=32*t2;
                    ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
                    for (t16=lbv;t16<=ubv;t16++) {
                      T2[t9][t15][t12][t16] = T2[t9][t15][t12][t16] + T1[t9][t11][t12][t16]*C3[t11][t15];;
                    }
                  }
                }
              }
            }
          }
        }
      }
      for (t4=0;t4<=floord(N-1,32);t4++) {
        for (t5=0;t5<=floord(N-1,32);t5++) {
          for (t8=0;t8<=floord(N-1,32);t8++) {
            for (t9=32*t1;t9<=min(N-1,32*t1+31);t9++) {
              for (t11=32*t4;t11<=min(N-1,32*t4+31);t11++) {
                for (t12=32*t5;t12<=min(N-1,32*t5+31);t12++) {
                  for (t15=32*t8;t15<=min(N-1,32*t8+31);t15++) {
                    lbv=32*t2;
                    ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
                    for (t16=lbv;t16<=ubv;t16++) {
                      T3[t9][t11][t12][t16] = T3[t9][t11][t12][t16] + T2[t9][t11][t15][t16]*C2[t15][t12];;
                    }
                  }
                }
              }
            }
          }
          for (t8=0;t8<=floord(N-1,32);t8++) {
            for (t9=32*t1;t9<=min(N-1,32*t1+31);t9++) {
              for (t11=32*t4;t11<=min(N-1,32*t4+31);t11++) {
                for (t12=32*t5;t12<=min(N-1,32*t5+31);t12++) {
                  for (t15=32*t8;t15<=min(N-1,32*t8+31);t15++) {
                    for (t16=32*t2;t16<=min(N-1,32*t2+31);t16++) {
                      B[t9][t11][t12][t15] = B[t9][t11][t12][t15] + T3[t9][t11][t12][t16]*C1[t16][t15];;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */

t_end = rtclock();
    printf("%0.3lfs\n", t_end - t_start);

    return 0;
}
