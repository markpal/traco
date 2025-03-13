#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))




int N = 100;


// heat2d
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int t,k,i,j,n=N,T=N;

	float ***A = new float**[N+2];
	float ***A1 = new float**[N+2];

    for (i=0; i<N+2; i++){
	  A[i] = new float*[N+2];
	  A1[i] = new float*[N+2];
    }

    for (i=0; i<N+2; i++){
		for (j=0; j<N+2; j++){
		  A[i][j] = new float[N+2];
		  A1[i][j] = new float[N+2];
		  }
    }

	// Set the input data
	for (i=0; i<N+2; i++) {
		for (j=0; j<N+2; j++) {
		 for (k=0; j<N+2; j++) {
			A[i][j][k] = ((float) i*i*(j+2) + 2*k) / N;
			A1[i][j][k] = ((float) i*i*(j+2) + 2*k) / N;
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
      A[t+1][i][j] = 0.125 * (A[t][i+1][j] - 2 * A[t][i][j] + A[t][i-1][j]) + 0.125 * (A[t][i][j+1] - 2 * A[t][i][j] + A[t][i][j-1]) + A[t][i][j];
    }
  }
 }

int c0,c1,c2,c3,c4,c5,c32;
for (c0 = 0; c0 <= floord(T - 2, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(N - 1, 32); c1 += 1)
    for (c2 = 0; c2 <= min(-c0 + (N + T - 3) / 32, floord(N - 2, 32) + 1); c2 += 1)
      for (c3 = max(32 * c0 + 1, -N + 32 * c0 + 32 * c2 + 2); c3 <= min(T - 1, 32 * c0 + 32); c3 += 1)
        for (c4 = 32 * c1 + 1; c4 <= min(N, 32 * c1 + 32); c4 += 1)
          for (c5 = max(1, 32 * c0 + 32 * c2 - c3 + 2); c5 <= min(32 * c0 + 32 * c2 - c3 + 33, N); c5 += 1)
            A1[c3+1][c4][c5]=0.125*(A1[c3][c4+1][c5]-2*A1[c3][c4][c5]+A1[c3][c4-1][c5])+0.125*(A1[c3][c4][c5+1]-2*A1[c3][c4][c5]+A1[c3][c4][c5-1])+A1[c3][c4][c5];


	for (i=0; i<N+2; i++) {
		for (j=0; j<N+2; j++) {
		 for (k=0; j<N+2; j++) {
            if(A[i][j][k] != A1[i][j][k])
                printf("%f %f",A[i][j][k], A1[i][j][k]);
			}
		}
	}


}
// pluto
// -----------------------------------
else if(kind == 3){


int t1,t2,t3,t32,t5,t6,lbv,ubv;

if ((N >= 1) && (T >= 2)) {
  for (t1=0;t1<=floord(T-1,32);t1++) {
    for (t2=t1;t2<=min(floord(T+N-1,32),floord(32*t1+N+31,32));t2++) {
      for (t3=max(ceild(32*t2-N-30,32),t1);t3<=min(min(floord(T+N-1,32),floord(32*t1+N+31,32)),floord(32*t2+N+30,32));t3++) {
        for (t32=max(max(max(1,32*t1),32*t2-N),32*t3-N);t32<=min(min(min(T-1,32*t1+31),32*t2+30),32*t3+30);t32++) {
          for (t5=max(32*t2,t32+1);t5<=min(32*t2+31,t32+N);t5++) {
            lbv=max(32*t3,t32+1);
            ubv=min(32*t3+31,t32+N);
#pragma ivdep
#pragma vector always
            for (t6=lbv;t6<=ubv;t6++) {
              A[t32+1][(-t32+t5)][(-t32+t6)] = 0.125*(A[t32][(-t32+t5)+1][(-t32+t6)] - 2 * A[t32][(-t32+t5)][(-t32+t6)] + A[t32][(-t32+t5)-1][(-t32+t6)]) + 0.125*(A[t32][(-t32+t5)][(-t32+t6)+1] - 2 * A[t32][(-t32+t5)][(-t32+t6)] + A[t32][(-t32+t5)][(-t32+t6)-1]) + A[t32][(-t32+t5)][(-t32+t6)];;
            }
          }
        }
      }
    }
  }
}

}else{

    //traco

int c0,c1,c2,c3,c4,c5,c32;

for (c0 = 0; c0 <= floord(T - 2, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(N - 1, 32); c1 += 1)
    for (c2 = 0; c2 <= (N - 1) / 32; c2 += 1)
      for (c3 = 32 * c0 + 1; c3 <= min(T - 1, 32 * c0 + 32); c3 += 1)
        for (c32 = 32 * c1 + 1; c32 <= min(32 * c1 + 32, N); c32 += 1) {
          for (c5 = max(1, 32 * c0 + 32 * c2 - c3 + 2); c5 <= min(32 * c0 + 32 * c2 - c3 + 33, N); c5 += 1)
            A[c3+1][c32][c5]=0.125*(A[c3][c32+1][c5]-2*A[c3][c32][c5]+A[c3][c32-1][c5])+0.125*(A[c3][c32][c5+1]-2*A[c3][c32][c5]+A[c3][c32][c5-1])+A[c3][c32][c5];
          if (32 * c2 + 32 >= N)
            for (c5 = 32 * c0 + 32 * c2 - c3 + 18; c5 <= N; c5 += 1)
              A[c3+1][c32][c5]=0.125*(A[c3][c32+1][c5]-2*A[c3][c32][c5]+A[c3][c32-1][c5])+0.125*(A[c3][c32][c5+1]-2*A[c3][c32][c5]+A[c3][c32][c5-1])+A[c3][c32][c5];
        }

// SIMPLIFY
/*
for (c0 = 0; c0 <= floord(T - 2, 32); c0 += 1)
  for (c1 = 0; c1 <= floord(N - 1, 32); c1 += 1)
    for (c2 = 0; c2 <= min(-c0 + (N + T - 3) / 32, floord(N - 2, 32) + 1); c2 += 1)
      for (c3 = max(32 * c0 + 1, -N + 32 * c0 + 32 * c2 + 2); c3 <= min(T - 1, 32 * c0 + 32); c3 += 1)
        for (c4 = 32 * c1 + 1; c4 <= min(N, 32 * c1 + 32); c4 += 1)
          for (c5 = max(1, 32 * c0 + 32 * c2 - c3 + 2); c5 <= min(32 * c0 + 32 * c2 - c3 + 33, N); c5 += 1)
            A[c3+1][c4][c5]=0.125*(A[c3][c4+1][c5]-2*A[c3][c4][c5]+A[c3][c4-1][c5])+0.125*(A[c3][c4][c5+1]-2*A[c3][c4][c5]+A[c3][c4][c5-1])+A[c3][c4][c5];
*/
}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
