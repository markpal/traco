#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 800;

int can_pair(int *input, int a, int b){
   return ((((input[a] + input[b]) == 3) && (a < b - 1))) ? 1 : 0;
}

int main(int argc, char *argv[])
{
    /*int num_proc=1;
    num_proc = atoi(argv[1]);
    int kind;

    if(argc > 2)
        N = atoi(argv[2]);



    if(argc > 3)
        kind = atoi(argv[3]);
*/
    int i,j,k,c=0;
    double start, end;

    int DIM = 2*N+2;
    double (*S)[DIM];
    double (*S1)[DIM];
    S = (double (*)[DIM])malloc(DIM * DIM * sizeof(double));
    S1 = (double (*)[DIM])malloc(DIM * DIM * sizeof(double));

    for(i=0; i<DIM; i++)
    for(j=0; j<DIM; j++){
           S1[i][j] = i*j+j/0.01;
           S[i][j]=i*j+j/0.01;
    }

    int *RNA;
    RNA = (int (*))malloc(DIM * sizeof(double));

int c1,c2,c3,c4,c5,c6,c7,c8,c9,c11;


    for (i = N-1; i >= 0; i--) {
     for (j = i+1; j < N; j++) {
      for (k = 0; k < j-i; k++) {
         S1[i][j] = max(S1[i][k+i] + S1[k+i+1][j], S1[i][j]); // s0
      }
      S1[i][j] = max(S1[i][j], S1[i+1][j-1] +can_pair(RNA, i, j));
     }
    }




    start = omp_get_wtime();
/*
for( c1 = 0; c1 <= (N - 1)/16; c1 += 1)
  for( c2 = 0; c2 <= 1; c2 += 1)
    for( c3 = 0; c3 <= min(c1, (N - 2)/16); c3 += 1) {
      if (c2 == 1) {
        for( c7 = max(0, N - 16 * c1 - 16); c7 < min(N - 16 * c1, N - 16 * c3 - 1); c7 += 1)
          for( c9 = 16 * c3 + c7 + 1; c9 <= min(N - 1, 16 * c3 + c7 + 16); c9 += 1)
            S[c7][c9] = max(S[c7][c9], S[c7+1][c9-1]  + can_pair(RNA, c7, c9));
      } else
        for( c5 = 0; c5 <= c3; c5 += 1)
          for( c7 = max(0, N - 16 * c1 - 16); c7 < min(N - 16 * c1, N - 15 * c1 - c3 - 1); c7 += 1) {
            if (c3 == 0 && c5 == 0 && 16 * c1 + c7 + 1 == N) {
              S[N-16*c1-1][N-16*c1] = max(S[N-16*c1-1][0+N-16*c1-1] + S[0+N-16*c1-1+1][N-16*c1], S[N-16*c1-1][N-16*c1]);
            } else if (c3 >= 1 && c5 == 0 && 16 * c1 + c7 + 1 == N) {
              for( c11 = 0; c11 <= 15; c11 += 1)
                S[N-16*c1-1][N-16*c1+16*c3] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][N-16*c1+16*c3], S[N-16*c1-1][N-16*c1+16*c3]);
            } else if (c5 == c3 && N >= 16 * c1 + c7 + 2) {
              S[c7][16*c3+c7+1] = max(S[c7][16*c3+c7] + S[16*c3+c7+1][16*c3+c7+1], S[c7][16*c3+c7+1]);
            } else if (c3 >= c5 + 1 && N >= 16 * c1 + c7 + 2)
              for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                S[c7][16*c3+c7+1] = max(S[c7][c11+c7] + S[c11+c7+1][16*c3+c7+1], S[c7][16*c3+c7+1]);
            if (c5 == 0)
              for( c9 = 16 * c3 + c7 + 2; c9 <= min(N - 1, 16 * c3 + c7 + 16); c9 += 1) {
                if (c3 == 0 && 16 * c1 + c7 + 1 == N) {
                  S[N-16*c1-1][c9] = max(S[N-16*c1-1][0+N-16*c1-1] + S[0+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
                } else if (c3 >= 1 && 16 * c1 + c7 + 1 == N) {
                  for( c11 = 0; c11 <= 15; c11 += 1)
                    S[N-16*c1-1][c9] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
                } else
                  for( c11 = 0; c11 <= 16 * c3; c11 += 1)
                    S[c7][c9] = max(S[c7][c11+c7] + S[c11+c7+1][c9], S[c7][c9]);
                for( c11 = 16 * c3 + 1; c11 < -c7 + c9; c11 += 1)
                  S[c7][c9] = max(S[c7][c11+c7] + S[c11+c7+1][c9], S[c7][c9]);
              }
            if (c5 >= 1 && c3 >= c5 + 1 && 16 * c1 + c7 + 1 == N) {
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= N - 16 * c1 + 16 * c3 + 15; c9 += 1)
                for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                  S[N-16*c1-1][c9] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
            } else if (c3 >= 1 && c5 == c3 && 16 * c1 + c7 + 1 == N)
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= N - 16 * c1 + 16 * c3 + 15; c9 += 1)
                S[N-16*c1-1][c9] = max(S[N-16*c1-1][16*c3+N-16*c1-1] + S[16*c3+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
          }
    }
*/

for( c1 = 0; c1 <= (N - 1)/16; c1 += 1)
  for( c2 = 0; c2 <= 1; c2 += 1)
    for( c3 = 0; c3 <= min(c1, -c1 + (N - 2)/8); c3 += 1) {
      if (c2 == 1) {
        for( c7 = max(0, N - 16 * c1 - 16); c7 < min(N - 16 * c1, N - 16 * c3 - 1); c7 += 1)
          for( c9 = 16 * c3 + c7 + 1; c9 <= min(N - 1, 16 * c3 + c7 + 16); c9 += 1)
            S[c7][c9] = max(S[c7][c9], S[c7+1][c9-1]  + can_pair(RNA, c7, c9));
      } else
        for( c5 = 0; c5 <= c3; c5 += 1)
          for( c7 = max(0, N - 16 * c1 - 16); c7 < min(N - 16 * c1, N - 15 * c1 - c3 - 1); c7 += 1) {
            if (c5 == 0 && 16 * c1 + c7 + 1 == N) {
              for( c11 = 0; c11 <= min(15, 15 * c3); c11 += 1)
                S[N-16*c1-1][N-16*c1+16*c3] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][N-16*c1+16*c3], S[N-16*c1-1][N-16*c1+16*c3]);
            } else if (N >= 16 * c1 + c7 + 2)
              for( c11 = 16 * c5; c11 <= min(15 * c3 + c5, 16 * c5 + 15); c11 += 1)
                S[c7][16*c3+c7+1] = max(S[c7][c11+c7] + S[c11+c7+1][16*c3+c7+1], S[c7][16*c3+c7+1]);
            if (c5 == 0)
              for( c9 = 16 * c3 + c7 + 2; c9 <= min(N - 1, 16 * c3 + c7 + 16); c9 += 1) {
                if (16 * c1 + c7 + 1 == N) {
                  for( c11 = 0; c11 <= min(15, 15 * c3); c11 += 1)
                    S[N-16*c1-1][c9] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
                } else
                  for( c11 = 0; c11 <= 16 * c3; c11 += 1)
                    S[c7][c9] = max(S[c7][c11+c7] + S[c11+c7+1][c9], S[c7][c9]);
                for( c11 = 16 * c3 + 1; c11 < -c7 + c9; c11 += 1)
                  S[c7][c9] = max(S[c7][c11+c7] + S[c11+c7+1][c9], S[c7][c9]);
              }
            if (c5 >= 1 && 16 * c1 + c7 + 1 == N)
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= N - 16 * c1 + 16 * c3 + 15; c9 += 1)
                for( c11 = 16 * c5; c11 <= min(15 * c3 + c5, 16 * c5 + 15); c11 += 1)
                  S[N-16*c1-1][c9] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
          }
    }

/*

for( c1 = 0; c1 <= (N - 1)/16; c1 += 1)
  for( c2 = 0; c2 <= 1; c2 += 1)
    for( c3 = 0; c3 <= min(c1, (N - 2)/16); c3 += 1) {
      if (c2 == 1) {
        for( c7 = max(0, N - 16 * c1 - 16); c7 < min(N - 16 * c1, N - 16 * c3 - 1); c7 += 1)
          for( c9 = 16 * c3 + c7 + 1; c9 <= min(N - 1, 16 * c3 + c7 + 16); c9 += 1)
            S[c7][c9] = max(S[c7][c9], S[c7+1][c9-1]  + can_pair(RNA, c7, c9));
      } else
        for( c5 = 0; c5 <= c3; c5 += 1)
          for( c7 = max(0, N - 16 * c1 - 16); c7 < min(N - 16 * c1, N - 15 * c1 - c3 - 1); c7 += 1) {
            if (c3 >= c5 + 1 && N >= 16 * c1 + c7 + 2) {
              for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                S[c7][16*c3+c7+1] = max(S[c7][c11+c7] + S[c11+c7+1][16*c3+c7+1], S[c7][16*c3+c7+1]);
            } else if (c5 == c3 && N >= 16 * c1 + c7 + 2) {
              S[c7][16*c3+c7+1] = max(S[c7][16*c3+c7] + S[16*c3+c7+1][16*c3+c7+1], S[c7][16*c3+c7+1]);
            } else if (c3 >= c5 + 1) {
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= N - 16 * c1 + 16 * c3 + 15; c9 += 1)
                for( c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
                  S[N-16*c1-1][c9] = max(S[N-16*c1-1][c11+N-16*c1-1] + S[c11+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
            } else {
              for( c9 = N - 16 * c1 + 16 * c3; c9 <= min(N - 16 * c1 + 32 * c3, N - 16 * c1 + 16 * c3 + 15); c9 += 1)
                S[N-16*c1-1][c9] = max(S[N-16*c1-1][16*c3+N-16*c1-1] + S[16*c3+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
              if (c3 == 0)
                for( c9 = N - 16 * c1 + 1; c9 <= N - 16 * c1 + 15; c9 += 1)
                  S[N-16*c1-1][c9] = max(S[N-16*c1-1][0+N-16*c1-1] + S[0+N-16*c1-1+1][c9], S[N-16*c1-1][c9]);
            }
          }
    }
*/


    end = omp_get_wtime();
	printf("%.6f\n%i", end - start,c);

	for(i=0; i<N; i++)
     for(j=0; j<N; j++)
       if(!(isnan(S[i][j]) && isnan(S1[i][j])))
         if(S[i][j] != S1[i][j]) { printf("Error %i %i %f %f\n", i, j, S[i][j], S1[i][j]); exit(0);}


    return 0;


}

