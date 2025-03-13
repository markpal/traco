#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>


#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))




int N = 1024;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int k,i,j,t;

	// Declare arrays on the stack
	float **path = new float*[N];
	float **D = new float*[N];
	for (i=0; i<N; i++){
	  path[i] = new float[N];
	  D[i] = new float[N];
	  }

	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			path[i][j] = ((float) i*i*(j+2) + 2) / N;
			D[i][j] = path[i][j];
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------

if(kind == 1){


#pragma scop
  for (k = 0; k < N; k++)
  {
      for(i = 0; i < N; i++)
	    for (j = 0; j < N; j++)
	      path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
  }
#pragma endscop
}
// pluto
// -----------------------------------
else if(kind == 3){


  int t1, t2, t3, t4, t5;

 register int lbv, ubv;

/* Start of CLooG code */
if (N >= 1) {
  for (t1=0;t1<=N-1;t1++) {
    for (t2=0;t2<=floord(N-1,32);t2++) {
      for (t3=0;t3<=floord(N-1,32);t3++) {
        for (t4=32*t2;t4<=min(N-1,32*t2+31);t4++) {
          for (t5=32*t3;t5<=min(N-1,32*t3+31);t5++) {
            path[t4][t5] = path[t4][t5] < path[t4][t1] + path[t1][t5] ? path[t4][t5] : path[t4][t1] + path[t1][t5];;
          }
        }
      }
    }
  }
}
/* End of CLooG code */
}

else if(kind == 5){
for(k = 0; k < N; k++) {
for(i = 0 ; i < N; i++) {
for(j = 0; j < N; j++) {
  if(i < k && j < k)
    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
  if(i > k && j < k)
    D[i][j] = min(D[i][j], D[i][k] + D[k][j]) ;
  if(i < k && j > k)
    D[i][j] = min(D[i][j], D[i][k] + D[k][j]) ;
  if(i > k && j > k)
    D[i][j] = min(D[i][j], D[i][k] + D[k][j]) ;
 }
}
}
}else{

    //traco
    int c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11;

    if (N >= 2)
  for( c1 = 0; c1 <= (N - 1) / 32; c1 += 1) {
 //   #pragma omp parallel for
    for( c3 = 0; c3 <= min(c1, floord(N - 2, 32)); c3 += 1) {
      for( c5 = 0; c5 < c1; c5 += 1)
        for( c7 = 32 * c1; c7 <= min(N - 1, 32 * c1 + 31); c7 += 1) {
          for( c9 = 32 * c3; c9 <= min(32 * c3 + 31, c7 - 1); c9 += 1)
            for( c11 = 32 * c5; c11 <= 32 * c5 + 31; c11 += 1)
              D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
              //intf("%i %i %i\n", c1,c3,c5);
          if (c3 == c1)
            for( c9 = c7 + 1; c9 <= min(N - 1, 32 * c1 + 31); c9 += 1)
              for( c11 = 32 * c5; c11 <= 32 * c5 + 31; c11 += 1)
                D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
                //intf("%i %i %i\n", c1,c3,c5);
        }
      if (N >= 32 * c1 + 2)
        for( c5 = c1; c5 <= (N - 1) / 32; c5 += 1)
          for( c7 = 32 * c1; c7 <= min(N - 1, 32 * c1 + 31); c7 += 1) {
            for( c9 = 32 * c3; c9 <= min(32 * c3 + 31, c7 - 1); c9 += 1) {
              if (c5 == c1)
                for( c11 = 32 * c1; c11 < c7; c11 += 1)
                  D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
                  //printf("%i %i %i\n", c1,c3,c5);
              for( c11 = max(32 * c5, c7 + 1); c11 <= min(N - 1, 32 * c5 + 31); c11 += 1)
                D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
                //printf("%i %i %i\n", c1,c3,c5);
            }
            if (c3 == c1)
              for( c9 = c7 + 1; c9 <= min(N - 1, 32 * c1 + 31); c9 += 1) {
                if (c5 == c1)
                  for( c11 = 32 * c1; c11 < c7; c11 += 1)
                    D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
                    //printf("%i %i %i\n", c1,c3,c5);
                for( c11 = max(32 * c5, c7 + 1); c11 <= min(N - 1, 32 * c5 + 31); c11 += 1)
                //printf("%i %i %i\n", c1,c3,c5);
                  D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
              }
          }
    }
   // #pragma omp parallel for
    for( c3 = c1 + 1; c3 <= (N - 1) / 32; c3 += 1)
      for( c5 = 0; c5 <= (N - 1) / 32; c5 += 1)
        for( c7 = 32 * c1; c7 <= 32 * c1 + 31; c7 += 1)
          for( c9 = 32 * c3; c9 <= min(N - 1, 32 * c3 + 31); c9 += 1) {
            for( c11 = 32 * c5; c11 <= min(32 * c5 + 31, c7 - 1); c11 += 1)
              D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
            for( c11 = max(32 * c5, c7 + 1); c11 <= min(N - 1, 32 * c5 + 31); c11 += 1)
              D[c9][c11] = min(D[c9][c11], D[c9][c7] + D[c7][c11]);
          }
  }
/*
for (c0 = 0; c0 <= floord(N - 1, 32); c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 32; c1 += 1)
    for (c2 = 0; c2 <= (N - 1) / 32; c2 += 1)
      if (N >= 32 * c2 + 33) {
        for (c4 = 32 * c1; c4 <= min(32 * c1 + 31, N - 1); c4 += 1)
          for (c5 = 32 * c2; c5 <= 32 * c2 + 31; c5 += 1)
            path[c4][c5]=path[c4][c5]<path[c4][32*c0]+path[32*c0][c5]?path[c4][c5]:path[c4][32*c0]+path[32*c0][c5];
      } else
        for (c3 = 32 * c0; c3 <= min(N - 1, 32 * c0 + 31); c3 += 1)
          for (c4 = 32 * c1; c4 <= min(N - 1, 32 * c1 + 31); c4 += 1) {
            if (c3 >= 32 * c0 + 1)
              for (c5 = 0; c5 < 32 * c2; c5 += 1)
                path[c4][c5]=path[c4][c5]<path[c4][c3]+path[c3][c5]?path[c4][c5]:path[c4][c3]+path[c3][c5];
            for (c5 = 32 * c2; c5 < N; c5 += 1)
              path[c4][c5]=path[c4][c5]<path[c4][c3]+path[c3][c5]?path[c4][c5]:path[c4][c3]+path[c3][c5];
          }
*/
 // simplify
 /*
for (c0 = 0; c0 <= floord(N - 1, 32); c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 32; c1 += 1) {
    for (c2 = 0; c2 <= (N - 1) / 32; c2 += 1)
      for (c4 = 32 * c1; c4 <= min(32 * c1 + 31, N - 1); c4 += 1)
        for (c5 = 32 * c2; c5 <= min(N - 1, 32 * c2 + 31); c5 += 1)
          path[c4][c5]=path[c4][c5]<path[c4][32*c0]+path[32*c0][c5]?path[c4][c5]:path[c4][32*c0]+path[32*c0][c5];
    for (c3 = 32 * c0 + 1; c3 <= min(32 * c0 + 31, N - 1); c3 += 1)
      for (c4 = 32 * c1; c4 <= min(32 * c1 + 31, N - 1); c4 += 1)
        for (c5 = 0; c5 < N; c5 += 1)
          path[c4][c5]=path[c4][c5]<path[c4][c3]+path[c3][c5]?path[c4][c5]:path[c4][c3]+path[c3][c5];
  }
  */
}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop
	if(1==0)
for(i=0;i<N;i++)
for(j=0;j<N;j++)
printf("%.2f %.2f \n", path[i][j], D[i][j] );

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
