#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include <omp.h>

#define N 100

#pragma declarations

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

double A[N+2][N+2][N+2][N+2];
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
      //  alpha[i] = beta[i] = r[i] = (i+1)*j;
        for (j=0; j<N; j++) {
          //  y[i][j] = (i+1)*(j+1);//i==j?1:0;
          //  sum[i][j] = (i+1)*(j+1);//i==j?1:0;
        }
    }
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

int main(int argc, char *argv[])
{
	int i, j, k, t, T=N;
    double t_start, t_end;

	init_array() ;

    int t1, t3, c1, c3, c5, t5,t2,lbp,ubp,lbv,ubv,t4;


  int num_proc=1;
  num_proc = atoi(argv[1]);



    omp_set_num_threads(num_proc);


	t_start = rtclock();
int c = 0;
#pragma scop
if ((N >= 1) && (T >= 1)) {
  for (t1=1;t1<=2*T+N-2;t1++) {
    lbp=max(ceild(t1+1,2),t1-T+1);
    ubp=min(floord(t1+N,2),t1);
#pragma omp parallel for private(lbv,ubv,t3,t4)
    for (t2=lbp;t2<=ubp;t2++) {
      for (t3=t1-t2+1;t3<=t1-t2+N;t3++) {
        lbv=t1-t2+1;
        ubv=t1-t2+N;
#pragma ivdep
#pragma vector always
        for (t4=lbv;t4<=ubv;t4++) {
          A[(t1-t2)+1][(-t1+2*t2) ][ (-t1+t2+t3) ][(-t1+t2+t4)] = 0.125 *(A[(t1-t2)][ (-t1+2*t2)+1][(-t1+t2+t3) ][(-t1+t2+t4)] -2.0*A[(t1-t2)][(-t1+2*t2) ][ (-t1+t2+t3) ][(-t1+t2+t4)] +A[(t1-t2)][ (-t1+2*t2)-1][(-t1+t2+t3)][(-t1+t2+t4)])+ 0.125 *(A[(t1-t2)][ (-t1+2*t2) ][ (-t1+t2+t3)+1][(-t1+t2+t4)] -2.0*A[(t1-t2)][(-t1+2*t2) ][ (-t1+t2+t3) ][(-t1+t2+t4)] +A[(t1-t2)][ (-t1+2*t2) ][ (-t1+t2+t3)-1][(-t1+t2+t4)]) + 0.125 *(A[(t1-t2)][ (-t1+2*t2) ][ (-t1+t2+t3)][(-t1+t2+t4)-1] -2.0*A[(t1-t2)][(-t1+2*t2) ][ (-t1+t2+t3) ][(-t1+t2+t4)] +A[(t1-t2)][ (-t1+2*t2) ][ (-t1+t2+t3)-1][(-t1+t2+t4)+1])+ A[(t1-t2)][ (-t1+2*t2) ][ (-t1+t2+t3) ][(-t1+t2+t4)];;
        }
      }
    }
  }
}
#pragma endscop




	t_end = rtclock();
	printf("%0.6lfs  %i\n", t_end - t_start,c);


    return 0;
}
