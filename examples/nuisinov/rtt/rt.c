#include <stdio.h>
#include <omp.h>

#define N 2000

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define ceild(n,d) ceil(((double)(n))/((double)(d)))

long double S[N][N];
long double S1[N][N];

int main(){

int i,j,k;
int c1,c2,c3,c5,c7,c9,c11,c10,c4,c12;


for(i=0; i<N; i++)
 for(j=0; j<N; j++){
 S[i][j] = i*j;
 S1[i][j] = S[i][j];


}
double start = omp_get_wtime();
int a=0;

    for (i = N-1; i >= 0; i--) {
     for (j = i+1; j < N; j++) {
      for (k = 0; k < j-i; k++) {
 S1[i][j] = S1[i][k+i] + S1[k+i+1][j] + S1[i][j];

      }
      for (k = 0; k < 1; k++) {
      S1[i][j] = S1[i+1][j-1] + S1[i][j];
     }
    }
   }
double stop = omp_get_wtime();
printf("%i %.2f\n",a, stop - start);
a=0;

/*
for( c1 = 1; c1 < N; c1 += 1)
  for( c2 = 0; c2 <= 1; c2 += 1)
    for( c3 = 0; c3 < c1; c3 += 1) {
      if (c2 == 1) {
    //    S[N-c1-1][N-c1+c3] = S[N-c1-1][N-c1+c3]  + S[N-c1-1+1][N-c1+c3-1];
      } else
        for( c5 = 0; c5 <= c3; c5 += 1){
          S[N-c1-1][N-c1+c3] = S[N-c1-1][c5+N-c1-1] + S[c5+N-c1-1+1][N-c1+c3]+ S[N-c1-1][N-c1+c3];
         a++;
}
    }
*/

//start = omp_get_wtime();
/*
for( c1 = 0; c1 <= floord(N - 1, 16); c1 += 1)
  for( c3 = 0; c3 <= min(c1, (N - 2)/ 16); c3 += 1)
    for( c4 = 0; c4 <= 1; c4 += 1) {
      if (c4 == 1) {
        for( c7 = max(-N + 16 * c1 + 1, -N + 16 * c3 + 2); c7 <= min(0, -N + 16 * c1 + 16); c7 += 1)
          for( c9 = 16 * c3 - c7 + 1; c9 <= min(N - 1, 16 * c3 - c7 + 16); c9 += 1)
            for( c10 = max(0, 16 * c3 - c7 - c9 + 2); c10 <= 1; c10 += 1) {
              if (c10 == 1) {
                S[-c7][c9] = S[-c7][c9]+ S[-c7+1][c9-1];
              } else {
                if (N + c7 >= 16 * c1 + 2)
                  for( c11 = 0; c11 <= 16 * c3; c11 += 1)
                    S[-c7][c9] = S[-c7][c11+-c7] + S[c11+-c7+1][c9]+ S[-c7][c9];
                for( c11 = 16 * c3 + 1; c11 < c7 + c9; c11 += 1)
                  S[-c7][c9] = S[-c7][c11+-c7] + S[c11+-c7+1][c9]+ S[-c7][c9];
              }
            }
      } else
        for( c5 = 0; c5 <= c3; c5 += 1)
          for( c7 = max(-N + 16 * c1 + 1, -N + 15 * c1 + c3 + 2); c7 <= min(0, -N + 16 * c1 + 16); c7 += 1) {
            if (c3 >= c5 + 1 && N + c7 >= 16 * c1 + 2) {
              for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                S[-c7][16*c3-c7+1] = S[-c7][c11+-c7] + S[c11+-c7+1][16*c3-c7+1]+ S[-c7][16*c3-c7+1];
            } else if (c3 >= c5 + 1 && N + c7 == 16 * c1 + 1) {
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= N - 16 * c1 + 16 * c3 + 15; c9 += 1)
                for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                  S[N-16*c1-1][c9] = S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][c9]+ S[N-16*c1-1][c9];
            } else if (N + c7 >= 16 * c1 + 2) {
              S[-c7][16*c3-c7+1] = S[-c7][16*c3+-c7] + S[16*c3+-c7+1][16*c3-c7+1]+ S[-c7][16*c3-c7+1];
            } else
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= N - 16 * c1 + 16 * c3 + 15; c9 += 1)
                S[N-16*c1-1][c9] = S[N-16*c1-1][16*c3+N-16*c1-1] + S[16*c3+N-16*c1-1+1][c9]+ S[N-16*c1-1][c9];
          }
    }

*/
 register int lbv1, ubv1;
start = omp_get_wtime();



for( c1 = 0; c1 <= floord(N - 2, 8); c1 += 1)
#pragma omp parallel for shared(c1, S) private(c2,c3,c5,c7,c9,c11,c10,c4,c12)
 for( c3 = max(0, c1 - (N + 15) / 16 + 1); c3 <= c1/2; c3 += 1)
    for( c4 = 0; c4 <= 1; c4 += 1) {
      if (c4 == 1) {
        for( c7 = max(-N + 16 * c1 - 16 * c3 + 1, -N + 16 * c3 + 2); c7 <= min(0, -N + 16 * c1 - 16 * c3 + 16); c7 += 1)
          for( c9 = 16 * c3 - c7 + 1; c9 <= min(N - 1, 16 * c3 - c7 + 16); c9 += 1)
            for( c10 = max(0, 16 * c3 - c7 - c9 + 2); c10 <= 1; c10 += 1) {
              if (c10 == 1) {
                S[-c7][c9] = S[-c7][c9]+ S[-c7+1][c9-1];
              } else {
                if (N + 16 * c3 + c7 >= 16 * c1 + 2)
                  for( c11 = 0; c11 <= 16 * c3; c11 += 1)
                    S[-c7][c9] = S[-c7][c11+-c7] + S[c11+-c7+1][c9]+ S[-c7][c9];
                for( c11 = 16 * c3 + 1; c11 < c7 + c9; c11 += 1)
                  S[-c7][c9] = S[-c7][c11+-c7] + S[c11+-c7+1][c9]+ S[-c7][c9];
              }
            }
      } else
        for( c5 = 0; c5 <= c3; c5 += 1)
          for( c7 = max(-N + 16 * c1 - 16 * c3 + 1, -N + 15 * c1 - 14 * c3 + 2); c7 <= min(0, -N + 16 * c1 - 16 * c3 + 16); c7 += 1) {
            if (c3 >= c5 + 1 && N + 16 * c3 + c7 >= 16 * c1 + 2) {
              for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                S[-c7][16*c3-c7+1] = S[-c7][c11+-c7] + S[c11+-c7+1][16*c3-c7+1]+ S[-c7][16*c3-c7+1];
            } else if (c3 >= c5 + 1 && N + 16 * c3 + c7 == 16 * c1 + 1) {
              for( c9 = N - 16 * c1 + 32 * c3; c9 <= N - 16 * c1 + 32 * c3 + 15; c9 += 1)
                for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                  S[N-16*c1+16*c3-1][c9] = S[N-16*c1+16*c3-1][c11+N-16*c1+16*c3-1] + S[c11+N-16*c1+16*c3-1+1][c9]+ S[N-16*c1+16*c3-1][c9];
            } else if (N + 16 * c3 + c7 >= 16 * c1 + 2) {
              S[-c7][16*c3-c7+1] = S[-c7][16*c3+-c7] + S[16*c3+-c7+1][16*c3-c7+1]+ S[-c7][16*c3-c7+1];
            } else
              for( c9 = N - 16 * c1 + 32 * c3; c9 <= N - 16 * c1 + 32 * c3 + 15; c9 += 1)
                S[N-16*c1+16*c3-1][c9] = S[N-16*c1+16*c3-1][16*c3+N-16*c1+16*c3-1] + S[16*c3+N-16*c1+16*c3-1+1][c9]+ S[N-16*c1+16*c3-1][c9];
          }
    }


stop = omp_get_wtime();
printf("%i %.2f\n",a, stop - start);


/*
    for (i = 1; i <= N-1; i++) {
#pragma omp parallel for shared(S,i) private(j,k)
     for (j = i; j < N; j++) {
      for (k = 0; k <= i-1; k++) {
 S[-i+j][j] = S[-i+j][k-i+j] + S[k-i+1+j][j] + S[-i+j][j];

      }
      for (k = 0; k < 1; k++) {
      S[-i+j][j] = S[-i+1+j][j-1] + S[-i+j][j];
     }
    }
   }
*/



  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */

start = omp_get_wtime();
if (N >= 2) {
  for (t2=max(-1,ceild(-N-29,32));t2<=floord(N-1,32);t2++) {
    lbp=max(0,t2);
    ubp=min(floord(N-1,32),floord(32*t2+N+29,32));
#pragma omp parallel for shared(lbv,ubv,t2) private(t5,t6,t7,t8,t9,t10)
    for (t4=lbp;t4<=ubp;t4++) {
      for (t5=max(max(-N+2,32*t2-32*t4),-32*t4-30);t5<=min(0,32*t2-32*t4+31);t5++) {
        for (t7=max(32*t4,-t5+1);t7<=min(N-1,32*t4+31);t7++) {
          for (t9=0;t9<=t5+t7-1;t9++) {
            S[-t5][t7] = S[-t5][t9+-t5] + S[t9+-t5+1][t7] + S[-t5][t7];;
          }
          S[-t5][t7] = S[-t5+1][t7-1] + S[-t5][t7];;
        }
      }
    }
  }
}
stop = omp_get_wtime();
printf("%i %.2f\n",a, stop - start);
//printf("%i ", c7);

//printf("\n");

/* End of CLooG code */


printf("%i\n",a);


for(i=0; i<N; i++)
 for(j=0; j<N; j++){
   if(S1[i][j] != S[i][j]){
 //printf("error %i %i  \n ", i,j);
//exit(0);
    //printf("error %i %i %Lf %Lf \n ", i,j, S[i][j], S1[i][j]);
  //  printf("error\n");
//exit(0);
  }
}


return 0;
}
