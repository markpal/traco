#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

using namespace std;
//
// This file is part of the Bones source-to-source compiler examples. The C-code
// is largely identical in terms of functionality and variable naming to the code
// found in PolyBench/C version 3.2. For more information on PolyBench/C or Bones
// please use the contact information below.
//
// == More information on PolyBench/C
// Contact............Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
// Web address........http://polybench.sourceforge.net/
//
// == More information on Bones
// Contact............Cedric Nugteren <c.nugteren@tue.nl>
// Web address........http://parse.ele.tue.nl/bones/
//
// == File information
// Filename...........benchmark/seidel-2d.c
// Author.............Cedric Nugteren
// Last modified on...05-April-2012
//


int N = 1024;

// This is 'seidel-2d', a 2D Seidel stencil computation
int main(int argc, char *argv[]) {

    int kind = atoi(argv[1]);
	int N = atoi(argv[2]);

	int k,l,i,j,t,loop=N,n=N;

	// Declare arrays on the stack
	int **b = new int*[N];
	for (i=0; i<N; i++)
	  b[i] = new int[N];
        int *w = new int[N];
        int *w1 = new int[N];

	// Set the input data
	for (i=0; i<N; i++) {
                w1[i] = i; w[i] = i;
		for (j=0; j<N; j++) {
			b[i][j] = ((int) i*i*(j+2) + 2) / N;
		}
	}

double start = omp_get_wtime();
// -- sekw.
// -----------------------------------
if(kind == 1){

    for ( l=1 ; l<=loop ; l++ ) {
        for ( i=1 ; i<n ; i++ ) {
            for ( k=0 ; k<i ; k++ ) {
                w[i] += b[k][i] * w[(i-k)-1];
            }
        }
    }
}
// pluto
// -----------------------------------
else if(kind == 3){



}else{

    //traco

int c0,c1,c2,c3,c4,c5;

//1x16x16
/*
for (c0 = 0; c0 < loop; c0 += 1)
  for (c1 = 0; c1 <= floord(n - 2, 16); c1 += 1)
    for (c2 = 0; c2 <= c1; c2 += 1) {
      for (c5 = 16 * c2; c5 <= min(16 * c2 + 15, 16 * c1); c5 += 1)
        w[16*c1+1]+=b[c5][16*c1+1]*w[(16*c1+1-c5)-1];
      if (c2 == c1)
        for (c4 = 16 * c1 + 2; c4 <= min(n - 1, 16 * c1 + 16); c4 += 1)
          for (c5 = 0; c5 < c4; c5 += 1)
            w[c4]+=b[c5][c4]*w[(c4-c5)-1];
    }
/*
// 16x1x16
*/

int a = 0;
    for ( l=1 ; l<=loop ; l++ ) {
        for ( i=1 ; i<n ; i++ ) {
            for ( k=0 ; k<i ; k++ ) {
                w1[i] += b[k][i] * w1[(i-k)-1];
                a++;
            }
        }
    }
cout << a;
start = omp_get_wtime();
/*
for (c0 = 0; c0 <= floord(loop - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(n - 2, 16); c1 += 1)
    for (c2 = 0; c2 <= min(n - 2, 16 * c1 + 15); c2 += 1) {
      if (c2 + 2 == n && 16 * c1 + 16 >= n) {
        w[n-1]+=b[n-2][n-1]*w[(n-1-n-2)-1];
        if (n >= 16 * c1 + 3 && loop >= 16 * c0 + 2)
          for (c5 = 0; c5 < n - 1; c5 += 1)
            w[n-1]+=b[c5][n-1]*w[(n-1-c5)-1];
      } else if (c2 == 0 && c1 == 0 && n >= 3) {
        for (c4 = 1; c4 <= 2; c4 += 1)
          w[c4]+=b[0][c4]*w[(c4-0)-1];
      } else {
        if (c2 == 16 * c1 + 15)
          w[16*c1+16]+=b[16*c1+15][16*c1+16]*w[(16*c1+16-16*c1+15)-1];
        if (c2 >= 1 && 15 * n >= 16 * c1 + 14 * c2 + 45)
          for (c3 = max(16 * c0 - 16 * c1 + c2 - 13, 16 * c0 + 1); c3 <= min(16 * c0 - 16 * c1 + c2 + 1, loop); c3 += 1) {
            if (c3 == 16 * c0 + 1)
              w[c2+1]+=b[c2][c2+1]*w[(c2+1-c2)-1];
            if ((-c1 + c2) % 15 == 0 || (c3 == 16 * c0 + 1 && c2 >= 16 * c1 + 1 && 16 * c1 + 14 >= c2)) {
              c4 = 240 * c0 + c2 + 15 >= 16 * c1 + 15 * c3 ? 16 * c0 + c2 - c3 + 3 : 16 * c1 + 16;
              for (c5 = 0; c5 < c2; c5 += 1)
                w[c4]+=b[c5][c4]*w[(c4-c5)-1];
              if ((c4 == 16 * c1 + 16 && c2 == 16 * c1 + 15) || (c4 == c2 + 2 && c3 == 16 * c0 + 1))
                w[c4]+=b[c2][c4]*w[(c4-c2)-1];
            }
            if (c3 == 16 * c0 + 2 && c2 + 3 == n && 16 * c1 + 17 >= n)
              for (c5 = 0; c5 < n - 2; c5 += 1)
                w[n-2]+=b[c5][n-2]*w[(n-2-c5)-1];
          }
      }
      if (c2 == 16 * c1 && loop >= 16 * c0 + 2 && 16 * c1 + 3 >= n)
        for (c5 = 0; c5 <= 16 * c1; c5 += 1)
          w[16*c1+1]+=b[c5][16*c1+1]*w[(16*c1+1-c5)-1];
      if (c2 + 2 == n && 16 * c1 + 16 >= n)
        for (c3 = 16 * c0 + 3; c3 <= min(16 * c0 + 16, loop); c3 += 1)
          for (c5 = 0; c5 < n - 1; c5 += 1)
            w[n-1]+=b[c5][n-1]*w[(n-1-c5)-1];
      if (16 * c1 >= c2 + 1)
        w[16*c1+1]+=b[c2][16*c1+1]*w[(16*c1+1-c2)-1];
    }

*/

//16x1x16
/*for (c0 = 0; c0 <= floord(loop - 1, 16); c0 += 1)
  for (c1 = 0; c1 < n - 1; c1 += 1) {
    for (c2 = 0; c2 <= c1 / 16; c2 += 1)
      for (c5 = 16 * c2; c5 <= min(16 * c2 + 15, c1); c5 += 1)
        w[c1+1]+=b[c5][c1+1]*w[(c1+1-c5)-1];
    for (c3 = 16 * c0 + 2; c3 <= min(loop, 16 * c0 + 16); c3 += 1)
      for (c5 = 0; c5 <= c1; c5 += 1)
        w[c1+1]+=b[c5][c1+1]*w[(c1+1-c5)-1];
  }

// 16x16x1
/*
for (c0 = 0; c0 <= floord(loop - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(n - 2, 16); c1 += 1) {
    for (c2 = 0; c2 <= 16 * c1; c2 += 1)
      w[16*c1+1]+=b[c2][16*c1+1]*w[(16*c1+1-c2)-1];
    for (c2 = 16 * c1 + 1; c2 <= min(min(16 * c1 + 16, loop - 16 * c0 + 16 * c1 + 14), n - c1 + floord(n - 2 * c1 - 3, 14) - 2); c2 += 1)
      if ((c2 >= 16 * c1 + 2 && 16 * c1 + 15 >= c2) || (-c1 + c2 - 1) % 15 == 0)
        for (c3 = max(16 * c0 + 1, 16 * c0 - 16 * c1 + c2 - 14); c3 <= min(loop, 16 * c0 - 16 * c1 + c2); c3 += 1)
          if ((-c1 + c2 - 1) % 15 == 0 || (c3 == 16 * c0 + 1 && c2 >= 16 * c1 + 2 && 16 * c1 + 15 >= c2)) {
            c4 = 240 * c0 + c2 + 14 >= 16 * c1 + 15 * c3 ? 16 * c0 + c2 - c3 + 2 : 16 * c1 + 16;
            for (c5 = 0; c5 < c2; c5 += 1)
              w[c4]+=b[c5][c4]*w[(c4-c5)-1];
            if (c4 == c2 + 1 && c3 == 16 * c0 + 1)
              w[c2+1]+=b[c2][c2+1]*w[(c2+1-c2)-1];
          }
  }


for (c0 = 0; c0 <= floord(loop - 1, 8); c0 += 1)
  for (c1 = 0; c1 <= floord(n - 2, 8); c1 += 1)
    for (c2 = 0; c2 <= c1; c2 += 1)
      if (c1 >= c2 + 1) {
        for (c5 = 8 * c2; c5 <= 8 * c2 + 7; c5 += 1)
          w[8*c1+1]+=b[c5][8*c1+1]*w[(8*c1+1-c5)-1];
      } else
        for (c3 = 8 * c0 + 1; c3 <= min(loop, 8 * c0 + 8); c3 += 1)
          for (c4 = 8 * c1 + 1; c4 <= min(n - 1, 8 * c1 + 8); c4 += 1) {
            if (c3 + c4 >= 8 * c0 + 8 * c1 + 3)
              for (c5 = 0; c5 < 8 * c1; c5 += 1)
                w[c4]+=b[c5][c4]*w[(c4-c5)-1];
            for (c5 = 8 * c1; c5 < c4; c5 += 1)
              w[c4]+=b[c5][c4]*w[(c4-c5)-1];
          }
*/

a = 0;

for (c0 = 0; c0 < floord(loop + 1, 2); c0 += 1)
  for (c1 = 0; c1 < n - 1; c1 += 1)
    for (c2 = 0; c2 <= c1; c2 += 1)
      if (c1 >= c2 + 1) {
        w[c1+1]=w[c1+1]+b[c2][c1+1]*w[(c1+1-c2)-1];
a++;
      } else
        for (c3 = 2 * c0 + 1; c3 <= min(loop, 2 * c0 + 2); c3 += 1) {
          if (c3 == 2 * c0 + 2)
            for (c5 = 0; c5 < c1; c5 += 1){
              w[c1+1]=w[c1+1]+b[c5][c1+1]*w[(c1+1-c5)-1];
              a++;}
          w[c1+1]=w[c1+1]+b[c1][c1+1]*w[(c1+1-c1)-1];
a++;
        }
cout << a;
/* SIMPLIFY
for (c0 = 0; c0 <= floord(loop - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(n - 2, 16); c1 += 1)
    for (c2 = 0; c2 <= min(n + loop - 16 * c0 - 15 * c1 - 3, c1 + 1); c2 += 1) {
      for (c5 = 16 * c2; c5 <= min(16 * c2 + 15, 16 * c1); c5 += 1)
        w[16*c1+1]+=b[c5][16*c1+1]*w[(16*c1+1-c5)-1];
      if (c2 == c1 + 1)
        for (c3 = max(-n + 16 * c0 + 16 * c1 + 4, 16 * c0 + 1); c3 <= min(16 * c0 + 16, loop); c3 += 1)
          for (c4 = max(16 * c1 + 1, 16 * c0 + 16 * c1 - c3 + 3); c4 <= min(n - 1, 16 * c1 + 16); c4 += 1)
            for (c5 = 0; c5 < c4; c5 += 1)
              w[c4]+=b[c5][c4]*w[(c4-c5)-1];
    }
*/


	for (i=0; i<N; i++) {
                if(w1[i] != w[i]) { std::cout << "error " << i << " " << w[i] << " " << w1[i]; exit(0);
 }
                 
        }



}

    double end = omp_get_wtime();
	printf("%.3f\n", end - start);

	#pragma endscop

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}
