#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>


#define N 500

#pragma declarations
double a[N][N];
//double v_a[32][35];
//double v_b[32][32];
//double v_c[32][33];
#pragma enddeclarations

#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
    int i, j, k;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                a[i][j] += (i+k+1)*(k+j+1);//i==j?1:0;
            }
        }
    }
}


void print_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            fprintf(stderr, "%lf ", round(a[i][j]));
            if (j%80 == 79) fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
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

int main()
{
	int i, j, k;
    double t_start, t_end;

	init_array() ;

	t_start = rtclock();
int c = 0;
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
  int t1, t2, t3, t4, t5, t6;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if (N >= 2) {
  for (t1=0;t1<=floord(N-2,16);t1++) {
    lbp=ceild(t1,2);
    ubp=min(floord(N-1,32),t1);
#pragma omp parallel for private(lbv,ubv,t3,t4,t5,t6)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=t1-t2;t3<=floord(N-1,32);t3++) {
        if (t1 == t2+t3) {
          for (t4=32*t1-32*t2;t4<=min(N-2,32*t1-32*t2+30);t4++) {
            lbv=max(32*t2,t4+1);
            ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              a[t4][t6] = a[t4][t6]/a[t4][t4];;
            }
            for (t5=t4+1;t5<=min(N-1,32*t1-32*t2+31);t5++) {
              lbv=max(32*t2,t4+1);
              ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                a[t5][t6] = a[t5][t6] - a[t5][t4]*a[t4][t6];;
              }
            }
          }
        }
        if ((t1 == t2+t3) && (t1 <= 2*t2-1)) {
          lbv=32*t2;
          ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            a[(32*t1-32*t2+31)][t6] = a[(32*t1-32*t2+31)][t6]/a[(32*t1-32*t2+31)][(32*t1-32*t2+31)];;
          }
        }
        if (t1 <= t2+t3-1) {
          for (t4=32*t1-32*t2;t4<=min(32*t2+30,32*t1-32*t2+31);t4++) {
            for (t5=32*t3;t5<=min(N-1,32*t3+31);t5++) {
              lbv=max(32*t2,t4+1);
              ubv=min(N-1,32*t2+31);
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                a[t5][t6] = a[t5][t6] - a[t5][t4]*a[t4][t6];;
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
	printf("%0.6lfs  %i\n", t_end - t_start,c);

    if (fopen(".test", "r")) {
#ifdef MPI
        if (my_rank == 0) {
            print_array();
        }
#else
        print_array();
#endif
    }
    return 0;
}
