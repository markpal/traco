/* This program detects the edges image.
   The program relies on a 2D-convolution routine to convolve the image with
   kernels (Sobel operators) that expose horizontal and vertical edge
   information. UTDSP */

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>


#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))




int N = 100;



int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);
	int K = 30;
	int cpus = atoi(argv[3]);
	int z = 0;

	omp_set_num_threads(cpus);

	int k,i,j,t,r,c;

    int dead_rows = K / 2;
    int dead_cols = K / 2;
    int normal_factor;

	// Declare arrays on the stack
	int **sum = new int*[N];
	int **sum1 = new int*[N];
	int **kernel = new int*[N];
	int **input_image = new int*[2*N];
	int **output_image = new int*[2*N];
	int **output_image1 = new int*[2*N];

	for (i=0; i<N; i++) { sum[i] = new int[2*N]; }
    for (i=0; i<2*N; i++) { sum1[i] = new int[2*N]; }
	for (i=0; i<N; i++) { kernel[i] = new int[N]; }
	for (i=0; i<2*N; i++) { input_image[i] = new int[2*N]; }
    for (i=0; i<2*N; i++) { output_image[i] = new int[2*N]; }
	for (i=0; i<2*N; i++) { output_image1[i] = new int[2*N]; }


	// Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			sum[i][j] = rand()/N;
			sum1[i][j] =  sum[i][j];
			kernel[i][j] = rand()/N;
		}
	}

    // Set the input data
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			output_image[i][j] = rand()/N;
			output_image1[i][j] =  output_image[i][j];
        	input_image[i][j] = rand()/N;
		}
	}


    normal_factor = 0;
    for (r = 0; r < K; r++) {
        for (c = 0; c < K; c++) {
      normal_factor += abs(kernel[r][c]);
        }
    }



double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

  for (r = 0; r < N - K + 1; r++) {
    for (c = 0; c < N - K + 1; c++) {
      sum[r][c] = 0;
      for (i = 0; i < K; i++) {
        for (j = 0; j < K; j++) {
          sum[r][c] += input_image[r+i][c+j] * kernel[i][j];
        }
      }
      output_image[r+dead_rows][c+dead_cols] = (sum[r][c] / normal_factor);
    }
  }
}

else if(kind == 3){



}
else{

    //traco
    int c0,c1,c2,c3,c4,c5,c6,c8,c7,c9,c11,c13,c15;

int UB = floord(N - K, 16);
#pragma omp parallel for
for (c1 = 0; c1 <= UB; c1 += 1)
  for (c3 = 0; c3 <= (N - K) / 16; c3 += 1) {
    if (K >= 1) {
      if (K >= 17)
        for (c9 = 16 * c1; c9 <= min(N - K, 16 * c1 + 15); c9 += 1)
          for (c11 = 16 * c3; c11 <= min(N - K, 16 * c3 + 15); c11 += 1)
            sum[c9][c11]=0;
      for (c9 = 16 * c1; c9 <= min(N - K, 16 * c1 + 15); c9 += 1)
        for (c11 = 16 * c3; c11 <= min(N - K, 16 * c3 + 15); c11 += 1) {
          if (K <= 16)
            sum[c9][c11]=0;
          output_image[c9+dead_rows][c11+dead_cols]=(sum[c9][c11]/normal_factor);
        }
    } else
      for (c9 = 16 * c1; c9 <= min(N - K, 16 * c1 + 15); c9 += 1)
        for (c11 = 16 * c3; c11 <= min(N - K, 16 * c3 + 15); c11 += 1)
          sum[c9][c11]=0;
    for (c5 = 0; c5 <= floord(K - 1, 16); c5 += 1)
      for (c7 = 0; c7 <= (K - 1) / 16; c7 += 1)
        for (c9 = 16 * c1; c9 <= min(N - K, 16 * c1 + 15); c9 += 1)
          for (c11 = 16 * c3; c11 <= min(N - K, 16 * c3 + 15); c11 += 1) {
            if (K >= 16 * c7 + 17) {
              for (c15 = 16 * c7; c15 <= 16 * c7 + 15; c15 += 1)
                sum[c9][c11]+=input_image[c9+16*c5][c11+c15]*kernel[16*c5][c15];
            } else
              for (c13 = 16 * c5; c13 <= min(K - 1, 16 * c5 + 15); c13 += 1) {
                if (c13 >= 16 * c5 + 1)
                  for (c15 = 0; c15 < 16 * c7; c15 += 1)
                    sum[c9][c11]+=input_image[c9+c13][c11+c15]*kernel[c13][c15];
                for (c15 = 16 * c7; c15 < K; c15 += 1)
                  sum[c9][c11]+=input_image[c9+c13][c11+c15]*kernel[c13][c15];
              }
          }
  }



}



    double end = omp_get_wtime();
	printf("%.3f\n", end - start);
	printf("%i\n", z);

    if(kind != 1){
      for (r = 0; r < N - K + 1; r++) {
        for (c = 0; c < N - K + 1; c++) {
          sum1[r][c] = 0;
          for (i = 0; i < K; i++) {
            for (j = 0; j < K; j++) {
              sum1[r][c] += input_image[r+i][c+j] * kernel[i][j];
            }
          }
          output_image1[r+dead_rows][c+dead_cols] = (sum1[r][c] / normal_factor);
        }
      }


          for(i = 0; i < 2*N; i++)
            for (j = 0; j < 2*N; j++){
              if(output_image[i][j] != output_image1[i][j])
                printf("Error!\n");
                exit(0);
              }

    }


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
