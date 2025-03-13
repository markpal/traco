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
  for (c0 = 0; c0 <= 98; c0 += 1)
    S[c0][c0+1] = MAX(S[c0][c0+1], S[c0+1][c0+1-1] + can_pair(RNA, c0, c0+1));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 97; c0 += 1)
    for (c1 = c0 + 2; c1 <= min(c0 + 3, 99); c1 += 1) {
      if (c1 == c0 + 2)
        S[c0][c0+2] = MAX(S[c0][0+c0] + S[0+c0+1][c0+2], S[c0][c0+2]);
      S[c0][c1] = MAX(S[c0][1+c0] + S[1+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 97; c0 += 1)
    S[c0][c0+2] = MAX(S[c0][c0+2], S[c0+1][c0+2-1] + can_pair(RNA, c0, c0+2));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 96; c0 += 1)
    for (c1 = c0 + 3; c1 <= min(c0 + 5, 99); c1 += 1) {
      if (c0 + 4 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-3+c0] + S[-c0+c1-3+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][2+c0] + S[2+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 96; c0 += 1)
    S[c0][c0+3] = MAX(S[c0][c0+3], S[c0+1][c0+3-1] + can_pair(RNA, c0, c0+3));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 95; c0 += 1)
    for (c1 = c0 + 4; c1 <= min(c0 + 7, 99); c1 += 1) {
      if (c0 + 6 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-4+c0] + S[-c0+c1-4+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][3+c0] + S[3+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 95; c0 += 1)
    S[c0][c0+4] = MAX(S[c0][c0+4], S[c0+1][c0+4-1] + can_pair(RNA, c0, c0+4));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 94; c0 += 1)
    for (c1 = c0 + 5; c1 <= min(c0 + 9, 99); c1 += 1) {
      if (c0 + 8 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-5+c0] + S[-c0+c1-5+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][4+c0] + S[4+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 94; c0 += 1)
    S[c0][c0+5] = MAX(S[c0][c0+5], S[c0+1][c0+5-1] + can_pair(RNA, c0, c0+5));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 93; c0 += 1)
    for (c1 = c0 + 6; c1 <= min(c0 + 11, 99); c1 += 1) {
      if (c0 + 10 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-6+c0] + S[-c0+c1-6+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][5+c0] + S[5+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 93; c0 += 1)
    S[c0][c0+6] = MAX(S[c0][c0+6], S[c0+1][c0+6-1] + can_pair(RNA, c0, c0+6));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 92; c0 += 1)
    for (c1 = c0 + 7; c1 <= min(c0 + 13, 99); c1 += 1) {
      if (c0 + 12 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-7+c0] + S[-c0+c1-7+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][6+c0] + S[6+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 92; c0 += 1)
    S[c0][c0+7] = MAX(S[c0][c0+7], S[c0+1][c0+7-1] + can_pair(RNA, c0, c0+7));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 91; c0 += 1)
    for (c1 = c0 + 8; c1 <= min(c0 + 15, 99); c1 += 1) {
      if (c0 + 14 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-8+c0] + S[-c0+c1-8+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][7+c0] + S[7+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 91; c0 += 1)
    S[c0][c0+8] = MAX(S[c0][c0+8], S[c0+1][c0+8-1] + can_pair(RNA, c0, c0+8));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 90; c0 += 1)
    for (c1 = c0 + 9; c1 <= min(c0 + 17, 99); c1 += 1) {
      if (c0 + 16 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-9+c0] + S[-c0+c1-9+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][8+c0] + S[8+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 90; c0 += 1)
    S[c0][c0+9] = MAX(S[c0][c0+9], S[c0+1][c0+9-1] + can_pair(RNA, c0, c0+9));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 89; c0 += 1)
    for (c1 = c0 + 10; c1 <= min(c0 + 19, 99); c1 += 1) {
      if (c0 + 18 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-10+c0] + S[-c0+c1-10+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][9+c0] + S[9+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 89; c0 += 1)
    S[c0][c0+10] = MAX(S[c0][c0+10], S[c0+1][c0+10-1] + can_pair(RNA, c0, c0+10));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 88; c0 += 1)
    for (c1 = c0 + 11; c1 <= min(c0 + 21, 99); c1 += 1) {
      if (c0 + 20 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-11+c0] + S[-c0+c1-11+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][10+c0] + S[10+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 88; c0 += 1)
    S[c0][c0+11] = MAX(S[c0][c0+11], S[c0+1][c0+11-1] + can_pair(RNA, c0, c0+11));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 87; c0 += 1)
    for (c1 = c0 + 12; c1 <= min(c0 + 23, 99); c1 += 1) {
      if (c0 + 22 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-12+c0] + S[-c0+c1-12+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][11+c0] + S[11+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 87; c0 += 1)
    S[c0][c0+12] = MAX(S[c0][c0+12], S[c0+1][c0+12-1] + can_pair(RNA, c0, c0+12));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 86; c0 += 1)
    for (c1 = c0 + 13; c1 <= min(c0 + 25, 99); c1 += 1) {
      if (c0 + 24 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-13+c0] + S[-c0+c1-13+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][12+c0] + S[12+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 86; c0 += 1)
    S[c0][c0+13] = MAX(S[c0][c0+13], S[c0+1][c0+13-1] + can_pair(RNA, c0, c0+13));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 85; c0 += 1)
    for (c1 = c0 + 14; c1 <= min(c0 + 27, 99); c1 += 1) {
      if (c0 + 26 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-14+c0] + S[-c0+c1-14+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][13+c0] + S[13+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 85; c0 += 1)
    S[c0][c0+14] = MAX(S[c0][c0+14], S[c0+1][c0+14-1] + can_pair(RNA, c0, c0+14));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 84; c0 += 1)
    for (c1 = c0 + 15; c1 <= min(c0 + 29, 99); c1 += 1) {
      if (c0 + 28 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-15+c0] + S[-c0+c1-15+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][14+c0] + S[14+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 84; c0 += 1)
    S[c0][c0+15] = MAX(S[c0][c0+15], S[c0+1][c0+15-1] + can_pair(RNA, c0, c0+15));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 83; c0 += 1)
    for (c1 = c0 + 16; c1 <= min(c0 + 31, 99); c1 += 1) {
      if (c0 + 30 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-16+c0] + S[-c0+c1-16+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][15+c0] + S[15+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 83; c0 += 1)
    S[c0][c0+16] = MAX(S[c0][c0+16], S[c0+1][c0+16-1] + can_pair(RNA, c0, c0+16));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 82; c0 += 1)
    for (c1 = c0 + 17; c1 <= min(c0 + 33, 99); c1 += 1) {
      if (c0 + 32 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-17+c0] + S[-c0+c1-17+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][16+c0] + S[16+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 82; c0 += 1)
    S[c0][c0+17] = MAX(S[c0][c0+17], S[c0+1][c0+17-1] + can_pair(RNA, c0, c0+17));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 81; c0 += 1)
    for (c1 = c0 + 18; c1 <= min(c0 + 35, 99); c1 += 1) {
      if (c0 + 34 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-18+c0] + S[-c0+c1-18+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][17+c0] + S[17+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 81; c0 += 1)
    S[c0][c0+18] = MAX(S[c0][c0+18], S[c0+1][c0+18-1] + can_pair(RNA, c0, c0+18));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 80; c0 += 1)
    for (c1 = c0 + 19; c1 <= min(c0 + 37, 99); c1 += 1) {
      if (c0 + 36 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-19+c0] + S[-c0+c1-19+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][18+c0] + S[18+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 80; c0 += 1)
    S[c0][c0+19] = MAX(S[c0][c0+19], S[c0+1][c0+19-1] + can_pair(RNA, c0, c0+19));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 79; c0 += 1)
    for (c1 = c0 + 20; c1 <= min(c0 + 39, 99); c1 += 1) {
      if (c0 + 38 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-20+c0] + S[-c0+c1-20+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][19+c0] + S[19+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 79; c0 += 1)
    S[c0][c0+20] = MAX(S[c0][c0+20], S[c0+1][c0+20-1] + can_pair(RNA, c0, c0+20));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 78; c0 += 1)
    for (c1 = c0 + 21; c1 <= min(c0 + 41, 99); c1 += 1) {
      if (c0 + 40 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-21+c0] + S[-c0+c1-21+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][20+c0] + S[20+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 78; c0 += 1)
    S[c0][c0+21] = MAX(S[c0][c0+21], S[c0+1][c0+21-1] + can_pair(RNA, c0, c0+21));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 77; c0 += 1)
    for (c1 = c0 + 22; c1 <= min(c0 + 43, 99); c1 += 1) {
      if (c0 + 42 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-22+c0] + S[-c0+c1-22+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][21+c0] + S[21+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 77; c0 += 1)
    S[c0][c0+22] = MAX(S[c0][c0+22], S[c0+1][c0+22-1] + can_pair(RNA, c0, c0+22));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 76; c0 += 1)
    for (c1 = c0 + 23; c1 <= min(c0 + 45, 99); c1 += 1) {
      if (c0 + 44 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-23+c0] + S[-c0+c1-23+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][22+c0] + S[22+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 76; c0 += 1)
    S[c0][c0+23] = MAX(S[c0][c0+23], S[c0+1][c0+23-1] + can_pair(RNA, c0, c0+23));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 75; c0 += 1)
    for (c1 = c0 + 24; c1 <= min(c0 + 47, 99); c1 += 1) {
      if (c0 + 46 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-24+c0] + S[-c0+c1-24+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][23+c0] + S[23+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 75; c0 += 1)
    S[c0][c0+24] = MAX(S[c0][c0+24], S[c0+1][c0+24-1] + can_pair(RNA, c0, c0+24));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 74; c0 += 1)
    for (c1 = c0 + 25; c1 <= min(c0 + 49, 99); c1 += 1) {
      if (c0 + 48 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-25+c0] + S[-c0+c1-25+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][24+c0] + S[24+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 74; c0 += 1)
    S[c0][c0+25] = MAX(S[c0][c0+25], S[c0+1][c0+25-1] + can_pair(RNA, c0, c0+25));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 73; c0 += 1)
    for (c1 = c0 + 26; c1 <= min(c0 + 51, 99); c1 += 1) {
      if (c0 + 50 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-26+c0] + S[-c0+c1-26+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][25+c0] + S[25+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 73; c0 += 1)
    S[c0][c0+26] = MAX(S[c0][c0+26], S[c0+1][c0+26-1] + can_pair(RNA, c0, c0+26));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 72; c0 += 1)
    for (c1 = c0 + 27; c1 <= min(c0 + 53, 99); c1 += 1) {
      if (c0 + 52 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-27+c0] + S[-c0+c1-27+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][26+c0] + S[26+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 72; c0 += 1)
    S[c0][c0+27] = MAX(S[c0][c0+27], S[c0+1][c0+27-1] + can_pair(RNA, c0, c0+27));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 71; c0 += 1)
    for (c1 = c0 + 28; c1 <= min(c0 + 55, 99); c1 += 1) {
      if (c0 + 54 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-28+c0] + S[-c0+c1-28+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][27+c0] + S[27+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 71; c0 += 1)
    S[c0][c0+28] = MAX(S[c0][c0+28], S[c0+1][c0+28-1] + can_pair(RNA, c0, c0+28));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 70; c0 += 1)
    for (c1 = c0 + 29; c1 <= min(c0 + 57, 99); c1 += 1) {
      if (c0 + 56 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-29+c0] + S[-c0+c1-29+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][28+c0] + S[28+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 70; c0 += 1)
    S[c0][c0+29] = MAX(S[c0][c0+29], S[c0+1][c0+29-1] + can_pair(RNA, c0, c0+29));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 69; c0 += 1)
    for (c1 = c0 + 30; c1 <= min(c0 + 59, 99); c1 += 1) {
      if (c0 + 58 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-30+c0] + S[-c0+c1-30+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][29+c0] + S[29+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 69; c0 += 1)
    S[c0][c0+30] = MAX(S[c0][c0+30], S[c0+1][c0+30-1] + can_pair(RNA, c0, c0+30));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 68; c0 += 1)
    for (c1 = c0 + 31; c1 <= min(c0 + 61, 99); c1 += 1) {
      if (c0 + 60 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-31+c0] + S[-c0+c1-31+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][30+c0] + S[30+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 68; c0 += 1)
    S[c0][c0+31] = MAX(S[c0][c0+31], S[c0+1][c0+31-1] + can_pair(RNA, c0, c0+31));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 67; c0 += 1)
    for (c1 = c0 + 32; c1 <= min(c0 + 63, 99); c1 += 1) {
      if (c0 + 62 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-32+c0] + S[-c0+c1-32+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][31+c0] + S[31+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 67; c0 += 1)
    S[c0][c0+32] = MAX(S[c0][c0+32], S[c0+1][c0+32-1] + can_pair(RNA, c0, c0+32));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 66; c0 += 1)
    for (c1 = c0 + 33; c1 <= min(c0 + 65, 99); c1 += 1) {
      if (c0 + 64 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-33+c0] + S[-c0+c1-33+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][32+c0] + S[32+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 66; c0 += 1)
    S[c0][c0+33] = MAX(S[c0][c0+33], S[c0+1][c0+33-1] + can_pair(RNA, c0, c0+33));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 65; c0 += 1)
    for (c1 = c0 + 34; c1 <= min(c0 + 67, 99); c1 += 1) {
      if (c0 + 66 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-34+c0] + S[-c0+c1-34+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][33+c0] + S[33+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 65; c0 += 1)
    S[c0][c0+34] = MAX(S[c0][c0+34], S[c0+1][c0+34-1] + can_pair(RNA, c0, c0+34));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 64; c0 += 1)
    for (c1 = c0 + 35; c1 <= min(c0 + 69, 99); c1 += 1) {
      if (c0 + 68 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-35+c0] + S[-c0+c1-35+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][34+c0] + S[34+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 64; c0 += 1)
    S[c0][c0+35] = MAX(S[c0][c0+35], S[c0+1][c0+35-1] + can_pair(RNA, c0, c0+35));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 63; c0 += 1)
    for (c1 = c0 + 36; c1 <= min(c0 + 71, 99); c1 += 1) {
      if (c0 + 70 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-36+c0] + S[-c0+c1-36+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][35+c0] + S[35+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 63; c0 += 1)
    S[c0][c0+36] = MAX(S[c0][c0+36], S[c0+1][c0+36-1] + can_pair(RNA, c0, c0+36));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 62; c0 += 1)
    for (c1 = c0 + 37; c1 <= min(c0 + 73, 99); c1 += 1) {
      if (c0 + 72 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-37+c0] + S[-c0+c1-37+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][36+c0] + S[36+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 62; c0 += 1)
    S[c0][c0+37] = MAX(S[c0][c0+37], S[c0+1][c0+37-1] + can_pair(RNA, c0, c0+37));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 61; c0 += 1)
    for (c1 = c0 + 38; c1 <= min(c0 + 75, 99); c1 += 1) {
      if (c0 + 74 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-38+c0] + S[-c0+c1-38+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][37+c0] + S[37+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 61; c0 += 1)
    S[c0][c0+38] = MAX(S[c0][c0+38], S[c0+1][c0+38-1] + can_pair(RNA, c0, c0+38));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 60; c0 += 1)
    for (c1 = c0 + 39; c1 <= min(c0 + 77, 99); c1 += 1) {
      if (c0 + 76 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-39+c0] + S[-c0+c1-39+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][38+c0] + S[38+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 60; c0 += 1)
    S[c0][c0+39] = MAX(S[c0][c0+39], S[c0+1][c0+39-1] + can_pair(RNA, c0, c0+39));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 59; c0 += 1)
    for (c1 = c0 + 40; c1 <= min(c0 + 79, 99); c1 += 1) {
      if (c0 + 78 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-40+c0] + S[-c0+c1-40+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][39+c0] + S[39+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 59; c0 += 1)
    S[c0][c0+40] = MAX(S[c0][c0+40], S[c0+1][c0+40-1] + can_pair(RNA, c0, c0+40));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 58; c0 += 1)
    for (c1 = c0 + 41; c1 <= min(c0 + 81, 99); c1 += 1) {
      if (c0 + 80 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-41+c0] + S[-c0+c1-41+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][40+c0] + S[40+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 58; c0 += 1)
    S[c0][c0+41] = MAX(S[c0][c0+41], S[c0+1][c0+41-1] + can_pair(RNA, c0, c0+41));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 57; c0 += 1)
    for (c1 = c0 + 42; c1 <= min(c0 + 83, 99); c1 += 1) {
      if (c0 + 82 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-42+c0] + S[-c0+c1-42+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][41+c0] + S[41+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 57; c0 += 1)
    S[c0][c0+42] = MAX(S[c0][c0+42], S[c0+1][c0+42-1] + can_pair(RNA, c0, c0+42));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 56; c0 += 1)
    for (c1 = c0 + 43; c1 <= min(c0 + 85, 99); c1 += 1) {
      if (c0 + 84 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-43+c0] + S[-c0+c1-43+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][42+c0] + S[42+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 56; c0 += 1)
    S[c0][c0+43] = MAX(S[c0][c0+43], S[c0+1][c0+43-1] + can_pair(RNA, c0, c0+43));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 55; c0 += 1)
    for (c1 = c0 + 44; c1 <= min(c0 + 87, 99); c1 += 1) {
      if (c0 + 86 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-44+c0] + S[-c0+c1-44+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][43+c0] + S[43+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 55; c0 += 1)
    S[c0][c0+44] = MAX(S[c0][c0+44], S[c0+1][c0+44-1] + can_pair(RNA, c0, c0+44));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 54; c0 += 1)
    for (c1 = c0 + 45; c1 <= min(c0 + 89, 99); c1 += 1) {
      if (c0 + 88 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-45+c0] + S[-c0+c1-45+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][44+c0] + S[44+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 54; c0 += 1)
    S[c0][c0+45] = MAX(S[c0][c0+45], S[c0+1][c0+45-1] + can_pair(RNA, c0, c0+45));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 53; c0 += 1)
    for (c1 = c0 + 46; c1 <= min(c0 + 91, 99); c1 += 1) {
      if (c0 + 90 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-46+c0] + S[-c0+c1-46+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][45+c0] + S[45+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 53; c0 += 1)
    S[c0][c0+46] = MAX(S[c0][c0+46], S[c0+1][c0+46-1] + can_pair(RNA, c0, c0+46));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 52; c0 += 1)
    for (c1 = c0 + 47; c1 <= min(c0 + 93, 99); c1 += 1) {
      if (c0 + 92 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-47+c0] + S[-c0+c1-47+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][46+c0] + S[46+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 52; c0 += 1)
    S[c0][c0+47] = MAX(S[c0][c0+47], S[c0+1][c0+47-1] + can_pair(RNA, c0, c0+47));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 51; c0 += 1)
    for (c1 = c0 + 48; c1 <= min(c0 + 95, 99); c1 += 1) {
      if (c0 + 94 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-48+c0] + S[-c0+c1-48+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][47+c0] + S[47+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 51; c0 += 1)
    S[c0][c0+48] = MAX(S[c0][c0+48], S[c0+1][c0+48-1] + can_pair(RNA, c0, c0+48));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 50; c0 += 1)
    for (c1 = c0 + 49; c1 <= min(c0 + 97, 99); c1 += 1) {
      if (c0 + 96 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-49+c0] + S[-c0+c1-49+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][48+c0] + S[48+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 50; c0 += 1)
    S[c0][c0+49] = MAX(S[c0][c0+49], S[c0+1][c0+49-1] + can_pair(RNA, c0, c0+49));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 49; c0 += 1)
    for (c1 = c0 + 50; c1 <= 99; c1 += 1) {
      if (c0 + 98 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-50+c0] + S[-c0+c1-50+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][49+c0] + S[49+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 49; c0 += 1)
    S[c0][c0+50] = MAX(S[c0][c0+50], S[c0+1][c0+50-1] + can_pair(RNA, c0, c0+50));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 48; c0 += 1)
    for (c1 = c0 + 51; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-51+c0] + S[-c0+c1-51+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][50+c0] + S[50+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 48; c0 += 1)
    S[c0][c0+51] = MAX(S[c0][c0+51], S[c0+1][c0+51-1] + can_pair(RNA, c0, c0+51));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 47; c0 += 1)
    for (c1 = c0 + 52; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-52+c0] + S[-c0+c1-52+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][51+c0] + S[51+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 47; c0 += 1)
    S[c0][c0+52] = MAX(S[c0][c0+52], S[c0+1][c0+52-1] + can_pair(RNA, c0, c0+52));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 46; c0 += 1)
    for (c1 = c0 + 53; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-53+c0] + S[-c0+c1-53+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][52+c0] + S[52+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 46; c0 += 1)
    S[c0][c0+53] = MAX(S[c0][c0+53], S[c0+1][c0+53-1] + can_pair(RNA, c0, c0+53));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 45; c0 += 1)
    for (c1 = c0 + 54; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-54+c0] + S[-c0+c1-54+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][53+c0] + S[53+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 45; c0 += 1)
    S[c0][c0+54] = MAX(S[c0][c0+54], S[c0+1][c0+54-1] + can_pair(RNA, c0, c0+54));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 44; c0 += 1)
    for (c1 = c0 + 55; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-55+c0] + S[-c0+c1-55+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][54+c0] + S[54+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 44; c0 += 1)
    S[c0][c0+55] = MAX(S[c0][c0+55], S[c0+1][c0+55-1] + can_pair(RNA, c0, c0+55));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 43; c0 += 1)
    for (c1 = c0 + 56; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-56+c0] + S[-c0+c1-56+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][55+c0] + S[55+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 43; c0 += 1)
    S[c0][c0+56] = MAX(S[c0][c0+56], S[c0+1][c0+56-1] + can_pair(RNA, c0, c0+56));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 42; c0 += 1)
    for (c1 = c0 + 57; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-57+c0] + S[-c0+c1-57+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][56+c0] + S[56+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 42; c0 += 1)
    S[c0][c0+57] = MAX(S[c0][c0+57], S[c0+1][c0+57-1] + can_pair(RNA, c0, c0+57));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 41; c0 += 1)
    for (c1 = c0 + 58; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-58+c0] + S[-c0+c1-58+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][57+c0] + S[57+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 41; c0 += 1)
    S[c0][c0+58] = MAX(S[c0][c0+58], S[c0+1][c0+58-1] + can_pair(RNA, c0, c0+58));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 40; c0 += 1)
    for (c1 = c0 + 59; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-59+c0] + S[-c0+c1-59+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][58+c0] + S[58+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 40; c0 += 1)
    S[c0][c0+59] = MAX(S[c0][c0+59], S[c0+1][c0+59-1] + can_pair(RNA, c0, c0+59));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 39; c0 += 1)
    for (c1 = c0 + 60; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-60+c0] + S[-c0+c1-60+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][59+c0] + S[59+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 39; c0 += 1)
    S[c0][c0+60] = MAX(S[c0][c0+60], S[c0+1][c0+60-1] + can_pair(RNA, c0, c0+60));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 38; c0 += 1)
    for (c1 = c0 + 61; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-61+c0] + S[-c0+c1-61+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][60+c0] + S[60+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 38; c0 += 1)
    S[c0][c0+61] = MAX(S[c0][c0+61], S[c0+1][c0+61-1] + can_pair(RNA, c0, c0+61));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 37; c0 += 1)
    for (c1 = c0 + 62; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-62+c0] + S[-c0+c1-62+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][61+c0] + S[61+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 37; c0 += 1)
    S[c0][c0+62] = MAX(S[c0][c0+62], S[c0+1][c0+62-1] + can_pair(RNA, c0, c0+62));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 36; c0 += 1)
    for (c1 = c0 + 63; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-63+c0] + S[-c0+c1-63+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][62+c0] + S[62+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 36; c0 += 1)
    S[c0][c0+63] = MAX(S[c0][c0+63], S[c0+1][c0+63-1] + can_pair(RNA, c0, c0+63));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 35; c0 += 1)
    for (c1 = c0 + 64; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-64+c0] + S[-c0+c1-64+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][63+c0] + S[63+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 35; c0 += 1)
    S[c0][c0+64] = MAX(S[c0][c0+64], S[c0+1][c0+64-1] + can_pair(RNA, c0, c0+64));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 34; c0 += 1)
    for (c1 = c0 + 65; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-65+c0] + S[-c0+c1-65+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][64+c0] + S[64+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 34; c0 += 1)
    S[c0][c0+65] = MAX(S[c0][c0+65], S[c0+1][c0+65-1] + can_pair(RNA, c0, c0+65));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 33; c0 += 1)
    for (c1 = c0 + 66; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-66+c0] + S[-c0+c1-66+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][65+c0] + S[65+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 33; c0 += 1)
    S[c0][c0+66] = MAX(S[c0][c0+66], S[c0+1][c0+66-1] + can_pair(RNA, c0, c0+66));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 32; c0 += 1)
    for (c1 = c0 + 67; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-67+c0] + S[-c0+c1-67+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][66+c0] + S[66+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 32; c0 += 1)
    S[c0][c0+67] = MAX(S[c0][c0+67], S[c0+1][c0+67-1] + can_pair(RNA, c0, c0+67));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 31; c0 += 1)
    for (c1 = c0 + 68; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-68+c0] + S[-c0+c1-68+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][67+c0] + S[67+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 31; c0 += 1)
    S[c0][c0+68] = MAX(S[c0][c0+68], S[c0+1][c0+68-1] + can_pair(RNA, c0, c0+68));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 30; c0 += 1)
    for (c1 = c0 + 69; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-69+c0] + S[-c0+c1-69+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][68+c0] + S[68+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 30; c0 += 1)
    S[c0][c0+69] = MAX(S[c0][c0+69], S[c0+1][c0+69-1] + can_pair(RNA, c0, c0+69));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 29; c0 += 1)
    for (c1 = c0 + 70; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-70+c0] + S[-c0+c1-70+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][69+c0] + S[69+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 29; c0 += 1)
    S[c0][c0+70] = MAX(S[c0][c0+70], S[c0+1][c0+70-1] + can_pair(RNA, c0, c0+70));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 28; c0 += 1)
    for (c1 = c0 + 71; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-71+c0] + S[-c0+c1-71+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][70+c0] + S[70+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 28; c0 += 1)
    S[c0][c0+71] = MAX(S[c0][c0+71], S[c0+1][c0+71-1] + can_pair(RNA, c0, c0+71));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 27; c0 += 1)
    for (c1 = c0 + 72; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-72+c0] + S[-c0+c1-72+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][71+c0] + S[71+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 27; c0 += 1)
    S[c0][c0+72] = MAX(S[c0][c0+72], S[c0+1][c0+72-1] + can_pair(RNA, c0, c0+72));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 26; c0 += 1)
    for (c1 = c0 + 73; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-73+c0] + S[-c0+c1-73+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][72+c0] + S[72+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 26; c0 += 1)
    S[c0][c0+73] = MAX(S[c0][c0+73], S[c0+1][c0+73-1] + can_pair(RNA, c0, c0+73));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 25; c0 += 1)
    for (c1 = c0 + 74; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-74+c0] + S[-c0+c1-74+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][73+c0] + S[73+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 25; c0 += 1)
    S[c0][c0+74] = MAX(S[c0][c0+74], S[c0+1][c0+74-1] + can_pair(RNA, c0, c0+74));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 24; c0 += 1)
    for (c1 = c0 + 75; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-75+c0] + S[-c0+c1-75+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][74+c0] + S[74+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 24; c0 += 1)
    S[c0][c0+75] = MAX(S[c0][c0+75], S[c0+1][c0+75-1] + can_pair(RNA, c0, c0+75));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 23; c0 += 1)
    for (c1 = c0 + 76; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-76+c0] + S[-c0+c1-76+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][75+c0] + S[75+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 23; c0 += 1)
    S[c0][c0+76] = MAX(S[c0][c0+76], S[c0+1][c0+76-1] + can_pair(RNA, c0, c0+76));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 22; c0 += 1)
    for (c1 = c0 + 77; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-77+c0] + S[-c0+c1-77+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][76+c0] + S[76+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 22; c0 += 1)
    S[c0][c0+77] = MAX(S[c0][c0+77], S[c0+1][c0+77-1] + can_pair(RNA, c0, c0+77));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 21; c0 += 1)
    for (c1 = c0 + 78; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-78+c0] + S[-c0+c1-78+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][77+c0] + S[77+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 21; c0 += 1)
    S[c0][c0+78] = MAX(S[c0][c0+78], S[c0+1][c0+78-1] + can_pair(RNA, c0, c0+78));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 20; c0 += 1)
    for (c1 = c0 + 79; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-79+c0] + S[-c0+c1-79+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][78+c0] + S[78+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 20; c0 += 1)
    S[c0][c0+79] = MAX(S[c0][c0+79], S[c0+1][c0+79-1] + can_pair(RNA, c0, c0+79));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 19; c0 += 1)
    for (c1 = c0 + 80; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-80+c0] + S[-c0+c1-80+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][79+c0] + S[79+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 19; c0 += 1)
    S[c0][c0+80] = MAX(S[c0][c0+80], S[c0+1][c0+80-1] + can_pair(RNA, c0, c0+80));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 18; c0 += 1)
    for (c1 = c0 + 81; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-81+c0] + S[-c0+c1-81+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][80+c0] + S[80+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 18; c0 += 1)
    S[c0][c0+81] = MAX(S[c0][c0+81], S[c0+1][c0+81-1] + can_pair(RNA, c0, c0+81));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 17; c0 += 1)
    for (c1 = c0 + 82; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-82+c0] + S[-c0+c1-82+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][81+c0] + S[81+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 17; c0 += 1)
    S[c0][c0+82] = MAX(S[c0][c0+82], S[c0+1][c0+82-1] + can_pair(RNA, c0, c0+82));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 16; c0 += 1)
    for (c1 = c0 + 83; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-83+c0] + S[-c0+c1-83+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][82+c0] + S[82+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 16; c0 += 1)
    S[c0][c0+83] = MAX(S[c0][c0+83], S[c0+1][c0+83-1] + can_pair(RNA, c0, c0+83));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 15; c0 += 1)
    for (c1 = c0 + 84; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-84+c0] + S[-c0+c1-84+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][83+c0] + S[83+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 15; c0 += 1)
    S[c0][c0+84] = MAX(S[c0][c0+84], S[c0+1][c0+84-1] + can_pair(RNA, c0, c0+84));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 14; c0 += 1)
    for (c1 = c0 + 85; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-85+c0] + S[-c0+c1-85+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][84+c0] + S[84+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 14; c0 += 1)
    S[c0][c0+85] = MAX(S[c0][c0+85], S[c0+1][c0+85-1] + can_pair(RNA, c0, c0+85));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 13; c0 += 1)
    for (c1 = c0 + 86; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-86+c0] + S[-c0+c1-86+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][85+c0] + S[85+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 13; c0 += 1)
    S[c0][c0+86] = MAX(S[c0][c0+86], S[c0+1][c0+86-1] + can_pair(RNA, c0, c0+86));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 12; c0 += 1)
    for (c1 = c0 + 87; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-87+c0] + S[-c0+c1-87+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][86+c0] + S[86+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 12; c0 += 1)
    S[c0][c0+87] = MAX(S[c0][c0+87], S[c0+1][c0+87-1] + can_pair(RNA, c0, c0+87));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 11; c0 += 1)
    for (c1 = c0 + 88; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-88+c0] + S[-c0+c1-88+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][87+c0] + S[87+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 11; c0 += 1)
    S[c0][c0+88] = MAX(S[c0][c0+88], S[c0+1][c0+88-1] + can_pair(RNA, c0, c0+88));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 10; c0 += 1)
    for (c1 = c0 + 89; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-89+c0] + S[-c0+c1-89+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][88+c0] + S[88+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 10; c0 += 1)
    S[c0][c0+89] = MAX(S[c0][c0+89], S[c0+1][c0+89-1] + can_pair(RNA, c0, c0+89));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 9; c0 += 1)
    for (c1 = c0 + 90; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-90+c0] + S[-c0+c1-90+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][89+c0] + S[89+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 9; c0 += 1)
    S[c0][c0+90] = MAX(S[c0][c0+90], S[c0+1][c0+90-1] + can_pair(RNA, c0, c0+90));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 8; c0 += 1)
    for (c1 = c0 + 91; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-91+c0] + S[-c0+c1-91+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][90+c0] + S[90+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 8; c0 += 1)
    S[c0][c0+91] = MAX(S[c0][c0+91], S[c0+1][c0+91-1] + can_pair(RNA, c0, c0+91));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 7; c0 += 1)
    for (c1 = c0 + 92; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-92+c0] + S[-c0+c1-92+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][91+c0] + S[91+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 7; c0 += 1)
    S[c0][c0+92] = MAX(S[c0][c0+92], S[c0+1][c0+92-1] + can_pair(RNA, c0, c0+92));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 6; c0 += 1)
    for (c1 = c0 + 93; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-93+c0] + S[-c0+c1-93+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][92+c0] + S[92+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 6; c0 += 1)
    S[c0][c0+93] = MAX(S[c0][c0+93], S[c0+1][c0+93-1] + can_pair(RNA, c0, c0+93));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 5; c0 += 1)
    for (c1 = c0 + 94; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-94+c0] + S[-c0+c1-94+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][93+c0] + S[93+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 5; c0 += 1)
    S[c0][c0+94] = MAX(S[c0][c0+94], S[c0+1][c0+94-1] + can_pair(RNA, c0, c0+94));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 4; c0 += 1)
    for (c1 = c0 + 95; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-95+c0] + S[-c0+c1-95+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][94+c0] + S[94+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 4; c0 += 1)
    S[c0][c0+95] = MAX(S[c0][c0+95], S[c0+1][c0+95-1] + can_pair(RNA, c0, c0+95));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 3; c0 += 1)
    for (c1 = c0 + 96; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-96+c0] + S[-c0+c1-96+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][95+c0] + S[95+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 3; c0 += 1)
    S[c0][c0+96] = MAX(S[c0][c0+96], S[c0+1][c0+96-1] + can_pair(RNA, c0, c0+96));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 2; c0 += 1)
    for (c1 = c0 + 97; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-97+c0] + S[-c0+c1-97+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][96+c0] + S[96+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 2; c0 += 1)
    S[c0][c0+97] = MAX(S[c0][c0+97], S[c0+1][c0+97-1] + can_pair(RNA, c0, c0+97));
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 1; c0 += 1)
    for (c1 = c0 + 98; c1 <= 99; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-98+c0] + S[-c0+c1-98+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][97+c0] + S[97+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp for
  for (c0 = 0; c0 <= 1; c0 += 1)
    if (c0 == 1) {
      S[1][99] = MAX(S[1][99], S[1+1][99-1] + can_pair(RNA, 1, 99));
    } else
      S[0][98] = MAX(S[0][98], S[0+1][98-1] + can_pair(RNA, 0, 98));
// --------------
if (N == 100) {
  S[0][99] = MAX(S[0][0+0] + S[0+0+1][99], S[0][99]);
  S[0][99] = MAX(S[0][98+0] + S[98+0+1][99], S[0][99]);
}
// --------------
  S[0][99] = MAX(S[0][99], S[0+1][99-1] + can_pair(RNA, 0, 99));
// --------------

}

    end = omp_get_wtime();
	printf("%.6f\n", end - start);

    return 0;


}

