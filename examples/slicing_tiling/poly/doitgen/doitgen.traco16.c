#include <stdio.h>

#include "decls.h"
#include "util.h"

double t_start, t_end;

main(int argc, char** argv)
{
    int t, p, q, r, s;
    int c0,c2,c4,c6,c8,c10,c12,c14;

      num_proc = atoi(argv[1]);
  printf("Ilosc procesorow: %i \n\n", num_proc);
  omp_set_num_threads(num_proc);

    init_array();

    t_start = rtclock();

#ifdef TIME
    for (t=0; t<1000; t++)  {
#endif

int ub = floord(N - 1, 16);
register int ubv, lbv;
#pragma omp parallel for private(ubv,lbv)
for (c0 = 0; c0 <= ub; c0 += 1)
  for (c2 = 0; c2 <= (N - 1) / 16; c2 += 1) {
    for (c4 = 0; c4 <= (N - 1) / 16; c4 += 1) {
      for (c8 = 16 * c0; c8 <= min(16 * c0 + 15, N - 1); c8 += 1)
        for (c10 = 16 * c2; c10 <= min(N - 1, 16 * c2 + 15); c10 += 1){
            lbv = 16*c4;
            ubv = min(N - 1, 16 * c4 + 15);
            #pragma ivdep
#pragma vector always
          for (c14 = lbv; c14 <= ubv; c14 += 1)
         // for (c14 = 16 * c4; c14 <= min(N - 1, 16 * c4 + 15); c14 += 1)
            sum[c8][c10][c14]=0;
        }
      for (c6 = 0; c6 <= (N - 1) / 16; c6 += 1)
        for (c8 = 16 * c0; c8 <= min(N - 1, 16 * c0 + 15); c8 += 1)
          for (c10 = 16 * c2; c10 <= min(N - 1, 16 * c2 + 15); c10 += 1)
            for (c12 = 16 * c6; c12 <= min(16 * c6 + 15, N - 1); c12 += 1)
            {
             lbv = 16*c4;
            ubv = min(N - 1, 16 * c4 + 15);
            #pragma ivdep
#pragma vector always
          for (c14 = lbv; c14 <= ubv; c14 += 1)
         // for (c14 = 16 * c4; c14 <= min(N - 1, 16 * c4 + 15); c14 += 1)

             // for (c14 = 16 * c4; c14 <= min(N - 1, 16 * c4 + 15); c14 += 1)
                sum[c8][c10][c14]=sum[c8][c10][c14]+A[c8][c10][c12]*C4[c12][c14];
            }
    }
    for (c4 = 0; c4 <= (N - 1) / 16; c4 += 1)
      for (c8 = 16 * c0; c8 <= min(16 * c0 + 15, N - 1); c8 += 1)
        for (c10 = 16 * c2; c10 <= min(N - 1, 16 * c2 + 15); c10 += 1){
          //for (c14 = 16 * c4; c14 <= min(16 * c4 + 15, N - 1); c14 += 1)
             lbv = 16*c4;
            ubv = min(N - 1, 16 * c4 + 15);
            #pragma ivdep
#pragma vector always
          for (c14 = lbv; c14 <= ubv; c14 += 1)


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
