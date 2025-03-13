#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>

#define nx 300
#define ny 300
#define nz 300
// #define T 20
// #define 9 9

#define f60 0.2
#define f61 0.5
#define f62 0.3

#define halfdtbydx 0.5
#define thirddtbydz 0.3
#define thirddtbydx 0.3
#define thirddtbydy 0.3

double a[nx+10][ny+10][nz+10];
double af[nx+10][ny+10][nz+10];
double ab[nx+10][ny+10][nz+10];
double al[nx+10][ny+10][nz+10];
double athird[nx+10][ny+10][nz+10];
double uxl[nx+10][ny+10][nz+10];
double uzf[nx+10][ny+10][nz+10];
double uyb[nx+10][ny+10][nz+10];


#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{

}


void print_array()
{
    int i, j, k;

    for (i=0; i<nx; i++) {
    for (j=0; j<ny; j++) {
    for (k=0; k<nz; k++) {
        fprintf(stdout, "%lf ", athird[i][j][k]);
        if (j%80 == 20) fprintf(stdout, "\n");
    }
    }
    }
    fprintf(stdout, "\n");
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

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

double t_start, t_end;

int main()
{
	assert(nx >= 100);
	assert(ny >= 100);
	assert(nz >= 100);
	int i, j, k, l, m, n, t;

  int t1, t2, t3, t4, t5, t6;
 register int lbv, ubv;
	init_array() ;

#ifdef PERFCTR
	PERF_INIT;
#endif

	t_start = rtclock();
#define reps 10

#pragma scop

/* Start of CLooG code */
if ((nx >= -3) && (nx >= -nz-5) && (ny >= -3) && (ny >= -nx-5) && (ny >= -nz-5) && (nz >= -3)) {
  for (t1=0;t1<=min(min(floord(ny+7,32),floord(ny+nx+9,32)),floord(ny+nz+9,32));t1++) {
    for (t2=0;t2<=min(min(floord(nx+7,32),floord(nx+nz+9,32)),floord(ny+nx+9,32));t2++) {
      for (t3=0;t3<=min(min(floord(nz+7,32),floord(nx+nz+9,32)),floord(ny+nz+9,32));t3++) {
        if ((nx >= -2) && (ny >= -2) && (nz >= -2) && (t1 == 0) && (t2 <= floord(nx+6,32)) && (t2 >= ceild(nx-24,32)) && (t3 <= floord(nz+6,32)) && (t3 >= ceild(nz-24,32))) {
          for (t5=max(4,32*t2);t5<=nx+6;t5++) {
            lbv=max(4,32*t3);
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[4][t5][t6] = (f60 * (a[4 -1][t5][t6] + a[4][t5][t6]) + f61 * (a[4 -2][t5][t6] + a[4 +1][t5][t6]) + f62 * (a[4 -3][t5][t6] + a[4 +2][t5][t6])) * thirddtbydy * uyb[4][t5][t6];;
              al[4][t5][t6] = (f60 * (a[4][t5-1][t6] + a[4][t5][t6]) + f61 * (a[4][t5-2][t6] + a[4][t5+1][t6]) + f62 * (a[4][t5-3][t6] + a[4][t5+2][t6])) * thirddtbydx * uxl[4][t5][t6];;
              af[4][t5][t6] = (f60 * (a[4][t5][t6-1] + a[4][t5][t6]) + f61 * (a[4][t5][t6-2] + a[4][t5][t6+1]) + f62 * (a[4][t5][t6-3] + a[4][t5][t6+2])) * thirddtbydz * uzf[4][t5][t6];;
            }
            af[4][t5][(nz+7)] = (f60 * (a[4][t5][(nz+7)-1] + a[4][t5][(nz+7)]) + f61 * (a[4][t5][(nz+7)-2] + a[4][t5][(nz+7)+1]) + f62 * (a[4][t5][(nz+7)-3] + a[4][t5][(nz+7)+2])) * thirddtbydz * uzf[4][t5][(nz+7)];;
          }
          lbv=max(4,32*t3);
          ubv=nz+6;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            al[4][(nx+7)][t6] = (f60 * (a[4][(nx+7)-1][t6] + a[4][(nx+7)][t6]) + f61 * (a[4][(nx+7)-2][t6] + a[4][(nx+7)+1][t6]) + f62 * (a[4][(nx+7)-3][t6] + a[4][(nx+7)+2][t6])) * thirddtbydx * uxl[4][(nx+7)][t6];;
          }
        }
        if ((ny >= -2) && (nz >= -2) && (t1 == 0) && (t2 <= floord(nx-25,32)) && (t3 <= floord(nz+6,32)) && (t3 >= ceild(nz-24,32))) {
          for (t5=max(4,32*t2);t5<=32*t2+31;t5++) {
            lbv=max(4,32*t3);
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[4][t5][t6] = (f60 * (a[4 -1][t5][t6] + a[4][t5][t6]) + f61 * (a[4 -2][t5][t6] + a[4 +1][t5][t6]) + f62 * (a[4 -3][t5][t6] + a[4 +2][t5][t6])) * thirddtbydy * uyb[4][t5][t6];;
              al[4][t5][t6] = (f60 * (a[4][t5-1][t6] + a[4][t5][t6]) + f61 * (a[4][t5-2][t6] + a[4][t5+1][t6]) + f62 * (a[4][t5-3][t6] + a[4][t5+2][t6])) * thirddtbydx * uxl[4][t5][t6];;
              af[4][t5][t6] = (f60 * (a[4][t5][t6-1] + a[4][t5][t6]) + f61 * (a[4][t5][t6-2] + a[4][t5][t6+1]) + f62 * (a[4][t5][t6-3] + a[4][t5][t6+2])) * thirddtbydz * uzf[4][t5][t6];;
            }
            af[4][t5][(nz+7)] = (f60 * (a[4][t5][(nz+7)-1] + a[4][t5][(nz+7)]) + f61 * (a[4][t5][(nz+7)-2] + a[4][t5][(nz+7)+1]) + f62 * (a[4][t5][(nz+7)-3] + a[4][t5][(nz+7)+2])) * thirddtbydz * uzf[4][t5][(nz+7)];;
          }
        }
        if ((nx >= -2) && (ny >= -2) && (t1 == 0) && (t2 <= floord(nx+6,32)) && (t2 >= ceild(nx-24,32)) && (t3 <= floord(nz-25,32))) {
          for (t5=max(4,32*t2);t5<=nx+6;t5++) {
            lbv=max(4,32*t3);
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[4][t5][t6] = (f60 * (a[4 -1][t5][t6] + a[4][t5][t6]) + f61 * (a[4 -2][t5][t6] + a[4 +1][t5][t6]) + f62 * (a[4 -3][t5][t6] + a[4 +2][t5][t6])) * thirddtbydy * uyb[4][t5][t6];;
              al[4][t5][t6] = (f60 * (a[4][t5-1][t6] + a[4][t5][t6]) + f61 * (a[4][t5-2][t6] + a[4][t5+1][t6]) + f62 * (a[4][t5-3][t6] + a[4][t5+2][t6])) * thirddtbydx * uxl[4][t5][t6];;
              af[4][t5][t6] = (f60 * (a[4][t5][t6-1] + a[4][t5][t6]) + f61 * (a[4][t5][t6-2] + a[4][t5][t6+1]) + f62 * (a[4][t5][t6-3] + a[4][t5][t6+2])) * thirddtbydz * uzf[4][t5][t6];;
            }
          }
          lbv=max(4,32*t3);
          ubv=32*t3+31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            al[4][(nx+7)][t6] = (f60 * (a[4][(nx+7)-1][t6] + a[4][(nx+7)][t6]) + f61 * (a[4][(nx+7)-2][t6] + a[4][(nx+7)+1][t6]) + f62 * (a[4][(nx+7)-3][t6] + a[4][(nx+7)+2][t6])) * thirddtbydx * uxl[4][(nx+7)][t6];;
          }
        }
        if ((ny >= -2) && (t1 == 0) && (t2 <= floord(nx-25,32)) && (t3 <= floord(nz-25,32))) {
          for (t5=max(4,32*t2);t5<=32*t2+31;t5++) {
            lbv=max(4,32*t3);
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[4][t5][t6] = (f60 * (a[4 -1][t5][t6] + a[4][t5][t6]) + f61 * (a[4 -2][t5][t6] + a[4 +1][t5][t6]) + f62 * (a[4 -3][t5][t6] + a[4 +2][t5][t6])) * thirddtbydy * uyb[4][t5][t6];;
              al[4][t5][t6] = (f60 * (a[4][t5-1][t6] + a[4][t5][t6]) + f61 * (a[4][t5-2][t6] + a[4][t5+1][t6]) + f62 * (a[4][t5-3][t6] + a[4][t5+2][t6])) * thirddtbydx * uxl[4][t5][t6];;
              af[4][t5][t6] = (f60 * (a[4][t5][t6-1] + a[4][t5][t6]) + f61 * (a[4][t5][t6-2] + a[4][t5][t6+1]) + f62 * (a[4][t5][t6-3] + a[4][t5][t6+2])) * thirddtbydz * uzf[4][t5][t6];;
            }
          }
        }
        if ((ny == -3) && (t1 == 0)) {
          for (t5=max(4,32*t2);t5<=min(nx+6,32*t2+31);t5++) {
            lbv=max(4,32*t3);
            ubv=min(nz+6,32*t3+31);
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[4][t5][t6] = (f60 * (a[4 -1][t5][t6] + a[4][t5][t6]) + f61 * (a[4 -2][t5][t6] + a[4 +1][t5][t6]) + f62 * (a[4 -3][t5][t6] + a[4 +2][t5][t6])) * thirddtbydy * uyb[4][t5][t6];;
            }
          }
        }
        if ((t1 == 0) && (32*t2 == nx+7) && (t3 <= floord(nz+6,32))) {
          lbv=max(4,32*t3);
          ubv=min(nz+6,32*t3+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            if ((nx+7)%32 == 0) {
              al[4][(nx+7)][t6] = (f60 * (a[4][(nx+7)-1][t6] + a[4][(nx+7)][t6]) + f61 * (a[4][(nx+7)-2][t6] + a[4][(nx+7)+1][t6]) + f62 * (a[4][(nx+7)-3][t6] + a[4][(nx+7)+2][t6])) * thirddtbydx * uxl[4][(nx+7)][t6];;
            }
          }
        }
        if ((nx == -3) && (t2 == 0)) {
          for (t4=max(4,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=max(4,32*t3);
            ubv=min(nz+6,32*t3+31);
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
            }
          }
        }
        if ((t1 == 0) && (t2 <= floord(nx+6,32)) && (32*t3 == nz+7)) {
          for (t5=max(4,32*t2);t5<=min(nx+6,32*t2+31);t5++) {
            if ((nz+7)%32 == 0) {
              af[4][t5][(nz+7)] = (f60 * (a[4][t5][(nz+7)-1] + a[4][t5][(nz+7)]) + f61 * (a[4][t5][(nz+7)-2] + a[4][t5][(nz+7)+1]) + f62 * (a[4][t5][(nz+7)-3] + a[4][t5][(nz+7)+2])) * thirddtbydz * uzf[4][t5][(nz+7)];;
            }
          }
        }
        if ((nz == -3) && (t3 == 0)) {
          for (t4=max(4,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=max(4,32*t2);t5<=min(nx+6,32*t2+31);t5++) {
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
            }
          }
        }
        if ((32*t2 == nx+7) && (32*t3 == nz+7)) {
          for (t4=max(5,32*t1);t4<=min(ny+7,32*t1+31);t4++) {
            if ((nz+7)%32 == 0) {
              if ((nx+7)%32 == 0) {
                athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
              }
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (nz >= -1) && (nz <= 24) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=4;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            for (t5=5;t5<=nx+6;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
            al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
            athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
          }
        }
        if ((nx >= 25) && (nz >= -1) && (nz <= 24) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=4;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            for (t5=5;t5<=31;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (nz == -2) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            ab[t4][4][4] = (f60 * (a[t4-1][4][4] + a[t4][4][4]) + f61 * (a[t4-2][4][4] + a[t4+1][4][4]) + f62 * (a[t4-3][4][4] + a[t4+2][4][4])) * thirddtbydy * uyb[t4][4][4];;
            al[t4][4][4] = (f60 * (a[t4][4 -1][4] + a[t4][4][4]) + f61 * (a[t4][4 -2][4] + a[t4][4 +1][4]) + f62 * (a[t4][4 -3][4] + a[t4][4 +2][4])) * thirddtbydx * uxl[t4][4][4];;
            af[t4][4][4] = (f60 * (a[t4][4][4 -1] + a[t4][4][4]) + f61 * (a[t4][4][4 -2] + a[t4][4][4 +1]) + f62 * (a[t4][4][4 -3] + a[t4][4][4 +2])) * thirddtbydz * uzf[t4][4][4];;
            af[t4][4][5] = (f60 * (a[t4][4][5 -1] + a[t4][4][5]) + f61 * (a[t4][4][5 -2] + a[t4][4][5 +1]) + f62 * (a[t4][4][5 -3] + a[t4][4][5 +2])) * thirddtbydz * uzf[t4][4][5];;
            for (t5=5;t5<=nx+6;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              athird[(t4-1)][(t5-1)][4] = a[(t4-1)][(t5-1)][4] + (al[(t4-1)][(t5-1)+1][4] - al[(t4-1)][(t5-1)][4]) + (ab[(t4-1)+1][(t5-1)][4] - ab[(t4-1)][(t5-1)][4]) + (af[(t4-1)][(t5-1)][4 +1] - af[(t4-1)][(t5-1)][4]);;
              af[t4][t5][5] = (f60 * (a[t4][t5][5 -1] + a[t4][t5][5]) + f61 * (a[t4][t5][5 -2] + a[t4][t5][5 +1]) + f62 * (a[t4][t5][5 -3] + a[t4][t5][5 +2])) * thirddtbydz * uzf[t4][t5][5];;
            }
            al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            athird[(t4-1)][(nx+6)][4] = a[(t4-1)][(nx+6)][4] + (al[(t4-1)][(nx+6)+1][4] - al[(t4-1)][(nx+6)][4]) + (ab[(t4-1)+1][(nx+6)][4] - ab[(t4-1)][(nx+6)][4]) + (af[(t4-1)][(nx+6)][4 +1] - af[(t4-1)][(nx+6)][4]);;
          }
        }
        if ((nx >= 25) && (nz == -2) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            ab[t4][4][4] = (f60 * (a[t4-1][4][4] + a[t4][4][4]) + f61 * (a[t4-2][4][4] + a[t4+1][4][4]) + f62 * (a[t4-3][4][4] + a[t4+2][4][4])) * thirddtbydy * uyb[t4][4][4];;
            al[t4][4][4] = (f60 * (a[t4][4 -1][4] + a[t4][4][4]) + f61 * (a[t4][4 -2][4] + a[t4][4 +1][4]) + f62 * (a[t4][4 -3][4] + a[t4][4 +2][4])) * thirddtbydx * uxl[t4][4][4];;
            af[t4][4][4] = (f60 * (a[t4][4][4 -1] + a[t4][4][4]) + f61 * (a[t4][4][4 -2] + a[t4][4][4 +1]) + f62 * (a[t4][4][4 -3] + a[t4][4][4 +2])) * thirddtbydz * uzf[t4][4][4];;
            af[t4][4][5] = (f60 * (a[t4][4][5 -1] + a[t4][4][5]) + f61 * (a[t4][4][5 -2] + a[t4][4][5 +1]) + f62 * (a[t4][4][5 -3] + a[t4][4][5 +2])) * thirddtbydz * uzf[t4][4][5];;
            for (t5=5;t5<=31;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              athird[(t4-1)][(t5-1)][4] = a[(t4-1)][(t5-1)][4] + (al[(t4-1)][(t5-1)+1][4] - al[(t4-1)][(t5-1)][4]) + (ab[(t4-1)+1][(t5-1)][4] - ab[(t4-1)][(t5-1)][4]) + (af[(t4-1)][(t5-1)][4 +1] - af[(t4-1)][(t5-1)][4]);;
              af[t4][t5][5] = (f60 * (a[t4][t5][5 -1] + a[t4][t5][5]) + f61 * (a[t4][t5][5 -2] + a[t4][t5][5 +1]) + f62 * (a[t4][t5][5 -3] + a[t4][t5][5 +2])) * thirddtbydz * uzf[t4][t5][5];;
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (t2 == 0) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            for (t5=5;t5<=nx+6;t5++) {
              lbv=32*t3;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
            athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
          }
        }
        if ((nx >= 25) && (t2 == 0) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            for (t5=5;t5<=31;t5++) {
              lbv=32*t3;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
          }
        }
        if ((nx == -2) && (nz >= -1) && (nz <= 24) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=4;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            al[t4][5][4] = (f60 * (a[t4][5 -1][4] + a[t4][5][4]) + f61 * (a[t4][5 -2][4] + a[t4][5 +1][4]) + f62 * (a[t4][5 -3][4] + a[t4][5 +2][4])) * thirddtbydx * uxl[t4][5][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][5][t6] = (f60 * (a[t4][5 -1][t6] + a[t4][5][t6]) + f61 * (a[t4][5 -2][t6] + a[t4][5 +1][t6]) + f62 * (a[t4][5 -3][t6] + a[t4][5 +2][t6])) * thirddtbydx * uxl[t4][5][t6];;
              athird[(t4-1)][4][(t6-1)] = a[(t4-1)][4][(t6-1)] + (al[(t4-1)][4 +1][(t6-1)] - al[(t4-1)][4][(t6-1)]) + (ab[(t4-1)+1][4][(t6-1)] - ab[(t4-1)][4][(t6-1)]) + (af[(t4-1)][4][(t6-1)+1] - af[(t4-1)][4][(t6-1)]);;
            }
            athird[(t4-1)][4][(nz+6)] = a[(t4-1)][4][(nz+6)] + (al[(t4-1)][4 +1][(nz+6)] - al[(t4-1)][4][(nz+6)]) + (ab[(t4-1)+1][4][(nz+6)] - ab[(t4-1)][4][(nz+6)]) + (af[(t4-1)][4][(nz+6)+1] - af[(t4-1)][4][(nz+6)]);;
          }
        }
        if ((nx == -2) && (nz == -2) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            ab[t4][4][4] = (f60 * (a[t4-1][4][4] + a[t4][4][4]) + f61 * (a[t4-2][4][4] + a[t4+1][4][4]) + f62 * (a[t4-3][4][4] + a[t4+2][4][4])) * thirddtbydy * uyb[t4][4][4];;
            al[t4][4][4] = (f60 * (a[t4][4 -1][4] + a[t4][4][4]) + f61 * (a[t4][4 -2][4] + a[t4][4 +1][4]) + f62 * (a[t4][4 -3][4] + a[t4][4 +2][4])) * thirddtbydx * uxl[t4][4][4];;
            af[t4][4][4] = (f60 * (a[t4][4][4 -1] + a[t4][4][4]) + f61 * (a[t4][4][4 -2] + a[t4][4][4 +1]) + f62 * (a[t4][4][4 -3] + a[t4][4][4 +2])) * thirddtbydz * uzf[t4][4][4];;
            af[t4][4][5] = (f60 * (a[t4][4][5 -1] + a[t4][4][5]) + f61 * (a[t4][4][5 -2] + a[t4][4][5 +1]) + f62 * (a[t4][4][5 -3] + a[t4][4][5 +2])) * thirddtbydz * uzf[t4][4][5];;
            al[t4][5][4] = (f60 * (a[t4][5 -1][4] + a[t4][5][4]) + f61 * (a[t4][5 -2][4] + a[t4][5 +1][4]) + f62 * (a[t4][5 -3][4] + a[t4][5 +2][4])) * thirddtbydx * uxl[t4][5][4];;
            athird[(t4-1)][4][4] = a[(t4-1)][4][4] + (al[(t4-1)][4 +1][4] - al[(t4-1)][4][4]) + (ab[(t4-1)+1][4][4] - ab[(t4-1)][4][4]) + (af[(t4-1)][4][4 +1] - af[(t4-1)][4][4]);;
          }
        }
        if ((nx == -2) && (t2 == 0) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][5][t6] = (f60 * (a[t4][5 -1][t6] + a[t4][5][t6]) + f61 * (a[t4][5 -2][t6] + a[t4][5 +1][t6]) + f62 * (a[t4][5 -3][t6] + a[t4][5 +2][t6])) * thirddtbydx * uxl[t4][5][t6];;
              athird[(t4-1)][4][(t6-1)] = a[(t4-1)][4][(t6-1)] + (al[(t4-1)][4 +1][(t6-1)] - al[(t4-1)][4][(t6-1)]) + (ab[(t4-1)+1][4][(t6-1)] - ab[(t4-1)][4][(t6-1)]) + (af[(t4-1)][4][(t6-1)+1] - af[(t4-1)][4][(t6-1)]);;
            }
            athird[(t4-1)][4][(nz+6)] = a[(t4-1)][4][(nz+6)] + (al[(t4-1)][4 +1][(nz+6)] - al[(t4-1)][4][(nz+6)]) + (ab[(t4-1)+1][4][(nz+6)] - ab[(t4-1)][4][(nz+6)]) + (af[(t4-1)][4][(nz+6)+1] - af[(t4-1)][4][(nz+6)]);;
          }
        }
        if ((nx >= -1) && (nx <= 24) && (nz >= 25) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=4;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            for (t5=5;t5<=nx+6;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
            al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
          }
        }
        if ((nx >= 25) && (nz >= 25) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=4;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            for (t5=5;t5<=31;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
          }
        }
        if ((nx == -2) && (nz >= 25) && (t2 == 0) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=4;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            al[t4][5][4] = (f60 * (a[t4][5 -1][4] + a[t4][5][4]) + f61 * (a[t4][5 -2][4] + a[t4][5 +1][4]) + f62 * (a[t4][5 -3][4] + a[t4][5 +2][4])) * thirddtbydx * uxl[t4][5][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][5][t6] = (f60 * (a[t4][5 -1][t6] + a[t4][5][t6]) + f61 * (a[t4][5 -2][t6] + a[t4][5 +1][t6]) + f62 * (a[t4][5 -3][t6] + a[t4][5 +2][t6])) * thirddtbydx * uxl[t4][5][t6];;
              athird[(t4-1)][4][(t6-1)] = a[(t4-1)][4][(t6-1)] + (al[(t4-1)][4 +1][(t6-1)] - al[(t4-1)][4][(t6-1)]) + (ab[(t4-1)+1][4][(t6-1)] - ab[(t4-1)][4][(t6-1)]) + (af[(t4-1)][4][(t6-1)+1] - af[(t4-1)][4][(t6-1)]);;
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (t2 == 0) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            for (t5=5;t5<=nx+6;t5++) {
              lbv=32*t3;
              ubv=32*t3+31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
          }
        }
        if ((nx >= 25) && (t2 == 0) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            for (t5=5;t5<=31;t5++) {
              lbv=32*t3;
              ubv=32*t3+31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
          }
        }
        if ((nx == -2) && (t2 == 0) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[t4][4][t6] = (f60 * (a[t4-1][4][t6] + a[t4][4][t6]) + f61 * (a[t4-2][4][t6] + a[t4+1][4][t6]) + f62 * (a[t4-3][4][t6] + a[t4+2][4][t6])) * thirddtbydy * uyb[t4][4][t6];;
              al[t4][4][t6] = (f60 * (a[t4][4 -1][t6] + a[t4][4][t6]) + f61 * (a[t4][4 -2][t6] + a[t4][4 +1][t6]) + f62 * (a[t4][4 -3][t6] + a[t4][4 +2][t6])) * thirddtbydx * uxl[t4][4][t6];;
              af[t4][4][t6] = (f60 * (a[t4][4][t6-1] + a[t4][4][t6]) + f61 * (a[t4][4][t6-2] + a[t4][4][t6+1]) + f62 * (a[t4][4][t6-3] + a[t4][4][t6+2])) * thirddtbydz * uzf[t4][4][t6];;
            }
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][5][t6] = (f60 * (a[t4][5 -1][t6] + a[t4][5][t6]) + f61 * (a[t4][5 -2][t6] + a[t4][5 +1][t6]) + f62 * (a[t4][5 -3][t6] + a[t4][5 +2][t6])) * thirddtbydx * uxl[t4][5][t6];;
              athird[(t4-1)][4][(t6-1)] = a[(t4-1)][4][(t6-1)] + (al[(t4-1)][4 +1][(t6-1)] - al[(t4-1)][4][(t6-1)]) + (ab[(t4-1)+1][4][(t6-1)] - ab[(t4-1)][4][(t6-1)]) + (af[(t4-1)][4][(t6-1)+1] - af[(t4-1)][4][(t6-1)]);;
            }
          }
        }
        if ((nz >= -1) && (nz <= 24) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=nx+6;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
            al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
            athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
          }
        }
        if ((nz >= -1) && (nz <= 24) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=32*t2+31;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
          }
        }
        if ((nz >= 25) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=nx+6;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
            al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
          }
        }
        if ((nz >= 25) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=32*t2+31;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              lbv=5;
              ubv=31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
          }
        }
        if ((nz == -2) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=nx+6;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              athird[(t4-1)][(t5-1)][4] = a[(t4-1)][(t5-1)][4] + (al[(t4-1)][(t5-1)+1][4] - al[(t4-1)][(t5-1)][4]) + (ab[(t4-1)+1][(t5-1)][4] - ab[(t4-1)][(t5-1)][4]) + (af[(t4-1)][(t5-1)][4 +1] - af[(t4-1)][(t5-1)][4]);;
              af[t4][t5][5] = (f60 * (a[t4][t5][5 -1] + a[t4][t5][5]) + f61 * (a[t4][t5][5 -2] + a[t4][t5][5 +1]) + f62 * (a[t4][t5][5 -3] + a[t4][t5][5 +2])) * thirddtbydz * uzf[t4][t5][5];;
            }
            al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            athird[(t4-1)][(nx+6)][4] = a[(t4-1)][(nx+6)][4] + (al[(t4-1)][(nx+6)+1][4] - al[(t4-1)][(nx+6)][4]) + (ab[(t4-1)+1][(nx+6)][4] - ab[(t4-1)][(nx+6)][4]) + (af[(t4-1)][(nx+6)][4 +1] - af[(t4-1)][(nx+6)][4]);;
          }
        }
        if ((nz == -2) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=32*t2+31;t5++) {
              ab[t4][t5][4] = (f60 * (a[t4-1][t5][4] + a[t4][t5][4]) + f61 * (a[t4-2][t5][4] + a[t4+1][t5][4]) + f62 * (a[t4-3][t5][4] + a[t4+2][t5][4])) * thirddtbydy * uyb[t4][t5][4];;
              al[t4][t5][4] = (f60 * (a[t4][t5-1][4] + a[t4][t5][4]) + f61 * (a[t4][t5-2][4] + a[t4][t5+1][4]) + f62 * (a[t4][t5-3][4] + a[t4][t5+2][4])) * thirddtbydx * uxl[t4][t5][4];;
              af[t4][t5][4] = (f60 * (a[t4][t5][4 -1] + a[t4][t5][4]) + f61 * (a[t4][t5][4 -2] + a[t4][t5][4 +1]) + f62 * (a[t4][t5][4 -3] + a[t4][t5][4 +2])) * thirddtbydz * uzf[t4][t5][4];;
              athird[(t4-1)][(t5-1)][4] = a[(t4-1)][(t5-1)][4] + (al[(t4-1)][(t5-1)+1][4] - al[(t4-1)][(t5-1)][4]) + (ab[(t4-1)+1][(t5-1)][4] - ab[(t4-1)][(t5-1)][4]) + (af[(t4-1)][(t5-1)][4 +1] - af[(t4-1)][(t5-1)][4]);;
              af[t4][t5][5] = (f60 * (a[t4][t5][5 -1] + a[t4][t5][5]) + f61 * (a[t4][t5][5 -2] + a[t4][t5][5 +1]) + f62 * (a[t4][t5][5 -3] + a[t4][t5][5 +2])) * thirddtbydz * uzf[t4][t5][5];;
            }
          }
        }
        if ((t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=nx+6;t5++) {
              lbv=32*t3;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
            athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
          }
        }
        if ((t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=32*t2+31;t5++) {
              lbv=32*t3;
              ubv=nz+6;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
              athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
            }
          }
        }
        if ((t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=nx+6;t5++) {
              lbv=32*t3;
              ubv=32*t3+31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
            }
          }
        }
        if ((t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=32*t2+31;t5++) {
              lbv=32*t3;
              ubv=32*t3+31;
#pragma ivdep
#pragma vector always
              for (t6=lbv;t6<=ubv;t6++) {
                ab[t4][t5][t6] = (f60 * (a[t4-1][t5][t6] + a[t4][t5][t6]) + f61 * (a[t4-2][t5][t6] + a[t4+1][t5][t6]) + f62 * (a[t4-3][t5][t6] + a[t4+2][t5][t6])) * thirddtbydy * uyb[t4][t5][t6];;
                al[t4][t5][t6] = (f60 * (a[t4][t5-1][t6] + a[t4][t5][t6]) + f61 * (a[t4][t5-2][t6] + a[t4][t5+1][t6]) + f62 * (a[t4][t5-3][t6] + a[t4][t5+2][t6])) * thirddtbydx * uxl[t4][t5][t6];;
                af[t4][t5][t6] = (f60 * (a[t4][t5][t6-1] + a[t4][t5][t6]) + f61 * (a[t4][t5][t6-2] + a[t4][t5][t6+1]) + f62 * (a[t4][t5][t6-3] + a[t4][t5][t6+2])) * thirddtbydz * uzf[t4][t5][t6];;
                athird[(t4-1)][(t5-1)][(t6-1)] = a[(t4-1)][(t5-1)][(t6-1)] + (al[(t4-1)][(t5-1)+1][(t6-1)] - al[(t4-1)][(t5-1)][(t6-1)]) + (ab[(t4-1)+1][(t5-1)][(t6-1)] - ab[(t4-1)][(t5-1)][(t6-1)]) + (af[(t4-1)][(t5-1)][(t6-1)+1] - af[(t4-1)][(t5-1)][(t6-1)]);;
              }
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (ny >= -2) && (nz >= -1) && (nz <= 24) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 == 0)) {
          lbv=4;
          ubv=nz+6;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=nx+6;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
          lbv=5;
          ubv=nz+7;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((nx >= 25) && (ny >= -2) && (nz >= -1) && (nz <= 24) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 == 0)) {
          lbv=4;
          ubv=nz+6;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=31;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
        }
        if ((nx >= -1) && (nx <= 24) && (ny >= -2) && (nz == -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 == 0)) {
          ab[(ny+7)][4][4] = (f60 * (a[(ny+7)-1][4][4] + a[(ny+7)][4][4]) + f61 * (a[(ny+7)-2][4][4] + a[(ny+7)+1][4][4]) + f62 * (a[(ny+7)-3][4][4] + a[(ny+7)+2][4][4])) * thirddtbydy * uyb[(ny+7)][4][4];;
          for (t5=5;t5<=nx+6;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            athird[(ny+6)][(t5-1)][4] = a[(ny+6)][(t5-1)][4] + (al[(ny+6)][(t5-1)+1][4] - al[(ny+6)][(t5-1)][4]) + (ab[(ny+6)+1][(t5-1)][4] - ab[(ny+6)][(t5-1)][4]) + (af[(ny+6)][(t5-1)][4 +1] - af[(ny+6)][(t5-1)][4]);;
          }
          athird[(ny+6)][(nx+6)][4] = a[(ny+6)][(nx+6)][4] + (al[(ny+6)][(nx+6)+1][4] - al[(ny+6)][(nx+6)][4]) + (ab[(ny+6)+1][(nx+6)][4] - ab[(ny+6)][(nx+6)][4]) + (af[(ny+6)][(nx+6)][4 +1] - af[(ny+6)][(nx+6)][4]);;
        }
        if ((nx >= 25) && (ny >= -2) && (nz == -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 == 0)) {
          ab[(ny+7)][4][4] = (f60 * (a[(ny+7)-1][4][4] + a[(ny+7)][4][4]) + f61 * (a[(ny+7)-2][4][4] + a[(ny+7)+1][4][4]) + f62 * (a[(ny+7)-3][4][4] + a[(ny+7)+2][4][4])) * thirddtbydy * uyb[(ny+7)][4][4];;
          for (t5=5;t5<=31;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            athird[(ny+6)][(t5-1)][4] = a[(ny+6)][(t5-1)][4] + (al[(ny+6)][(t5-1)+1][4] - al[(ny+6)][(t5-1)][4]) + (ab[(ny+6)+1][(t5-1)][4] - ab[(ny+6)][(t5-1)][4]) + (af[(ny+6)][(t5-1)][4 +1] - af[(ny+6)][(t5-1)][4]);;
          }
        }
        if ((nx >= -1) && (nx <= 24) && (ny >= -2) && (nz >= 25) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 == 0)) {
          lbv=4;
          ubv=31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=nx+6;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
          lbv=5;
          ubv=31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((nx >= 25) && (ny >= -2) && (nz >= 25) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 == 0)) {
          lbv=4;
          ubv=31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=31;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          lbv=32*t3;
          ubv=nz+6;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=nx+6;t5++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
          lbv=32*t3;
          ubv=nz+7;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((nx >= 25) && (ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          lbv=32*t3;
          ubv=nz+6;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=31;t5++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
        }
        if ((nx >= -1) && (nx <= 24) && (ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          lbv=32*t3;
          ubv=32*t3+31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=nx+6;t5++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
          lbv=32*t3;
          ubv=32*t3+31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((nx >= 25) && (ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          lbv=32*t3;
          ubv=32*t3+31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          for (t5=5;t5<=31;t5++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
        }
        if ((nx == -2) && (ny >= -2) && (nz >= -2) && (t1 >= ceild(ny-24,32)) && (t2 == 0) && (t3 <= floord(nz+6,32))) {
          lbv=max(4,32*t3);
          ubv=min(nz+6,32*t3+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            ab[(ny+7)][4][t6] = (f60 * (a[(ny+7)-1][4][t6] + a[(ny+7)][4][t6]) + f61 * (a[(ny+7)-2][4][t6] + a[(ny+7)+1][4][t6]) + f62 * (a[(ny+7)-3][4][t6] + a[(ny+7)+2][4][t6])) * thirddtbydy * uyb[(ny+7)][4][t6];;
          }
          lbv=max(5,32*t3);
          ubv=min(nz+7,32*t3+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][4][(t6-1)] = a[(ny+6)][4][(t6-1)] + (al[(ny+6)][4 +1][(t6-1)] - al[(ny+6)][4][(t6-1)]) + (ab[(ny+6)+1][4][(t6-1)] - ab[(ny+6)][4][(t6-1)]) + (af[(ny+6)][4][(t6-1)+1] - af[(ny+6)][4][(t6-1)]);;
          }
        }
        if ((ny >= -2) && (nz >= -1) && (nz <= 24) && (t1 >= ceild(ny-24,32)) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 == 0)) {
          for (t5=32*t2;t5<=nx+6;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
          lbv=5;
          ubv=nz+7;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((ny >= -2) && (nz >= -1) && (nz <= 24) && (t1 >= ceild(ny-24,32)) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 == 0)) {
          for (t5=32*t2;t5<=32*t2+31;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
        }
        if ((ny >= -2) && (nz >= 25) && (t1 >= ceild(ny-24,32)) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 == 0)) {
          for (t5=32*t2;t5<=nx+6;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
          lbv=5;
          ubv=31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((ny >= -2) && (nz >= 25) && (t1 >= ceild(ny-24,32)) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 == 0)) {
          for (t5=32*t2;t5<=32*t2+31;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
        }
        if ((ny >= -2) && (nz == -2) && (t1 >= ceild(ny-24,32)) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 == 0)) {
          for (t5=32*t2;t5<=nx+6;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            athird[(ny+6)][(t5-1)][4] = a[(ny+6)][(t5-1)][4] + (al[(ny+6)][(t5-1)+1][4] - al[(ny+6)][(t5-1)][4]) + (ab[(ny+6)+1][(t5-1)][4] - ab[(ny+6)][(t5-1)][4]) + (af[(ny+6)][(t5-1)][4 +1] - af[(ny+6)][(t5-1)][4]);;
          }
          athird[(ny+6)][(nx+6)][4] = a[(ny+6)][(nx+6)][4] + (al[(ny+6)][(nx+6)+1][4] - al[(ny+6)][(nx+6)][4]) + (ab[(ny+6)+1][(nx+6)][4] - ab[(ny+6)][(nx+6)][4]) + (af[(ny+6)][(nx+6)][4 +1] - af[(ny+6)][(nx+6)][4]);;
        }
        if ((ny >= -2) && (nz == -2) && (t1 >= ceild(ny-24,32)) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 == 0)) {
          for (t5=32*t2;t5<=32*t2+31;t5++) {
            ab[(ny+7)][t5][4] = (f60 * (a[(ny+7)-1][t5][4] + a[(ny+7)][t5][4]) + f61 * (a[(ny+7)-2][t5][4] + a[(ny+7)+1][t5][4]) + f62 * (a[(ny+7)-3][t5][4] + a[(ny+7)+2][t5][4])) * thirddtbydy * uyb[(ny+7)][t5][4];;
            athird[(ny+6)][(t5-1)][4] = a[(ny+6)][(t5-1)][4] + (al[(ny+6)][(t5-1)+1][4] - al[(ny+6)][(t5-1)][4]) + (ab[(ny+6)+1][(t5-1)][4] - ab[(ny+6)][(t5-1)][4]) + (af[(ny+6)][(t5-1)][4 +1] - af[(ny+6)][(t5-1)][4]);;
          }
        }
        if ((ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t5=32*t2;t5<=nx+6;t5++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
          lbv=32*t3;
          ubv=nz+7;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t5=32*t2;t5<=32*t2+31;t5++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
            athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
          }
        }
        if ((ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t5=32*t2;t5<=nx+6;t5++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
          lbv=32*t3;
          ubv=32*t3+31;
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
          }
        }
        if ((ny >= -2) && (t1 >= ceild(ny-24,32)) && (t2 >= 1) && (t2 <= floord(nx-25,32)) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t5=32*t2;t5<=32*t2+31;t5++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              ab[(ny+7)][t5][t6] = (f60 * (a[(ny+7)-1][t5][t6] + a[(ny+7)][t5][t6]) + f61 * (a[(ny+7)-2][t5][t6] + a[(ny+7)+1][t5][t6]) + f62 * (a[(ny+7)-3][t5][t6] + a[(ny+7)+2][t5][t6])) * thirddtbydy * uyb[(ny+7)][t5][t6];;
              athird[(ny+6)][(t5-1)][(t6-1)] = a[(ny+6)][(t5-1)][(t6-1)] + (al[(ny+6)][(t5-1)+1][(t6-1)] - al[(ny+6)][(t5-1)][(t6-1)]) + (ab[(ny+6)+1][(t5-1)][(t6-1)] - ab[(ny+6)][(t5-1)][(t6-1)]) + (af[(ny+6)][(t5-1)][(t6-1)+1] - af[(ny+6)][(t5-1)][(t6-1)]);;
            }
          }
        }
        if ((nz >= -1) && (nz <= 24) && (32*t2 == nx+7) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            if ((nx+7)%32 == 0) {
              al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            }
            lbv=5;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              if ((nx+7)%32 == 0) {
                al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              }
              if ((nx+7)%32 == 0) {
                athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
              }
            }
            if ((nx+7)%32 == 0) {
              athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
            }
          }
        }
        if ((nz >= 25) && (32*t2 == nx+7) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            if ((nx+7)%32 == 0) {
              al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            }
            lbv=5;
            ubv=31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              if ((nx+7)%32 == 0) {
                al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              }
              if ((nx+7)%32 == 0) {
                athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
              }
            }
          }
        }
        if ((nz == -2) && (32*t2 == nx+7) && (t3 == 0)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            if ((nx+7)%32 == 0) {
              al[t4][(nx+7)][4] = (f60 * (a[t4][(nx+7)-1][4] + a[t4][(nx+7)][4]) + f61 * (a[t4][(nx+7)-2][4] + a[t4][(nx+7)+1][4]) + f62 * (a[t4][(nx+7)-3][4] + a[t4][(nx+7)+2][4])) * thirddtbydx * uxl[t4][(nx+7)][4];;
            }
            if ((nx+7)%32 == 0) {
              athird[(t4-1)][(nx+6)][4] = a[(t4-1)][(nx+6)][4] + (al[(t4-1)][(nx+6)+1][4] - al[(t4-1)][(nx+6)][4]) + (ab[(t4-1)+1][(nx+6)][4] - ab[(t4-1)][(nx+6)][4]) + (af[(t4-1)][(nx+6)][4 +1] - af[(t4-1)][(nx+6)][4]);;
            }
          }
        }
        if ((32*t2 == nx+7) && (t3 <= floord(nz+6,32)) && (t3 >= max(1,ceild(nz-24,32)))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=nz+6;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              if ((nx+7)%32 == 0) {
                al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              }
              if ((nx+7)%32 == 0) {
                athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
              }
            }
            if ((nx+7)%32 == 0) {
              athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
            }
          }
        }
        if ((32*t2 == nx+7) && (t3 >= 1) && (t3 <= floord(nz-25,32))) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            lbv=32*t3;
            ubv=32*t3+31;
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              if ((nx+7)%32 == 0) {
                al[t4][(nx+7)][t6] = (f60 * (a[t4][(nx+7)-1][t6] + a[t4][(nx+7)][t6]) + f61 * (a[t4][(nx+7)-2][t6] + a[t4][(nx+7)+1][t6]) + f62 * (a[t4][(nx+7)-3][t6] + a[t4][(nx+7)+2][t6])) * thirddtbydx * uxl[t4][(nx+7)][t6];;
              }
              if ((nx+7)%32 == 0) {
                athird[(t4-1)][(nx+6)][(t6-1)] = a[(t4-1)][(nx+6)][(t6-1)] + (al[(t4-1)][(nx+6)+1][(t6-1)] - al[(t4-1)][(nx+6)][(t6-1)]) + (ab[(t4-1)+1][(nx+6)][(t6-1)] - ab[(t4-1)][(nx+6)][(t6-1)]) + (af[(t4-1)][(nx+6)][(t6-1)+1] - af[(t4-1)][(nx+6)][(t6-1)]);;
              }
            }
          }
        }
        if ((nx >= -1) && (nx <= 24) && (t2 == 0) && (32*t3 == nz+7)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            if ((nz+7)%32 == 0) {
              af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            }
            for (t5=5;t5<=nx+6;t5++) {
              if ((nz+7)%32 == 0) {
                athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              }
              if ((nz+7)%32 == 0) {
                af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
              }
            }
            if ((nz+7)%32 == 0) {
              athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
            }
          }
        }
        if ((nx >= 25) && (t2 == 0) && (32*t3 == nz+7)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            if ((nz+7)%32 == 0) {
              af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            }
            for (t5=5;t5<=31;t5++) {
              if ((nz+7)%32 == 0) {
                athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              }
              if ((nz+7)%32 == 0) {
                af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
              }
            }
          }
        }
        if ((nx == -2) && (t2 == 0) && (32*t3 == nz+7)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            if ((nz+7)%32 == 0) {
              af[t4][4][(nz+7)] = (f60 * (a[t4][4][(nz+7)-1] + a[t4][4][(nz+7)]) + f61 * (a[t4][4][(nz+7)-2] + a[t4][4][(nz+7)+1]) + f62 * (a[t4][4][(nz+7)-3] + a[t4][4][(nz+7)+2])) * thirddtbydz * uzf[t4][4][(nz+7)];;
            }
            if ((nz+7)%32 == 0) {
              athird[(t4-1)][4][(nz+6)] = a[(t4-1)][4][(nz+6)] + (al[(t4-1)][4 +1][(nz+6)] - al[(t4-1)][4][(nz+6)]) + (ab[(t4-1)+1][4][(nz+6)] - ab[(t4-1)][4][(nz+6)]) + (af[(t4-1)][4][(nz+6)+1] - af[(t4-1)][4][(nz+6)]);;
            }
          }
        }
        if ((t2 <= floord(nx+6,32)) && (t2 >= max(1,ceild(nx-24,32))) && (32*t3 == nz+7)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=nx+6;t5++) {
              if ((nz+7)%32 == 0) {
                athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              }
              if ((nz+7)%32 == 0) {
                af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
              }
            }
            if ((nz+7)%32 == 0) {
              athird[(t4-1)][(nx+6)][(nz+6)] = a[(t4-1)][(nx+6)][(nz+6)] + (al[(t4-1)][(nx+6)+1][(nz+6)] - al[(t4-1)][(nx+6)][(nz+6)]) + (ab[(t4-1)+1][(nx+6)][(nz+6)] - ab[(t4-1)][(nx+6)][(nz+6)]) + (af[(t4-1)][(nx+6)][(nz+6)+1] - af[(t4-1)][(nx+6)][(nz+6)]);;
            }
          }
        }
        if ((t2 >= 1) && (t2 <= floord(nx-25,32)) && (32*t3 == nz+7)) {
          for (t4=max(5,32*t1);t4<=min(ny+6,32*t1+31);t4++) {
            for (t5=32*t2;t5<=32*t2+31;t5++) {
              if ((nz+7)%32 == 0) {
                athird[(t4-1)][(t5-1)][(nz+6)] = a[(t4-1)][(t5-1)][(nz+6)] + (al[(t4-1)][(t5-1)+1][(nz+6)] - al[(t4-1)][(t5-1)][(nz+6)]) + (ab[(t4-1)+1][(t5-1)][(nz+6)] - ab[(t4-1)][(t5-1)][(nz+6)]) + (af[(t4-1)][(t5-1)][(nz+6)+1] - af[(t4-1)][(t5-1)][(nz+6)]);;
              }
              if ((nz+7)%32 == 0) {
                af[t4][t5][(nz+7)] = (f60 * (a[t4][t5][(nz+7)-1] + a[t4][t5][(nz+7)]) + f61 * (a[t4][t5][(nz+7)-2] + a[t4][t5][(nz+7)+1]) + f62 * (a[t4][t5][(nz+7)-3] + a[t4][t5][(nz+7)+2])) * thirddtbydz * uzf[t4][t5][(nz+7)];;
              }
            }
          }
        }
        if ((t1 >= ceild(ny-24,32)) && (t2 <= floord(nx+6,32)) && (32*t3 == nz+7)) {
          for (t5=max(5,32*t2);t5<=min(nx+7,32*t2+31);t5++) {
            if ((nz+7)%32 == 0) {
              athird[(ny+6)][(t5-1)][(nz+6)] = a[(ny+6)][(t5-1)][(nz+6)] + (al[(ny+6)][(t5-1)+1][(nz+6)] - al[(ny+6)][(t5-1)][(nz+6)]) + (ab[(ny+6)+1][(t5-1)][(nz+6)] - ab[(ny+6)][(t5-1)][(nz+6)]) + (af[(ny+6)][(t5-1)][(nz+6)+1] - af[(ny+6)][(t5-1)][(nz+6)]);;
            }
          }
        }
        if ((t1 >= ceild(ny-24,32)) && (32*t2 == nx+7) && (t3 <= floord(nz+6,32))) {
          lbv=max(5,32*t3);
          ubv=min(nz+7,32*t3+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            if ((nx+7)%32 == 0) {
              athird[(ny+6)][(nx+6)][(t6-1)] = a[(ny+6)][(nx+6)][(t6-1)] + (al[(ny+6)][(nx+6)+1][(t6-1)] - al[(ny+6)][(nx+6)][(t6-1)]) + (ab[(ny+6)+1][(nx+6)][(t6-1)] - ab[(ny+6)][(nx+6)][(t6-1)]) + (af[(ny+6)][(nx+6)][(t6-1)+1] - af[(ny+6)][(nx+6)][(t6-1)]);;
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
#pragma endscop


    t_end = rtclock();
    printf("%0.6lfs\n", t_end - t_start);

#ifdef PERFCTR
    PERF_EXIT;
#endif

#ifdef TEST
    print_array();
#endif
    return 0;
}

