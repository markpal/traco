#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))




int N = 1024;
int b,n;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);
	int cpus = atoi(argv[3]);
	int z = 0;
	float det=1;
	n=N;
	b=(n+2)/2;

	omp_set_num_threads(cpus);

	int k,i,j,t;

	// Declare arrays on the stack
	float **w = new float*[2*N];
	float **w1 = new float*[2*N];
	float **a = new float*[2*N];
	float **a1 = new float*[2*N];

	for (i=0; i<2*N; i++) { w[i] = new float[2*N]; }
    for (i=0; i<2*N; i++) { w1[i] = new float[2*N]; }
	for (i=0; i<2*N; i++) { a[i] = new float[2*N]; }
	for (i=0; i<2*N; i++) { a1[i] = new float[2*N]; }

	// Set the input data
	for (i=0; i<2*N; i++) {
		for (j=0; j<2*N; j++) {
			//path[i][j] = ((float) (N-j)*j*(j+2) + 2) / N;
			w[i][j] = 00.1;
			w1[i][j] = w[i][j]; //  ((float) (N-j)*j*(j+2) + 2) / N;
			a[i][j] = 00.2;
			a1[i][j] = a[i][j]; //  ((float) (N-j)*j*(j+2) + 2) / N;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

    for(k=1; k<=b; k++){
      det = a[k][k]*a[n-k+1][n-k+1] - a[n-k+1][k]*a[k][n-k+1];
      for(i=k+1; i<=n-k; i++){
        w[i][k] = a[n-k+1][n-k+1]*a[i][k] - a[n-k+1][k]*a[i][n-k+1]/det;
        w[i][n-k+1] = a[k][k]*a[i][n-k+1] - a[k][n-k+1]*a[i][k] / det;

        for(j=k+1; j<=n-k; j++){
          a[i][j] = a[i][j] - w[i][k]*a[k][j] - w[i][n-k+1]*a[n-k+1][j];


      }
     }
   }

}

else if(kind == 3){

printf("pl\n");
  int t1, t2, t3, t4, t5;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if ((b >= 3) && (2*b == n+2)) {
  for (t1=1;t1<=b;t1++) {
    for (t2=max(-1,ceild(29*t1-29*b,32));t2<=min(floord(-t1+2*b-2,16),floord(-3*t1+5*b-6,32));t2++) {
      if (t2 == 0) {
        det = a[t1][t1]*a[n-t1+1][n-t1+1] - a[n-t1+1][t1]*a[t1][n-t1+1];;
      }
      if (t1 <= b-2) {
        lbp=max(0,ceild(t1+32*t2-2*b+2,32));
        ubp=min(floord(-t1+2*b-2,32),floord(-t1+32*t2+30,32));
#pragma omp parallel for private(lbv,ubv,t4,t5)
        for (t3=lbp;t3<=ubp;t3++) {
          if ((t1 <= 30) && (t3 == 0)) {
            for (t4=max(32*t2,t1+1);t4<=min(32*t2+31,-t1+2*b-2);t4++) {
              w[t4][t1] = a[n-t1+1][n-t1+1]*a[t4][t1] - a[n-t1+1][t1]*a[t4][n-t1+1]/det;;
              w[t4][n-t1+1] = a[t1][t1]*a[t4][n-t1+1] - a[t1][n-t1+1]*a[t4][t1] / det;;
              for (t5=t1+1;t5<=min(31,-t1+2*b-2);t5++) {
                a[t4][t5] = a[t4][t5] - w[t4][t1]*a[t1][t5] - w[t4][n-t1+1]*a[n-t1+1][t5];;
              }
            }
          }
          if ((t1 >= 31) && (t3 == 0)) {
            for (t4=max(32*t2,t1+1);t4<=min(32*t2+31,-t1+2*b-2);t4++) {
              w[t4][t1] = a[n-t1+1][n-t1+1]*a[t4][t1] - a[n-t1+1][t1]*a[t4][n-t1+1]/det;;
              w[t4][n-t1+1] = a[t1][t1]*a[t4][n-t1+1] - a[t1][n-t1+1]*a[t4][t1] / det;;
            }
          }
          if (t1 <= 32*t3+30) {
            for (t4=max(t1+1,32*t2-32*t3);t4<=min(min(32*t2-1,-t1+2*b-2),32*t2-32*t3+31);t4++) {
              for (t5=max(32*t3,t1+1);t5<=min(32*t3+31,-t1+2*b-2);t5++) {
                a[t4][t5] = a[t4][t5] - w[t4][t1]*a[t1][t5] - w[t4][n-t1+1]*a[n-t1+1][t5];;
              }
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */


}
else{

    //traco
    int c0,c1,c2,c3,c4,c5,c6,c7,c8,l,c9,c11;


for(c0=1; c0<=b; c0++){
  det = a[c0][c0]*a[n-c0+1][n-c0+1] - a[n-c0+1][c0]*a[c0][n-c0+1];
  #pragma omp parallel for private(det)
    for (c1 = 0; c1 <= (-2 * c0 + n - 1)/32; c1 += 1) {
      for (c2 = 1; c2 <= 2; c2 += 1)
        for (c5 = c0 + 32 * c1 + 1; c5 <= min(-c0 + n, c0 + 32 * c1 + 32); c5 += 1) {
          if (c2 == 2) {
            w[c5][n-c0+1]=a[c0][c0]*a[c5][n-c0+1]-a[c0][n-c0+1]*a[c5][c0]/det;
          } else
            w[c5][c0]=a[n-c0+1][n-c0+1]*a[c5][c0]-a[n-c0+1][c0]*a[c5][n-c0+1]/det;
        }
      for (c3 = max(0, floord(c0 + 1, 32)); c3 <= floord(-c0 + n, 32); c3 += 1)
        for (c5 = c0 + 32 * c1 + 1; c5 <= min(-c0 + n, c0 + 32 * c1 + 32); c5 += 1)
          for (c7 = max(c0 + 1, 32 * c3); c7 <= min(-c0 + n, 32 * c3 + 31); c7 += 1)
            a[c5][c7]=a[c5][c7]-w[c5][c0]*a[c0][c7]-w[c5][n-c0+1]*a[n-c0+1][c7];
    }
}

}



    double end = omp_get_wtime();
	printf("%.3f\n", end - start);
	printf("%i\n", z);

    if(kind != 1){


    for(k=1; k<=b; k++){
      det = a1[k][k]*a1[n-k+1][n-k+1] - a1[n-k+1][k]*a1[k][n-k+1];
      for(i=k+1; i<=n-k; i++){
        w1[i][k] = a1[n-k+1][n-k+1]*a1[i][k] - a1[n-k+1][k]*a1[i][n-k+1]/det;
        w1[i][n-k+1] = a1[k][k]*a1[i][n-k+1] - a1[k][n-k+1]*a1[i][k] / det;

        for(j=k+1; j<=n-k; j++){
          a1[i][j] = a1[i][j] - w1[i][k]*a1[k][j] - w1[i][n-k+1]*a1[n-k+1][j];
      }
      }

    }


printf("Checking...");

          for(i = 0; i < 2*N; i++)
            for (j = 0; j < 2*N; j++){
              if((a[i][j] != a1[i][j] && !isnan(a[i][j]) && !isnan(a[i][j])) ||
                  (w[i][j] != w1[i][j] && !isnan(w[i][j]) && !isnan(w[i][j] )))
                   {

                if(a[i][j] != a1[i][j]){
                    printf("Error a!\n");

                if(w[i][j] != w1[i][j])
                    printf("Error w!\n");


                printf("%.8f %.8f %.8f %.8f %i %i\n",a[i][j],a1[i][j],w[i][j],w1[i][j],i,j);
                exit(0);
               }
                }

              }

    }
    printf("OK");


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
