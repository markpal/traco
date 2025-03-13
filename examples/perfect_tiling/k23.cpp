#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))



int N = 1024;


int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int k,l,i,j,t,loop=N,n=N;

	// Declare arrays on the stack
	float **za = new float*[N+1];
	float **zb = new float*[N+1];
	float **zr = new float*[N+1];
	float **zu = new float*[N+1];
	float **zv = new float*[N+1];
	float **zz = new float*[N+1];

	for (i=0; i<N+1; i++){
	  za[i] = new float[N+1];
	  zb[i] = new float[N+1];
	  zr[i] = new float[N+1];
	  zu[i] = new float[N+1];
	  zv[i] = new float[N+1];
	  zz[i] = new float[N+1];


    }
    float *w = new float[N];

	// Set the input data
	for (i=0; i<N+1; i++) {
		for (j=0; j<N+1; j++) {
			za[i][j] = ((float) i*i*(j+2) + 2) / N;
			zb[i][j] = ((float) i*i*(j+2) + 2) / N;
			zr[i][j] = ((float) i*i*(j+2) + 2) / N;
			zv[i][j] = ((float) i*i*(j+2) + 2) / N;
			zu[i][j] = ((float) i*i*(j+2) + 2) / N;
			zz[i][j] = ((float) i*i*(j+2) + 2) / N;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){


    for ( l=1 ; l<=loop ; l++ ) {
        for ( j=1 ; j<6 ; j++ ) {
            for ( k=1 ; k<n ; k++ ) {
                za[j][k] = za[j][k] + 0.175*( za[j+1][k]*zr[j][k] + za[j-1][k]*zb[j][k] + za[j][k+1]*zu[j][k] + za[j][k-1]*zv[j][k] + zz[j][k] - za[j][k] );
            }
        }
    }
}
// pluto
// -----------------------------------
else if(kind == 3){

int t1,t2,t3,t4,t5,t6;
if ((loop >= 1) && (n >= 2)) {
  for (t1=0;t1<=floord(loop,32);t1++) {
    for (t2=t1;t2<=min(floord(loop+5,32),t1+1);t2++) {
      for (t3=t1;t3<=min(min(floord(loop+n-1,32),floord(32*t1+n+30,32)),floord(32*t2+n+29,32));t3++) {
        for (t4=max(max(max(1,32*t1),32*t2-5),32*t3-n+1);t4<=min(min(min(loop,32*t1+31),32*t2+30),32*t3+30);t4++) {
          for (t5=max(32*t2,t4+1);t5<=min(32*t2+31,t4+5);t5++) {
            for (t6=max(32*t3,t4+1);t6<=min(32*t3+31,t4+n-1);t6++) {
              za[(-t4+t5)][(-t4+t6)] = za[(-t4+t5)][(-t4+t6)] + 0.175*( za[(-t4+t5)+1][(-t4+t6)]*zr[(-t4+t5)][(-t4+t6)] + za[(-t4+t5)-1][(-t4+t6)]*zb[(-t4+t5)][(-t4+t6)] + za[(-t4+t5)][(-t4+t6)+1]*zu[(-t4+t5)][(-t4+t6)] + za[(-t4+t5)][(-t4+t6)-1]*zv[(-t4+t5)][(-t4+t6)] + zz[(-t4+t5)][(-t4+t6)] - za[(-t4+t5)][(-t4+t6)] );;
            }
          }
        }
      }
    }
  }
}



}else{

    //traco

int c0,c1,c2,c3,c4,c5;

for (c0 = 0; c0 <= floord(loop - 1, 32); c0 += 1)
  for (c2 = 0; c2 <= floord(n - 2, 32); c2 += 1)
    for (c3 = 32 * c0 + 1; c3 <= min(loop, 32 * c0 + 32); c3 += 1)
      for (c4 = 1; c4 <= 5; c4 += 1) {
        for (c5 = max(1, 32 * c0 + 32 * c2 - c3 + 2); c5 <= 32 * c2; c5 += 1)
          za[c4][c5]=za[c4][c5]+0.175*(za[c4+1][c5]*zr[c4][c5]+za[c4-1][c5]*zb[c4][c5]+za[c4][c5+1]*zu[c4][c5]+za[c4][c5-1]*zv[c4][c5]+zz[c4][c5]-za[c4][c5]);
        if (32 * c2 + 33 >= n) {
          for (c5 = 32 * c2 + 1; c5 < n; c5 += 1)
            za[c4][c5]=za[c4][c5]+0.175*(za[c4+1][c5]*zr[c4][c5]+za[c4-1][c5]*zb[c4][c5]+za[c4][c5+1]*zu[c4][c5]+za[c4][c5-1]*zv[c4][c5]+zz[c4][c5]-za[c4][c5]);
        } else
          for (c5 = 32 * c2 + 1; c5 <= 32 * c0 + 32 * c2 - c3 + 33; c5 += 1)
            za[c4][c5]=za[c4][c5]+0.175*(za[c4+1][c5]*zr[c4][c5]+za[c4-1][c5]*zb[c4][c5]+za[c4][c5+1]*zu[c4][c5]+za[c4][c5-1]*zv[c4][c5]+zz[c4][c5]-za[c4][c5]);
      }

}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
