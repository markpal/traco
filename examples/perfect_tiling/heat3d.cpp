#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))




int N = 10;


// heat2d
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int t,k,i,j,n=N,T=N;

	float ****A = new float***[N+2];

    for (i=0; i<N+2; i++)
	  A[i] = new float**[N+2];

    for (i=0; i<N+2; i++)
		for (j=0; j<N+2; j++)
		  A[i][j] = new float*[N+2];

    for (i=0; i<N+2; i++)
		for (j=0; j<N+2; j++)
		  for (k=0; k<N+2; k++)
		     A[i][j][k] = new float[N+2];

	// Set the input data
	for (i=0; i<N+2; i++) {
		for (j=0; j<N+2; j++) {
		 for (k=0; j<N+2; j++) {
		   for (t=0; t<N+2; t++) {
			A[i][j][k][t] = ((float) i*i*(j+2) + 2*k+t) / N;
			  }
			}
		}
	}




double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


for ( t = 0; t < T; t++) {
 for ( i = 1; i < N+1; i++) {
   for ( j = 1; j < N+1; j++) {
     for (k = 1; k < N+1; k++) {
      A[t+1][i ][ j ][k] = 0.125 *(A[t][ i+1][j ][k] -2.0*A[t][i ][ j ][k] +A[t][ i-1][j][k])+ 0.125 *(A[t][ i ][ j+1][k] -2.0*A[t][i ][ j ][k] +A[t][ i ][ j-1][k]) + 0.125 *(A[t][ i ][ j][k-1] -2.0*A[t][i ][ j ][k] +A[t][ i ][ j-1][k+1])+ A[t][ i ][ j ][k];
    }
   }
  }
 }



}
// pluto
// -----------------------------------
else if(kind == 3){


int t1,t2,t3,t32,t5,t6,t7,t4,t8,lbv,ubv;

if ((N >= 1) && (T >= 1)) {
  for (t1=0;t1<=floord(T-1,32);t1++) {
    for (t2=t1;t2<=min(floord(T+N-1,32),floord(32*t1+N+31,32));t2++) {
      for (t3=max(ceild(32*t2-N-30,32),t1);t3<=min(min(floord(T+N-1,32),floord(32*t1+N+31,32)),floord(32*t2+N+30,32));t3++) {
        for (t4=max(max(ceild(32*t2-N-30,32),ceild(32*t3-N-30,32)),t1);t4<=min(min(min(floord(T+N-1,32),floord(32*t1+N+31,32)),floord(32*t2+N+30,32)),floord(32*t3+N+30,32));t4++) {
          for (t5=max(max(max(32*t1,32*t2-N),32*t3-N),32*t4-N);t5<=min(min(min(min(T-1,32*t1+31),32*t2+30),32*t3+30),32*t4+30);t5++) {
            for (t6=max(32*t2,t5+1);t6<=min(32*t2+31,t5+N);t6++) {
              for (t7=max(32*t3,t5+1);t7<=min(32*t3+31,t5+N);t7++) {
                lbv=max(32*t4,t5+1);
                ubv=min(32*t4+31,t5+N);
#pragma ivdep
#pragma vector always
                for (t8=lbv;t8<=ubv;t8++) {
                  A[t5+1][(-t5+t6) ][ (-t5+t7) ][(-t5+t8)] = 0.125 *(A[t5][ (-t5+t6)+1][(-t5+t7) ][(-t5+t8)] -2.0*A[t5][(-t5+t6) ][ (-t5+t7) ][(-t5+t8)] +A[t5][ (-t5+t6)-1][(-t5+t7)][(-t5+t8)])+ 0.125 *(A[t5][ (-t5+t6) ][ (-t5+t7)+1][(-t5+t8)] -2.0*A[t5][(-t5+t6) ][ (-t5+t7) ][(-t5+t8)] +A[t5][ (-t5+t6) ][ (-t5+t7)-1][(-t5+t8)]) + 0.125 *(A[t5][ (-t5+t6) ][ (-t5+t7)][(-t5+t8)-1] -2.0*A[t5][(-t5+t6) ][ (-t5+t7) ][(-t5+t8)] +A[t5][ (-t5+t6) ][ (-t5+t7)-1][(-t5+t8)+1])+ A[t5][ (-t5+t6) ][ (-t5+t7) ][(-t5+t8)];;
                }
              }
            }
          }
        }
      }
    }
  }
}

}else{

    //traco

int c0,c1,c2,c3,c4,c5,c6,c7;

for (c0 = 0; c0 <= floord(T - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= (N - 1) / 16; c2 += 1)
      for (c3 = 0; c3 <= (N - 1) / 16; c3 += 1)
        for (c4 = 16 * c0; c4 <= min(T - 1, 16 * c0 + 15); c4 += 1)
          for (c5 = 16 * c1 + 1; c5 <= min(16 * c1 + 16, N); c5 += 1)
            for (c6 = 16 * c2 + 1; c6 <= min(N, 16 * c2 + 16); c6 += 1) {
              for (c7 = max(1, 8 * c0 + 8 * c2 + 16 * c3 - c4 - c6 + (c4 + c6) / 2 + 2); c7 <= 16 * c2 + 16 * c3 - c6 + 1; c7 += 1)
                A[c4+1][c5][c6][c7]=0.125*(A[c4][c5+1][c6][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5-1][c6][c7])+0.125*(A[c4][c5][c6+1][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7])+0.125*(A[c4][c5][c6][c7-1]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7+1])+A[c4][c5][c6][c7];
              for (c7 = max(max(16 * c0 + 16 * c3 - c4 + 1, 16 * c2 + 16 * c3 - c6 + 2), 1); c7 <= 16 * c3; c7 += 1)
                A[c4+1][c5][c6][c7]=0.125*(A[c4][c5+1][c6][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5-1][c6][c7])+0.125*(A[c4][c5][c6+1][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7])+0.125*(A[c4][c5][c6][c7-1]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7+1])+A[c4][c5][c6][c7];
              if (N >= 16 * c3 + 17) {
                for (c7 = 16 * c3 + 1; c7 <= 8 * c0 + 8 * c2 + 16 * c3 - c4 - c6 + (c4 + c6) / 2 + 17; c7 += 1)
                  A[c4+1][c5][c6][c7]=0.125*(A[c4][c5+1][c6][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5-1][c6][c7])+0.125*(A[c4][c5][c6+1][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7])+0.125*(A[c4][c5][c6][c7-1]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7+1])+A[c4][c5][c6][c7];
                for (c7 = 8 * c0 + 8 * c2 + 16 * c3 - c4 - c6 + (c4 + c6) / 2 + 18; c7 <= 16 * c0 + 16 * c3 - c4 + 16; c7 += 1)
                  A[c4+1][c5][c6][c7]=0.125*(A[c4][c5+1][c6][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5-1][c6][c7])+0.125*(A[c4][c5][c6+1][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7])+0.125*(A[c4][c5][c6][c7-1]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7+1])+A[c4][c5][c6][c7];
              } else
                for (c7 = 16 * c3 + 1; c7 <= N; c7 += 1)
                  A[c4+1][c5][c6][c7]=0.125*(A[c4][c5+1][c6][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5-1][c6][c7])+0.125*(A[c4][c5][c6+1][c7]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7])+0.125*(A[c4][c5][c6][c7-1]-2.0*A[c4][c5][c6][c7]+A[c4][c5][c6-1][c7+1])+A[c4][c5][c6][c7];
            }

}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
