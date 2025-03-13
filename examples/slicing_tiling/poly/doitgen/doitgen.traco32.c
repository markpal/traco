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
    int c0,c2,c4,c6,c8,c10,c12,c14;
    init_array();

    t_start = rtclock();

          num_proc = atoi(argv[1]);
  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

#ifdef TIME
    for (t=0; t<1000; t++)  {
#endif

register int ubv, lbv;
int ub = floord(N - 1, 32);
#pragma omp parallel for private(ubv,lbv)
for (c0 = 0; c0 <= ub; c0 += 1) {
  for (c2 = 0; c2 <= (N - 1) / 32; c2 += 1)
    for (c4 = 0; c4 <= (N - 1) / 32; c4 += 1)
      for (c8 = 32 * c0; c8 <= min(32 * c0 + 31, N - 1); c8 += 1)
        for (c10 = 32 * c2; c10 <= min(N - 1, 32 * c2 + 31); c10 += 1){
          lbv = 32 * c4;
          ubv =  ubv = min(N - 1, 32 * c4 + 31);
          //for (c14 = 32 * c4; c14 <= min(N - 1, 32 * c4 + 31); c14 += 1)
          for (c14 = lbv; c14 <= ubv; c14 += 1)
            sum[c8][c10][c14]=0;
        }
  for (c2 = 0; c2 <= (N - 1) / 32; c2 += 1)
    for (c4 = 0; c4 <= (N - 1) / 32; c4 += 1)
      for (c6 = 0; c6 <= (N - 1) / 32; c6 += 1)
        for (c8 = 32 * c0; c8 <= min(N - 1, 32 * c0 + 31); c8 += 1)
          for (c10 = 32 * c2; c10 <= min(N - 1, 32 * c2 + 31); c10 += 1)
            for (c12 = 32 * c6; c12 <= min(32 * c6 + 31, N - 1); c12 += 1)
              {
               lbv = 32 * c4;
               ubv = min(N - 1, 32 * c4 + 31);
                 //for (c14 = 32 * c4; c14 <= min(N - 1, 32 * c4 + 31); c14 += 1)
                 for (c14 = lbv; c14 <= ubv; c14 += 1)
                sum[c8][c10][c14]=sum[c8][c10][c14]+A[c8][c10][c12]*C4[c12][c14];
              }
  for (c2 = 0; c2 <= (N - 1) / 32; c2 += 1)
    for (c4 = 0; c4 <= (N - 1) / 32; c4 += 1)
      for (c8 = 32 * c0; c8 <= min(32 * c0 + 31, N - 1); c8 += 1)
        for (c10 = 32 * c2; c10 <= min(N - 1, 32 * c2 + 31); c10 += 1){
                lbv = 32 * c4;
               ubv = min(N - 1, 32 * c4 + 31);
                 //for (c14 = 32 * c4; c14 <= min(N - 1, 32 * c4 + 31); c14 += 1)
                 for (c14 = lbv; c14 <= ubv; c14 += 1)
         // for (c14 = 32 * c4; c14 <= min(32 * c4 + 31, N - 1); c14 += 1)
                   A[c8][c10][c14]=sum[c8][c10][c14];
        }
}


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
