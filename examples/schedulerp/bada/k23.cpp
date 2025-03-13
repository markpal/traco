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
	int cpus = atoi(argv[3]);

	omp_set_num_threads(cpus);

	int k,l,i,j,t,loop=N,n=N;

	// Declare arrays on the stack
	double **za = new double*[N+1];
	double **za1 = new double*[N+1];
	double **zb = new double*[N+1];
	double **zr = new double*[N+1];
	double **zu = new double*[N+1];
	double **zv = new double*[N+1];
	double **zz = new double*[N+1];

	for (i=0; i<N+1; i++){
	  za[i] = new double[N+1];
	  za1[i] = new double[N+1];
	  zb[i] = new double[N+1];
	  zr[i] = new double[N+1];
	  zu[i] = new double[N+1];
	  zv[i] = new double[N+1];
	  zz[i] = new double[N+1];


    }
    double *w = new double[N];

	// Set the input data
	for (i=0; i<N+1; i++) {
		for (j=0; j<N+1; j++) {
			za[i][j] = 0.001;
			za1[i][j] = 0.001;
			zb[i][j] = 0.002;
			zr[i][j] = 0.003;
			zv[i][j] = 0.005;
			zu[i][j] = 0.002;
			zz[i][j] = 0.001;
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

int c0,c1,c2,c3,c4,c5c6,c7,c8,c10,c12;

if (n >= 34 && loop >= 34)
  for (c0 = 0; c0 <= (n + 2 * loop - 4) / 32; c0 += 1)
{
  register int LB =  max(max(0, c0 - (n + loop + 29) / 32 + 1), floord(-n + 32 * c0 - 30, 64) + 1);
#pragma omp parallel for
    for (c2 = LB; c2 <= min((loop - 1) / 32, c0 / 2); c2 += 1) {
      if (c2 >= 1) {
        for (c8 = max(32 * c2 + 1, -n + 32 * c0 - 32 * c2 + 3); c8 <= min(loop, 32 * c2 + 32); c8 += 1)
          for (c10 = 1; c10 <= 5; c10 += 1)
            for (c12 = max(1, 32 * c0 - 32 * c2 - c8 + 2); c12 <= min(n - 1, 32 * c0 - 32 * c2 - c8 + 33); c12 += 1)
              za[c10][c12]=za[c10][c12]+0.175*(za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12]);
      } else
        for (c8 = max(1, -n + 32 * c0 + 3); c8 <= 32; c8 += 1)
          for (c10 = 1; c10 <= 5; c10 += 1) {
            if (c0 >= 1) {
              for (c12 = 32 * c0 - c8 + 2; c12 <= min(n - 1, 32 * c0 - c8 + 33); c12 += 1)
                za[c10][c12]=za[c10][c12]+0.175*(za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12]);
            } else
              for (c12 = 1; c12 <= -c8 + 33; c12 += 1)
                za[c10][c12]=za[c10][c12]+0.175*(za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12]);
          }
    }
    }






}
    double end = omp_get_wtime();
	printf("%.3f\n", end - start);


    if(kind != 1){
    for ( l=1 ; l<=loop ; l++ ) {
        for ( j=1 ; j<6 ; j++ ) {
            for ( k=1 ; k<n ; k++ ) {
                za1[j][k] = za1[j][k] + 0.175*( za1[j+1][k]*zr[j][k] + za1[j-1][k]*zb[j][k] + za1[j][k+1]*zu[j][k] + za1[j][k-1]*zv[j][k] + zz[j][k] - za1[j][k] );
            }
        }
    }

    for ( l=1 ; l<=loop ; l++ ) {
        for ( j=1 ; j<6 ; j++ ) {
            for ( k=1 ; k<n ; k++ ) {
              if(za[j][k] != za1[j][k])
                printf("Error!\n %.f %.f\n", za[j][k], za1[j][k]);
                exit(0);
              }
        }
    }
    }



	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
