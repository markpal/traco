#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>

#include "decls.h"
#include "util.h"

double t_start, t_end;

main(int argc, char** argv)
{
    int t, p, q, r, s;

    init_array();

    t_start = rtclock();

          num_proc = atoi(argv[1]);
  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

#ifdef TIME
    for (t=0; t<1000; t++)  {
#endif






  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;

/* Start of CLooG code */
if (N >= 1) {
  lbp=0;
  ubp=floord(N-1,32);
#pragma omp parallel for private(lbv,ubv)
  for (t1=lbp;t1<=ubp;t1++) {
    for (t2=0;t2<=floord(N-1,32);t2++) {
      for (t4=0;t4<=floord(N-1,32);t4++) {
        for (t6=32*t2;t6<=min(N-1,32*t2+31);t6++) {
          for (t9=32*t1;t9<=min(N-1,32*t1+31);t9++) {
            lbv=32*t4;
            ubv=min(N-1,32*t4+31);
#pragma ivdep
#pragma vector always
            for (t10=lbv;t10<=ubv;t10++) {
              sum[t9][t6][t10]=0;;
            }
          }
        }
      }
      for (t4=0;t4<=floord(N-1,32);t4++) {
        for (t5=0;t5<=floord(N-1,32);t5++) {
          for (t6=32*t2;t6<=min(N-1,32*t2+31);t6++) {
            for (t8=32*t4;t8<=min(N-1,32*t4+31);t8++) {
              for (t9=32*t5;t9<=min(N-1,32*t5+31);t9++) {
                lbv=32*t1;
                ubv=min(N-1,32*t1+31);
#pragma ivdep
#pragma vector always
                for (t10=lbv;t10<=ubv;t10++) {
                  sum[t10][t6][t8]=sum[t10][t6][t8]+A[t10][t6][t9]*C4[t9][t8];;
                }
              }
            }
          }
        }
      }
      for (t4=0;t4<=floord(N-1,32);t4++) {
        for (t6=32*t2;t6<=min(N-1,32*t2+31);t6++) {
          for (t8=32*t4;t8<=min(N-1,32*t4+31);t8++) {
            lbv=32*t1;
            ubv=min(N-1,32*t1+31);
#pragma ivdep
#pragma vector always
            for (t10=lbv;t10<=ubv;t10++) {
              A[t10][t6][t8]=sum[t10][t6][t8];;
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */

#ifdef TIME
    }
#endif

    t_end = rtclock();
    printf("%0.6lfs\n", t_end - t_start);

#ifdef TEST
    print_array();
#endif

    return 0;

}
