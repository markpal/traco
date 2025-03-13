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
	int cpus = atoi(argv[3]);
	int z = 0;

	omp_set_num_threads(cpus);

	int k,i,j,t;

	// Declare arrays on the stack
	float **path = new float*[N];
	for (i=0; i<N; i++)
	  path[i] = new float[N];

    float **path1 = new float*[N];
	for (i=0; i<N; i++)
	  path1[i] = new float[N];

	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			//path[i][j] = ((float) (N-j)*j*(j+2) + 2) / N;
			path[i][j] = rand()/N;
			path1[i][j] =  path[i][j]; //  ((float) (N-j)*j*(j+2) + 2) / N;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

  for (k = 0; k < N; k++)
  {
      for(i = 0; i < N; i++)
	    for (j = 0; j < N; j++){
	      path1[i][j] = path1[i][j] < path1[i][k] + path1[k][j] ? path1[i][j] : path1[i][k] + path1[k][j];

	      }

  }
}
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
}
else{

    //traco
    int c0,c1,c2,c3,c4,c5,c6,c8,l;



for (l = 0; l < N; l++){
  for (c0 = 0; c0 <= min(3, N - l + 1); c0 += 1) {
    if (N >= l + c0 && c0 <= 2)
#pragma omp parallel for
      for (c2 = 0; c2 <= min(c0 + l / 32 - 1, -c0 + l / 32 + 1); c2 += 1) {
        if (c0 == 2) {
          for (c4 = l / 32 + 1; c4 <= (N - 1) / 32; c4 += 1)
            for (c6 = 32 * c2; c6 <= 32 * c2 + 31; c6 += 1)
              for (c8 = 32 * c4; c8 <= min(N - 1, 32 * c4 + 31); c8 += 1)
                path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
        } else if (c0 == 0) {
          for (c4 = 0; c4 < l / 32; c4 += 1)
            for (c6 = 32 * c2; c6 <= 32 * c2 + 31; c6 += 1)
              for (c8 = 32 * c4; c8 <= 32 * c4 + 31; c8 += 1)
                path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
        } else if (l >= 32 * c2 + 32) {
          for (c6 = 32 * c2; c6 <= 32 * c2 + 31; c6 += 1)
            for (c8 = -(l % 32) + l; c8 <= min(N - 1, -(l % 32) + l + 31); c8 += 1)
              path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
        } else
          for (c4 = 0; c4 < c2; c4 += 1)
            for (c6 = 32 * c2; c6 <= min(N - 1, 32 * c2 + 31); c6 += 1)
              for (c8 = 32 * c4; c8 <= 32 * c4 + 31; c8 += 1)
                path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
      }
    if (c0 == 2)
#pragma omp parallel for
      for (c6 = -(l % 32) + l; c6 <= min(N - 1, -(l % 32) + l + 31); c6 += 1)
        for (c8 = -(l % 32) + l; c8 <= min(N - 1, -(l % 32) + l + 31); c8 += 1)
          path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
    if (c0 >= 2)
#pragma omp parallel for
      for (c2 = -c0 + l / 32 + 3; c2 <= (N - 1) / 32; c2 += 1) {
        if (c0 == 2) {
          for (c4 = 0; c4 < floord(l, 32); c4 += 1)
            for (c6 = 32 * c2; c6 <= min(N - 1, 32 * c2 + 31); c6 += 1)
              for (c8 = 32 * c4; c8 <= 32 * c4 + 31; c8 += 1)
                path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
        } else if (32 * c2 >= l + 1) {
          for (c6 = 32 * c2; c6 <= min(N - 1, 32 * c2 + 31); c6 += 1)
            for (c8 = -(l % 32) + l; c8 <= -(l % 32) + l + 31; c8 += 1)
              path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
        } else
          for (c4 = c2 + 1; c4 <= (N - 1) / 32; c4 += 1)
            for (c6 = 32 * c2; c6 <= 32 * c2 + 31; c6 += 1)
              for (c8 = 32 * c4; c8 <= min(N - 1, 32 * c4 + 31); c8 += 1)
                path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];
      }
  }
#pragma omp parallel for
  for (c2 = l / 32 + 1; c2 <= (N - 1) / 32; c2 += 1)
    for (c4 = l / 32 + 1; c4 <= (N - 1) / 32; c4 += 1)
      for (c6 = 32 * c2; c6 <= min(N - 1, 32 * c2 + 31); c6 += 1)
        for (c8 = 32 * c4; c8 <= min(N - 1, 32 * c4 + 31); c8 += 1)
          path[c6][c8]=path[c6][c8]<path[c6][l]+path[l][c8]?path[c6][c8]:path[c6][l]+path[l][c8];

}




}



    double end = omp_get_wtime();
	printf("%.3f\n", end - start);
	printf("%i\n", z);

    if(kind != 1){
        for (k = 0; k < N; k++)
        {
          for(i = 0; i < N; i++)
            for (j = 0; j < N; j++){
              path1[i][j] = path1[i][j] < path1[i][k] + path1[k][j] ? path1[i][j] : path1[i][k] + path1[k][j];

              }
        }

        for (k = 0; k < N; k++)
        {
          for(i = 0; i < N; i++)
            for (j = 0; j < N; j++){
              if(path1[i][j] != path[i][j]){
                printf("Error!\n");
                exit(0);
              }
              }
        }
    }


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
