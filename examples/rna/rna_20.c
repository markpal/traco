#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define MAX(x,y)    ((x) > (y)? (x) : (y))


#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 20;

int can_pair(int *input, int a, int b){
   return ((((input[a] + input[b]) == 3) && (a < b - 1))) ? 1 : 0;
}

int main(int argc, char *argv[])
{
    int num_proc=1;
    num_proc = atoi(argv[1]);
    int kind;

    if(argc > 2)
        N = atoi(argv[2]);

    int DIM = 2*N+2;

    if(argc > 3)
        kind = atoi(argv[3]);

    int i,j,k,c0,c1;
    double start, end;


    float (*S)[DIM];
    S = (float (*)[DIM])malloc(DIM * DIM * sizeof(float));
    int *RNA;
    RNA = (int (*))malloc(DIM * sizeof(float));


    start = omp_get_wtime();

#pragma parallel shared(S,RNA)
{
#pragma omp for
  for (c0 = 0; c0 <= 18; c0 += 1)
    S[c0][c0+1] = MAX(S[c0][c0+1], S[c0+1][c0+1-1] + can_pair(RNA, c0, c0+1));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 17; c0 += 1)
    for (c1 = c0 + 2; c1 <= min(c0 + 3, 19); c1 += 1) {
      if (c1 == c0 + 2)
        S[c0][c0+2] = MAX(S[c0][0+c0] + S[0+c0+1][c0+2], S[c0][c0+2]);
      S[c0][c1] = MAX(S[c0][1+c0] + S[1+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 17; c0 += 1)
    S[c0][c0+2] = MAX(S[c0][c0+2], S[c0+1][c0+2-1] + can_pair(RNA, c0, c0+2));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 16; c0 += 1)
    for (c1 = c0 + 3; c1 <= min(c0 + 5, 19); c1 += 1) {
      if (c0 + 4 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-3+c0] + S[-c0+c1-3+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][2+c0] + S[2+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 16; c0 += 1)
    S[c0][c0+3] = MAX(S[c0][c0+3], S[c0+1][c0+3-1] + can_pair(RNA, c0, c0+3));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 15; c0 += 1)
    for (c1 = c0 + 4; c1 <= min(c0 + 7, 19); c1 += 1) {
      if (c0 + 6 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-4+c0] + S[-c0+c1-4+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][3+c0] + S[3+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 15; c0 += 1)
    S[c0][c0+4] = MAX(S[c0][c0+4], S[c0+1][c0+4-1] + can_pair(RNA, c0, c0+4));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 14; c0 += 1)
    for (c1 = c0 + 5; c1 <= min(c0 + 9, 19); c1 += 1) {
      if (c0 + 8 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-5+c0] + S[-c0+c1-5+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][4+c0] + S[4+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 14; c0 += 1)
    S[c0][c0+5] = MAX(S[c0][c0+5], S[c0+1][c0+5-1] + can_pair(RNA, c0, c0+5));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 13; c0 += 1)
    for (c1 = c0 + 6; c1 <= min(c0 + 11, 19); c1 += 1) {
      if (c0 + 10 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-6+c0] + S[-c0+c1-6+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][5+c0] + S[5+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 13; c0 += 1)
    S[c0][c0+6] = MAX(S[c0][c0+6], S[c0+1][c0+6-1] + can_pair(RNA, c0, c0+6));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 12; c0 += 1)
    for (c1 = c0 + 7; c1 <= min(c0 + 13, 19); c1 += 1) {
      if (c0 + 12 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-7+c0] + S[-c0+c1-7+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][6+c0] + S[6+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 12; c0 += 1)
    S[c0][c0+7] = MAX(S[c0][c0+7], S[c0+1][c0+7-1] + can_pair(RNA, c0, c0+7));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 11; c0 += 1)
    for (c1 = c0 + 8; c1 <= min(c0 + 15, 19); c1 += 1) {
      if (c0 + 14 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-8+c0] + S[-c0+c1-8+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][7+c0] + S[7+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 11; c0 += 1)
    S[c0][c0+8] = MAX(S[c0][c0+8], S[c0+1][c0+8-1] + can_pair(RNA, c0, c0+8));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 10; c0 += 1)
    for (c1 = c0 + 9; c1 <= min(c0 + 17, 19); c1 += 1) {
      if (c0 + 16 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-9+c0] + S[-c0+c1-9+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][8+c0] + S[8+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 10; c0 += 1)
    S[c0][c0+9] = MAX(S[c0][c0+9], S[c0+1][c0+9-1] + can_pair(RNA, c0, c0+9));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 9; c0 += 1)
    for (c1 = c0 + 10; c1 <= 19; c1 += 1) {
      if (c0 + 18 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-10+c0] + S[-c0+c1-10+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][9+c0] + S[9+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 9; c0 += 1)
    S[c0][c0+10] = MAX(S[c0][c0+10], S[c0+1][c0+10-1] + can_pair(RNA, c0, c0+10));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 8; c0 += 1)
    for (c1 = c0 + 11; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-11+c0] + S[-c0+c1-11+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][10+c0] + S[10+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 8; c0 += 1)
    S[c0][c0+11] = MAX(S[c0][c0+11], S[c0+1][c0+11-1] + can_pair(RNA, c0, c0+11));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 7; c0 += 1)
    for (c1 = c0 + 12; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-12+c0] + S[-c0+c1-12+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][11+c0] + S[11+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 7; c0 += 1)
    S[c0][c0+12] = MAX(S[c0][c0+12], S[c0+1][c0+12-1] + can_pair(RNA, c0, c0+12));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 6; c0 += 1)
    for (c1 = c0 + 13; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-13+c0] + S[-c0+c1-13+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][12+c0] + S[12+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 6; c0 += 1)
    S[c0][c0+13] = MAX(S[c0][c0+13], S[c0+1][c0+13-1] + can_pair(RNA, c0, c0+13));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 5; c0 += 1)
    for (c1 = c0 + 14; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-14+c0] + S[-c0+c1-14+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][13+c0] + S[13+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 5; c0 += 1)
    S[c0][c0+14] = MAX(S[c0][c0+14], S[c0+1][c0+14-1] + can_pair(RNA, c0, c0+14));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 4; c0 += 1)
    for (c1 = c0 + 15; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-15+c0] + S[-c0+c1-15+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][14+c0] + S[14+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 4; c0 += 1)
    S[c0][c0+15] = MAX(S[c0][c0+15], S[c0+1][c0+15-1] + can_pair(RNA, c0, c0+15));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 3; c0 += 1)
    for (c1 = c0 + 16; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-16+c0] + S[-c0+c1-16+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][15+c0] + S[15+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 3; c0 += 1)
    S[c0][c0+16] = MAX(S[c0][c0+16], S[c0+1][c0+16-1] + can_pair(RNA, c0, c0+16));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 2; c0 += 1)
    for (c1 = c0 + 17; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-17+c0] + S[-c0+c1-17+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][16+c0] + S[16+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 2; c0 += 1)
    S[c0][c0+17] = MAX(S[c0][c0+17], S[c0+1][c0+17-1] + can_pair(RNA, c0, c0+17));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 1; c0 += 1)
    for (c1 = c0 + 18; c1 <= 19; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-18+c0] + S[-c0+c1-18+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][17+c0] + S[17+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 1; c0 += 1)
    if (c0 == 1) {
      S[1][19] = MAX(S[1][19], S[1+1][19-1] + can_pair(RNA, 1, 19));
    } else
      S[0][18] = MAX(S[0][18], S[0+1][18-1] + can_pair(RNA, 0, 18));
// --------------
if (N == 20) {
  S[0][19] = MAX(S[0][0+0] + S[0+0+1][19], S[0][19]);
  S[0][19] = MAX(S[0][18+0] + S[18+0+1][19], S[0][19]);
}
// --------------
  S[0][19] = MAX(S[0][19], S[0+1][19-1] + can_pair(RNA, 0, 19));
// --------------

}

    end = omp_get_wtime();
	printf("%.6f\n", end - start);

    return 0;


}

