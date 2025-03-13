#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define MAX(x,y)    ((x) > (y)? (x) : (y))
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int N = 1000;

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

    omp_set_num_threads(num_proc);

    start = omp_get_wtime();

#pragma omp parallel shared(S,RNA)
{
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 998; c0 += 1)
    S[c0][c0+1] = MAX(S[c0][c0+1], S[c0+1][c0+1-1] + can_pair(RNA, c0, c0+1));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 997; c0 += 1)
    for (c1 = c0 + 2; c1 <= min(c0 + 3, 999); c1 += 1) {
      if (c1 == c0 + 2)
        S[c0][c0+2] = MAX(S[c0][0+c0] + S[0+c0+1][c0+2], S[c0][c0+2]);
      S[c0][c1] = MAX(S[c0][1+c0] + S[1+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 997; c0 += 1)
    S[c0][c0+2] = MAX(S[c0][c0+2], S[c0+1][c0+2-1] + can_pair(RNA, c0, c0+2));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 996; c0 += 1)
    for (c1 = c0 + 3; c1 <= min(c0 + 5, 999); c1 += 1) {
      if (c0 + 4 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-3+c0] + S[-c0+c1-3+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][2+c0] + S[2+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 996; c0 += 1)
    S[c0][c0+3] = MAX(S[c0][c0+3], S[c0+1][c0+3-1] + can_pair(RNA, c0, c0+3));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 995; c0 += 1)
    for (c1 = c0 + 4; c1 <= min(c0 + 7, 999); c1 += 1) {
      if (c0 + 6 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-4+c0] + S[-c0+c1-4+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][3+c0] + S[3+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 995; c0 += 1)
    S[c0][c0+4] = MAX(S[c0][c0+4], S[c0+1][c0+4-1] + can_pair(RNA, c0, c0+4));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 994; c0 += 1)
    for (c1 = c0 + 5; c1 <= min(c0 + 9, 999); c1 += 1) {
      if (c0 + 8 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-5+c0] + S[-c0+c1-5+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][4+c0] + S[4+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 994; c0 += 1)
    S[c0][c0+5] = MAX(S[c0][c0+5], S[c0+1][c0+5-1] + can_pair(RNA, c0, c0+5));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 993; c0 += 1)
    for (c1 = c0 + 6; c1 <= min(c0 + 11, 999); c1 += 1) {
      if (c0 + 10 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-6+c0] + S[-c0+c1-6+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][5+c0] + S[5+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 993; c0 += 1)
    S[c0][c0+6] = MAX(S[c0][c0+6], S[c0+1][c0+6-1] + can_pair(RNA, c0, c0+6));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 992; c0 += 1)
    for (c1 = c0 + 7; c1 <= min(c0 + 13, 999); c1 += 1) {
      if (c0 + 12 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-7+c0] + S[-c0+c1-7+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][6+c0] + S[6+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 992; c0 += 1)
    S[c0][c0+7] = MAX(S[c0][c0+7], S[c0+1][c0+7-1] + can_pair(RNA, c0, c0+7));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 991; c0 += 1)
    for (c1 = c0 + 8; c1 <= min(c0 + 15, 999); c1 += 1) {
      if (c0 + 14 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-8+c0] + S[-c0+c1-8+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][7+c0] + S[7+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 991; c0 += 1)
    S[c0][c0+8] = MAX(S[c0][c0+8], S[c0+1][c0+8-1] + can_pair(RNA, c0, c0+8));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 990; c0 += 1)
    for (c1 = c0 + 9; c1 <= min(c0 + 17, 999); c1 += 1) {
      if (c0 + 16 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-9+c0] + S[-c0+c1-9+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][8+c0] + S[8+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 990; c0 += 1)
    S[c0][c0+9] = MAX(S[c0][c0+9], S[c0+1][c0+9-1] + can_pair(RNA, c0, c0+9));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 989; c0 += 1)
    for (c1 = c0 + 10; c1 <= min(c0 + 19, 999); c1 += 1) {
      if (c0 + 18 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-10+c0] + S[-c0+c1-10+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][9+c0] + S[9+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 989; c0 += 1)
    S[c0][c0+10] = MAX(S[c0][c0+10], S[c0+1][c0+10-1] + can_pair(RNA, c0, c0+10));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 988; c0 += 1)
    for (c1 = c0 + 11; c1 <= min(c0 + 21, 999); c1 += 1) {
      if (c0 + 20 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-11+c0] + S[-c0+c1-11+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][10+c0] + S[10+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 988; c0 += 1)
    S[c0][c0+11] = MAX(S[c0][c0+11], S[c0+1][c0+11-1] + can_pair(RNA, c0, c0+11));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 987; c0 += 1)
    for (c1 = c0 + 12; c1 <= min(c0 + 23, 999); c1 += 1) {
      if (c0 + 22 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-12+c0] + S[-c0+c1-12+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][11+c0] + S[11+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 987; c0 += 1)
    S[c0][c0+12] = MAX(S[c0][c0+12], S[c0+1][c0+12-1] + can_pair(RNA, c0, c0+12));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 986; c0 += 1)
    for (c1 = c0 + 13; c1 <= min(c0 + 25, 999); c1 += 1) {
      if (c0 + 24 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-13+c0] + S[-c0+c1-13+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][12+c0] + S[12+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 986; c0 += 1)
    S[c0][c0+13] = MAX(S[c0][c0+13], S[c0+1][c0+13-1] + can_pair(RNA, c0, c0+13));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 985; c0 += 1)
    for (c1 = c0 + 14; c1 <= min(c0 + 27, 999); c1 += 1) {
      if (c0 + 26 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-14+c0] + S[-c0+c1-14+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][13+c0] + S[13+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 985; c0 += 1)
    S[c0][c0+14] = MAX(S[c0][c0+14], S[c0+1][c0+14-1] + can_pair(RNA, c0, c0+14));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 984; c0 += 1)
    for (c1 = c0 + 15; c1 <= min(c0 + 29, 999); c1 += 1) {
      if (c0 + 28 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-15+c0] + S[-c0+c1-15+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][14+c0] + S[14+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 984; c0 += 1)
    S[c0][c0+15] = MAX(S[c0][c0+15], S[c0+1][c0+15-1] + can_pair(RNA, c0, c0+15));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 983; c0 += 1)
    for (c1 = c0 + 16; c1 <= min(c0 + 31, 999); c1 += 1) {
      if (c0 + 30 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-16+c0] + S[-c0+c1-16+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][15+c0] + S[15+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 983; c0 += 1)
    S[c0][c0+16] = MAX(S[c0][c0+16], S[c0+1][c0+16-1] + can_pair(RNA, c0, c0+16));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 982; c0 += 1)
    for (c1 = c0 + 17; c1 <= min(c0 + 33, 999); c1 += 1) {
      if (c0 + 32 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-17+c0] + S[-c0+c1-17+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][16+c0] + S[16+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 982; c0 += 1)
    S[c0][c0+17] = MAX(S[c0][c0+17], S[c0+1][c0+17-1] + can_pair(RNA, c0, c0+17));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 981; c0 += 1)
    for (c1 = c0 + 18; c1 <= min(c0 + 35, 999); c1 += 1) {
      if (c0 + 34 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-18+c0] + S[-c0+c1-18+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][17+c0] + S[17+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 981; c0 += 1)
    S[c0][c0+18] = MAX(S[c0][c0+18], S[c0+1][c0+18-1] + can_pair(RNA, c0, c0+18));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 980; c0 += 1)
    for (c1 = c0 + 19; c1 <= min(c0 + 37, 999); c1 += 1) {
      if (c0 + 36 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-19+c0] + S[-c0+c1-19+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][18+c0] + S[18+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 980; c0 += 1)
    S[c0][c0+19] = MAX(S[c0][c0+19], S[c0+1][c0+19-1] + can_pair(RNA, c0, c0+19));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 979; c0 += 1)
    for (c1 = c0 + 20; c1 <= min(c0 + 39, 999); c1 += 1) {
      if (c0 + 38 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-20+c0] + S[-c0+c1-20+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][19+c0] + S[19+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 979; c0 += 1)
    S[c0][c0+20] = MAX(S[c0][c0+20], S[c0+1][c0+20-1] + can_pair(RNA, c0, c0+20));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 978; c0 += 1)
    for (c1 = c0 + 21; c1 <= min(c0 + 41, 999); c1 += 1) {
      if (c0 + 40 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-21+c0] + S[-c0+c1-21+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][20+c0] + S[20+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 978; c0 += 1)
    S[c0][c0+21] = MAX(S[c0][c0+21], S[c0+1][c0+21-1] + can_pair(RNA, c0, c0+21));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 977; c0 += 1)
    for (c1 = c0 + 22; c1 <= min(c0 + 43, 999); c1 += 1) {
      if (c0 + 42 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-22+c0] + S[-c0+c1-22+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][21+c0] + S[21+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 977; c0 += 1)
    S[c0][c0+22] = MAX(S[c0][c0+22], S[c0+1][c0+22-1] + can_pair(RNA, c0, c0+22));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 976; c0 += 1)
    for (c1 = c0 + 23; c1 <= min(c0 + 45, 999); c1 += 1) {
      if (c0 + 44 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-23+c0] + S[-c0+c1-23+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][22+c0] + S[22+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 976; c0 += 1)
    S[c0][c0+23] = MAX(S[c0][c0+23], S[c0+1][c0+23-1] + can_pair(RNA, c0, c0+23));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 975; c0 += 1)
    for (c1 = c0 + 24; c1 <= min(c0 + 47, 999); c1 += 1) {
      if (c0 + 46 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-24+c0] + S[-c0+c1-24+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][23+c0] + S[23+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 975; c0 += 1)
    S[c0][c0+24] = MAX(S[c0][c0+24], S[c0+1][c0+24-1] + can_pair(RNA, c0, c0+24));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 974; c0 += 1)
    for (c1 = c0 + 25; c1 <= min(c0 + 49, 999); c1 += 1) {
      if (c0 + 48 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-25+c0] + S[-c0+c1-25+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][24+c0] + S[24+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 974; c0 += 1)
    S[c0][c0+25] = MAX(S[c0][c0+25], S[c0+1][c0+25-1] + can_pair(RNA, c0, c0+25));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 973; c0 += 1)
    for (c1 = c0 + 26; c1 <= min(c0 + 51, 999); c1 += 1) {
      if (c0 + 50 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-26+c0] + S[-c0+c1-26+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][25+c0] + S[25+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 973; c0 += 1)
    S[c0][c0+26] = MAX(S[c0][c0+26], S[c0+1][c0+26-1] + can_pair(RNA, c0, c0+26));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 972; c0 += 1)
    for (c1 = c0 + 27; c1 <= min(c0 + 53, 999); c1 += 1) {
      if (c0 + 52 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-27+c0] + S[-c0+c1-27+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][26+c0] + S[26+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 972; c0 += 1)
    S[c0][c0+27] = MAX(S[c0][c0+27], S[c0+1][c0+27-1] + can_pair(RNA, c0, c0+27));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 971; c0 += 1)
    for (c1 = c0 + 28; c1 <= min(c0 + 55, 999); c1 += 1) {
      if (c0 + 54 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-28+c0] + S[-c0+c1-28+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][27+c0] + S[27+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 971; c0 += 1)
    S[c0][c0+28] = MAX(S[c0][c0+28], S[c0+1][c0+28-1] + can_pair(RNA, c0, c0+28));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 970; c0 += 1)
    for (c1 = c0 + 29; c1 <= min(c0 + 57, 999); c1 += 1) {
      if (c0 + 56 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-29+c0] + S[-c0+c1-29+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][28+c0] + S[28+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 970; c0 += 1)
    S[c0][c0+29] = MAX(S[c0][c0+29], S[c0+1][c0+29-1] + can_pair(RNA, c0, c0+29));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 969; c0 += 1)
    for (c1 = c0 + 30; c1 <= min(c0 + 59, 999); c1 += 1) {
      if (c0 + 58 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-30+c0] + S[-c0+c1-30+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][29+c0] + S[29+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 969; c0 += 1)
    S[c0][c0+30] = MAX(S[c0][c0+30], S[c0+1][c0+30-1] + can_pair(RNA, c0, c0+30));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 968; c0 += 1)
    for (c1 = c0 + 31; c1 <= min(c0 + 61, 999); c1 += 1) {
      if (c0 + 60 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-31+c0] + S[-c0+c1-31+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][30+c0] + S[30+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 968; c0 += 1)
    S[c0][c0+31] = MAX(S[c0][c0+31], S[c0+1][c0+31-1] + can_pair(RNA, c0, c0+31));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 967; c0 += 1)
    for (c1 = c0 + 32; c1 <= min(c0 + 63, 999); c1 += 1) {
      if (c0 + 62 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-32+c0] + S[-c0+c1-32+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][31+c0] + S[31+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 967; c0 += 1)
    S[c0][c0+32] = MAX(S[c0][c0+32], S[c0+1][c0+32-1] + can_pair(RNA, c0, c0+32));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 966; c0 += 1)
    for (c1 = c0 + 33; c1 <= min(c0 + 65, 999); c1 += 1) {
      if (c0 + 64 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-33+c0] + S[-c0+c1-33+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][32+c0] + S[32+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 966; c0 += 1)
    S[c0][c0+33] = MAX(S[c0][c0+33], S[c0+1][c0+33-1] + can_pair(RNA, c0, c0+33));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 965; c0 += 1)
    for (c1 = c0 + 34; c1 <= min(c0 + 67, 999); c1 += 1) {
      if (c0 + 66 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-34+c0] + S[-c0+c1-34+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][33+c0] + S[33+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 965; c0 += 1)
    S[c0][c0+34] = MAX(S[c0][c0+34], S[c0+1][c0+34-1] + can_pair(RNA, c0, c0+34));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 964; c0 += 1)
    for (c1 = c0 + 35; c1 <= min(c0 + 69, 999); c1 += 1) {
      if (c0 + 68 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-35+c0] + S[-c0+c1-35+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][34+c0] + S[34+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 964; c0 += 1)
    S[c0][c0+35] = MAX(S[c0][c0+35], S[c0+1][c0+35-1] + can_pair(RNA, c0, c0+35));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 963; c0 += 1)
    for (c1 = c0 + 36; c1 <= min(c0 + 71, 999); c1 += 1) {
      if (c0 + 70 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-36+c0] + S[-c0+c1-36+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][35+c0] + S[35+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 963; c0 += 1)
    S[c0][c0+36] = MAX(S[c0][c0+36], S[c0+1][c0+36-1] + can_pair(RNA, c0, c0+36));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 962; c0 += 1)
    for (c1 = c0 + 37; c1 <= min(c0 + 73, 999); c1 += 1) {
      if (c0 + 72 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-37+c0] + S[-c0+c1-37+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][36+c0] + S[36+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 962; c0 += 1)
    S[c0][c0+37] = MAX(S[c0][c0+37], S[c0+1][c0+37-1] + can_pair(RNA, c0, c0+37));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 961; c0 += 1)
    for (c1 = c0 + 38; c1 <= min(c0 + 75, 999); c1 += 1) {
      if (c0 + 74 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-38+c0] + S[-c0+c1-38+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][37+c0] + S[37+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 961; c0 += 1)
    S[c0][c0+38] = MAX(S[c0][c0+38], S[c0+1][c0+38-1] + can_pair(RNA, c0, c0+38));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 960; c0 += 1)
    for (c1 = c0 + 39; c1 <= min(c0 + 77, 999); c1 += 1) {
      if (c0 + 76 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-39+c0] + S[-c0+c1-39+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][38+c0] + S[38+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 960; c0 += 1)
    S[c0][c0+39] = MAX(S[c0][c0+39], S[c0+1][c0+39-1] + can_pair(RNA, c0, c0+39));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 959; c0 += 1)
    for (c1 = c0 + 40; c1 <= min(c0 + 79, 999); c1 += 1) {
      if (c0 + 78 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-40+c0] + S[-c0+c1-40+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][39+c0] + S[39+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 959; c0 += 1)
    S[c0][c0+40] = MAX(S[c0][c0+40], S[c0+1][c0+40-1] + can_pair(RNA, c0, c0+40));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 958; c0 += 1)
    for (c1 = c0 + 41; c1 <= min(c0 + 81, 999); c1 += 1) {
      if (c0 + 80 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-41+c0] + S[-c0+c1-41+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][40+c0] + S[40+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 958; c0 += 1)
    S[c0][c0+41] = MAX(S[c0][c0+41], S[c0+1][c0+41-1] + can_pair(RNA, c0, c0+41));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 957; c0 += 1)
    for (c1 = c0 + 42; c1 <= min(c0 + 83, 999); c1 += 1) {
      if (c0 + 82 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-42+c0] + S[-c0+c1-42+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][41+c0] + S[41+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 957; c0 += 1)
    S[c0][c0+42] = MAX(S[c0][c0+42], S[c0+1][c0+42-1] + can_pair(RNA, c0, c0+42));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 956; c0 += 1)
    for (c1 = c0 + 43; c1 <= min(c0 + 85, 999); c1 += 1) {
      if (c0 + 84 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-43+c0] + S[-c0+c1-43+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][42+c0] + S[42+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 956; c0 += 1)
    S[c0][c0+43] = MAX(S[c0][c0+43], S[c0+1][c0+43-1] + can_pair(RNA, c0, c0+43));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 955; c0 += 1)
    for (c1 = c0 + 44; c1 <= min(c0 + 87, 999); c1 += 1) {
      if (c0 + 86 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-44+c0] + S[-c0+c1-44+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][43+c0] + S[43+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 955; c0 += 1)
    S[c0][c0+44] = MAX(S[c0][c0+44], S[c0+1][c0+44-1] + can_pair(RNA, c0, c0+44));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 954; c0 += 1)
    for (c1 = c0 + 45; c1 <= min(c0 + 89, 999); c1 += 1) {
      if (c0 + 88 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-45+c0] + S[-c0+c1-45+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][44+c0] + S[44+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 954; c0 += 1)
    S[c0][c0+45] = MAX(S[c0][c0+45], S[c0+1][c0+45-1] + can_pair(RNA, c0, c0+45));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 953; c0 += 1)
    for (c1 = c0 + 46; c1 <= min(c0 + 91, 999); c1 += 1) {
      if (c0 + 90 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-46+c0] + S[-c0+c1-46+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][45+c0] + S[45+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 953; c0 += 1)
    S[c0][c0+46] = MAX(S[c0][c0+46], S[c0+1][c0+46-1] + can_pair(RNA, c0, c0+46));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 952; c0 += 1)
    for (c1 = c0 + 47; c1 <= min(c0 + 93, 999); c1 += 1) {
      if (c0 + 92 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-47+c0] + S[-c0+c1-47+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][46+c0] + S[46+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 952; c0 += 1)
    S[c0][c0+47] = MAX(S[c0][c0+47], S[c0+1][c0+47-1] + can_pair(RNA, c0, c0+47));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 951; c0 += 1)
    for (c1 = c0 + 48; c1 <= min(c0 + 95, 999); c1 += 1) {
      if (c0 + 94 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-48+c0] + S[-c0+c1-48+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][47+c0] + S[47+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 951; c0 += 1)
    S[c0][c0+48] = MAX(S[c0][c0+48], S[c0+1][c0+48-1] + can_pair(RNA, c0, c0+48));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 950; c0 += 1)
    for (c1 = c0 + 49; c1 <= min(c0 + 97, 999); c1 += 1) {
      if (c0 + 96 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-49+c0] + S[-c0+c1-49+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][48+c0] + S[48+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 950; c0 += 1)
    S[c0][c0+49] = MAX(S[c0][c0+49], S[c0+1][c0+49-1] + can_pair(RNA, c0, c0+49));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 949; c0 += 1)
    for (c1 = c0 + 50; c1 <= min(c0 + 99, 999); c1 += 1) {
      if (c0 + 98 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-50+c0] + S[-c0+c1-50+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][49+c0] + S[49+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 949; c0 += 1)
    S[c0][c0+50] = MAX(S[c0][c0+50], S[c0+1][c0+50-1] + can_pair(RNA, c0, c0+50));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 948; c0 += 1)
    for (c1 = c0 + 51; c1 <= min(c0 + 101, 999); c1 += 1) {
      if (c0 + 100 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-51+c0] + S[-c0+c1-51+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][50+c0] + S[50+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 948; c0 += 1)
    S[c0][c0+51] = MAX(S[c0][c0+51], S[c0+1][c0+51-1] + can_pair(RNA, c0, c0+51));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 947; c0 += 1)
    for (c1 = c0 + 52; c1 <= min(c0 + 103, 999); c1 += 1) {
      if (c0 + 102 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-52+c0] + S[-c0+c1-52+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][51+c0] + S[51+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 947; c0 += 1)
    S[c0][c0+52] = MAX(S[c0][c0+52], S[c0+1][c0+52-1] + can_pair(RNA, c0, c0+52));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 946; c0 += 1)
    for (c1 = c0 + 53; c1 <= min(c0 + 105, 999); c1 += 1) {
      if (c0 + 104 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-53+c0] + S[-c0+c1-53+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][52+c0] + S[52+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 946; c0 += 1)
    S[c0][c0+53] = MAX(S[c0][c0+53], S[c0+1][c0+53-1] + can_pair(RNA, c0, c0+53));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 945; c0 += 1)
    for (c1 = c0 + 54; c1 <= min(c0 + 107, 999); c1 += 1) {
      if (c0 + 106 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-54+c0] + S[-c0+c1-54+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][53+c0] + S[53+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 945; c0 += 1)
    S[c0][c0+54] = MAX(S[c0][c0+54], S[c0+1][c0+54-1] + can_pair(RNA, c0, c0+54));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 944; c0 += 1)
    for (c1 = c0 + 55; c1 <= min(c0 + 109, 999); c1 += 1) {
      if (c0 + 108 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-55+c0] + S[-c0+c1-55+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][54+c0] + S[54+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 944; c0 += 1)
    S[c0][c0+55] = MAX(S[c0][c0+55], S[c0+1][c0+55-1] + can_pair(RNA, c0, c0+55));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 943; c0 += 1)
    for (c1 = c0 + 56; c1 <= min(c0 + 111, 999); c1 += 1) {
      if (c0 + 110 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-56+c0] + S[-c0+c1-56+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][55+c0] + S[55+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 943; c0 += 1)
    S[c0][c0+56] = MAX(S[c0][c0+56], S[c0+1][c0+56-1] + can_pair(RNA, c0, c0+56));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 942; c0 += 1)
    for (c1 = c0 + 57; c1 <= min(c0 + 113, 999); c1 += 1) {
      if (c0 + 112 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-57+c0] + S[-c0+c1-57+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][56+c0] + S[56+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 942; c0 += 1)
    S[c0][c0+57] = MAX(S[c0][c0+57], S[c0+1][c0+57-1] + can_pair(RNA, c0, c0+57));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 941; c0 += 1)
    for (c1 = c0 + 58; c1 <= min(c0 + 115, 999); c1 += 1) {
      if (c0 + 114 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-58+c0] + S[-c0+c1-58+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][57+c0] + S[57+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 941; c0 += 1)
    S[c0][c0+58] = MAX(S[c0][c0+58], S[c0+1][c0+58-1] + can_pair(RNA, c0, c0+58));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 940; c0 += 1)
    for (c1 = c0 + 59; c1 <= min(c0 + 117, 999); c1 += 1) {
      if (c0 + 116 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-59+c0] + S[-c0+c1-59+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][58+c0] + S[58+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 940; c0 += 1)
    S[c0][c0+59] = MAX(S[c0][c0+59], S[c0+1][c0+59-1] + can_pair(RNA, c0, c0+59));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 939; c0 += 1)
    for (c1 = c0 + 60; c1 <= min(c0 + 119, 999); c1 += 1) {
      if (c0 + 118 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-60+c0] + S[-c0+c1-60+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][59+c0] + S[59+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 939; c0 += 1)
    S[c0][c0+60] = MAX(S[c0][c0+60], S[c0+1][c0+60-1] + can_pair(RNA, c0, c0+60));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 938; c0 += 1)
    for (c1 = c0 + 61; c1 <= min(c0 + 121, 999); c1 += 1) {
      if (c0 + 120 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-61+c0] + S[-c0+c1-61+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][60+c0] + S[60+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 938; c0 += 1)
    S[c0][c0+61] = MAX(S[c0][c0+61], S[c0+1][c0+61-1] + can_pair(RNA, c0, c0+61));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 937; c0 += 1)
    for (c1 = c0 + 62; c1 <= min(c0 + 123, 999); c1 += 1) {
      if (c0 + 122 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-62+c0] + S[-c0+c1-62+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][61+c0] + S[61+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 937; c0 += 1)
    S[c0][c0+62] = MAX(S[c0][c0+62], S[c0+1][c0+62-1] + can_pair(RNA, c0, c0+62));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 936; c0 += 1)
    for (c1 = c0 + 63; c1 <= min(c0 + 125, 999); c1 += 1) {
      if (c0 + 124 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-63+c0] + S[-c0+c1-63+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][62+c0] + S[62+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 936; c0 += 1)
    S[c0][c0+63] = MAX(S[c0][c0+63], S[c0+1][c0+63-1] + can_pair(RNA, c0, c0+63));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 935; c0 += 1)
    for (c1 = c0 + 64; c1 <= min(c0 + 127, 999); c1 += 1) {
      if (c0 + 126 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-64+c0] + S[-c0+c1-64+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][63+c0] + S[63+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 935; c0 += 1)
    S[c0][c0+64] = MAX(S[c0][c0+64], S[c0+1][c0+64-1] + can_pair(RNA, c0, c0+64));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 934; c0 += 1)
    for (c1 = c0 + 65; c1 <= min(c0 + 129, 999); c1 += 1) {
      if (c0 + 128 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-65+c0] + S[-c0+c1-65+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][64+c0] + S[64+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 934; c0 += 1)
    S[c0][c0+65] = MAX(S[c0][c0+65], S[c0+1][c0+65-1] + can_pair(RNA, c0, c0+65));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 933; c0 += 1)
    for (c1 = c0 + 66; c1 <= min(c0 + 131, 999); c1 += 1) {
      if (c0 + 130 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-66+c0] + S[-c0+c1-66+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][65+c0] + S[65+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 933; c0 += 1)
    S[c0][c0+66] = MAX(S[c0][c0+66], S[c0+1][c0+66-1] + can_pair(RNA, c0, c0+66));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 932; c0 += 1)
    for (c1 = c0 + 67; c1 <= min(c0 + 133, 999); c1 += 1) {
      if (c0 + 132 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-67+c0] + S[-c0+c1-67+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][66+c0] + S[66+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 932; c0 += 1)
    S[c0][c0+67] = MAX(S[c0][c0+67], S[c0+1][c0+67-1] + can_pair(RNA, c0, c0+67));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 931; c0 += 1)
    for (c1 = c0 + 68; c1 <= min(c0 + 135, 999); c1 += 1) {
      if (c0 + 134 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-68+c0] + S[-c0+c1-68+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][67+c0] + S[67+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 931; c0 += 1)
    S[c0][c0+68] = MAX(S[c0][c0+68], S[c0+1][c0+68-1] + can_pair(RNA, c0, c0+68));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 930; c0 += 1)
    for (c1 = c0 + 69; c1 <= min(c0 + 137, 999); c1 += 1) {
      if (c0 + 136 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-69+c0] + S[-c0+c1-69+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][68+c0] + S[68+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 930; c0 += 1)
    S[c0][c0+69] = MAX(S[c0][c0+69], S[c0+1][c0+69-1] + can_pair(RNA, c0, c0+69));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 929; c0 += 1)
    for (c1 = c0 + 70; c1 <= min(c0 + 139, 999); c1 += 1) {
      if (c0 + 138 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-70+c0] + S[-c0+c1-70+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][69+c0] + S[69+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 929; c0 += 1)
    S[c0][c0+70] = MAX(S[c0][c0+70], S[c0+1][c0+70-1] + can_pair(RNA, c0, c0+70));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 928; c0 += 1)
    for (c1 = c0 + 71; c1 <= min(c0 + 141, 999); c1 += 1) {
      if (c0 + 140 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-71+c0] + S[-c0+c1-71+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][70+c0] + S[70+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 928; c0 += 1)
    S[c0][c0+71] = MAX(S[c0][c0+71], S[c0+1][c0+71-1] + can_pair(RNA, c0, c0+71));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 927; c0 += 1)
    for (c1 = c0 + 72; c1 <= min(c0 + 143, 999); c1 += 1) {
      if (c0 + 142 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-72+c0] + S[-c0+c1-72+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][71+c0] + S[71+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 927; c0 += 1)
    S[c0][c0+72] = MAX(S[c0][c0+72], S[c0+1][c0+72-1] + can_pair(RNA, c0, c0+72));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 926; c0 += 1)
    for (c1 = c0 + 73; c1 <= min(c0 + 145, 999); c1 += 1) {
      if (c0 + 144 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-73+c0] + S[-c0+c1-73+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][72+c0] + S[72+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 926; c0 += 1)
    S[c0][c0+73] = MAX(S[c0][c0+73], S[c0+1][c0+73-1] + can_pair(RNA, c0, c0+73));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 925; c0 += 1)
    for (c1 = c0 + 74; c1 <= min(c0 + 147, 999); c1 += 1) {
      if (c0 + 146 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-74+c0] + S[-c0+c1-74+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][73+c0] + S[73+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 925; c0 += 1)
    S[c0][c0+74] = MAX(S[c0][c0+74], S[c0+1][c0+74-1] + can_pair(RNA, c0, c0+74));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 924; c0 += 1)
    for (c1 = c0 + 75; c1 <= min(c0 + 149, 999); c1 += 1) {
      if (c0 + 148 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-75+c0] + S[-c0+c1-75+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][74+c0] + S[74+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 924; c0 += 1)
    S[c0][c0+75] = MAX(S[c0][c0+75], S[c0+1][c0+75-1] + can_pair(RNA, c0, c0+75));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 923; c0 += 1)
    for (c1 = c0 + 76; c1 <= min(c0 + 151, 999); c1 += 1) {
      if (c0 + 150 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-76+c0] + S[-c0+c1-76+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][75+c0] + S[75+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 923; c0 += 1)
    S[c0][c0+76] = MAX(S[c0][c0+76], S[c0+1][c0+76-1] + can_pair(RNA, c0, c0+76));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 922; c0 += 1)
    for (c1 = c0 + 77; c1 <= min(c0 + 153, 999); c1 += 1) {
      if (c0 + 152 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-77+c0] + S[-c0+c1-77+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][76+c0] + S[76+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 922; c0 += 1)
    S[c0][c0+77] = MAX(S[c0][c0+77], S[c0+1][c0+77-1] + can_pair(RNA, c0, c0+77));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 921; c0 += 1)
    for (c1 = c0 + 78; c1 <= min(c0 + 155, 999); c1 += 1) {
      if (c0 + 154 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-78+c0] + S[-c0+c1-78+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][77+c0] + S[77+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 921; c0 += 1)
    S[c0][c0+78] = MAX(S[c0][c0+78], S[c0+1][c0+78-1] + can_pair(RNA, c0, c0+78));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 920; c0 += 1)
    for (c1 = c0 + 79; c1 <= min(c0 + 157, 999); c1 += 1) {
      if (c0 + 156 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-79+c0] + S[-c0+c1-79+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][78+c0] + S[78+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 920; c0 += 1)
    S[c0][c0+79] = MAX(S[c0][c0+79], S[c0+1][c0+79-1] + can_pair(RNA, c0, c0+79));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 919; c0 += 1)
    for (c1 = c0 + 80; c1 <= min(c0 + 159, 999); c1 += 1) {
      if (c0 + 158 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-80+c0] + S[-c0+c1-80+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][79+c0] + S[79+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 919; c0 += 1)
    S[c0][c0+80] = MAX(S[c0][c0+80], S[c0+1][c0+80-1] + can_pair(RNA, c0, c0+80));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 918; c0 += 1)
    for (c1 = c0 + 81; c1 <= min(c0 + 161, 999); c1 += 1) {
      if (c0 + 160 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-81+c0] + S[-c0+c1-81+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][80+c0] + S[80+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 918; c0 += 1)
    S[c0][c0+81] = MAX(S[c0][c0+81], S[c0+1][c0+81-1] + can_pair(RNA, c0, c0+81));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 917; c0 += 1)
    for (c1 = c0 + 82; c1 <= min(c0 + 163, 999); c1 += 1) {
      if (c0 + 162 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-82+c0] + S[-c0+c1-82+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][81+c0] + S[81+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 917; c0 += 1)
    S[c0][c0+82] = MAX(S[c0][c0+82], S[c0+1][c0+82-1] + can_pair(RNA, c0, c0+82));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 916; c0 += 1)
    for (c1 = c0 + 83; c1 <= min(c0 + 165, 999); c1 += 1) {
      if (c0 + 164 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-83+c0] + S[-c0+c1-83+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][82+c0] + S[82+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 916; c0 += 1)
    S[c0][c0+83] = MAX(S[c0][c0+83], S[c0+1][c0+83-1] + can_pair(RNA, c0, c0+83));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 915; c0 += 1)
    for (c1 = c0 + 84; c1 <= min(c0 + 167, 999); c1 += 1) {
      if (c0 + 166 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-84+c0] + S[-c0+c1-84+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][83+c0] + S[83+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 915; c0 += 1)
    S[c0][c0+84] = MAX(S[c0][c0+84], S[c0+1][c0+84-1] + can_pair(RNA, c0, c0+84));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 914; c0 += 1)
    for (c1 = c0 + 85; c1 <= min(c0 + 169, 999); c1 += 1) {
      if (c0 + 168 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-85+c0] + S[-c0+c1-85+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][84+c0] + S[84+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 914; c0 += 1)
    S[c0][c0+85] = MAX(S[c0][c0+85], S[c0+1][c0+85-1] + can_pair(RNA, c0, c0+85));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 913; c0 += 1)
    for (c1 = c0 + 86; c1 <= min(c0 + 171, 999); c1 += 1) {
      if (c0 + 170 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-86+c0] + S[-c0+c1-86+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][85+c0] + S[85+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 913; c0 += 1)
    S[c0][c0+86] = MAX(S[c0][c0+86], S[c0+1][c0+86-1] + can_pair(RNA, c0, c0+86));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 912; c0 += 1)
    for (c1 = c0 + 87; c1 <= min(c0 + 173, 999); c1 += 1) {
      if (c0 + 172 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-87+c0] + S[-c0+c1-87+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][86+c0] + S[86+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 912; c0 += 1)
    S[c0][c0+87] = MAX(S[c0][c0+87], S[c0+1][c0+87-1] + can_pair(RNA, c0, c0+87));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 911; c0 += 1)
    for (c1 = c0 + 88; c1 <= min(c0 + 175, 999); c1 += 1) {
      if (c0 + 174 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-88+c0] + S[-c0+c1-88+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][87+c0] + S[87+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 911; c0 += 1)
    S[c0][c0+88] = MAX(S[c0][c0+88], S[c0+1][c0+88-1] + can_pair(RNA, c0, c0+88));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 910; c0 += 1)
    for (c1 = c0 + 89; c1 <= min(c0 + 177, 999); c1 += 1) {
      if (c0 + 176 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-89+c0] + S[-c0+c1-89+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][88+c0] + S[88+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 910; c0 += 1)
    S[c0][c0+89] = MAX(S[c0][c0+89], S[c0+1][c0+89-1] + can_pair(RNA, c0, c0+89));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 909; c0 += 1)
    for (c1 = c0 + 90; c1 <= min(c0 + 179, 999); c1 += 1) {
      if (c0 + 178 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-90+c0] + S[-c0+c1-90+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][89+c0] + S[89+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 909; c0 += 1)
    S[c0][c0+90] = MAX(S[c0][c0+90], S[c0+1][c0+90-1] + can_pair(RNA, c0, c0+90));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 908; c0 += 1)
    for (c1 = c0 + 91; c1 <= min(c0 + 181, 999); c1 += 1) {
      if (c0 + 180 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-91+c0] + S[-c0+c1-91+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][90+c0] + S[90+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 908; c0 += 1)
    S[c0][c0+91] = MAX(S[c0][c0+91], S[c0+1][c0+91-1] + can_pair(RNA, c0, c0+91));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 907; c0 += 1)
    for (c1 = c0 + 92; c1 <= min(c0 + 183, 999); c1 += 1) {
      if (c0 + 182 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-92+c0] + S[-c0+c1-92+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][91+c0] + S[91+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 907; c0 += 1)
    S[c0][c0+92] = MAX(S[c0][c0+92], S[c0+1][c0+92-1] + can_pair(RNA, c0, c0+92));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 906; c0 += 1)
    for (c1 = c0 + 93; c1 <= min(c0 + 185, 999); c1 += 1) {
      if (c0 + 184 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-93+c0] + S[-c0+c1-93+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][92+c0] + S[92+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 906; c0 += 1)
    S[c0][c0+93] = MAX(S[c0][c0+93], S[c0+1][c0+93-1] + can_pair(RNA, c0, c0+93));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 905; c0 += 1)
    for (c1 = c0 + 94; c1 <= min(c0 + 187, 999); c1 += 1) {
      if (c0 + 186 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-94+c0] + S[-c0+c1-94+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][93+c0] + S[93+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 905; c0 += 1)
    S[c0][c0+94] = MAX(S[c0][c0+94], S[c0+1][c0+94-1] + can_pair(RNA, c0, c0+94));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 904; c0 += 1)
    for (c1 = c0 + 95; c1 <= min(c0 + 189, 999); c1 += 1) {
      if (c0 + 188 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-95+c0] + S[-c0+c1-95+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][94+c0] + S[94+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 904; c0 += 1)
    S[c0][c0+95] = MAX(S[c0][c0+95], S[c0+1][c0+95-1] + can_pair(RNA, c0, c0+95));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 903; c0 += 1)
    for (c1 = c0 + 96; c1 <= min(c0 + 191, 999); c1 += 1) {
      if (c0 + 190 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-96+c0] + S[-c0+c1-96+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][95+c0] + S[95+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 903; c0 += 1)
    S[c0][c0+96] = MAX(S[c0][c0+96], S[c0+1][c0+96-1] + can_pair(RNA, c0, c0+96));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 902; c0 += 1)
    for (c1 = c0 + 97; c1 <= min(c0 + 193, 999); c1 += 1) {
      if (c0 + 192 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-97+c0] + S[-c0+c1-97+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][96+c0] + S[96+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 902; c0 += 1)
    S[c0][c0+97] = MAX(S[c0][c0+97], S[c0+1][c0+97-1] + can_pair(RNA, c0, c0+97));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 901; c0 += 1)
    for (c1 = c0 + 98; c1 <= min(c0 + 195, 999); c1 += 1) {
      if (c0 + 194 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-98+c0] + S[-c0+c1-98+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][97+c0] + S[97+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 901; c0 += 1)
    S[c0][c0+98] = MAX(S[c0][c0+98], S[c0+1][c0+98-1] + can_pair(RNA, c0, c0+98));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 900; c0 += 1)
    for (c1 = c0 + 99; c1 <= min(c0 + 197, 999); c1 += 1) {
      if (c0 + 196 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-99+c0] + S[-c0+c1-99+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][98+c0] + S[98+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 900; c0 += 1)
    S[c0][c0+99] = MAX(S[c0][c0+99], S[c0+1][c0+99-1] + can_pair(RNA, c0, c0+99));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 899; c0 += 1)
    for (c1 = c0 + 100; c1 <= min(c0 + 199, 999); c1 += 1) {
      if (c0 + 198 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-100+c0] + S[-c0+c1-100+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][99+c0] + S[99+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 899; c0 += 1)
    S[c0][c0+100] = MAX(S[c0][c0+100], S[c0+1][c0+100-1] + can_pair(RNA, c0, c0+100));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 898; c0 += 1)
    for (c1 = c0 + 101; c1 <= min(c0 + 201, 999); c1 += 1) {
      if (c0 + 200 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-101+c0] + S[-c0+c1-101+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][100+c0] + S[100+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 898; c0 += 1)
    S[c0][c0+101] = MAX(S[c0][c0+101], S[c0+1][c0+101-1] + can_pair(RNA, c0, c0+101));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 897; c0 += 1)
    for (c1 = c0 + 102; c1 <= min(c0 + 203, 999); c1 += 1) {
      if (c0 + 202 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-102+c0] + S[-c0+c1-102+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][101+c0] + S[101+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 897; c0 += 1)
    S[c0][c0+102] = MAX(S[c0][c0+102], S[c0+1][c0+102-1] + can_pair(RNA, c0, c0+102));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 896; c0 += 1)
    for (c1 = c0 + 103; c1 <= min(c0 + 205, 999); c1 += 1) {
      if (c0 + 204 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-103+c0] + S[-c0+c1-103+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][102+c0] + S[102+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 896; c0 += 1)
    S[c0][c0+103] = MAX(S[c0][c0+103], S[c0+1][c0+103-1] + can_pair(RNA, c0, c0+103));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 895; c0 += 1)
    for (c1 = c0 + 104; c1 <= min(c0 + 207, 999); c1 += 1) {
      if (c0 + 206 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-104+c0] + S[-c0+c1-104+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][103+c0] + S[103+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 895; c0 += 1)
    S[c0][c0+104] = MAX(S[c0][c0+104], S[c0+1][c0+104-1] + can_pair(RNA, c0, c0+104));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 894; c0 += 1)
    for (c1 = c0 + 105; c1 <= min(c0 + 209, 999); c1 += 1) {
      if (c0 + 208 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-105+c0] + S[-c0+c1-105+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][104+c0] + S[104+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 894; c0 += 1)
    S[c0][c0+105] = MAX(S[c0][c0+105], S[c0+1][c0+105-1] + can_pair(RNA, c0, c0+105));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 893; c0 += 1)
    for (c1 = c0 + 106; c1 <= min(c0 + 211, 999); c1 += 1) {
      if (c0 + 210 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-106+c0] + S[-c0+c1-106+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][105+c0] + S[105+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 893; c0 += 1)
    S[c0][c0+106] = MAX(S[c0][c0+106], S[c0+1][c0+106-1] + can_pair(RNA, c0, c0+106));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 892; c0 += 1)
    for (c1 = c0 + 107; c1 <= min(c0 + 213, 999); c1 += 1) {
      if (c0 + 212 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-107+c0] + S[-c0+c1-107+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][106+c0] + S[106+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 892; c0 += 1)
    S[c0][c0+107] = MAX(S[c0][c0+107], S[c0+1][c0+107-1] + can_pair(RNA, c0, c0+107));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 891; c0 += 1)
    for (c1 = c0 + 108; c1 <= min(c0 + 215, 999); c1 += 1) {
      if (c0 + 214 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-108+c0] + S[-c0+c1-108+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][107+c0] + S[107+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 891; c0 += 1)
    S[c0][c0+108] = MAX(S[c0][c0+108], S[c0+1][c0+108-1] + can_pair(RNA, c0, c0+108));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 890; c0 += 1)
    for (c1 = c0 + 109; c1 <= min(c0 + 217, 999); c1 += 1) {
      if (c0 + 216 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-109+c0] + S[-c0+c1-109+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][108+c0] + S[108+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 890; c0 += 1)
    S[c0][c0+109] = MAX(S[c0][c0+109], S[c0+1][c0+109-1] + can_pair(RNA, c0, c0+109));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 889; c0 += 1)
    for (c1 = c0 + 110; c1 <= min(c0 + 219, 999); c1 += 1) {
      if (c0 + 218 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-110+c0] + S[-c0+c1-110+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][109+c0] + S[109+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 889; c0 += 1)
    S[c0][c0+110] = MAX(S[c0][c0+110], S[c0+1][c0+110-1] + can_pair(RNA, c0, c0+110));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 888; c0 += 1)
    for (c1 = c0 + 111; c1 <= min(c0 + 221, 999); c1 += 1) {
      if (c0 + 220 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-111+c0] + S[-c0+c1-111+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][110+c0] + S[110+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 888; c0 += 1)
    S[c0][c0+111] = MAX(S[c0][c0+111], S[c0+1][c0+111-1] + can_pair(RNA, c0, c0+111));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 887; c0 += 1)
    for (c1 = c0 + 112; c1 <= min(c0 + 223, 999); c1 += 1) {
      if (c0 + 222 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-112+c0] + S[-c0+c1-112+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][111+c0] + S[111+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 887; c0 += 1)
    S[c0][c0+112] = MAX(S[c0][c0+112], S[c0+1][c0+112-1] + can_pair(RNA, c0, c0+112));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 886; c0 += 1)
    for (c1 = c0 + 113; c1 <= min(c0 + 225, 999); c1 += 1) {
      if (c0 + 224 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-113+c0] + S[-c0+c1-113+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][112+c0] + S[112+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 886; c0 += 1)
    S[c0][c0+113] = MAX(S[c0][c0+113], S[c0+1][c0+113-1] + can_pair(RNA, c0, c0+113));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 885; c0 += 1)
    for (c1 = c0 + 114; c1 <= min(c0 + 227, 999); c1 += 1) {
      if (c0 + 226 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-114+c0] + S[-c0+c1-114+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][113+c0] + S[113+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 885; c0 += 1)
    S[c0][c0+114] = MAX(S[c0][c0+114], S[c0+1][c0+114-1] + can_pair(RNA, c0, c0+114));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 884; c0 += 1)
    for (c1 = c0 + 115; c1 <= min(c0 + 229, 999); c1 += 1) {
      if (c0 + 228 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-115+c0] + S[-c0+c1-115+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][114+c0] + S[114+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 884; c0 += 1)
    S[c0][c0+115] = MAX(S[c0][c0+115], S[c0+1][c0+115-1] + can_pair(RNA, c0, c0+115));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 883; c0 += 1)
    for (c1 = c0 + 116; c1 <= min(c0 + 231, 999); c1 += 1) {
      if (c0 + 230 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-116+c0] + S[-c0+c1-116+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][115+c0] + S[115+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 883; c0 += 1)
    S[c0][c0+116] = MAX(S[c0][c0+116], S[c0+1][c0+116-1] + can_pair(RNA, c0, c0+116));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 882; c0 += 1)
    for (c1 = c0 + 117; c1 <= min(c0 + 233, 999); c1 += 1) {
      if (c0 + 232 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-117+c0] + S[-c0+c1-117+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][116+c0] + S[116+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 882; c0 += 1)
    S[c0][c0+117] = MAX(S[c0][c0+117], S[c0+1][c0+117-1] + can_pair(RNA, c0, c0+117));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 881; c0 += 1)
    for (c1 = c0 + 118; c1 <= min(c0 + 235, 999); c1 += 1) {
      if (c0 + 234 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-118+c0] + S[-c0+c1-118+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][117+c0] + S[117+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 881; c0 += 1)
    S[c0][c0+118] = MAX(S[c0][c0+118], S[c0+1][c0+118-1] + can_pair(RNA, c0, c0+118));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 880; c0 += 1)
    for (c1 = c0 + 119; c1 <= min(c0 + 237, 999); c1 += 1) {
      if (c0 + 236 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-119+c0] + S[-c0+c1-119+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][118+c0] + S[118+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 880; c0 += 1)
    S[c0][c0+119] = MAX(S[c0][c0+119], S[c0+1][c0+119-1] + can_pair(RNA, c0, c0+119));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 879; c0 += 1)
    for (c1 = c0 + 120; c1 <= min(c0 + 239, 999); c1 += 1) {
      if (c0 + 238 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-120+c0] + S[-c0+c1-120+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][119+c0] + S[119+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 879; c0 += 1)
    S[c0][c0+120] = MAX(S[c0][c0+120], S[c0+1][c0+120-1] + can_pair(RNA, c0, c0+120));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 878; c0 += 1)
    for (c1 = c0 + 121; c1 <= min(c0 + 241, 999); c1 += 1) {
      if (c0 + 240 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-121+c0] + S[-c0+c1-121+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][120+c0] + S[120+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 878; c0 += 1)
    S[c0][c0+121] = MAX(S[c0][c0+121], S[c0+1][c0+121-1] + can_pair(RNA, c0, c0+121));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 877; c0 += 1)
    for (c1 = c0 + 122; c1 <= min(c0 + 243, 999); c1 += 1) {
      if (c0 + 242 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-122+c0] + S[-c0+c1-122+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][121+c0] + S[121+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 877; c0 += 1)
    S[c0][c0+122] = MAX(S[c0][c0+122], S[c0+1][c0+122-1] + can_pair(RNA, c0, c0+122));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 876; c0 += 1)
    for (c1 = c0 + 123; c1 <= min(c0 + 245, 999); c1 += 1) {
      if (c0 + 244 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-123+c0] + S[-c0+c1-123+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][122+c0] + S[122+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 876; c0 += 1)
    S[c0][c0+123] = MAX(S[c0][c0+123], S[c0+1][c0+123-1] + can_pair(RNA, c0, c0+123));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 875; c0 += 1)
    for (c1 = c0 + 124; c1 <= min(c0 + 247, 999); c1 += 1) {
      if (c0 + 246 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-124+c0] + S[-c0+c1-124+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][123+c0] + S[123+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 875; c0 += 1)
    S[c0][c0+124] = MAX(S[c0][c0+124], S[c0+1][c0+124-1] + can_pair(RNA, c0, c0+124));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 874; c0 += 1)
    for (c1 = c0 + 125; c1 <= min(c0 + 249, 999); c1 += 1) {
      if (c0 + 248 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-125+c0] + S[-c0+c1-125+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][124+c0] + S[124+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 874; c0 += 1)
    S[c0][c0+125] = MAX(S[c0][c0+125], S[c0+1][c0+125-1] + can_pair(RNA, c0, c0+125));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 873; c0 += 1)
    for (c1 = c0 + 126; c1 <= min(c0 + 251, 999); c1 += 1) {
      if (c0 + 250 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-126+c0] + S[-c0+c1-126+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][125+c0] + S[125+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 873; c0 += 1)
    S[c0][c0+126] = MAX(S[c0][c0+126], S[c0+1][c0+126-1] + can_pair(RNA, c0, c0+126));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 872; c0 += 1)
    for (c1 = c0 + 127; c1 <= min(c0 + 253, 999); c1 += 1) {
      if (c0 + 252 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-127+c0] + S[-c0+c1-127+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][126+c0] + S[126+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 872; c0 += 1)
    S[c0][c0+127] = MAX(S[c0][c0+127], S[c0+1][c0+127-1] + can_pair(RNA, c0, c0+127));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 871; c0 += 1)
    for (c1 = c0 + 128; c1 <= min(c0 + 255, 999); c1 += 1) {
      if (c0 + 254 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-128+c0] + S[-c0+c1-128+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][127+c0] + S[127+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 871; c0 += 1)
    S[c0][c0+128] = MAX(S[c0][c0+128], S[c0+1][c0+128-1] + can_pair(RNA, c0, c0+128));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 870; c0 += 1)
    for (c1 = c0 + 129; c1 <= min(c0 + 257, 999); c1 += 1) {
      if (c0 + 256 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-129+c0] + S[-c0+c1-129+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][128+c0] + S[128+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 870; c0 += 1)
    S[c0][c0+129] = MAX(S[c0][c0+129], S[c0+1][c0+129-1] + can_pair(RNA, c0, c0+129));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 869; c0 += 1)
    for (c1 = c0 + 130; c1 <= min(c0 + 259, 999); c1 += 1) {
      if (c0 + 258 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-130+c0] + S[-c0+c1-130+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][129+c0] + S[129+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 869; c0 += 1)
    S[c0][c0+130] = MAX(S[c0][c0+130], S[c0+1][c0+130-1] + can_pair(RNA, c0, c0+130));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 868; c0 += 1)
    for (c1 = c0 + 131; c1 <= min(c0 + 261, 999); c1 += 1) {
      if (c0 + 260 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-131+c0] + S[-c0+c1-131+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][130+c0] + S[130+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 868; c0 += 1)
    S[c0][c0+131] = MAX(S[c0][c0+131], S[c0+1][c0+131-1] + can_pair(RNA, c0, c0+131));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 867; c0 += 1)
    for (c1 = c0 + 132; c1 <= min(c0 + 263, 999); c1 += 1) {
      if (c0 + 262 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-132+c0] + S[-c0+c1-132+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][131+c0] + S[131+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 867; c0 += 1)
    S[c0][c0+132] = MAX(S[c0][c0+132], S[c0+1][c0+132-1] + can_pair(RNA, c0, c0+132));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 866; c0 += 1)
    for (c1 = c0 + 133; c1 <= min(c0 + 265, 999); c1 += 1) {
      if (c0 + 264 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-133+c0] + S[-c0+c1-133+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][132+c0] + S[132+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 866; c0 += 1)
    S[c0][c0+133] = MAX(S[c0][c0+133], S[c0+1][c0+133-1] + can_pair(RNA, c0, c0+133));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 865; c0 += 1)
    for (c1 = c0 + 134; c1 <= min(c0 + 267, 999); c1 += 1) {
      if (c0 + 266 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-134+c0] + S[-c0+c1-134+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][133+c0] + S[133+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 865; c0 += 1)
    S[c0][c0+134] = MAX(S[c0][c0+134], S[c0+1][c0+134-1] + can_pair(RNA, c0, c0+134));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 864; c0 += 1)
    for (c1 = c0 + 135; c1 <= min(c0 + 269, 999); c1 += 1) {
      if (c0 + 268 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-135+c0] + S[-c0+c1-135+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][134+c0] + S[134+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 864; c0 += 1)
    S[c0][c0+135] = MAX(S[c0][c0+135], S[c0+1][c0+135-1] + can_pair(RNA, c0, c0+135));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 863; c0 += 1)
    for (c1 = c0 + 136; c1 <= min(c0 + 271, 999); c1 += 1) {
      if (c0 + 270 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-136+c0] + S[-c0+c1-136+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][135+c0] + S[135+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 863; c0 += 1)
    S[c0][c0+136] = MAX(S[c0][c0+136], S[c0+1][c0+136-1] + can_pair(RNA, c0, c0+136));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 862; c0 += 1)
    for (c1 = c0 + 137; c1 <= min(c0 + 273, 999); c1 += 1) {
      if (c0 + 272 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-137+c0] + S[-c0+c1-137+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][136+c0] + S[136+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 862; c0 += 1)
    S[c0][c0+137] = MAX(S[c0][c0+137], S[c0+1][c0+137-1] + can_pair(RNA, c0, c0+137));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 861; c0 += 1)
    for (c1 = c0 + 138; c1 <= min(c0 + 275, 999); c1 += 1) {
      if (c0 + 274 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-138+c0] + S[-c0+c1-138+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][137+c0] + S[137+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 861; c0 += 1)
    S[c0][c0+138] = MAX(S[c0][c0+138], S[c0+1][c0+138-1] + can_pair(RNA, c0, c0+138));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 860; c0 += 1)
    for (c1 = c0 + 139; c1 <= min(c0 + 277, 999); c1 += 1) {
      if (c0 + 276 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-139+c0] + S[-c0+c1-139+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][138+c0] + S[138+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 860; c0 += 1)
    S[c0][c0+139] = MAX(S[c0][c0+139], S[c0+1][c0+139-1] + can_pair(RNA, c0, c0+139));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 859; c0 += 1)
    for (c1 = c0 + 140; c1 <= min(c0 + 279, 999); c1 += 1) {
      if (c0 + 278 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-140+c0] + S[-c0+c1-140+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][139+c0] + S[139+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 859; c0 += 1)
    S[c0][c0+140] = MAX(S[c0][c0+140], S[c0+1][c0+140-1] + can_pair(RNA, c0, c0+140));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 858; c0 += 1)
    for (c1 = c0 + 141; c1 <= min(c0 + 281, 999); c1 += 1) {
      if (c0 + 280 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-141+c0] + S[-c0+c1-141+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][140+c0] + S[140+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 858; c0 += 1)
    S[c0][c0+141] = MAX(S[c0][c0+141], S[c0+1][c0+141-1] + can_pair(RNA, c0, c0+141));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 857; c0 += 1)
    for (c1 = c0 + 142; c1 <= min(c0 + 283, 999); c1 += 1) {
      if (c0 + 282 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-142+c0] + S[-c0+c1-142+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][141+c0] + S[141+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 857; c0 += 1)
    S[c0][c0+142] = MAX(S[c0][c0+142], S[c0+1][c0+142-1] + can_pair(RNA, c0, c0+142));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 856; c0 += 1)
    for (c1 = c0 + 143; c1 <= min(c0 + 285, 999); c1 += 1) {
      if (c0 + 284 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-143+c0] + S[-c0+c1-143+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][142+c0] + S[142+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 856; c0 += 1)
    S[c0][c0+143] = MAX(S[c0][c0+143], S[c0+1][c0+143-1] + can_pair(RNA, c0, c0+143));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 855; c0 += 1)
    for (c1 = c0 + 144; c1 <= min(c0 + 287, 999); c1 += 1) {
      if (c0 + 286 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-144+c0] + S[-c0+c1-144+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][143+c0] + S[143+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 855; c0 += 1)
    S[c0][c0+144] = MAX(S[c0][c0+144], S[c0+1][c0+144-1] + can_pair(RNA, c0, c0+144));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 854; c0 += 1)
    for (c1 = c0 + 145; c1 <= min(c0 + 289, 999); c1 += 1) {
      if (c0 + 288 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-145+c0] + S[-c0+c1-145+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][144+c0] + S[144+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 854; c0 += 1)
    S[c0][c0+145] = MAX(S[c0][c0+145], S[c0+1][c0+145-1] + can_pair(RNA, c0, c0+145));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 853; c0 += 1)
    for (c1 = c0 + 146; c1 <= min(c0 + 291, 999); c1 += 1) {
      if (c0 + 290 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-146+c0] + S[-c0+c1-146+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][145+c0] + S[145+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 853; c0 += 1)
    S[c0][c0+146] = MAX(S[c0][c0+146], S[c0+1][c0+146-1] + can_pair(RNA, c0, c0+146));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 852; c0 += 1)
    for (c1 = c0 + 147; c1 <= min(c0 + 293, 999); c1 += 1) {
      if (c0 + 292 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-147+c0] + S[-c0+c1-147+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][146+c0] + S[146+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 852; c0 += 1)
    S[c0][c0+147] = MAX(S[c0][c0+147], S[c0+1][c0+147-1] + can_pair(RNA, c0, c0+147));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 851; c0 += 1)
    for (c1 = c0 + 148; c1 <= min(c0 + 295, 999); c1 += 1) {
      if (c0 + 294 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-148+c0] + S[-c0+c1-148+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][147+c0] + S[147+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 851; c0 += 1)
    S[c0][c0+148] = MAX(S[c0][c0+148], S[c0+1][c0+148-1] + can_pair(RNA, c0, c0+148));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 850; c0 += 1)
    for (c1 = c0 + 149; c1 <= min(c0 + 297, 999); c1 += 1) {
      if (c0 + 296 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-149+c0] + S[-c0+c1-149+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][148+c0] + S[148+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 850; c0 += 1)
    S[c0][c0+149] = MAX(S[c0][c0+149], S[c0+1][c0+149-1] + can_pair(RNA, c0, c0+149));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 849; c0 += 1)
    for (c1 = c0 + 150; c1 <= min(c0 + 299, 999); c1 += 1) {
      if (c0 + 298 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-150+c0] + S[-c0+c1-150+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][149+c0] + S[149+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 849; c0 += 1)
    S[c0][c0+150] = MAX(S[c0][c0+150], S[c0+1][c0+150-1] + can_pair(RNA, c0, c0+150));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 848; c0 += 1)
    for (c1 = c0 + 151; c1 <= min(c0 + 301, 999); c1 += 1) {
      if (c0 + 300 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-151+c0] + S[-c0+c1-151+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][150+c0] + S[150+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 848; c0 += 1)
    S[c0][c0+151] = MAX(S[c0][c0+151], S[c0+1][c0+151-1] + can_pair(RNA, c0, c0+151));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 847; c0 += 1)
    for (c1 = c0 + 152; c1 <= min(c0 + 303, 999); c1 += 1) {
      if (c0 + 302 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-152+c0] + S[-c0+c1-152+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][151+c0] + S[151+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 847; c0 += 1)
    S[c0][c0+152] = MAX(S[c0][c0+152], S[c0+1][c0+152-1] + can_pair(RNA, c0, c0+152));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 846; c0 += 1)
    for (c1 = c0 + 153; c1 <= min(c0 + 305, 999); c1 += 1) {
      if (c0 + 304 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-153+c0] + S[-c0+c1-153+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][152+c0] + S[152+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 846; c0 += 1)
    S[c0][c0+153] = MAX(S[c0][c0+153], S[c0+1][c0+153-1] + can_pair(RNA, c0, c0+153));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 845; c0 += 1)
    for (c1 = c0 + 154; c1 <= min(c0 + 307, 999); c1 += 1) {
      if (c0 + 306 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-154+c0] + S[-c0+c1-154+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][153+c0] + S[153+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 845; c0 += 1)
    S[c0][c0+154] = MAX(S[c0][c0+154], S[c0+1][c0+154-1] + can_pair(RNA, c0, c0+154));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 844; c0 += 1)
    for (c1 = c0 + 155; c1 <= min(c0 + 309, 999); c1 += 1) {
      if (c0 + 308 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-155+c0] + S[-c0+c1-155+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][154+c0] + S[154+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 844; c0 += 1)
    S[c0][c0+155] = MAX(S[c0][c0+155], S[c0+1][c0+155-1] + can_pair(RNA, c0, c0+155));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 843; c0 += 1)
    for (c1 = c0 + 156; c1 <= min(c0 + 311, 999); c1 += 1) {
      if (c0 + 310 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-156+c0] + S[-c0+c1-156+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][155+c0] + S[155+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 843; c0 += 1)
    S[c0][c0+156] = MAX(S[c0][c0+156], S[c0+1][c0+156-1] + can_pair(RNA, c0, c0+156));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 842; c0 += 1)
    for (c1 = c0 + 157; c1 <= min(c0 + 313, 999); c1 += 1) {
      if (c0 + 312 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-157+c0] + S[-c0+c1-157+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][156+c0] + S[156+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 842; c0 += 1)
    S[c0][c0+157] = MAX(S[c0][c0+157], S[c0+1][c0+157-1] + can_pair(RNA, c0, c0+157));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 841; c0 += 1)
    for (c1 = c0 + 158; c1 <= min(c0 + 315, 999); c1 += 1) {
      if (c0 + 314 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-158+c0] + S[-c0+c1-158+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][157+c0] + S[157+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 841; c0 += 1)
    S[c0][c0+158] = MAX(S[c0][c0+158], S[c0+1][c0+158-1] + can_pair(RNA, c0, c0+158));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 840; c0 += 1)
    for (c1 = c0 + 159; c1 <= min(c0 + 317, 999); c1 += 1) {
      if (c0 + 316 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-159+c0] + S[-c0+c1-159+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][158+c0] + S[158+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 840; c0 += 1)
    S[c0][c0+159] = MAX(S[c0][c0+159], S[c0+1][c0+159-1] + can_pair(RNA, c0, c0+159));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 839; c0 += 1)
    for (c1 = c0 + 160; c1 <= min(c0 + 319, 999); c1 += 1) {
      if (c0 + 318 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-160+c0] + S[-c0+c1-160+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][159+c0] + S[159+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 839; c0 += 1)
    S[c0][c0+160] = MAX(S[c0][c0+160], S[c0+1][c0+160-1] + can_pair(RNA, c0, c0+160));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 838; c0 += 1)
    for (c1 = c0 + 161; c1 <= min(c0 + 321, 999); c1 += 1) {
      if (c0 + 320 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-161+c0] + S[-c0+c1-161+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][160+c0] + S[160+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 838; c0 += 1)
    S[c0][c0+161] = MAX(S[c0][c0+161], S[c0+1][c0+161-1] + can_pair(RNA, c0, c0+161));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 837; c0 += 1)
    for (c1 = c0 + 162; c1 <= min(c0 + 323, 999); c1 += 1) {
      if (c0 + 322 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-162+c0] + S[-c0+c1-162+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][161+c0] + S[161+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 837; c0 += 1)
    S[c0][c0+162] = MAX(S[c0][c0+162], S[c0+1][c0+162-1] + can_pair(RNA, c0, c0+162));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 836; c0 += 1)
    for (c1 = c0 + 163; c1 <= min(c0 + 325, 999); c1 += 1) {
      if (c0 + 324 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-163+c0] + S[-c0+c1-163+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][162+c0] + S[162+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 836; c0 += 1)
    S[c0][c0+163] = MAX(S[c0][c0+163], S[c0+1][c0+163-1] + can_pair(RNA, c0, c0+163));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 835; c0 += 1)
    for (c1 = c0 + 164; c1 <= min(c0 + 327, 999); c1 += 1) {
      if (c0 + 326 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-164+c0] + S[-c0+c1-164+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][163+c0] + S[163+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 835; c0 += 1)
    S[c0][c0+164] = MAX(S[c0][c0+164], S[c0+1][c0+164-1] + can_pair(RNA, c0, c0+164));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 834; c0 += 1)
    for (c1 = c0 + 165; c1 <= min(c0 + 329, 999); c1 += 1) {
      if (c0 + 328 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-165+c0] + S[-c0+c1-165+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][164+c0] + S[164+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 834; c0 += 1)
    S[c0][c0+165] = MAX(S[c0][c0+165], S[c0+1][c0+165-1] + can_pair(RNA, c0, c0+165));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 833; c0 += 1)
    for (c1 = c0 + 166; c1 <= min(c0 + 331, 999); c1 += 1) {
      if (c0 + 330 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-166+c0] + S[-c0+c1-166+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][165+c0] + S[165+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 833; c0 += 1)
    S[c0][c0+166] = MAX(S[c0][c0+166], S[c0+1][c0+166-1] + can_pair(RNA, c0, c0+166));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 832; c0 += 1)
    for (c1 = c0 + 167; c1 <= min(c0 + 333, 999); c1 += 1) {
      if (c0 + 332 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-167+c0] + S[-c0+c1-167+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][166+c0] + S[166+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 832; c0 += 1)
    S[c0][c0+167] = MAX(S[c0][c0+167], S[c0+1][c0+167-1] + can_pair(RNA, c0, c0+167));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 831; c0 += 1)
    for (c1 = c0 + 168; c1 <= min(c0 + 335, 999); c1 += 1) {
      if (c0 + 334 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-168+c0] + S[-c0+c1-168+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][167+c0] + S[167+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 831; c0 += 1)
    S[c0][c0+168] = MAX(S[c0][c0+168], S[c0+1][c0+168-1] + can_pair(RNA, c0, c0+168));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 830; c0 += 1)
    for (c1 = c0 + 169; c1 <= min(c0 + 337, 999); c1 += 1) {
      if (c0 + 336 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-169+c0] + S[-c0+c1-169+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][168+c0] + S[168+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 830; c0 += 1)
    S[c0][c0+169] = MAX(S[c0][c0+169], S[c0+1][c0+169-1] + can_pair(RNA, c0, c0+169));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 829; c0 += 1)
    for (c1 = c0 + 170; c1 <= min(c0 + 339, 999); c1 += 1) {
      if (c0 + 338 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-170+c0] + S[-c0+c1-170+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][169+c0] + S[169+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 829; c0 += 1)
    S[c0][c0+170] = MAX(S[c0][c0+170], S[c0+1][c0+170-1] + can_pair(RNA, c0, c0+170));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 828; c0 += 1)
    for (c1 = c0 + 171; c1 <= min(c0 + 341, 999); c1 += 1) {
      if (c0 + 340 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-171+c0] + S[-c0+c1-171+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][170+c0] + S[170+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 828; c0 += 1)
    S[c0][c0+171] = MAX(S[c0][c0+171], S[c0+1][c0+171-1] + can_pair(RNA, c0, c0+171));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 827; c0 += 1)
    for (c1 = c0 + 172; c1 <= min(c0 + 343, 999); c1 += 1) {
      if (c0 + 342 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-172+c0] + S[-c0+c1-172+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][171+c0] + S[171+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 827; c0 += 1)
    S[c0][c0+172] = MAX(S[c0][c0+172], S[c0+1][c0+172-1] + can_pair(RNA, c0, c0+172));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 826; c0 += 1)
    for (c1 = c0 + 173; c1 <= min(c0 + 345, 999); c1 += 1) {
      if (c0 + 344 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-173+c0] + S[-c0+c1-173+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][172+c0] + S[172+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 826; c0 += 1)
    S[c0][c0+173] = MAX(S[c0][c0+173], S[c0+1][c0+173-1] + can_pair(RNA, c0, c0+173));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 825; c0 += 1)
    for (c1 = c0 + 174; c1 <= min(c0 + 347, 999); c1 += 1) {
      if (c0 + 346 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-174+c0] + S[-c0+c1-174+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][173+c0] + S[173+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 825; c0 += 1)
    S[c0][c0+174] = MAX(S[c0][c0+174], S[c0+1][c0+174-1] + can_pair(RNA, c0, c0+174));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 824; c0 += 1)
    for (c1 = c0 + 175; c1 <= min(c0 + 349, 999); c1 += 1) {
      if (c0 + 348 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-175+c0] + S[-c0+c1-175+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][174+c0] + S[174+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 824; c0 += 1)
    S[c0][c0+175] = MAX(S[c0][c0+175], S[c0+1][c0+175-1] + can_pair(RNA, c0, c0+175));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 823; c0 += 1)
    for (c1 = c0 + 176; c1 <= min(c0 + 351, 999); c1 += 1) {
      if (c0 + 350 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-176+c0] + S[-c0+c1-176+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][175+c0] + S[175+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 823; c0 += 1)
    S[c0][c0+176] = MAX(S[c0][c0+176], S[c0+1][c0+176-1] + can_pair(RNA, c0, c0+176));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 822; c0 += 1)
    for (c1 = c0 + 177; c1 <= min(c0 + 353, 999); c1 += 1) {
      if (c0 + 352 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-177+c0] + S[-c0+c1-177+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][176+c0] + S[176+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 822; c0 += 1)
    S[c0][c0+177] = MAX(S[c0][c0+177], S[c0+1][c0+177-1] + can_pair(RNA, c0, c0+177));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 821; c0 += 1)
    for (c1 = c0 + 178; c1 <= min(c0 + 355, 999); c1 += 1) {
      if (c0 + 354 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-178+c0] + S[-c0+c1-178+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][177+c0] + S[177+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 821; c0 += 1)
    S[c0][c0+178] = MAX(S[c0][c0+178], S[c0+1][c0+178-1] + can_pair(RNA, c0, c0+178));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 820; c0 += 1)
    for (c1 = c0 + 179; c1 <= min(c0 + 357, 999); c1 += 1) {
      if (c0 + 356 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-179+c0] + S[-c0+c1-179+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][178+c0] + S[178+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 820; c0 += 1)
    S[c0][c0+179] = MAX(S[c0][c0+179], S[c0+1][c0+179-1] + can_pair(RNA, c0, c0+179));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 819; c0 += 1)
    for (c1 = c0 + 180; c1 <= min(c0 + 359, 999); c1 += 1) {
      if (c0 + 358 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-180+c0] + S[-c0+c1-180+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][179+c0] + S[179+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 819; c0 += 1)
    S[c0][c0+180] = MAX(S[c0][c0+180], S[c0+1][c0+180-1] + can_pair(RNA, c0, c0+180));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 818; c0 += 1)
    for (c1 = c0 + 181; c1 <= min(c0 + 361, 999); c1 += 1) {
      if (c0 + 360 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-181+c0] + S[-c0+c1-181+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][180+c0] + S[180+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 818; c0 += 1)
    S[c0][c0+181] = MAX(S[c0][c0+181], S[c0+1][c0+181-1] + can_pair(RNA, c0, c0+181));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 817; c0 += 1)
    for (c1 = c0 + 182; c1 <= min(c0 + 363, 999); c1 += 1) {
      if (c0 + 362 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-182+c0] + S[-c0+c1-182+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][181+c0] + S[181+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 817; c0 += 1)
    S[c0][c0+182] = MAX(S[c0][c0+182], S[c0+1][c0+182-1] + can_pair(RNA, c0, c0+182));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 816; c0 += 1)
    for (c1 = c0 + 183; c1 <= min(c0 + 365, 999); c1 += 1) {
      if (c0 + 364 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-183+c0] + S[-c0+c1-183+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][182+c0] + S[182+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 816; c0 += 1)
    S[c0][c0+183] = MAX(S[c0][c0+183], S[c0+1][c0+183-1] + can_pair(RNA, c0, c0+183));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 815; c0 += 1)
    for (c1 = c0 + 184; c1 <= min(c0 + 367, 999); c1 += 1) {
      if (c0 + 366 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-184+c0] + S[-c0+c1-184+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][183+c0] + S[183+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 815; c0 += 1)
    S[c0][c0+184] = MAX(S[c0][c0+184], S[c0+1][c0+184-1] + can_pair(RNA, c0, c0+184));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 814; c0 += 1)
    for (c1 = c0 + 185; c1 <= min(c0 + 369, 999); c1 += 1) {
      if (c0 + 368 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-185+c0] + S[-c0+c1-185+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][184+c0] + S[184+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 814; c0 += 1)
    S[c0][c0+185] = MAX(S[c0][c0+185], S[c0+1][c0+185-1] + can_pair(RNA, c0, c0+185));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 813; c0 += 1)
    for (c1 = c0 + 186; c1 <= min(c0 + 371, 999); c1 += 1) {
      if (c0 + 370 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-186+c0] + S[-c0+c1-186+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][185+c0] + S[185+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 813; c0 += 1)
    S[c0][c0+186] = MAX(S[c0][c0+186], S[c0+1][c0+186-1] + can_pair(RNA, c0, c0+186));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 812; c0 += 1)
    for (c1 = c0 + 187; c1 <= min(c0 + 373, 999); c1 += 1) {
      if (c0 + 372 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-187+c0] + S[-c0+c1-187+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][186+c0] + S[186+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 812; c0 += 1)
    S[c0][c0+187] = MAX(S[c0][c0+187], S[c0+1][c0+187-1] + can_pair(RNA, c0, c0+187));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 811; c0 += 1)
    for (c1 = c0 + 188; c1 <= min(c0 + 375, 999); c1 += 1) {
      if (c0 + 374 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-188+c0] + S[-c0+c1-188+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][187+c0] + S[187+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 811; c0 += 1)
    S[c0][c0+188] = MAX(S[c0][c0+188], S[c0+1][c0+188-1] + can_pair(RNA, c0, c0+188));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 810; c0 += 1)
    for (c1 = c0 + 189; c1 <= min(c0 + 377, 999); c1 += 1) {
      if (c0 + 376 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-189+c0] + S[-c0+c1-189+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][188+c0] + S[188+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 810; c0 += 1)
    S[c0][c0+189] = MAX(S[c0][c0+189], S[c0+1][c0+189-1] + can_pair(RNA, c0, c0+189));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 809; c0 += 1)
    for (c1 = c0 + 190; c1 <= min(c0 + 379, 999); c1 += 1) {
      if (c0 + 378 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-190+c0] + S[-c0+c1-190+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][189+c0] + S[189+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 809; c0 += 1)
    S[c0][c0+190] = MAX(S[c0][c0+190], S[c0+1][c0+190-1] + can_pair(RNA, c0, c0+190));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 808; c0 += 1)
    for (c1 = c0 + 191; c1 <= min(c0 + 381, 999); c1 += 1) {
      if (c0 + 380 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-191+c0] + S[-c0+c1-191+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][190+c0] + S[190+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 808; c0 += 1)
    S[c0][c0+191] = MAX(S[c0][c0+191], S[c0+1][c0+191-1] + can_pair(RNA, c0, c0+191));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 807; c0 += 1)
    for (c1 = c0 + 192; c1 <= min(c0 + 383, 999); c1 += 1) {
      if (c0 + 382 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-192+c0] + S[-c0+c1-192+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][191+c0] + S[191+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 807; c0 += 1)
    S[c0][c0+192] = MAX(S[c0][c0+192], S[c0+1][c0+192-1] + can_pair(RNA, c0, c0+192));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 806; c0 += 1)
    for (c1 = c0 + 193; c1 <= min(c0 + 385, 999); c1 += 1) {
      if (c0 + 384 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-193+c0] + S[-c0+c1-193+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][192+c0] + S[192+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 806; c0 += 1)
    S[c0][c0+193] = MAX(S[c0][c0+193], S[c0+1][c0+193-1] + can_pair(RNA, c0, c0+193));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 805; c0 += 1)
    for (c1 = c0 + 194; c1 <= min(c0 + 387, 999); c1 += 1) {
      if (c0 + 386 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-194+c0] + S[-c0+c1-194+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][193+c0] + S[193+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 805; c0 += 1)
    S[c0][c0+194] = MAX(S[c0][c0+194], S[c0+1][c0+194-1] + can_pair(RNA, c0, c0+194));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 804; c0 += 1)
    for (c1 = c0 + 195; c1 <= min(c0 + 389, 999); c1 += 1) {
      if (c0 + 388 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-195+c0] + S[-c0+c1-195+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][194+c0] + S[194+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 804; c0 += 1)
    S[c0][c0+195] = MAX(S[c0][c0+195], S[c0+1][c0+195-1] + can_pair(RNA, c0, c0+195));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 803; c0 += 1)
    for (c1 = c0 + 196; c1 <= min(c0 + 391, 999); c1 += 1) {
      if (c0 + 390 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-196+c0] + S[-c0+c1-196+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][195+c0] + S[195+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 803; c0 += 1)
    S[c0][c0+196] = MAX(S[c0][c0+196], S[c0+1][c0+196-1] + can_pair(RNA, c0, c0+196));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 802; c0 += 1)
    for (c1 = c0 + 197; c1 <= min(c0 + 393, 999); c1 += 1) {
      if (c0 + 392 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-197+c0] + S[-c0+c1-197+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][196+c0] + S[196+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 802; c0 += 1)
    S[c0][c0+197] = MAX(S[c0][c0+197], S[c0+1][c0+197-1] + can_pair(RNA, c0, c0+197));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 801; c0 += 1)
    for (c1 = c0 + 198; c1 <= min(c0 + 395, 999); c1 += 1) {
      if (c0 + 394 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-198+c0] + S[-c0+c1-198+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][197+c0] + S[197+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 801; c0 += 1)
    S[c0][c0+198] = MAX(S[c0][c0+198], S[c0+1][c0+198-1] + can_pair(RNA, c0, c0+198));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 800; c0 += 1)
    for (c1 = c0 + 199; c1 <= min(c0 + 397, 999); c1 += 1) {
      if (c0 + 396 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-199+c0] + S[-c0+c1-199+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][198+c0] + S[198+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 800; c0 += 1)
    S[c0][c0+199] = MAX(S[c0][c0+199], S[c0+1][c0+199-1] + can_pair(RNA, c0, c0+199));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 799; c0 += 1)
    for (c1 = c0 + 200; c1 <= min(c0 + 399, 999); c1 += 1) {
      if (c0 + 398 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-200+c0] + S[-c0+c1-200+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][199+c0] + S[199+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 799; c0 += 1)
    S[c0][c0+200] = MAX(S[c0][c0+200], S[c0+1][c0+200-1] + can_pair(RNA, c0, c0+200));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 798; c0 += 1)
    for (c1 = c0 + 201; c1 <= min(c0 + 401, 999); c1 += 1) {
      if (c0 + 400 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-201+c0] + S[-c0+c1-201+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][200+c0] + S[200+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 798; c0 += 1)
    S[c0][c0+201] = MAX(S[c0][c0+201], S[c0+1][c0+201-1] + can_pair(RNA, c0, c0+201));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 797; c0 += 1)
    for (c1 = c0 + 202; c1 <= min(c0 + 403, 999); c1 += 1) {
      if (c0 + 402 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-202+c0] + S[-c0+c1-202+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][201+c0] + S[201+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 797; c0 += 1)
    S[c0][c0+202] = MAX(S[c0][c0+202], S[c0+1][c0+202-1] + can_pair(RNA, c0, c0+202));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 796; c0 += 1)
    for (c1 = c0 + 203; c1 <= min(c0 + 405, 999); c1 += 1) {
      if (c0 + 404 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-203+c0] + S[-c0+c1-203+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][202+c0] + S[202+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 796; c0 += 1)
    S[c0][c0+203] = MAX(S[c0][c0+203], S[c0+1][c0+203-1] + can_pair(RNA, c0, c0+203));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 795; c0 += 1)
    for (c1 = c0 + 204; c1 <= min(c0 + 407, 999); c1 += 1) {
      if (c0 + 406 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-204+c0] + S[-c0+c1-204+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][203+c0] + S[203+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 795; c0 += 1)
    S[c0][c0+204] = MAX(S[c0][c0+204], S[c0+1][c0+204-1] + can_pair(RNA, c0, c0+204));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 794; c0 += 1)
    for (c1 = c0 + 205; c1 <= min(c0 + 409, 999); c1 += 1) {
      if (c0 + 408 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-205+c0] + S[-c0+c1-205+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][204+c0] + S[204+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 794; c0 += 1)
    S[c0][c0+205] = MAX(S[c0][c0+205], S[c0+1][c0+205-1] + can_pair(RNA, c0, c0+205));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 793; c0 += 1)
    for (c1 = c0 + 206; c1 <= min(c0 + 411, 999); c1 += 1) {
      if (c0 + 410 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-206+c0] + S[-c0+c1-206+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][205+c0] + S[205+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 793; c0 += 1)
    S[c0][c0+206] = MAX(S[c0][c0+206], S[c0+1][c0+206-1] + can_pair(RNA, c0, c0+206));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 792; c0 += 1)
    for (c1 = c0 + 207; c1 <= min(c0 + 413, 999); c1 += 1) {
      if (c0 + 412 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-207+c0] + S[-c0+c1-207+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][206+c0] + S[206+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 792; c0 += 1)
    S[c0][c0+207] = MAX(S[c0][c0+207], S[c0+1][c0+207-1] + can_pair(RNA, c0, c0+207));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 791; c0 += 1)
    for (c1 = c0 + 208; c1 <= min(c0 + 415, 999); c1 += 1) {
      if (c0 + 414 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-208+c0] + S[-c0+c1-208+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][207+c0] + S[207+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 791; c0 += 1)
    S[c0][c0+208] = MAX(S[c0][c0+208], S[c0+1][c0+208-1] + can_pair(RNA, c0, c0+208));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 790; c0 += 1)
    for (c1 = c0 + 209; c1 <= min(c0 + 417, 999); c1 += 1) {
      if (c0 + 416 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-209+c0] + S[-c0+c1-209+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][208+c0] + S[208+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 790; c0 += 1)
    S[c0][c0+209] = MAX(S[c0][c0+209], S[c0+1][c0+209-1] + can_pair(RNA, c0, c0+209));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 789; c0 += 1)
    for (c1 = c0 + 210; c1 <= min(c0 + 419, 999); c1 += 1) {
      if (c0 + 418 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-210+c0] + S[-c0+c1-210+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][209+c0] + S[209+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 789; c0 += 1)
    S[c0][c0+210] = MAX(S[c0][c0+210], S[c0+1][c0+210-1] + can_pair(RNA, c0, c0+210));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 788; c0 += 1)
    for (c1 = c0 + 211; c1 <= min(c0 + 421, 999); c1 += 1) {
      if (c0 + 420 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-211+c0] + S[-c0+c1-211+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][210+c0] + S[210+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 788; c0 += 1)
    S[c0][c0+211] = MAX(S[c0][c0+211], S[c0+1][c0+211-1] + can_pair(RNA, c0, c0+211));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 787; c0 += 1)
    for (c1 = c0 + 212; c1 <= min(c0 + 423, 999); c1 += 1) {
      if (c0 + 422 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-212+c0] + S[-c0+c1-212+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][211+c0] + S[211+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 787; c0 += 1)
    S[c0][c0+212] = MAX(S[c0][c0+212], S[c0+1][c0+212-1] + can_pair(RNA, c0, c0+212));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 786; c0 += 1)
    for (c1 = c0 + 213; c1 <= min(c0 + 425, 999); c1 += 1) {
      if (c0 + 424 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-213+c0] + S[-c0+c1-213+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][212+c0] + S[212+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 786; c0 += 1)
    S[c0][c0+213] = MAX(S[c0][c0+213], S[c0+1][c0+213-1] + can_pair(RNA, c0, c0+213));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 785; c0 += 1)
    for (c1 = c0 + 214; c1 <= min(c0 + 427, 999); c1 += 1) {
      if (c0 + 426 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-214+c0] + S[-c0+c1-214+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][213+c0] + S[213+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 785; c0 += 1)
    S[c0][c0+214] = MAX(S[c0][c0+214], S[c0+1][c0+214-1] + can_pair(RNA, c0, c0+214));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 784; c0 += 1)
    for (c1 = c0 + 215; c1 <= min(c0 + 429, 999); c1 += 1) {
      if (c0 + 428 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-215+c0] + S[-c0+c1-215+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][214+c0] + S[214+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 784; c0 += 1)
    S[c0][c0+215] = MAX(S[c0][c0+215], S[c0+1][c0+215-1] + can_pair(RNA, c0, c0+215));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 783; c0 += 1)
    for (c1 = c0 + 216; c1 <= min(c0 + 431, 999); c1 += 1) {
      if (c0 + 430 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-216+c0] + S[-c0+c1-216+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][215+c0] + S[215+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 783; c0 += 1)
    S[c0][c0+216] = MAX(S[c0][c0+216], S[c0+1][c0+216-1] + can_pair(RNA, c0, c0+216));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 782; c0 += 1)
    for (c1 = c0 + 217; c1 <= min(c0 + 433, 999); c1 += 1) {
      if (c0 + 432 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-217+c0] + S[-c0+c1-217+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][216+c0] + S[216+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 782; c0 += 1)
    S[c0][c0+217] = MAX(S[c0][c0+217], S[c0+1][c0+217-1] + can_pair(RNA, c0, c0+217));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 781; c0 += 1)
    for (c1 = c0 + 218; c1 <= min(c0 + 435, 999); c1 += 1) {
      if (c0 + 434 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-218+c0] + S[-c0+c1-218+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][217+c0] + S[217+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 781; c0 += 1)
    S[c0][c0+218] = MAX(S[c0][c0+218], S[c0+1][c0+218-1] + can_pair(RNA, c0, c0+218));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 780; c0 += 1)
    for (c1 = c0 + 219; c1 <= min(c0 + 437, 999); c1 += 1) {
      if (c0 + 436 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-219+c0] + S[-c0+c1-219+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][218+c0] + S[218+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 780; c0 += 1)
    S[c0][c0+219] = MAX(S[c0][c0+219], S[c0+1][c0+219-1] + can_pair(RNA, c0, c0+219));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 779; c0 += 1)
    for (c1 = c0 + 220; c1 <= min(c0 + 439, 999); c1 += 1) {
      if (c0 + 438 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-220+c0] + S[-c0+c1-220+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][219+c0] + S[219+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 779; c0 += 1)
    S[c0][c0+220] = MAX(S[c0][c0+220], S[c0+1][c0+220-1] + can_pair(RNA, c0, c0+220));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 778; c0 += 1)
    for (c1 = c0 + 221; c1 <= min(c0 + 441, 999); c1 += 1) {
      if (c0 + 440 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-221+c0] + S[-c0+c1-221+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][220+c0] + S[220+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 778; c0 += 1)
    S[c0][c0+221] = MAX(S[c0][c0+221], S[c0+1][c0+221-1] + can_pair(RNA, c0, c0+221));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 777; c0 += 1)
    for (c1 = c0 + 222; c1 <= min(c0 + 443, 999); c1 += 1) {
      if (c0 + 442 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-222+c0] + S[-c0+c1-222+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][221+c0] + S[221+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 777; c0 += 1)
    S[c0][c0+222] = MAX(S[c0][c0+222], S[c0+1][c0+222-1] + can_pair(RNA, c0, c0+222));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 776; c0 += 1)
    for (c1 = c0 + 223; c1 <= min(c0 + 445, 999); c1 += 1) {
      if (c0 + 444 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-223+c0] + S[-c0+c1-223+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][222+c0] + S[222+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 776; c0 += 1)
    S[c0][c0+223] = MAX(S[c0][c0+223], S[c0+1][c0+223-1] + can_pair(RNA, c0, c0+223));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 775; c0 += 1)
    for (c1 = c0 + 224; c1 <= min(c0 + 447, 999); c1 += 1) {
      if (c0 + 446 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-224+c0] + S[-c0+c1-224+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][223+c0] + S[223+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 775; c0 += 1)
    S[c0][c0+224] = MAX(S[c0][c0+224], S[c0+1][c0+224-1] + can_pair(RNA, c0, c0+224));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 774; c0 += 1)
    for (c1 = c0 + 225; c1 <= min(c0 + 449, 999); c1 += 1) {
      if (c0 + 448 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-225+c0] + S[-c0+c1-225+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][224+c0] + S[224+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 774; c0 += 1)
    S[c0][c0+225] = MAX(S[c0][c0+225], S[c0+1][c0+225-1] + can_pair(RNA, c0, c0+225));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 773; c0 += 1)
    for (c1 = c0 + 226; c1 <= min(c0 + 451, 999); c1 += 1) {
      if (c0 + 450 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-226+c0] + S[-c0+c1-226+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][225+c0] + S[225+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 773; c0 += 1)
    S[c0][c0+226] = MAX(S[c0][c0+226], S[c0+1][c0+226-1] + can_pair(RNA, c0, c0+226));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 772; c0 += 1)
    for (c1 = c0 + 227; c1 <= min(c0 + 453, 999); c1 += 1) {
      if (c0 + 452 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-227+c0] + S[-c0+c1-227+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][226+c0] + S[226+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 772; c0 += 1)
    S[c0][c0+227] = MAX(S[c0][c0+227], S[c0+1][c0+227-1] + can_pair(RNA, c0, c0+227));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 771; c0 += 1)
    for (c1 = c0 + 228; c1 <= min(c0 + 455, 999); c1 += 1) {
      if (c0 + 454 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-228+c0] + S[-c0+c1-228+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][227+c0] + S[227+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 771; c0 += 1)
    S[c0][c0+228] = MAX(S[c0][c0+228], S[c0+1][c0+228-1] + can_pair(RNA, c0, c0+228));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 770; c0 += 1)
    for (c1 = c0 + 229; c1 <= min(c0 + 457, 999); c1 += 1) {
      if (c0 + 456 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-229+c0] + S[-c0+c1-229+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][228+c0] + S[228+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 770; c0 += 1)
    S[c0][c0+229] = MAX(S[c0][c0+229], S[c0+1][c0+229-1] + can_pair(RNA, c0, c0+229));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 769; c0 += 1)
    for (c1 = c0 + 230; c1 <= min(c0 + 459, 999); c1 += 1) {
      if (c0 + 458 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-230+c0] + S[-c0+c1-230+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][229+c0] + S[229+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 769; c0 += 1)
    S[c0][c0+230] = MAX(S[c0][c0+230], S[c0+1][c0+230-1] + can_pair(RNA, c0, c0+230));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 768; c0 += 1)
    for (c1 = c0 + 231; c1 <= min(c0 + 461, 999); c1 += 1) {
      if (c0 + 460 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-231+c0] + S[-c0+c1-231+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][230+c0] + S[230+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 768; c0 += 1)
    S[c0][c0+231] = MAX(S[c0][c0+231], S[c0+1][c0+231-1] + can_pair(RNA, c0, c0+231));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 767; c0 += 1)
    for (c1 = c0 + 232; c1 <= min(c0 + 463, 999); c1 += 1) {
      if (c0 + 462 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-232+c0] + S[-c0+c1-232+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][231+c0] + S[231+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 767; c0 += 1)
    S[c0][c0+232] = MAX(S[c0][c0+232], S[c0+1][c0+232-1] + can_pair(RNA, c0, c0+232));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 766; c0 += 1)
    for (c1 = c0 + 233; c1 <= min(c0 + 465, 999); c1 += 1) {
      if (c0 + 464 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-233+c0] + S[-c0+c1-233+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][232+c0] + S[232+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 766; c0 += 1)
    S[c0][c0+233] = MAX(S[c0][c0+233], S[c0+1][c0+233-1] + can_pair(RNA, c0, c0+233));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 765; c0 += 1)
    for (c1 = c0 + 234; c1 <= min(c0 + 467, 999); c1 += 1) {
      if (c0 + 466 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-234+c0] + S[-c0+c1-234+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][233+c0] + S[233+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 765; c0 += 1)
    S[c0][c0+234] = MAX(S[c0][c0+234], S[c0+1][c0+234-1] + can_pair(RNA, c0, c0+234));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 764; c0 += 1)
    for (c1 = c0 + 235; c1 <= min(c0 + 469, 999); c1 += 1) {
      if (c0 + 468 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-235+c0] + S[-c0+c1-235+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][234+c0] + S[234+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 764; c0 += 1)
    S[c0][c0+235] = MAX(S[c0][c0+235], S[c0+1][c0+235-1] + can_pair(RNA, c0, c0+235));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 763; c0 += 1)
    for (c1 = c0 + 236; c1 <= min(c0 + 471, 999); c1 += 1) {
      if (c0 + 470 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-236+c0] + S[-c0+c1-236+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][235+c0] + S[235+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 763; c0 += 1)
    S[c0][c0+236] = MAX(S[c0][c0+236], S[c0+1][c0+236-1] + can_pair(RNA, c0, c0+236));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 762; c0 += 1)
    for (c1 = c0 + 237; c1 <= min(c0 + 473, 999); c1 += 1) {
      if (c0 + 472 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-237+c0] + S[-c0+c1-237+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][236+c0] + S[236+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 762; c0 += 1)
    S[c0][c0+237] = MAX(S[c0][c0+237], S[c0+1][c0+237-1] + can_pair(RNA, c0, c0+237));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 761; c0 += 1)
    for (c1 = c0 + 238; c1 <= min(c0 + 475, 999); c1 += 1) {
      if (c0 + 474 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-238+c0] + S[-c0+c1-238+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][237+c0] + S[237+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 761; c0 += 1)
    S[c0][c0+238] = MAX(S[c0][c0+238], S[c0+1][c0+238-1] + can_pair(RNA, c0, c0+238));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 760; c0 += 1)
    for (c1 = c0 + 239; c1 <= min(c0 + 477, 999); c1 += 1) {
      if (c0 + 476 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-239+c0] + S[-c0+c1-239+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][238+c0] + S[238+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 760; c0 += 1)
    S[c0][c0+239] = MAX(S[c0][c0+239], S[c0+1][c0+239-1] + can_pair(RNA, c0, c0+239));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 759; c0 += 1)
    for (c1 = c0 + 240; c1 <= min(c0 + 479, 999); c1 += 1) {
      if (c0 + 478 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-240+c0] + S[-c0+c1-240+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][239+c0] + S[239+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 759; c0 += 1)
    S[c0][c0+240] = MAX(S[c0][c0+240], S[c0+1][c0+240-1] + can_pair(RNA, c0, c0+240));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 758; c0 += 1)
    for (c1 = c0 + 241; c1 <= min(c0 + 481, 999); c1 += 1) {
      if (c0 + 480 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-241+c0] + S[-c0+c1-241+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][240+c0] + S[240+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 758; c0 += 1)
    S[c0][c0+241] = MAX(S[c0][c0+241], S[c0+1][c0+241-1] + can_pair(RNA, c0, c0+241));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 757; c0 += 1)
    for (c1 = c0 + 242; c1 <= min(c0 + 483, 999); c1 += 1) {
      if (c0 + 482 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-242+c0] + S[-c0+c1-242+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][241+c0] + S[241+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 757; c0 += 1)
    S[c0][c0+242] = MAX(S[c0][c0+242], S[c0+1][c0+242-1] + can_pair(RNA, c0, c0+242));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 756; c0 += 1)
    for (c1 = c0 + 243; c1 <= min(c0 + 485, 999); c1 += 1) {
      if (c0 + 484 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-243+c0] + S[-c0+c1-243+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][242+c0] + S[242+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 756; c0 += 1)
    S[c0][c0+243] = MAX(S[c0][c0+243], S[c0+1][c0+243-1] + can_pair(RNA, c0, c0+243));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 755; c0 += 1)
    for (c1 = c0 + 244; c1 <= min(c0 + 487, 999); c1 += 1) {
      if (c0 + 486 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-244+c0] + S[-c0+c1-244+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][243+c0] + S[243+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 755; c0 += 1)
    S[c0][c0+244] = MAX(S[c0][c0+244], S[c0+1][c0+244-1] + can_pair(RNA, c0, c0+244));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 754; c0 += 1)
    for (c1 = c0 + 245; c1 <= min(c0 + 489, 999); c1 += 1) {
      if (c0 + 488 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-245+c0] + S[-c0+c1-245+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][244+c0] + S[244+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 754; c0 += 1)
    S[c0][c0+245] = MAX(S[c0][c0+245], S[c0+1][c0+245-1] + can_pair(RNA, c0, c0+245));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 753; c0 += 1)
    for (c1 = c0 + 246; c1 <= min(c0 + 491, 999); c1 += 1) {
      if (c0 + 490 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-246+c0] + S[-c0+c1-246+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][245+c0] + S[245+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 753; c0 += 1)
    S[c0][c0+246] = MAX(S[c0][c0+246], S[c0+1][c0+246-1] + can_pair(RNA, c0, c0+246));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 752; c0 += 1)
    for (c1 = c0 + 247; c1 <= min(c0 + 493, 999); c1 += 1) {
      if (c0 + 492 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-247+c0] + S[-c0+c1-247+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][246+c0] + S[246+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 752; c0 += 1)
    S[c0][c0+247] = MAX(S[c0][c0+247], S[c0+1][c0+247-1] + can_pair(RNA, c0, c0+247));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 751; c0 += 1)
    for (c1 = c0 + 248; c1 <= min(c0 + 495, 999); c1 += 1) {
      if (c0 + 494 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-248+c0] + S[-c0+c1-248+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][247+c0] + S[247+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 751; c0 += 1)
    S[c0][c0+248] = MAX(S[c0][c0+248], S[c0+1][c0+248-1] + can_pair(RNA, c0, c0+248));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 750; c0 += 1)
    for (c1 = c0 + 249; c1 <= min(c0 + 497, 999); c1 += 1) {
      if (c0 + 496 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-249+c0] + S[-c0+c1-249+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][248+c0] + S[248+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 750; c0 += 1)
    S[c0][c0+249] = MAX(S[c0][c0+249], S[c0+1][c0+249-1] + can_pair(RNA, c0, c0+249));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 749; c0 += 1)
    for (c1 = c0 + 250; c1 <= min(c0 + 499, 999); c1 += 1) {
      if (c0 + 498 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-250+c0] + S[-c0+c1-250+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][249+c0] + S[249+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 749; c0 += 1)
    S[c0][c0+250] = MAX(S[c0][c0+250], S[c0+1][c0+250-1] + can_pair(RNA, c0, c0+250));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 748; c0 += 1)
    for (c1 = c0 + 251; c1 <= min(c0 + 501, 999); c1 += 1) {
      if (c0 + 500 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-251+c0] + S[-c0+c1-251+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][250+c0] + S[250+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 748; c0 += 1)
    S[c0][c0+251] = MAX(S[c0][c0+251], S[c0+1][c0+251-1] + can_pair(RNA, c0, c0+251));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 747; c0 += 1)
    for (c1 = c0 + 252; c1 <= min(c0 + 503, 999); c1 += 1) {
      if (c0 + 502 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-252+c0] + S[-c0+c1-252+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][251+c0] + S[251+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 747; c0 += 1)
    S[c0][c0+252] = MAX(S[c0][c0+252], S[c0+1][c0+252-1] + can_pair(RNA, c0, c0+252));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 746; c0 += 1)
    for (c1 = c0 + 253; c1 <= min(c0 + 505, 999); c1 += 1) {
      if (c0 + 504 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-253+c0] + S[-c0+c1-253+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][252+c0] + S[252+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 746; c0 += 1)
    S[c0][c0+253] = MAX(S[c0][c0+253], S[c0+1][c0+253-1] + can_pair(RNA, c0, c0+253));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 745; c0 += 1)
    for (c1 = c0 + 254; c1 <= min(c0 + 507, 999); c1 += 1) {
      if (c0 + 506 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-254+c0] + S[-c0+c1-254+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][253+c0] + S[253+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 745; c0 += 1)
    S[c0][c0+254] = MAX(S[c0][c0+254], S[c0+1][c0+254-1] + can_pair(RNA, c0, c0+254));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 744; c0 += 1)
    for (c1 = c0 + 255; c1 <= min(c0 + 509, 999); c1 += 1) {
      if (c0 + 508 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-255+c0] + S[-c0+c1-255+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][254+c0] + S[254+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 744; c0 += 1)
    S[c0][c0+255] = MAX(S[c0][c0+255], S[c0+1][c0+255-1] + can_pair(RNA, c0, c0+255));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 743; c0 += 1)
    for (c1 = c0 + 256; c1 <= min(c0 + 511, 999); c1 += 1) {
      if (c0 + 510 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-256+c0] + S[-c0+c1-256+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][255+c0] + S[255+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 743; c0 += 1)
    S[c0][c0+256] = MAX(S[c0][c0+256], S[c0+1][c0+256-1] + can_pair(RNA, c0, c0+256));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 742; c0 += 1)
    for (c1 = c0 + 257; c1 <= min(c0 + 513, 999); c1 += 1) {
      if (c0 + 512 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-257+c0] + S[-c0+c1-257+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][256+c0] + S[256+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 742; c0 += 1)
    S[c0][c0+257] = MAX(S[c0][c0+257], S[c0+1][c0+257-1] + can_pair(RNA, c0, c0+257));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 741; c0 += 1)
    for (c1 = c0 + 258; c1 <= min(c0 + 515, 999); c1 += 1) {
      if (c0 + 514 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-258+c0] + S[-c0+c1-258+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][257+c0] + S[257+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 741; c0 += 1)
    S[c0][c0+258] = MAX(S[c0][c0+258], S[c0+1][c0+258-1] + can_pair(RNA, c0, c0+258));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 740; c0 += 1)
    for (c1 = c0 + 259; c1 <= min(c0 + 517, 999); c1 += 1) {
      if (c0 + 516 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-259+c0] + S[-c0+c1-259+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][258+c0] + S[258+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 740; c0 += 1)
    S[c0][c0+259] = MAX(S[c0][c0+259], S[c0+1][c0+259-1] + can_pair(RNA, c0, c0+259));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 739; c0 += 1)
    for (c1 = c0 + 260; c1 <= min(c0 + 519, 999); c1 += 1) {
      if (c0 + 518 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-260+c0] + S[-c0+c1-260+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][259+c0] + S[259+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 739; c0 += 1)
    S[c0][c0+260] = MAX(S[c0][c0+260], S[c0+1][c0+260-1] + can_pair(RNA, c0, c0+260));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 738; c0 += 1)
    for (c1 = c0 + 261; c1 <= min(c0 + 521, 999); c1 += 1) {
      if (c0 + 520 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-261+c0] + S[-c0+c1-261+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][260+c0] + S[260+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 738; c0 += 1)
    S[c0][c0+261] = MAX(S[c0][c0+261], S[c0+1][c0+261-1] + can_pair(RNA, c0, c0+261));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 737; c0 += 1)
    for (c1 = c0 + 262; c1 <= min(c0 + 523, 999); c1 += 1) {
      if (c0 + 522 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-262+c0] + S[-c0+c1-262+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][261+c0] + S[261+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 737; c0 += 1)
    S[c0][c0+262] = MAX(S[c0][c0+262], S[c0+1][c0+262-1] + can_pair(RNA, c0, c0+262));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 736; c0 += 1)
    for (c1 = c0 + 263; c1 <= min(c0 + 525, 999); c1 += 1) {
      if (c0 + 524 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-263+c0] + S[-c0+c1-263+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][262+c0] + S[262+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 736; c0 += 1)
    S[c0][c0+263] = MAX(S[c0][c0+263], S[c0+1][c0+263-1] + can_pair(RNA, c0, c0+263));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 735; c0 += 1)
    for (c1 = c0 + 264; c1 <= min(c0 + 527, 999); c1 += 1) {
      if (c0 + 526 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-264+c0] + S[-c0+c1-264+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][263+c0] + S[263+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 735; c0 += 1)
    S[c0][c0+264] = MAX(S[c0][c0+264], S[c0+1][c0+264-1] + can_pair(RNA, c0, c0+264));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 734; c0 += 1)
    for (c1 = c0 + 265; c1 <= min(c0 + 529, 999); c1 += 1) {
      if (c0 + 528 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-265+c0] + S[-c0+c1-265+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][264+c0] + S[264+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 734; c0 += 1)
    S[c0][c0+265] = MAX(S[c0][c0+265], S[c0+1][c0+265-1] + can_pair(RNA, c0, c0+265));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 733; c0 += 1)
    for (c1 = c0 + 266; c1 <= min(c0 + 531, 999); c1 += 1) {
      if (c0 + 530 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-266+c0] + S[-c0+c1-266+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][265+c0] + S[265+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 733; c0 += 1)
    S[c0][c0+266] = MAX(S[c0][c0+266], S[c0+1][c0+266-1] + can_pair(RNA, c0, c0+266));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 732; c0 += 1)
    for (c1 = c0 + 267; c1 <= min(c0 + 533, 999); c1 += 1) {
      if (c0 + 532 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-267+c0] + S[-c0+c1-267+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][266+c0] + S[266+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 732; c0 += 1)
    S[c0][c0+267] = MAX(S[c0][c0+267], S[c0+1][c0+267-1] + can_pair(RNA, c0, c0+267));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 731; c0 += 1)
    for (c1 = c0 + 268; c1 <= min(c0 + 535, 999); c1 += 1) {
      if (c0 + 534 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-268+c0] + S[-c0+c1-268+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][267+c0] + S[267+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 731; c0 += 1)
    S[c0][c0+268] = MAX(S[c0][c0+268], S[c0+1][c0+268-1] + can_pair(RNA, c0, c0+268));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 730; c0 += 1)
    for (c1 = c0 + 269; c1 <= min(c0 + 537, 999); c1 += 1) {
      if (c0 + 536 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-269+c0] + S[-c0+c1-269+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][268+c0] + S[268+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 730; c0 += 1)
    S[c0][c0+269] = MAX(S[c0][c0+269], S[c0+1][c0+269-1] + can_pair(RNA, c0, c0+269));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 729; c0 += 1)
    for (c1 = c0 + 270; c1 <= min(c0 + 539, 999); c1 += 1) {
      if (c0 + 538 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-270+c0] + S[-c0+c1-270+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][269+c0] + S[269+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 729; c0 += 1)
    S[c0][c0+270] = MAX(S[c0][c0+270], S[c0+1][c0+270-1] + can_pair(RNA, c0, c0+270));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 728; c0 += 1)
    for (c1 = c0 + 271; c1 <= min(c0 + 541, 999); c1 += 1) {
      if (c0 + 540 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-271+c0] + S[-c0+c1-271+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][270+c0] + S[270+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 728; c0 += 1)
    S[c0][c0+271] = MAX(S[c0][c0+271], S[c0+1][c0+271-1] + can_pair(RNA, c0, c0+271));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 727; c0 += 1)
    for (c1 = c0 + 272; c1 <= min(c0 + 543, 999); c1 += 1) {
      if (c0 + 542 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-272+c0] + S[-c0+c1-272+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][271+c0] + S[271+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 727; c0 += 1)
    S[c0][c0+272] = MAX(S[c0][c0+272], S[c0+1][c0+272-1] + can_pair(RNA, c0, c0+272));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 726; c0 += 1)
    for (c1 = c0 + 273; c1 <= min(c0 + 545, 999); c1 += 1) {
      if (c0 + 544 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-273+c0] + S[-c0+c1-273+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][272+c0] + S[272+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 726; c0 += 1)
    S[c0][c0+273] = MAX(S[c0][c0+273], S[c0+1][c0+273-1] + can_pair(RNA, c0, c0+273));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 725; c0 += 1)
    for (c1 = c0 + 274; c1 <= min(c0 + 547, 999); c1 += 1) {
      if (c0 + 546 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-274+c0] + S[-c0+c1-274+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][273+c0] + S[273+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 725; c0 += 1)
    S[c0][c0+274] = MAX(S[c0][c0+274], S[c0+1][c0+274-1] + can_pair(RNA, c0, c0+274));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 724; c0 += 1)
    for (c1 = c0 + 275; c1 <= min(c0 + 549, 999); c1 += 1) {
      if (c0 + 548 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-275+c0] + S[-c0+c1-275+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][274+c0] + S[274+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 724; c0 += 1)
    S[c0][c0+275] = MAX(S[c0][c0+275], S[c0+1][c0+275-1] + can_pair(RNA, c0, c0+275));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 723; c0 += 1)
    for (c1 = c0 + 276; c1 <= min(c0 + 551, 999); c1 += 1) {
      if (c0 + 550 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-276+c0] + S[-c0+c1-276+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][275+c0] + S[275+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 723; c0 += 1)
    S[c0][c0+276] = MAX(S[c0][c0+276], S[c0+1][c0+276-1] + can_pair(RNA, c0, c0+276));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 722; c0 += 1)
    for (c1 = c0 + 277; c1 <= min(c0 + 553, 999); c1 += 1) {
      if (c0 + 552 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-277+c0] + S[-c0+c1-277+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][276+c0] + S[276+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 722; c0 += 1)
    S[c0][c0+277] = MAX(S[c0][c0+277], S[c0+1][c0+277-1] + can_pair(RNA, c0, c0+277));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 721; c0 += 1)
    for (c1 = c0 + 278; c1 <= min(c0 + 555, 999); c1 += 1) {
      if (c0 + 554 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-278+c0] + S[-c0+c1-278+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][277+c0] + S[277+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 721; c0 += 1)
    S[c0][c0+278] = MAX(S[c0][c0+278], S[c0+1][c0+278-1] + can_pair(RNA, c0, c0+278));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 720; c0 += 1)
    for (c1 = c0 + 279; c1 <= min(c0 + 557, 999); c1 += 1) {
      if (c0 + 556 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-279+c0] + S[-c0+c1-279+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][278+c0] + S[278+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 720; c0 += 1)
    S[c0][c0+279] = MAX(S[c0][c0+279], S[c0+1][c0+279-1] + can_pair(RNA, c0, c0+279));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 719; c0 += 1)
    for (c1 = c0 + 280; c1 <= min(c0 + 559, 999); c1 += 1) {
      if (c0 + 558 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-280+c0] + S[-c0+c1-280+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][279+c0] + S[279+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 719; c0 += 1)
    S[c0][c0+280] = MAX(S[c0][c0+280], S[c0+1][c0+280-1] + can_pair(RNA, c0, c0+280));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 718; c0 += 1)
    for (c1 = c0 + 281; c1 <= min(c0 + 561, 999); c1 += 1) {
      if (c0 + 560 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-281+c0] + S[-c0+c1-281+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][280+c0] + S[280+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 718; c0 += 1)
    S[c0][c0+281] = MAX(S[c0][c0+281], S[c0+1][c0+281-1] + can_pair(RNA, c0, c0+281));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 717; c0 += 1)
    for (c1 = c0 + 282; c1 <= min(c0 + 563, 999); c1 += 1) {
      if (c0 + 562 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-282+c0] + S[-c0+c1-282+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][281+c0] + S[281+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 717; c0 += 1)
    S[c0][c0+282] = MAX(S[c0][c0+282], S[c0+1][c0+282-1] + can_pair(RNA, c0, c0+282));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 716; c0 += 1)
    for (c1 = c0 + 283; c1 <= min(c0 + 565, 999); c1 += 1) {
      if (c0 + 564 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-283+c0] + S[-c0+c1-283+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][282+c0] + S[282+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 716; c0 += 1)
    S[c0][c0+283] = MAX(S[c0][c0+283], S[c0+1][c0+283-1] + can_pair(RNA, c0, c0+283));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 715; c0 += 1)
    for (c1 = c0 + 284; c1 <= min(c0 + 567, 999); c1 += 1) {
      if (c0 + 566 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-284+c0] + S[-c0+c1-284+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][283+c0] + S[283+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 715; c0 += 1)
    S[c0][c0+284] = MAX(S[c0][c0+284], S[c0+1][c0+284-1] + can_pair(RNA, c0, c0+284));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 714; c0 += 1)
    for (c1 = c0 + 285; c1 <= min(c0 + 569, 999); c1 += 1) {
      if (c0 + 568 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-285+c0] + S[-c0+c1-285+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][284+c0] + S[284+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 714; c0 += 1)
    S[c0][c0+285] = MAX(S[c0][c0+285], S[c0+1][c0+285-1] + can_pair(RNA, c0, c0+285));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 713; c0 += 1)
    for (c1 = c0 + 286; c1 <= min(c0 + 571, 999); c1 += 1) {
      if (c0 + 570 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-286+c0] + S[-c0+c1-286+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][285+c0] + S[285+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 713; c0 += 1)
    S[c0][c0+286] = MAX(S[c0][c0+286], S[c0+1][c0+286-1] + can_pair(RNA, c0, c0+286));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 712; c0 += 1)
    for (c1 = c0 + 287; c1 <= min(c0 + 573, 999); c1 += 1) {
      if (c0 + 572 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-287+c0] + S[-c0+c1-287+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][286+c0] + S[286+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 712; c0 += 1)
    S[c0][c0+287] = MAX(S[c0][c0+287], S[c0+1][c0+287-1] + can_pair(RNA, c0, c0+287));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 711; c0 += 1)
    for (c1 = c0 + 288; c1 <= min(c0 + 575, 999); c1 += 1) {
      if (c0 + 574 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-288+c0] + S[-c0+c1-288+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][287+c0] + S[287+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 711; c0 += 1)
    S[c0][c0+288] = MAX(S[c0][c0+288], S[c0+1][c0+288-1] + can_pair(RNA, c0, c0+288));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 710; c0 += 1)
    for (c1 = c0 + 289; c1 <= min(c0 + 577, 999); c1 += 1) {
      if (c0 + 576 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-289+c0] + S[-c0+c1-289+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][288+c0] + S[288+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 710; c0 += 1)
    S[c0][c0+289] = MAX(S[c0][c0+289], S[c0+1][c0+289-1] + can_pair(RNA, c0, c0+289));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 709; c0 += 1)
    for (c1 = c0 + 290; c1 <= min(c0 + 579, 999); c1 += 1) {
      if (c0 + 578 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-290+c0] + S[-c0+c1-290+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][289+c0] + S[289+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 709; c0 += 1)
    S[c0][c0+290] = MAX(S[c0][c0+290], S[c0+1][c0+290-1] + can_pair(RNA, c0, c0+290));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 708; c0 += 1)
    for (c1 = c0 + 291; c1 <= min(c0 + 581, 999); c1 += 1) {
      if (c0 + 580 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-291+c0] + S[-c0+c1-291+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][290+c0] + S[290+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 708; c0 += 1)
    S[c0][c0+291] = MAX(S[c0][c0+291], S[c0+1][c0+291-1] + can_pair(RNA, c0, c0+291));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 707; c0 += 1)
    for (c1 = c0 + 292; c1 <= min(c0 + 583, 999); c1 += 1) {
      if (c0 + 582 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-292+c0] + S[-c0+c1-292+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][291+c0] + S[291+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 707; c0 += 1)
    S[c0][c0+292] = MAX(S[c0][c0+292], S[c0+1][c0+292-1] + can_pair(RNA, c0, c0+292));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 706; c0 += 1)
    for (c1 = c0 + 293; c1 <= min(c0 + 585, 999); c1 += 1) {
      if (c0 + 584 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-293+c0] + S[-c0+c1-293+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][292+c0] + S[292+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 706; c0 += 1)
    S[c0][c0+293] = MAX(S[c0][c0+293], S[c0+1][c0+293-1] + can_pair(RNA, c0, c0+293));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 705; c0 += 1)
    for (c1 = c0 + 294; c1 <= min(c0 + 587, 999); c1 += 1) {
      if (c0 + 586 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-294+c0] + S[-c0+c1-294+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][293+c0] + S[293+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 705; c0 += 1)
    S[c0][c0+294] = MAX(S[c0][c0+294], S[c0+1][c0+294-1] + can_pair(RNA, c0, c0+294));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 704; c0 += 1)
    for (c1 = c0 + 295; c1 <= min(c0 + 589, 999); c1 += 1) {
      if (c0 + 588 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-295+c0] + S[-c0+c1-295+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][294+c0] + S[294+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 704; c0 += 1)
    S[c0][c0+295] = MAX(S[c0][c0+295], S[c0+1][c0+295-1] + can_pair(RNA, c0, c0+295));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 703; c0 += 1)
    for (c1 = c0 + 296; c1 <= min(c0 + 591, 999); c1 += 1) {
      if (c0 + 590 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-296+c0] + S[-c0+c1-296+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][295+c0] + S[295+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 703; c0 += 1)
    S[c0][c0+296] = MAX(S[c0][c0+296], S[c0+1][c0+296-1] + can_pair(RNA, c0, c0+296));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 702; c0 += 1)
    for (c1 = c0 + 297; c1 <= min(c0 + 593, 999); c1 += 1) {
      if (c0 + 592 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-297+c0] + S[-c0+c1-297+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][296+c0] + S[296+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 702; c0 += 1)
    S[c0][c0+297] = MAX(S[c0][c0+297], S[c0+1][c0+297-1] + can_pair(RNA, c0, c0+297));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 701; c0 += 1)
    for (c1 = c0 + 298; c1 <= min(c0 + 595, 999); c1 += 1) {
      if (c0 + 594 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-298+c0] + S[-c0+c1-298+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][297+c0] + S[297+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 701; c0 += 1)
    S[c0][c0+298] = MAX(S[c0][c0+298], S[c0+1][c0+298-1] + can_pair(RNA, c0, c0+298));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 700; c0 += 1)
    for (c1 = c0 + 299; c1 <= min(c0 + 597, 999); c1 += 1) {
      if (c0 + 596 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-299+c0] + S[-c0+c1-299+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][298+c0] + S[298+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 700; c0 += 1)
    S[c0][c0+299] = MAX(S[c0][c0+299], S[c0+1][c0+299-1] + can_pair(RNA, c0, c0+299));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 699; c0 += 1)
    for (c1 = c0 + 300; c1 <= min(c0 + 599, 999); c1 += 1) {
      if (c0 + 598 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-300+c0] + S[-c0+c1-300+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][299+c0] + S[299+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 699; c0 += 1)
    S[c0][c0+300] = MAX(S[c0][c0+300], S[c0+1][c0+300-1] + can_pair(RNA, c0, c0+300));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 698; c0 += 1)
    for (c1 = c0 + 301; c1 <= min(c0 + 601, 999); c1 += 1) {
      if (c0 + 600 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-301+c0] + S[-c0+c1-301+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][300+c0] + S[300+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 698; c0 += 1)
    S[c0][c0+301] = MAX(S[c0][c0+301], S[c0+1][c0+301-1] + can_pair(RNA, c0, c0+301));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 697; c0 += 1)
    for (c1 = c0 + 302; c1 <= min(c0 + 603, 999); c1 += 1) {
      if (c0 + 602 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-302+c0] + S[-c0+c1-302+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][301+c0] + S[301+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 697; c0 += 1)
    S[c0][c0+302] = MAX(S[c0][c0+302], S[c0+1][c0+302-1] + can_pair(RNA, c0, c0+302));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 696; c0 += 1)
    for (c1 = c0 + 303; c1 <= min(c0 + 605, 999); c1 += 1) {
      if (c0 + 604 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-303+c0] + S[-c0+c1-303+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][302+c0] + S[302+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 696; c0 += 1)
    S[c0][c0+303] = MAX(S[c0][c0+303], S[c0+1][c0+303-1] + can_pair(RNA, c0, c0+303));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 695; c0 += 1)
    for (c1 = c0 + 304; c1 <= min(c0 + 607, 999); c1 += 1) {
      if (c0 + 606 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-304+c0] + S[-c0+c1-304+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][303+c0] + S[303+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 695; c0 += 1)
    S[c0][c0+304] = MAX(S[c0][c0+304], S[c0+1][c0+304-1] + can_pair(RNA, c0, c0+304));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 694; c0 += 1)
    for (c1 = c0 + 305; c1 <= min(c0 + 609, 999); c1 += 1) {
      if (c0 + 608 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-305+c0] + S[-c0+c1-305+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][304+c0] + S[304+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 694; c0 += 1)
    S[c0][c0+305] = MAX(S[c0][c0+305], S[c0+1][c0+305-1] + can_pair(RNA, c0, c0+305));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 693; c0 += 1)
    for (c1 = c0 + 306; c1 <= min(c0 + 611, 999); c1 += 1) {
      if (c0 + 610 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-306+c0] + S[-c0+c1-306+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][305+c0] + S[305+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 693; c0 += 1)
    S[c0][c0+306] = MAX(S[c0][c0+306], S[c0+1][c0+306-1] + can_pair(RNA, c0, c0+306));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 692; c0 += 1)
    for (c1 = c0 + 307; c1 <= min(c0 + 613, 999); c1 += 1) {
      if (c0 + 612 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-307+c0] + S[-c0+c1-307+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][306+c0] + S[306+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 692; c0 += 1)
    S[c0][c0+307] = MAX(S[c0][c0+307], S[c0+1][c0+307-1] + can_pair(RNA, c0, c0+307));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 691; c0 += 1)
    for (c1 = c0 + 308; c1 <= min(c0 + 615, 999); c1 += 1) {
      if (c0 + 614 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-308+c0] + S[-c0+c1-308+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][307+c0] + S[307+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 691; c0 += 1)
    S[c0][c0+308] = MAX(S[c0][c0+308], S[c0+1][c0+308-1] + can_pair(RNA, c0, c0+308));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 690; c0 += 1)
    for (c1 = c0 + 309; c1 <= min(c0 + 617, 999); c1 += 1) {
      if (c0 + 616 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-309+c0] + S[-c0+c1-309+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][308+c0] + S[308+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 690; c0 += 1)
    S[c0][c0+309] = MAX(S[c0][c0+309], S[c0+1][c0+309-1] + can_pair(RNA, c0, c0+309));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 689; c0 += 1)
    for (c1 = c0 + 310; c1 <= min(c0 + 619, 999); c1 += 1) {
      if (c0 + 618 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-310+c0] + S[-c0+c1-310+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][309+c0] + S[309+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 689; c0 += 1)
    S[c0][c0+310] = MAX(S[c0][c0+310], S[c0+1][c0+310-1] + can_pair(RNA, c0, c0+310));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 688; c0 += 1)
    for (c1 = c0 + 311; c1 <= min(c0 + 621, 999); c1 += 1) {
      if (c0 + 620 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-311+c0] + S[-c0+c1-311+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][310+c0] + S[310+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 688; c0 += 1)
    S[c0][c0+311] = MAX(S[c0][c0+311], S[c0+1][c0+311-1] + can_pair(RNA, c0, c0+311));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 687; c0 += 1)
    for (c1 = c0 + 312; c1 <= min(c0 + 623, 999); c1 += 1) {
      if (c0 + 622 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-312+c0] + S[-c0+c1-312+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][311+c0] + S[311+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 687; c0 += 1)
    S[c0][c0+312] = MAX(S[c0][c0+312], S[c0+1][c0+312-1] + can_pair(RNA, c0, c0+312));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 686; c0 += 1)
    for (c1 = c0 + 313; c1 <= min(c0 + 625, 999); c1 += 1) {
      if (c0 + 624 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-313+c0] + S[-c0+c1-313+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][312+c0] + S[312+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 686; c0 += 1)
    S[c0][c0+313] = MAX(S[c0][c0+313], S[c0+1][c0+313-1] + can_pair(RNA, c0, c0+313));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 685; c0 += 1)
    for (c1 = c0 + 314; c1 <= min(c0 + 627, 999); c1 += 1) {
      if (c0 + 626 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-314+c0] + S[-c0+c1-314+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][313+c0] + S[313+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 685; c0 += 1)
    S[c0][c0+314] = MAX(S[c0][c0+314], S[c0+1][c0+314-1] + can_pair(RNA, c0, c0+314));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 684; c0 += 1)
    for (c1 = c0 + 315; c1 <= min(c0 + 629, 999); c1 += 1) {
      if (c0 + 628 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-315+c0] + S[-c0+c1-315+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][314+c0] + S[314+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 684; c0 += 1)
    S[c0][c0+315] = MAX(S[c0][c0+315], S[c0+1][c0+315-1] + can_pair(RNA, c0, c0+315));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 683; c0 += 1)
    for (c1 = c0 + 316; c1 <= min(c0 + 631, 999); c1 += 1) {
      if (c0 + 630 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-316+c0] + S[-c0+c1-316+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][315+c0] + S[315+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 683; c0 += 1)
    S[c0][c0+316] = MAX(S[c0][c0+316], S[c0+1][c0+316-1] + can_pair(RNA, c0, c0+316));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 682; c0 += 1)
    for (c1 = c0 + 317; c1 <= min(c0 + 633, 999); c1 += 1) {
      if (c0 + 632 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-317+c0] + S[-c0+c1-317+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][316+c0] + S[316+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 682; c0 += 1)
    S[c0][c0+317] = MAX(S[c0][c0+317], S[c0+1][c0+317-1] + can_pair(RNA, c0, c0+317));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 681; c0 += 1)
    for (c1 = c0 + 318; c1 <= min(c0 + 635, 999); c1 += 1) {
      if (c0 + 634 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-318+c0] + S[-c0+c1-318+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][317+c0] + S[317+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 681; c0 += 1)
    S[c0][c0+318] = MAX(S[c0][c0+318], S[c0+1][c0+318-1] + can_pair(RNA, c0, c0+318));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 680; c0 += 1)
    for (c1 = c0 + 319; c1 <= min(c0 + 637, 999); c1 += 1) {
      if (c0 + 636 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-319+c0] + S[-c0+c1-319+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][318+c0] + S[318+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 680; c0 += 1)
    S[c0][c0+319] = MAX(S[c0][c0+319], S[c0+1][c0+319-1] + can_pair(RNA, c0, c0+319));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 679; c0 += 1)
    for (c1 = c0 + 320; c1 <= min(c0 + 639, 999); c1 += 1) {
      if (c0 + 638 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-320+c0] + S[-c0+c1-320+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][319+c0] + S[319+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 679; c0 += 1)
    S[c0][c0+320] = MAX(S[c0][c0+320], S[c0+1][c0+320-1] + can_pair(RNA, c0, c0+320));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 678; c0 += 1)
    for (c1 = c0 + 321; c1 <= min(c0 + 641, 999); c1 += 1) {
      if (c0 + 640 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-321+c0] + S[-c0+c1-321+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][320+c0] + S[320+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 678; c0 += 1)
    S[c0][c0+321] = MAX(S[c0][c0+321], S[c0+1][c0+321-1] + can_pair(RNA, c0, c0+321));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 677; c0 += 1)
    for (c1 = c0 + 322; c1 <= min(c0 + 643, 999); c1 += 1) {
      if (c0 + 642 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-322+c0] + S[-c0+c1-322+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][321+c0] + S[321+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 677; c0 += 1)
    S[c0][c0+322] = MAX(S[c0][c0+322], S[c0+1][c0+322-1] + can_pair(RNA, c0, c0+322));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 676; c0 += 1)
    for (c1 = c0 + 323; c1 <= min(c0 + 645, 999); c1 += 1) {
      if (c0 + 644 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-323+c0] + S[-c0+c1-323+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][322+c0] + S[322+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 676; c0 += 1)
    S[c0][c0+323] = MAX(S[c0][c0+323], S[c0+1][c0+323-1] + can_pair(RNA, c0, c0+323));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 675; c0 += 1)
    for (c1 = c0 + 324; c1 <= min(c0 + 647, 999); c1 += 1) {
      if (c0 + 646 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-324+c0] + S[-c0+c1-324+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][323+c0] + S[323+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 675; c0 += 1)
    S[c0][c0+324] = MAX(S[c0][c0+324], S[c0+1][c0+324-1] + can_pair(RNA, c0, c0+324));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 674; c0 += 1)
    for (c1 = c0 + 325; c1 <= min(c0 + 649, 999); c1 += 1) {
      if (c0 + 648 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-325+c0] + S[-c0+c1-325+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][324+c0] + S[324+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 674; c0 += 1)
    S[c0][c0+325] = MAX(S[c0][c0+325], S[c0+1][c0+325-1] + can_pair(RNA, c0, c0+325));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 673; c0 += 1)
    for (c1 = c0 + 326; c1 <= min(c0 + 651, 999); c1 += 1) {
      if (c0 + 650 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-326+c0] + S[-c0+c1-326+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][325+c0] + S[325+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 673; c0 += 1)
    S[c0][c0+326] = MAX(S[c0][c0+326], S[c0+1][c0+326-1] + can_pair(RNA, c0, c0+326));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 672; c0 += 1)
    for (c1 = c0 + 327; c1 <= min(c0 + 653, 999); c1 += 1) {
      if (c0 + 652 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-327+c0] + S[-c0+c1-327+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][326+c0] + S[326+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 672; c0 += 1)
    S[c0][c0+327] = MAX(S[c0][c0+327], S[c0+1][c0+327-1] + can_pair(RNA, c0, c0+327));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 671; c0 += 1)
    for (c1 = c0 + 328; c1 <= min(c0 + 655, 999); c1 += 1) {
      if (c0 + 654 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-328+c0] + S[-c0+c1-328+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][327+c0] + S[327+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 671; c0 += 1)
    S[c0][c0+328] = MAX(S[c0][c0+328], S[c0+1][c0+328-1] + can_pair(RNA, c0, c0+328));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 670; c0 += 1)
    for (c1 = c0 + 329; c1 <= min(c0 + 657, 999); c1 += 1) {
      if (c0 + 656 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-329+c0] + S[-c0+c1-329+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][328+c0] + S[328+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 670; c0 += 1)
    S[c0][c0+329] = MAX(S[c0][c0+329], S[c0+1][c0+329-1] + can_pair(RNA, c0, c0+329));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 669; c0 += 1)
    for (c1 = c0 + 330; c1 <= min(c0 + 659, 999); c1 += 1) {
      if (c0 + 658 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-330+c0] + S[-c0+c1-330+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][329+c0] + S[329+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 669; c0 += 1)
    S[c0][c0+330] = MAX(S[c0][c0+330], S[c0+1][c0+330-1] + can_pair(RNA, c0, c0+330));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 668; c0 += 1)
    for (c1 = c0 + 331; c1 <= min(c0 + 661, 999); c1 += 1) {
      if (c0 + 660 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-331+c0] + S[-c0+c1-331+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][330+c0] + S[330+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 668; c0 += 1)
    S[c0][c0+331] = MAX(S[c0][c0+331], S[c0+1][c0+331-1] + can_pair(RNA, c0, c0+331));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 667; c0 += 1)
    for (c1 = c0 + 332; c1 <= min(c0 + 663, 999); c1 += 1) {
      if (c0 + 662 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-332+c0] + S[-c0+c1-332+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][331+c0] + S[331+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 667; c0 += 1)
    S[c0][c0+332] = MAX(S[c0][c0+332], S[c0+1][c0+332-1] + can_pair(RNA, c0, c0+332));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 666; c0 += 1)
    for (c1 = c0 + 333; c1 <= min(c0 + 665, 999); c1 += 1) {
      if (c0 + 664 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-333+c0] + S[-c0+c1-333+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][332+c0] + S[332+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 666; c0 += 1)
    S[c0][c0+333] = MAX(S[c0][c0+333], S[c0+1][c0+333-1] + can_pair(RNA, c0, c0+333));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 665; c0 += 1)
    for (c1 = c0 + 334; c1 <= min(c0 + 667, 999); c1 += 1) {
      if (c0 + 666 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-334+c0] + S[-c0+c1-334+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][333+c0] + S[333+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 665; c0 += 1)
    S[c0][c0+334] = MAX(S[c0][c0+334], S[c0+1][c0+334-1] + can_pair(RNA, c0, c0+334));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 664; c0 += 1)
    for (c1 = c0 + 335; c1 <= min(c0 + 669, 999); c1 += 1) {
      if (c0 + 668 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-335+c0] + S[-c0+c1-335+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][334+c0] + S[334+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 664; c0 += 1)
    S[c0][c0+335] = MAX(S[c0][c0+335], S[c0+1][c0+335-1] + can_pair(RNA, c0, c0+335));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 663; c0 += 1)
    for (c1 = c0 + 336; c1 <= min(c0 + 671, 999); c1 += 1) {
      if (c0 + 670 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-336+c0] + S[-c0+c1-336+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][335+c0] + S[335+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 663; c0 += 1)
    S[c0][c0+336] = MAX(S[c0][c0+336], S[c0+1][c0+336-1] + can_pair(RNA, c0, c0+336));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 662; c0 += 1)
    for (c1 = c0 + 337; c1 <= min(c0 + 673, 999); c1 += 1) {
      if (c0 + 672 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-337+c0] + S[-c0+c1-337+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][336+c0] + S[336+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 662; c0 += 1)
    S[c0][c0+337] = MAX(S[c0][c0+337], S[c0+1][c0+337-1] + can_pair(RNA, c0, c0+337));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 661; c0 += 1)
    for (c1 = c0 + 338; c1 <= min(c0 + 675, 999); c1 += 1) {
      if (c0 + 674 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-338+c0] + S[-c0+c1-338+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][337+c0] + S[337+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 661; c0 += 1)
    S[c0][c0+338] = MAX(S[c0][c0+338], S[c0+1][c0+338-1] + can_pair(RNA, c0, c0+338));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 660; c0 += 1)
    for (c1 = c0 + 339; c1 <= min(c0 + 677, 999); c1 += 1) {
      if (c0 + 676 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-339+c0] + S[-c0+c1-339+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][338+c0] + S[338+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 660; c0 += 1)
    S[c0][c0+339] = MAX(S[c0][c0+339], S[c0+1][c0+339-1] + can_pair(RNA, c0, c0+339));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 659; c0 += 1)
    for (c1 = c0 + 340; c1 <= min(c0 + 679, 999); c1 += 1) {
      if (c0 + 678 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-340+c0] + S[-c0+c1-340+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][339+c0] + S[339+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 659; c0 += 1)
    S[c0][c0+340] = MAX(S[c0][c0+340], S[c0+1][c0+340-1] + can_pair(RNA, c0, c0+340));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 658; c0 += 1)
    for (c1 = c0 + 341; c1 <= min(c0 + 681, 999); c1 += 1) {
      if (c0 + 680 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-341+c0] + S[-c0+c1-341+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][340+c0] + S[340+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 658; c0 += 1)
    S[c0][c0+341] = MAX(S[c0][c0+341], S[c0+1][c0+341-1] + can_pair(RNA, c0, c0+341));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 657; c0 += 1)
    for (c1 = c0 + 342; c1 <= min(c0 + 683, 999); c1 += 1) {
      if (c0 + 682 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-342+c0] + S[-c0+c1-342+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][341+c0] + S[341+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 657; c0 += 1)
    S[c0][c0+342] = MAX(S[c0][c0+342], S[c0+1][c0+342-1] + can_pair(RNA, c0, c0+342));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 656; c0 += 1)
    for (c1 = c0 + 343; c1 <= min(c0 + 685, 999); c1 += 1) {
      if (c0 + 684 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-343+c0] + S[-c0+c1-343+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][342+c0] + S[342+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 656; c0 += 1)
    S[c0][c0+343] = MAX(S[c0][c0+343], S[c0+1][c0+343-1] + can_pair(RNA, c0, c0+343));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 655; c0 += 1)
    for (c1 = c0 + 344; c1 <= min(c0 + 687, 999); c1 += 1) {
      if (c0 + 686 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-344+c0] + S[-c0+c1-344+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][343+c0] + S[343+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 655; c0 += 1)
    S[c0][c0+344] = MAX(S[c0][c0+344], S[c0+1][c0+344-1] + can_pair(RNA, c0, c0+344));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 654; c0 += 1)
    for (c1 = c0 + 345; c1 <= min(c0 + 689, 999); c1 += 1) {
      if (c0 + 688 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-345+c0] + S[-c0+c1-345+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][344+c0] + S[344+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 654; c0 += 1)
    S[c0][c0+345] = MAX(S[c0][c0+345], S[c0+1][c0+345-1] + can_pair(RNA, c0, c0+345));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 653; c0 += 1)
    for (c1 = c0 + 346; c1 <= min(c0 + 691, 999); c1 += 1) {
      if (c0 + 690 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-346+c0] + S[-c0+c1-346+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][345+c0] + S[345+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 653; c0 += 1)
    S[c0][c0+346] = MAX(S[c0][c0+346], S[c0+1][c0+346-1] + can_pair(RNA, c0, c0+346));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 652; c0 += 1)
    for (c1 = c0 + 347; c1 <= min(c0 + 693, 999); c1 += 1) {
      if (c0 + 692 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-347+c0] + S[-c0+c1-347+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][346+c0] + S[346+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 652; c0 += 1)
    S[c0][c0+347] = MAX(S[c0][c0+347], S[c0+1][c0+347-1] + can_pair(RNA, c0, c0+347));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 651; c0 += 1)
    for (c1 = c0 + 348; c1 <= min(c0 + 695, 999); c1 += 1) {
      if (c0 + 694 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-348+c0] + S[-c0+c1-348+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][347+c0] + S[347+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 651; c0 += 1)
    S[c0][c0+348] = MAX(S[c0][c0+348], S[c0+1][c0+348-1] + can_pair(RNA, c0, c0+348));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 650; c0 += 1)
    for (c1 = c0 + 349; c1 <= min(c0 + 697, 999); c1 += 1) {
      if (c0 + 696 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-349+c0] + S[-c0+c1-349+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][348+c0] + S[348+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 650; c0 += 1)
    S[c0][c0+349] = MAX(S[c0][c0+349], S[c0+1][c0+349-1] + can_pair(RNA, c0, c0+349));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 649; c0 += 1)
    for (c1 = c0 + 350; c1 <= min(c0 + 699, 999); c1 += 1) {
      if (c0 + 698 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-350+c0] + S[-c0+c1-350+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][349+c0] + S[349+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 649; c0 += 1)
    S[c0][c0+350] = MAX(S[c0][c0+350], S[c0+1][c0+350-1] + can_pair(RNA, c0, c0+350));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 648; c0 += 1)
    for (c1 = c0 + 351; c1 <= min(c0 + 701, 999); c1 += 1) {
      if (c0 + 700 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-351+c0] + S[-c0+c1-351+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][350+c0] + S[350+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 648; c0 += 1)
    S[c0][c0+351] = MAX(S[c0][c0+351], S[c0+1][c0+351-1] + can_pair(RNA, c0, c0+351));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 647; c0 += 1)
    for (c1 = c0 + 352; c1 <= min(c0 + 703, 999); c1 += 1) {
      if (c0 + 702 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-352+c0] + S[-c0+c1-352+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][351+c0] + S[351+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 647; c0 += 1)
    S[c0][c0+352] = MAX(S[c0][c0+352], S[c0+1][c0+352-1] + can_pair(RNA, c0, c0+352));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 646; c0 += 1)
    for (c1 = c0 + 353; c1 <= min(c0 + 705, 999); c1 += 1) {
      if (c0 + 704 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-353+c0] + S[-c0+c1-353+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][352+c0] + S[352+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 646; c0 += 1)
    S[c0][c0+353] = MAX(S[c0][c0+353], S[c0+1][c0+353-1] + can_pair(RNA, c0, c0+353));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 645; c0 += 1)
    for (c1 = c0 + 354; c1 <= min(c0 + 707, 999); c1 += 1) {
      if (c0 + 706 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-354+c0] + S[-c0+c1-354+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][353+c0] + S[353+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 645; c0 += 1)
    S[c0][c0+354] = MAX(S[c0][c0+354], S[c0+1][c0+354-1] + can_pair(RNA, c0, c0+354));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 644; c0 += 1)
    for (c1 = c0 + 355; c1 <= min(c0 + 709, 999); c1 += 1) {
      if (c0 + 708 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-355+c0] + S[-c0+c1-355+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][354+c0] + S[354+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 644; c0 += 1)
    S[c0][c0+355] = MAX(S[c0][c0+355], S[c0+1][c0+355-1] + can_pair(RNA, c0, c0+355));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 643; c0 += 1)
    for (c1 = c0 + 356; c1 <= min(c0 + 711, 999); c1 += 1) {
      if (c0 + 710 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-356+c0] + S[-c0+c1-356+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][355+c0] + S[355+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 643; c0 += 1)
    S[c0][c0+356] = MAX(S[c0][c0+356], S[c0+1][c0+356-1] + can_pair(RNA, c0, c0+356));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 642; c0 += 1)
    for (c1 = c0 + 357; c1 <= min(c0 + 713, 999); c1 += 1) {
      if (c0 + 712 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-357+c0] + S[-c0+c1-357+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][356+c0] + S[356+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 642; c0 += 1)
    S[c0][c0+357] = MAX(S[c0][c0+357], S[c0+1][c0+357-1] + can_pair(RNA, c0, c0+357));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 641; c0 += 1)
    for (c1 = c0 + 358; c1 <= min(c0 + 715, 999); c1 += 1) {
      if (c0 + 714 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-358+c0] + S[-c0+c1-358+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][357+c0] + S[357+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 641; c0 += 1)
    S[c0][c0+358] = MAX(S[c0][c0+358], S[c0+1][c0+358-1] + can_pair(RNA, c0, c0+358));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 640; c0 += 1)
    for (c1 = c0 + 359; c1 <= min(c0 + 717, 999); c1 += 1) {
      if (c0 + 716 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-359+c0] + S[-c0+c1-359+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][358+c0] + S[358+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 640; c0 += 1)
    S[c0][c0+359] = MAX(S[c0][c0+359], S[c0+1][c0+359-1] + can_pair(RNA, c0, c0+359));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 639; c0 += 1)
    for (c1 = c0 + 360; c1 <= min(c0 + 719, 999); c1 += 1) {
      if (c0 + 718 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-360+c0] + S[-c0+c1-360+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][359+c0] + S[359+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 639; c0 += 1)
    S[c0][c0+360] = MAX(S[c0][c0+360], S[c0+1][c0+360-1] + can_pair(RNA, c0, c0+360));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 638; c0 += 1)
    for (c1 = c0 + 361; c1 <= min(c0 + 721, 999); c1 += 1) {
      if (c0 + 720 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-361+c0] + S[-c0+c1-361+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][360+c0] + S[360+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 638; c0 += 1)
    S[c0][c0+361] = MAX(S[c0][c0+361], S[c0+1][c0+361-1] + can_pair(RNA, c0, c0+361));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 637; c0 += 1)
    for (c1 = c0 + 362; c1 <= min(c0 + 723, 999); c1 += 1) {
      if (c0 + 722 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-362+c0] + S[-c0+c1-362+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][361+c0] + S[361+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 637; c0 += 1)
    S[c0][c0+362] = MAX(S[c0][c0+362], S[c0+1][c0+362-1] + can_pair(RNA, c0, c0+362));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 636; c0 += 1)
    for (c1 = c0 + 363; c1 <= min(c0 + 725, 999); c1 += 1) {
      if (c0 + 724 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-363+c0] + S[-c0+c1-363+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][362+c0] + S[362+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 636; c0 += 1)
    S[c0][c0+363] = MAX(S[c0][c0+363], S[c0+1][c0+363-1] + can_pair(RNA, c0, c0+363));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 635; c0 += 1)
    for (c1 = c0 + 364; c1 <= min(c0 + 727, 999); c1 += 1) {
      if (c0 + 726 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-364+c0] + S[-c0+c1-364+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][363+c0] + S[363+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 635; c0 += 1)
    S[c0][c0+364] = MAX(S[c0][c0+364], S[c0+1][c0+364-1] + can_pair(RNA, c0, c0+364));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 634; c0 += 1)
    for (c1 = c0 + 365; c1 <= min(c0 + 729, 999); c1 += 1) {
      if (c0 + 728 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-365+c0] + S[-c0+c1-365+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][364+c0] + S[364+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 634; c0 += 1)
    S[c0][c0+365] = MAX(S[c0][c0+365], S[c0+1][c0+365-1] + can_pair(RNA, c0, c0+365));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 633; c0 += 1)
    for (c1 = c0 + 366; c1 <= min(c0 + 731, 999); c1 += 1) {
      if (c0 + 730 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-366+c0] + S[-c0+c1-366+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][365+c0] + S[365+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 633; c0 += 1)
    S[c0][c0+366] = MAX(S[c0][c0+366], S[c0+1][c0+366-1] + can_pair(RNA, c0, c0+366));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 632; c0 += 1)
    for (c1 = c0 + 367; c1 <= min(c0 + 733, 999); c1 += 1) {
      if (c0 + 732 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-367+c0] + S[-c0+c1-367+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][366+c0] + S[366+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 632; c0 += 1)
    S[c0][c0+367] = MAX(S[c0][c0+367], S[c0+1][c0+367-1] + can_pair(RNA, c0, c0+367));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 631; c0 += 1)
    for (c1 = c0 + 368; c1 <= min(c0 + 735, 999); c1 += 1) {
      if (c0 + 734 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-368+c0] + S[-c0+c1-368+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][367+c0] + S[367+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 631; c0 += 1)
    S[c0][c0+368] = MAX(S[c0][c0+368], S[c0+1][c0+368-1] + can_pair(RNA, c0, c0+368));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 630; c0 += 1)
    for (c1 = c0 + 369; c1 <= min(c0 + 737, 999); c1 += 1) {
      if (c0 + 736 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-369+c0] + S[-c0+c1-369+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][368+c0] + S[368+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 630; c0 += 1)
    S[c0][c0+369] = MAX(S[c0][c0+369], S[c0+1][c0+369-1] + can_pair(RNA, c0, c0+369));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 629; c0 += 1)
    for (c1 = c0 + 370; c1 <= min(c0 + 739, 999); c1 += 1) {
      if (c0 + 738 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-370+c0] + S[-c0+c1-370+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][369+c0] + S[369+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 629; c0 += 1)
    S[c0][c0+370] = MAX(S[c0][c0+370], S[c0+1][c0+370-1] + can_pair(RNA, c0, c0+370));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 628; c0 += 1)
    for (c1 = c0 + 371; c1 <= min(c0 + 741, 999); c1 += 1) {
      if (c0 + 740 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-371+c0] + S[-c0+c1-371+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][370+c0] + S[370+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 628; c0 += 1)
    S[c0][c0+371] = MAX(S[c0][c0+371], S[c0+1][c0+371-1] + can_pair(RNA, c0, c0+371));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 627; c0 += 1)
    for (c1 = c0 + 372; c1 <= min(c0 + 743, 999); c1 += 1) {
      if (c0 + 742 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-372+c0] + S[-c0+c1-372+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][371+c0] + S[371+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 627; c0 += 1)
    S[c0][c0+372] = MAX(S[c0][c0+372], S[c0+1][c0+372-1] + can_pair(RNA, c0, c0+372));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 626; c0 += 1)
    for (c1 = c0 + 373; c1 <= min(c0 + 745, 999); c1 += 1) {
      if (c0 + 744 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-373+c0] + S[-c0+c1-373+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][372+c0] + S[372+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 626; c0 += 1)
    S[c0][c0+373] = MAX(S[c0][c0+373], S[c0+1][c0+373-1] + can_pair(RNA, c0, c0+373));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 625; c0 += 1)
    for (c1 = c0 + 374; c1 <= min(c0 + 747, 999); c1 += 1) {
      if (c0 + 746 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-374+c0] + S[-c0+c1-374+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][373+c0] + S[373+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 625; c0 += 1)
    S[c0][c0+374] = MAX(S[c0][c0+374], S[c0+1][c0+374-1] + can_pair(RNA, c0, c0+374));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 624; c0 += 1)
    for (c1 = c0 + 375; c1 <= min(c0 + 749, 999); c1 += 1) {
      if (c0 + 748 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-375+c0] + S[-c0+c1-375+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][374+c0] + S[374+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 624; c0 += 1)
    S[c0][c0+375] = MAX(S[c0][c0+375], S[c0+1][c0+375-1] + can_pair(RNA, c0, c0+375));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 623; c0 += 1)
    for (c1 = c0 + 376; c1 <= min(c0 + 751, 999); c1 += 1) {
      if (c0 + 750 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-376+c0] + S[-c0+c1-376+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][375+c0] + S[375+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 623; c0 += 1)
    S[c0][c0+376] = MAX(S[c0][c0+376], S[c0+1][c0+376-1] + can_pair(RNA, c0, c0+376));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 622; c0 += 1)
    for (c1 = c0 + 377; c1 <= min(c0 + 753, 999); c1 += 1) {
      if (c0 + 752 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-377+c0] + S[-c0+c1-377+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][376+c0] + S[376+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 622; c0 += 1)
    S[c0][c0+377] = MAX(S[c0][c0+377], S[c0+1][c0+377-1] + can_pair(RNA, c0, c0+377));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 621; c0 += 1)
    for (c1 = c0 + 378; c1 <= min(c0 + 755, 999); c1 += 1) {
      if (c0 + 754 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-378+c0] + S[-c0+c1-378+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][377+c0] + S[377+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 621; c0 += 1)
    S[c0][c0+378] = MAX(S[c0][c0+378], S[c0+1][c0+378-1] + can_pair(RNA, c0, c0+378));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 620; c0 += 1)
    for (c1 = c0 + 379; c1 <= min(c0 + 757, 999); c1 += 1) {
      if (c0 + 756 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-379+c0] + S[-c0+c1-379+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][378+c0] + S[378+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 620; c0 += 1)
    S[c0][c0+379] = MAX(S[c0][c0+379], S[c0+1][c0+379-1] + can_pair(RNA, c0, c0+379));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 619; c0 += 1)
    for (c1 = c0 + 380; c1 <= min(c0 + 759, 999); c1 += 1) {
      if (c0 + 758 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-380+c0] + S[-c0+c1-380+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][379+c0] + S[379+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 619; c0 += 1)
    S[c0][c0+380] = MAX(S[c0][c0+380], S[c0+1][c0+380-1] + can_pair(RNA, c0, c0+380));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 618; c0 += 1)
    for (c1 = c0 + 381; c1 <= min(c0 + 761, 999); c1 += 1) {
      if (c0 + 760 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-381+c0] + S[-c0+c1-381+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][380+c0] + S[380+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 618; c0 += 1)
    S[c0][c0+381] = MAX(S[c0][c0+381], S[c0+1][c0+381-1] + can_pair(RNA, c0, c0+381));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 617; c0 += 1)
    for (c1 = c0 + 382; c1 <= min(c0 + 763, 999); c1 += 1) {
      if (c0 + 762 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-382+c0] + S[-c0+c1-382+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][381+c0] + S[381+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 617; c0 += 1)
    S[c0][c0+382] = MAX(S[c0][c0+382], S[c0+1][c0+382-1] + can_pair(RNA, c0, c0+382));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 616; c0 += 1)
    for (c1 = c0 + 383; c1 <= min(c0 + 765, 999); c1 += 1) {
      if (c0 + 764 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-383+c0] + S[-c0+c1-383+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][382+c0] + S[382+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 616; c0 += 1)
    S[c0][c0+383] = MAX(S[c0][c0+383], S[c0+1][c0+383-1] + can_pair(RNA, c0, c0+383));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 615; c0 += 1)
    for (c1 = c0 + 384; c1 <= min(c0 + 767, 999); c1 += 1) {
      if (c0 + 766 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-384+c0] + S[-c0+c1-384+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][383+c0] + S[383+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 615; c0 += 1)
    S[c0][c0+384] = MAX(S[c0][c0+384], S[c0+1][c0+384-1] + can_pair(RNA, c0, c0+384));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 614; c0 += 1)
    for (c1 = c0 + 385; c1 <= min(c0 + 769, 999); c1 += 1) {
      if (c0 + 768 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-385+c0] + S[-c0+c1-385+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][384+c0] + S[384+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 614; c0 += 1)
    S[c0][c0+385] = MAX(S[c0][c0+385], S[c0+1][c0+385-1] + can_pair(RNA, c0, c0+385));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 613; c0 += 1)
    for (c1 = c0 + 386; c1 <= min(c0 + 771, 999); c1 += 1) {
      if (c0 + 770 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-386+c0] + S[-c0+c1-386+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][385+c0] + S[385+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 613; c0 += 1)
    S[c0][c0+386] = MAX(S[c0][c0+386], S[c0+1][c0+386-1] + can_pair(RNA, c0, c0+386));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 612; c0 += 1)
    for (c1 = c0 + 387; c1 <= min(c0 + 773, 999); c1 += 1) {
      if (c0 + 772 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-387+c0] + S[-c0+c1-387+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][386+c0] + S[386+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 612; c0 += 1)
    S[c0][c0+387] = MAX(S[c0][c0+387], S[c0+1][c0+387-1] + can_pair(RNA, c0, c0+387));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 611; c0 += 1)
    for (c1 = c0 + 388; c1 <= min(c0 + 775, 999); c1 += 1) {
      if (c0 + 774 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-388+c0] + S[-c0+c1-388+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][387+c0] + S[387+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 611; c0 += 1)
    S[c0][c0+388] = MAX(S[c0][c0+388], S[c0+1][c0+388-1] + can_pair(RNA, c0, c0+388));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 610; c0 += 1)
    for (c1 = c0 + 389; c1 <= min(c0 + 777, 999); c1 += 1) {
      if (c0 + 776 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-389+c0] + S[-c0+c1-389+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][388+c0] + S[388+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 610; c0 += 1)
    S[c0][c0+389] = MAX(S[c0][c0+389], S[c0+1][c0+389-1] + can_pair(RNA, c0, c0+389));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 609; c0 += 1)
    for (c1 = c0 + 390; c1 <= min(c0 + 779, 999); c1 += 1) {
      if (c0 + 778 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-390+c0] + S[-c0+c1-390+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][389+c0] + S[389+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 609; c0 += 1)
    S[c0][c0+390] = MAX(S[c0][c0+390], S[c0+1][c0+390-1] + can_pair(RNA, c0, c0+390));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 608; c0 += 1)
    for (c1 = c0 + 391; c1 <= min(c0 + 781, 999); c1 += 1) {
      if (c0 + 780 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-391+c0] + S[-c0+c1-391+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][390+c0] + S[390+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 608; c0 += 1)
    S[c0][c0+391] = MAX(S[c0][c0+391], S[c0+1][c0+391-1] + can_pair(RNA, c0, c0+391));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 607; c0 += 1)
    for (c1 = c0 + 392; c1 <= min(c0 + 783, 999); c1 += 1) {
      if (c0 + 782 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-392+c0] + S[-c0+c1-392+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][391+c0] + S[391+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 607; c0 += 1)
    S[c0][c0+392] = MAX(S[c0][c0+392], S[c0+1][c0+392-1] + can_pair(RNA, c0, c0+392));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 606; c0 += 1)
    for (c1 = c0 + 393; c1 <= min(c0 + 785, 999); c1 += 1) {
      if (c0 + 784 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-393+c0] + S[-c0+c1-393+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][392+c0] + S[392+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 606; c0 += 1)
    S[c0][c0+393] = MAX(S[c0][c0+393], S[c0+1][c0+393-1] + can_pair(RNA, c0, c0+393));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 605; c0 += 1)
    for (c1 = c0 + 394; c1 <= min(c0 + 787, 999); c1 += 1) {
      if (c0 + 786 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-394+c0] + S[-c0+c1-394+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][393+c0] + S[393+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 605; c0 += 1)
    S[c0][c0+394] = MAX(S[c0][c0+394], S[c0+1][c0+394-1] + can_pair(RNA, c0, c0+394));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 604; c0 += 1)
    for (c1 = c0 + 395; c1 <= min(c0 + 789, 999); c1 += 1) {
      if (c0 + 788 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-395+c0] + S[-c0+c1-395+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][394+c0] + S[394+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 604; c0 += 1)
    S[c0][c0+395] = MAX(S[c0][c0+395], S[c0+1][c0+395-1] + can_pair(RNA, c0, c0+395));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 603; c0 += 1)
    for (c1 = c0 + 396; c1 <= min(c0 + 791, 999); c1 += 1) {
      if (c0 + 790 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-396+c0] + S[-c0+c1-396+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][395+c0] + S[395+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 603; c0 += 1)
    S[c0][c0+396] = MAX(S[c0][c0+396], S[c0+1][c0+396-1] + can_pair(RNA, c0, c0+396));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 602; c0 += 1)
    for (c1 = c0 + 397; c1 <= min(c0 + 793, 999); c1 += 1) {
      if (c0 + 792 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-397+c0] + S[-c0+c1-397+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][396+c0] + S[396+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 602; c0 += 1)
    S[c0][c0+397] = MAX(S[c0][c0+397], S[c0+1][c0+397-1] + can_pair(RNA, c0, c0+397));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 601; c0 += 1)
    for (c1 = c0 + 398; c1 <= min(c0 + 795, 999); c1 += 1) {
      if (c0 + 794 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-398+c0] + S[-c0+c1-398+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][397+c0] + S[397+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 601; c0 += 1)
    S[c0][c0+398] = MAX(S[c0][c0+398], S[c0+1][c0+398-1] + can_pair(RNA, c0, c0+398));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 600; c0 += 1)
    for (c1 = c0 + 399; c1 <= min(c0 + 797, 999); c1 += 1) {
      if (c0 + 796 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-399+c0] + S[-c0+c1-399+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][398+c0] + S[398+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 600; c0 += 1)
    S[c0][c0+399] = MAX(S[c0][c0+399], S[c0+1][c0+399-1] + can_pair(RNA, c0, c0+399));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 599; c0 += 1)
    for (c1 = c0 + 400; c1 <= min(c0 + 799, 999); c1 += 1) {
      if (c0 + 798 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-400+c0] + S[-c0+c1-400+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][399+c0] + S[399+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 599; c0 += 1)
    S[c0][c0+400] = MAX(S[c0][c0+400], S[c0+1][c0+400-1] + can_pair(RNA, c0, c0+400));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 598; c0 += 1)
    for (c1 = c0 + 401; c1 <= min(c0 + 801, 999); c1 += 1) {
      if (c0 + 800 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-401+c0] + S[-c0+c1-401+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][400+c0] + S[400+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 598; c0 += 1)
    S[c0][c0+401] = MAX(S[c0][c0+401], S[c0+1][c0+401-1] + can_pair(RNA, c0, c0+401));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 597; c0 += 1)
    for (c1 = c0 + 402; c1 <= min(c0 + 803, 999); c1 += 1) {
      if (c0 + 802 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-402+c0] + S[-c0+c1-402+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][401+c0] + S[401+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 597; c0 += 1)
    S[c0][c0+402] = MAX(S[c0][c0+402], S[c0+1][c0+402-1] + can_pair(RNA, c0, c0+402));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 596; c0 += 1)
    for (c1 = c0 + 403; c1 <= min(c0 + 805, 999); c1 += 1) {
      if (c0 + 804 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-403+c0] + S[-c0+c1-403+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][402+c0] + S[402+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 596; c0 += 1)
    S[c0][c0+403] = MAX(S[c0][c0+403], S[c0+1][c0+403-1] + can_pair(RNA, c0, c0+403));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 595; c0 += 1)
    for (c1 = c0 + 404; c1 <= min(c0 + 807, 999); c1 += 1) {
      if (c0 + 806 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-404+c0] + S[-c0+c1-404+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][403+c0] + S[403+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 595; c0 += 1)
    S[c0][c0+404] = MAX(S[c0][c0+404], S[c0+1][c0+404-1] + can_pair(RNA, c0, c0+404));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 594; c0 += 1)
    for (c1 = c0 + 405; c1 <= min(c0 + 809, 999); c1 += 1) {
      if (c0 + 808 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-405+c0] + S[-c0+c1-405+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][404+c0] + S[404+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 594; c0 += 1)
    S[c0][c0+405] = MAX(S[c0][c0+405], S[c0+1][c0+405-1] + can_pair(RNA, c0, c0+405));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 593; c0 += 1)
    for (c1 = c0 + 406; c1 <= min(c0 + 811, 999); c1 += 1) {
      if (c0 + 810 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-406+c0] + S[-c0+c1-406+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][405+c0] + S[405+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 593; c0 += 1)
    S[c0][c0+406] = MAX(S[c0][c0+406], S[c0+1][c0+406-1] + can_pair(RNA, c0, c0+406));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 592; c0 += 1)
    for (c1 = c0 + 407; c1 <= min(c0 + 813, 999); c1 += 1) {
      if (c0 + 812 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-407+c0] + S[-c0+c1-407+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][406+c0] + S[406+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 592; c0 += 1)
    S[c0][c0+407] = MAX(S[c0][c0+407], S[c0+1][c0+407-1] + can_pair(RNA, c0, c0+407));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 591; c0 += 1)
    for (c1 = c0 + 408; c1 <= min(c0 + 815, 999); c1 += 1) {
      if (c0 + 814 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-408+c0] + S[-c0+c1-408+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][407+c0] + S[407+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 591; c0 += 1)
    S[c0][c0+408] = MAX(S[c0][c0+408], S[c0+1][c0+408-1] + can_pair(RNA, c0, c0+408));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 590; c0 += 1)
    for (c1 = c0 + 409; c1 <= min(c0 + 817, 999); c1 += 1) {
      if (c0 + 816 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-409+c0] + S[-c0+c1-409+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][408+c0] + S[408+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 590; c0 += 1)
    S[c0][c0+409] = MAX(S[c0][c0+409], S[c0+1][c0+409-1] + can_pair(RNA, c0, c0+409));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 589; c0 += 1)
    for (c1 = c0 + 410; c1 <= min(c0 + 819, 999); c1 += 1) {
      if (c0 + 818 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-410+c0] + S[-c0+c1-410+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][409+c0] + S[409+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 589; c0 += 1)
    S[c0][c0+410] = MAX(S[c0][c0+410], S[c0+1][c0+410-1] + can_pair(RNA, c0, c0+410));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 588; c0 += 1)
    for (c1 = c0 + 411; c1 <= min(c0 + 821, 999); c1 += 1) {
      if (c0 + 820 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-411+c0] + S[-c0+c1-411+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][410+c0] + S[410+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 588; c0 += 1)
    S[c0][c0+411] = MAX(S[c0][c0+411], S[c0+1][c0+411-1] + can_pair(RNA, c0, c0+411));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 587; c0 += 1)
    for (c1 = c0 + 412; c1 <= min(c0 + 823, 999); c1 += 1) {
      if (c0 + 822 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-412+c0] + S[-c0+c1-412+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][411+c0] + S[411+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 587; c0 += 1)
    S[c0][c0+412] = MAX(S[c0][c0+412], S[c0+1][c0+412-1] + can_pair(RNA, c0, c0+412));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 586; c0 += 1)
    for (c1 = c0 + 413; c1 <= min(c0 + 825, 999); c1 += 1) {
      if (c0 + 824 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-413+c0] + S[-c0+c1-413+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][412+c0] + S[412+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 586; c0 += 1)
    S[c0][c0+413] = MAX(S[c0][c0+413], S[c0+1][c0+413-1] + can_pair(RNA, c0, c0+413));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 585; c0 += 1)
    for (c1 = c0 + 414; c1 <= min(c0 + 827, 999); c1 += 1) {
      if (c0 + 826 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-414+c0] + S[-c0+c1-414+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][413+c0] + S[413+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 585; c0 += 1)
    S[c0][c0+414] = MAX(S[c0][c0+414], S[c0+1][c0+414-1] + can_pair(RNA, c0, c0+414));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 584; c0 += 1)
    for (c1 = c0 + 415; c1 <= min(c0 + 829, 999); c1 += 1) {
      if (c0 + 828 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-415+c0] + S[-c0+c1-415+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][414+c0] + S[414+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 584; c0 += 1)
    S[c0][c0+415] = MAX(S[c0][c0+415], S[c0+1][c0+415-1] + can_pair(RNA, c0, c0+415));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 583; c0 += 1)
    for (c1 = c0 + 416; c1 <= min(c0 + 831, 999); c1 += 1) {
      if (c0 + 830 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-416+c0] + S[-c0+c1-416+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][415+c0] + S[415+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 583; c0 += 1)
    S[c0][c0+416] = MAX(S[c0][c0+416], S[c0+1][c0+416-1] + can_pair(RNA, c0, c0+416));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 582; c0 += 1)
    for (c1 = c0 + 417; c1 <= min(c0 + 833, 999); c1 += 1) {
      if (c0 + 832 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-417+c0] + S[-c0+c1-417+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][416+c0] + S[416+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 582; c0 += 1)
    S[c0][c0+417] = MAX(S[c0][c0+417], S[c0+1][c0+417-1] + can_pair(RNA, c0, c0+417));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 581; c0 += 1)
    for (c1 = c0 + 418; c1 <= min(c0 + 835, 999); c1 += 1) {
      if (c0 + 834 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-418+c0] + S[-c0+c1-418+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][417+c0] + S[417+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 581; c0 += 1)
    S[c0][c0+418] = MAX(S[c0][c0+418], S[c0+1][c0+418-1] + can_pair(RNA, c0, c0+418));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 580; c0 += 1)
    for (c1 = c0 + 419; c1 <= min(c0 + 837, 999); c1 += 1) {
      if (c0 + 836 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-419+c0] + S[-c0+c1-419+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][418+c0] + S[418+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 580; c0 += 1)
    S[c0][c0+419] = MAX(S[c0][c0+419], S[c0+1][c0+419-1] + can_pair(RNA, c0, c0+419));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 579; c0 += 1)
    for (c1 = c0 + 420; c1 <= min(c0 + 839, 999); c1 += 1) {
      if (c0 + 838 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-420+c0] + S[-c0+c1-420+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][419+c0] + S[419+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 579; c0 += 1)
    S[c0][c0+420] = MAX(S[c0][c0+420], S[c0+1][c0+420-1] + can_pair(RNA, c0, c0+420));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 578; c0 += 1)
    for (c1 = c0 + 421; c1 <= min(c0 + 841, 999); c1 += 1) {
      if (c0 + 840 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-421+c0] + S[-c0+c1-421+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][420+c0] + S[420+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 578; c0 += 1)
    S[c0][c0+421] = MAX(S[c0][c0+421], S[c0+1][c0+421-1] + can_pair(RNA, c0, c0+421));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 577; c0 += 1)
    for (c1 = c0 + 422; c1 <= min(c0 + 843, 999); c1 += 1) {
      if (c0 + 842 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-422+c0] + S[-c0+c1-422+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][421+c0] + S[421+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 577; c0 += 1)
    S[c0][c0+422] = MAX(S[c0][c0+422], S[c0+1][c0+422-1] + can_pair(RNA, c0, c0+422));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 576; c0 += 1)
    for (c1 = c0 + 423; c1 <= min(c0 + 845, 999); c1 += 1) {
      if (c0 + 844 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-423+c0] + S[-c0+c1-423+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][422+c0] + S[422+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 576; c0 += 1)
    S[c0][c0+423] = MAX(S[c0][c0+423], S[c0+1][c0+423-1] + can_pair(RNA, c0, c0+423));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 575; c0 += 1)
    for (c1 = c0 + 424; c1 <= min(c0 + 847, 999); c1 += 1) {
      if (c0 + 846 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-424+c0] + S[-c0+c1-424+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][423+c0] + S[423+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 575; c0 += 1)
    S[c0][c0+424] = MAX(S[c0][c0+424], S[c0+1][c0+424-1] + can_pair(RNA, c0, c0+424));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 574; c0 += 1)
    for (c1 = c0 + 425; c1 <= min(c0 + 849, 999); c1 += 1) {
      if (c0 + 848 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-425+c0] + S[-c0+c1-425+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][424+c0] + S[424+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 574; c0 += 1)
    S[c0][c0+425] = MAX(S[c0][c0+425], S[c0+1][c0+425-1] + can_pair(RNA, c0, c0+425));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 573; c0 += 1)
    for (c1 = c0 + 426; c1 <= min(c0 + 851, 999); c1 += 1) {
      if (c0 + 850 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-426+c0] + S[-c0+c1-426+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][425+c0] + S[425+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 573; c0 += 1)
    S[c0][c0+426] = MAX(S[c0][c0+426], S[c0+1][c0+426-1] + can_pair(RNA, c0, c0+426));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 572; c0 += 1)
    for (c1 = c0 + 427; c1 <= min(c0 + 853, 999); c1 += 1) {
      if (c0 + 852 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-427+c0] + S[-c0+c1-427+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][426+c0] + S[426+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 572; c0 += 1)
    S[c0][c0+427] = MAX(S[c0][c0+427], S[c0+1][c0+427-1] + can_pair(RNA, c0, c0+427));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 571; c0 += 1)
    for (c1 = c0 + 428; c1 <= min(c0 + 855, 999); c1 += 1) {
      if (c0 + 854 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-428+c0] + S[-c0+c1-428+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][427+c0] + S[427+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 571; c0 += 1)
    S[c0][c0+428] = MAX(S[c0][c0+428], S[c0+1][c0+428-1] + can_pair(RNA, c0, c0+428));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 570; c0 += 1)
    for (c1 = c0 + 429; c1 <= min(c0 + 857, 999); c1 += 1) {
      if (c0 + 856 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-429+c0] + S[-c0+c1-429+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][428+c0] + S[428+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 570; c0 += 1)
    S[c0][c0+429] = MAX(S[c0][c0+429], S[c0+1][c0+429-1] + can_pair(RNA, c0, c0+429));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 569; c0 += 1)
    for (c1 = c0 + 430; c1 <= min(c0 + 859, 999); c1 += 1) {
      if (c0 + 858 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-430+c0] + S[-c0+c1-430+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][429+c0] + S[429+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 569; c0 += 1)
    S[c0][c0+430] = MAX(S[c0][c0+430], S[c0+1][c0+430-1] + can_pair(RNA, c0, c0+430));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 568; c0 += 1)
    for (c1 = c0 + 431; c1 <= min(c0 + 861, 999); c1 += 1) {
      if (c0 + 860 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-431+c0] + S[-c0+c1-431+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][430+c0] + S[430+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 568; c0 += 1)
    S[c0][c0+431] = MAX(S[c0][c0+431], S[c0+1][c0+431-1] + can_pair(RNA, c0, c0+431));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 567; c0 += 1)
    for (c1 = c0 + 432; c1 <= min(c0 + 863, 999); c1 += 1) {
      if (c0 + 862 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-432+c0] + S[-c0+c1-432+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][431+c0] + S[431+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 567; c0 += 1)
    S[c0][c0+432] = MAX(S[c0][c0+432], S[c0+1][c0+432-1] + can_pair(RNA, c0, c0+432));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 566; c0 += 1)
    for (c1 = c0 + 433; c1 <= min(c0 + 865, 999); c1 += 1) {
      if (c0 + 864 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-433+c0] + S[-c0+c1-433+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][432+c0] + S[432+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 566; c0 += 1)
    S[c0][c0+433] = MAX(S[c0][c0+433], S[c0+1][c0+433-1] + can_pair(RNA, c0, c0+433));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 565; c0 += 1)
    for (c1 = c0 + 434; c1 <= min(c0 + 867, 999); c1 += 1) {
      if (c0 + 866 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-434+c0] + S[-c0+c1-434+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][433+c0] + S[433+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 565; c0 += 1)
    S[c0][c0+434] = MAX(S[c0][c0+434], S[c0+1][c0+434-1] + can_pair(RNA, c0, c0+434));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 564; c0 += 1)
    for (c1 = c0 + 435; c1 <= min(c0 + 869, 999); c1 += 1) {
      if (c0 + 868 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-435+c0] + S[-c0+c1-435+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][434+c0] + S[434+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 564; c0 += 1)
    S[c0][c0+435] = MAX(S[c0][c0+435], S[c0+1][c0+435-1] + can_pair(RNA, c0, c0+435));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 563; c0 += 1)
    for (c1 = c0 + 436; c1 <= min(c0 + 871, 999); c1 += 1) {
      if (c0 + 870 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-436+c0] + S[-c0+c1-436+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][435+c0] + S[435+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 563; c0 += 1)
    S[c0][c0+436] = MAX(S[c0][c0+436], S[c0+1][c0+436-1] + can_pair(RNA, c0, c0+436));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 562; c0 += 1)
    for (c1 = c0 + 437; c1 <= min(c0 + 873, 999); c1 += 1) {
      if (c0 + 872 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-437+c0] + S[-c0+c1-437+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][436+c0] + S[436+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 562; c0 += 1)
    S[c0][c0+437] = MAX(S[c0][c0+437], S[c0+1][c0+437-1] + can_pair(RNA, c0, c0+437));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 561; c0 += 1)
    for (c1 = c0 + 438; c1 <= min(c0 + 875, 999); c1 += 1) {
      if (c0 + 874 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-438+c0] + S[-c0+c1-438+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][437+c0] + S[437+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 561; c0 += 1)
    S[c0][c0+438] = MAX(S[c0][c0+438], S[c0+1][c0+438-1] + can_pair(RNA, c0, c0+438));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 560; c0 += 1)
    for (c1 = c0 + 439; c1 <= min(c0 + 877, 999); c1 += 1) {
      if (c0 + 876 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-439+c0] + S[-c0+c1-439+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][438+c0] + S[438+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 560; c0 += 1)
    S[c0][c0+439] = MAX(S[c0][c0+439], S[c0+1][c0+439-1] + can_pair(RNA, c0, c0+439));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 559; c0 += 1)
    for (c1 = c0 + 440; c1 <= min(c0 + 879, 999); c1 += 1) {
      if (c0 + 878 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-440+c0] + S[-c0+c1-440+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][439+c0] + S[439+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 559; c0 += 1)
    S[c0][c0+440] = MAX(S[c0][c0+440], S[c0+1][c0+440-1] + can_pair(RNA, c0, c0+440));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 558; c0 += 1)
    for (c1 = c0 + 441; c1 <= min(c0 + 881, 999); c1 += 1) {
      if (c0 + 880 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-441+c0] + S[-c0+c1-441+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][440+c0] + S[440+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 558; c0 += 1)
    S[c0][c0+441] = MAX(S[c0][c0+441], S[c0+1][c0+441-1] + can_pair(RNA, c0, c0+441));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 557; c0 += 1)
    for (c1 = c0 + 442; c1 <= min(c0 + 883, 999); c1 += 1) {
      if (c0 + 882 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-442+c0] + S[-c0+c1-442+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][441+c0] + S[441+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 557; c0 += 1)
    S[c0][c0+442] = MAX(S[c0][c0+442], S[c0+1][c0+442-1] + can_pair(RNA, c0, c0+442));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 556; c0 += 1)
    for (c1 = c0 + 443; c1 <= min(c0 + 885, 999); c1 += 1) {
      if (c0 + 884 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-443+c0] + S[-c0+c1-443+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][442+c0] + S[442+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 556; c0 += 1)
    S[c0][c0+443] = MAX(S[c0][c0+443], S[c0+1][c0+443-1] + can_pair(RNA, c0, c0+443));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 555; c0 += 1)
    for (c1 = c0 + 444; c1 <= min(c0 + 887, 999); c1 += 1) {
      if (c0 + 886 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-444+c0] + S[-c0+c1-444+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][443+c0] + S[443+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 555; c0 += 1)
    S[c0][c0+444] = MAX(S[c0][c0+444], S[c0+1][c0+444-1] + can_pair(RNA, c0, c0+444));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 554; c0 += 1)
    for (c1 = c0 + 445; c1 <= min(c0 + 889, 999); c1 += 1) {
      if (c0 + 888 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-445+c0] + S[-c0+c1-445+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][444+c0] + S[444+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 554; c0 += 1)
    S[c0][c0+445] = MAX(S[c0][c0+445], S[c0+1][c0+445-1] + can_pair(RNA, c0, c0+445));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 553; c0 += 1)
    for (c1 = c0 + 446; c1 <= min(c0 + 891, 999); c1 += 1) {
      if (c0 + 890 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-446+c0] + S[-c0+c1-446+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][445+c0] + S[445+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 553; c0 += 1)
    S[c0][c0+446] = MAX(S[c0][c0+446], S[c0+1][c0+446-1] + can_pair(RNA, c0, c0+446));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 552; c0 += 1)
    for (c1 = c0 + 447; c1 <= min(c0 + 893, 999); c1 += 1) {
      if (c0 + 892 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-447+c0] + S[-c0+c1-447+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][446+c0] + S[446+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 552; c0 += 1)
    S[c0][c0+447] = MAX(S[c0][c0+447], S[c0+1][c0+447-1] + can_pair(RNA, c0, c0+447));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 551; c0 += 1)
    for (c1 = c0 + 448; c1 <= min(c0 + 895, 999); c1 += 1) {
      if (c0 + 894 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-448+c0] + S[-c0+c1-448+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][447+c0] + S[447+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 551; c0 += 1)
    S[c0][c0+448] = MAX(S[c0][c0+448], S[c0+1][c0+448-1] + can_pair(RNA, c0, c0+448));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 550; c0 += 1)
    for (c1 = c0 + 449; c1 <= min(c0 + 897, 999); c1 += 1) {
      if (c0 + 896 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-449+c0] + S[-c0+c1-449+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][448+c0] + S[448+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 550; c0 += 1)
    S[c0][c0+449] = MAX(S[c0][c0+449], S[c0+1][c0+449-1] + can_pair(RNA, c0, c0+449));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 549; c0 += 1)
    for (c1 = c0 + 450; c1 <= min(c0 + 899, 999); c1 += 1) {
      if (c0 + 898 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-450+c0] + S[-c0+c1-450+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][449+c0] + S[449+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 549; c0 += 1)
    S[c0][c0+450] = MAX(S[c0][c0+450], S[c0+1][c0+450-1] + can_pair(RNA, c0, c0+450));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 548; c0 += 1)
    for (c1 = c0 + 451; c1 <= min(c0 + 901, 999); c1 += 1) {
      if (c0 + 900 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-451+c0] + S[-c0+c1-451+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][450+c0] + S[450+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 548; c0 += 1)
    S[c0][c0+451] = MAX(S[c0][c0+451], S[c0+1][c0+451-1] + can_pair(RNA, c0, c0+451));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 547; c0 += 1)
    for (c1 = c0 + 452; c1 <= min(c0 + 903, 999); c1 += 1) {
      if (c0 + 902 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-452+c0] + S[-c0+c1-452+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][451+c0] + S[451+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 547; c0 += 1)
    S[c0][c0+452] = MAX(S[c0][c0+452], S[c0+1][c0+452-1] + can_pair(RNA, c0, c0+452));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 546; c0 += 1)
    for (c1 = c0 + 453; c1 <= min(c0 + 905, 999); c1 += 1) {
      if (c0 + 904 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-453+c0] + S[-c0+c1-453+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][452+c0] + S[452+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 546; c0 += 1)
    S[c0][c0+453] = MAX(S[c0][c0+453], S[c0+1][c0+453-1] + can_pair(RNA, c0, c0+453));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 545; c0 += 1)
    for (c1 = c0 + 454; c1 <= min(c0 + 907, 999); c1 += 1) {
      if (c0 + 906 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-454+c0] + S[-c0+c1-454+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][453+c0] + S[453+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 545; c0 += 1)
    S[c0][c0+454] = MAX(S[c0][c0+454], S[c0+1][c0+454-1] + can_pair(RNA, c0, c0+454));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 544; c0 += 1)
    for (c1 = c0 + 455; c1 <= min(c0 + 909, 999); c1 += 1) {
      if (c0 + 908 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-455+c0] + S[-c0+c1-455+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][454+c0] + S[454+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 544; c0 += 1)
    S[c0][c0+455] = MAX(S[c0][c0+455], S[c0+1][c0+455-1] + can_pair(RNA, c0, c0+455));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 543; c0 += 1)
    for (c1 = c0 + 456; c1 <= min(c0 + 911, 999); c1 += 1) {
      if (c0 + 910 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-456+c0] + S[-c0+c1-456+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][455+c0] + S[455+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 543; c0 += 1)
    S[c0][c0+456] = MAX(S[c0][c0+456], S[c0+1][c0+456-1] + can_pair(RNA, c0, c0+456));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 542; c0 += 1)
    for (c1 = c0 + 457; c1 <= min(c0 + 913, 999); c1 += 1) {
      if (c0 + 912 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-457+c0] + S[-c0+c1-457+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][456+c0] + S[456+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 542; c0 += 1)
    S[c0][c0+457] = MAX(S[c0][c0+457], S[c0+1][c0+457-1] + can_pair(RNA, c0, c0+457));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 541; c0 += 1)
    for (c1 = c0 + 458; c1 <= min(c0 + 915, 999); c1 += 1) {
      if (c0 + 914 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-458+c0] + S[-c0+c1-458+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][457+c0] + S[457+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 541; c0 += 1)
    S[c0][c0+458] = MAX(S[c0][c0+458], S[c0+1][c0+458-1] + can_pair(RNA, c0, c0+458));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 540; c0 += 1)
    for (c1 = c0 + 459; c1 <= min(c0 + 917, 999); c1 += 1) {
      if (c0 + 916 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-459+c0] + S[-c0+c1-459+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][458+c0] + S[458+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 540; c0 += 1)
    S[c0][c0+459] = MAX(S[c0][c0+459], S[c0+1][c0+459-1] + can_pair(RNA, c0, c0+459));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 539; c0 += 1)
    for (c1 = c0 + 460; c1 <= min(c0 + 919, 999); c1 += 1) {
      if (c0 + 918 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-460+c0] + S[-c0+c1-460+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][459+c0] + S[459+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 539; c0 += 1)
    S[c0][c0+460] = MAX(S[c0][c0+460], S[c0+1][c0+460-1] + can_pair(RNA, c0, c0+460));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 538; c0 += 1)
    for (c1 = c0 + 461; c1 <= min(c0 + 921, 999); c1 += 1) {
      if (c0 + 920 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-461+c0] + S[-c0+c1-461+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][460+c0] + S[460+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 538; c0 += 1)
    S[c0][c0+461] = MAX(S[c0][c0+461], S[c0+1][c0+461-1] + can_pair(RNA, c0, c0+461));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 537; c0 += 1)
    for (c1 = c0 + 462; c1 <= min(c0 + 923, 999); c1 += 1) {
      if (c0 + 922 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-462+c0] + S[-c0+c1-462+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][461+c0] + S[461+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 537; c0 += 1)
    S[c0][c0+462] = MAX(S[c0][c0+462], S[c0+1][c0+462-1] + can_pair(RNA, c0, c0+462));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 536; c0 += 1)
    for (c1 = c0 + 463; c1 <= min(c0 + 925, 999); c1 += 1) {
      if (c0 + 924 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-463+c0] + S[-c0+c1-463+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][462+c0] + S[462+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 536; c0 += 1)
    S[c0][c0+463] = MAX(S[c0][c0+463], S[c0+1][c0+463-1] + can_pair(RNA, c0, c0+463));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 535; c0 += 1)
    for (c1 = c0 + 464; c1 <= min(c0 + 927, 999); c1 += 1) {
      if (c0 + 926 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-464+c0] + S[-c0+c1-464+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][463+c0] + S[463+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 535; c0 += 1)
    S[c0][c0+464] = MAX(S[c0][c0+464], S[c0+1][c0+464-1] + can_pair(RNA, c0, c0+464));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 534; c0 += 1)
    for (c1 = c0 + 465; c1 <= min(c0 + 929, 999); c1 += 1) {
      if (c0 + 928 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-465+c0] + S[-c0+c1-465+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][464+c0] + S[464+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 534; c0 += 1)
    S[c0][c0+465] = MAX(S[c0][c0+465], S[c0+1][c0+465-1] + can_pair(RNA, c0, c0+465));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 533; c0 += 1)
    for (c1 = c0 + 466; c1 <= min(c0 + 931, 999); c1 += 1) {
      if (c0 + 930 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-466+c0] + S[-c0+c1-466+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][465+c0] + S[465+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 533; c0 += 1)
    S[c0][c0+466] = MAX(S[c0][c0+466], S[c0+1][c0+466-1] + can_pair(RNA, c0, c0+466));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 532; c0 += 1)
    for (c1 = c0 + 467; c1 <= min(c0 + 933, 999); c1 += 1) {
      if (c0 + 932 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-467+c0] + S[-c0+c1-467+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][466+c0] + S[466+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 532; c0 += 1)
    S[c0][c0+467] = MAX(S[c0][c0+467], S[c0+1][c0+467-1] + can_pair(RNA, c0, c0+467));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 531; c0 += 1)
    for (c1 = c0 + 468; c1 <= min(c0 + 935, 999); c1 += 1) {
      if (c0 + 934 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-468+c0] + S[-c0+c1-468+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][467+c0] + S[467+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 531; c0 += 1)
    S[c0][c0+468] = MAX(S[c0][c0+468], S[c0+1][c0+468-1] + can_pair(RNA, c0, c0+468));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 530; c0 += 1)
    for (c1 = c0 + 469; c1 <= min(c0 + 937, 999); c1 += 1) {
      if (c0 + 936 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-469+c0] + S[-c0+c1-469+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][468+c0] + S[468+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 530; c0 += 1)
    S[c0][c0+469] = MAX(S[c0][c0+469], S[c0+1][c0+469-1] + can_pair(RNA, c0, c0+469));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 529; c0 += 1)
    for (c1 = c0 + 470; c1 <= min(c0 + 939, 999); c1 += 1) {
      if (c0 + 938 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-470+c0] + S[-c0+c1-470+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][469+c0] + S[469+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 529; c0 += 1)
    S[c0][c0+470] = MAX(S[c0][c0+470], S[c0+1][c0+470-1] + can_pair(RNA, c0, c0+470));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 528; c0 += 1)
    for (c1 = c0 + 471; c1 <= min(c0 + 941, 999); c1 += 1) {
      if (c0 + 940 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-471+c0] + S[-c0+c1-471+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][470+c0] + S[470+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 528; c0 += 1)
    S[c0][c0+471] = MAX(S[c0][c0+471], S[c0+1][c0+471-1] + can_pair(RNA, c0, c0+471));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 527; c0 += 1)
    for (c1 = c0 + 472; c1 <= min(c0 + 943, 999); c1 += 1) {
      if (c0 + 942 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-472+c0] + S[-c0+c1-472+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][471+c0] + S[471+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 527; c0 += 1)
    S[c0][c0+472] = MAX(S[c0][c0+472], S[c0+1][c0+472-1] + can_pair(RNA, c0, c0+472));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 526; c0 += 1)
    for (c1 = c0 + 473; c1 <= min(c0 + 945, 999); c1 += 1) {
      if (c0 + 944 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-473+c0] + S[-c0+c1-473+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][472+c0] + S[472+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 526; c0 += 1)
    S[c0][c0+473] = MAX(S[c0][c0+473], S[c0+1][c0+473-1] + can_pair(RNA, c0, c0+473));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 525; c0 += 1)
    for (c1 = c0 + 474; c1 <= min(c0 + 947, 999); c1 += 1) {
      if (c0 + 946 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-474+c0] + S[-c0+c1-474+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][473+c0] + S[473+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 525; c0 += 1)
    S[c0][c0+474] = MAX(S[c0][c0+474], S[c0+1][c0+474-1] + can_pair(RNA, c0, c0+474));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 524; c0 += 1)
    for (c1 = c0 + 475; c1 <= min(c0 + 949, 999); c1 += 1) {
      if (c0 + 948 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-475+c0] + S[-c0+c1-475+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][474+c0] + S[474+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 524; c0 += 1)
    S[c0][c0+475] = MAX(S[c0][c0+475], S[c0+1][c0+475-1] + can_pair(RNA, c0, c0+475));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 523; c0 += 1)
    for (c1 = c0 + 476; c1 <= min(c0 + 951, 999); c1 += 1) {
      if (c0 + 950 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-476+c0] + S[-c0+c1-476+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][475+c0] + S[475+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 523; c0 += 1)
    S[c0][c0+476] = MAX(S[c0][c0+476], S[c0+1][c0+476-1] + can_pair(RNA, c0, c0+476));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 522; c0 += 1)
    for (c1 = c0 + 477; c1 <= min(c0 + 953, 999); c1 += 1) {
      if (c0 + 952 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-477+c0] + S[-c0+c1-477+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][476+c0] + S[476+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 522; c0 += 1)
    S[c0][c0+477] = MAX(S[c0][c0+477], S[c0+1][c0+477-1] + can_pair(RNA, c0, c0+477));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 521; c0 += 1)
    for (c1 = c0 + 478; c1 <= min(c0 + 955, 999); c1 += 1) {
      if (c0 + 954 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-478+c0] + S[-c0+c1-478+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][477+c0] + S[477+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 521; c0 += 1)
    S[c0][c0+478] = MAX(S[c0][c0+478], S[c0+1][c0+478-1] + can_pair(RNA, c0, c0+478));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 520; c0 += 1)
    for (c1 = c0 + 479; c1 <= min(c0 + 957, 999); c1 += 1) {
      if (c0 + 956 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-479+c0] + S[-c0+c1-479+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][478+c0] + S[478+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 520; c0 += 1)
    S[c0][c0+479] = MAX(S[c0][c0+479], S[c0+1][c0+479-1] + can_pair(RNA, c0, c0+479));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 519; c0 += 1)
    for (c1 = c0 + 480; c1 <= min(c0 + 959, 999); c1 += 1) {
      if (c0 + 958 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-480+c0] + S[-c0+c1-480+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][479+c0] + S[479+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 519; c0 += 1)
    S[c0][c0+480] = MAX(S[c0][c0+480], S[c0+1][c0+480-1] + can_pair(RNA, c0, c0+480));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 518; c0 += 1)
    for (c1 = c0 + 481; c1 <= min(c0 + 961, 999); c1 += 1) {
      if (c0 + 960 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-481+c0] + S[-c0+c1-481+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][480+c0] + S[480+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 518; c0 += 1)
    S[c0][c0+481] = MAX(S[c0][c0+481], S[c0+1][c0+481-1] + can_pair(RNA, c0, c0+481));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 517; c0 += 1)
    for (c1 = c0 + 482; c1 <= min(c0 + 963, 999); c1 += 1) {
      if (c0 + 962 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-482+c0] + S[-c0+c1-482+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][481+c0] + S[481+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 517; c0 += 1)
    S[c0][c0+482] = MAX(S[c0][c0+482], S[c0+1][c0+482-1] + can_pair(RNA, c0, c0+482));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 516; c0 += 1)
    for (c1 = c0 + 483; c1 <= min(c0 + 965, 999); c1 += 1) {
      if (c0 + 964 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-483+c0] + S[-c0+c1-483+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][482+c0] + S[482+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 516; c0 += 1)
    S[c0][c0+483] = MAX(S[c0][c0+483], S[c0+1][c0+483-1] + can_pair(RNA, c0, c0+483));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 515; c0 += 1)
    for (c1 = c0 + 484; c1 <= min(c0 + 967, 999); c1 += 1) {
      if (c0 + 966 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-484+c0] + S[-c0+c1-484+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][483+c0] + S[483+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 515; c0 += 1)
    S[c0][c0+484] = MAX(S[c0][c0+484], S[c0+1][c0+484-1] + can_pair(RNA, c0, c0+484));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 514; c0 += 1)
    for (c1 = c0 + 485; c1 <= min(c0 + 969, 999); c1 += 1) {
      if (c0 + 968 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-485+c0] + S[-c0+c1-485+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][484+c0] + S[484+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 514; c0 += 1)
    S[c0][c0+485] = MAX(S[c0][c0+485], S[c0+1][c0+485-1] + can_pair(RNA, c0, c0+485));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 513; c0 += 1)
    for (c1 = c0 + 486; c1 <= min(c0 + 971, 999); c1 += 1) {
      if (c0 + 970 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-486+c0] + S[-c0+c1-486+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][485+c0] + S[485+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 513; c0 += 1)
    S[c0][c0+486] = MAX(S[c0][c0+486], S[c0+1][c0+486-1] + can_pair(RNA, c0, c0+486));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 512; c0 += 1)
    for (c1 = c0 + 487; c1 <= min(c0 + 973, 999); c1 += 1) {
      if (c0 + 972 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-487+c0] + S[-c0+c1-487+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][486+c0] + S[486+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 512; c0 += 1)
    S[c0][c0+487] = MAX(S[c0][c0+487], S[c0+1][c0+487-1] + can_pair(RNA, c0, c0+487));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 511; c0 += 1)
    for (c1 = c0 + 488; c1 <= min(c0 + 975, 999); c1 += 1) {
      if (c0 + 974 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-488+c0] + S[-c0+c1-488+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][487+c0] + S[487+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 511; c0 += 1)
    S[c0][c0+488] = MAX(S[c0][c0+488], S[c0+1][c0+488-1] + can_pair(RNA, c0, c0+488));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 510; c0 += 1)
    for (c1 = c0 + 489; c1 <= min(c0 + 977, 999); c1 += 1) {
      if (c0 + 976 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-489+c0] + S[-c0+c1-489+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][488+c0] + S[488+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 510; c0 += 1)
    S[c0][c0+489] = MAX(S[c0][c0+489], S[c0+1][c0+489-1] + can_pair(RNA, c0, c0+489));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 509; c0 += 1)
    for (c1 = c0 + 490; c1 <= min(c0 + 979, 999); c1 += 1) {
      if (c0 + 978 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-490+c0] + S[-c0+c1-490+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][489+c0] + S[489+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 509; c0 += 1)
    S[c0][c0+490] = MAX(S[c0][c0+490], S[c0+1][c0+490-1] + can_pair(RNA, c0, c0+490));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 508; c0 += 1)
    for (c1 = c0 + 491; c1 <= min(c0 + 981, 999); c1 += 1) {
      if (c0 + 980 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-491+c0] + S[-c0+c1-491+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][490+c0] + S[490+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 508; c0 += 1)
    S[c0][c0+491] = MAX(S[c0][c0+491], S[c0+1][c0+491-1] + can_pair(RNA, c0, c0+491));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 507; c0 += 1)
    for (c1 = c0 + 492; c1 <= min(c0 + 983, 999); c1 += 1) {
      if (c0 + 982 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-492+c0] + S[-c0+c1-492+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][491+c0] + S[491+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 507; c0 += 1)
    S[c0][c0+492] = MAX(S[c0][c0+492], S[c0+1][c0+492-1] + can_pair(RNA, c0, c0+492));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 506; c0 += 1)
    for (c1 = c0 + 493; c1 <= min(c0 + 985, 999); c1 += 1) {
      if (c0 + 984 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-493+c0] + S[-c0+c1-493+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][492+c0] + S[492+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 506; c0 += 1)
    S[c0][c0+493] = MAX(S[c0][c0+493], S[c0+1][c0+493-1] + can_pair(RNA, c0, c0+493));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 505; c0 += 1)
    for (c1 = c0 + 494; c1 <= min(c0 + 987, 999); c1 += 1) {
      if (c0 + 986 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-494+c0] + S[-c0+c1-494+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][493+c0] + S[493+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 505; c0 += 1)
    S[c0][c0+494] = MAX(S[c0][c0+494], S[c0+1][c0+494-1] + can_pair(RNA, c0, c0+494));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 504; c0 += 1)
    for (c1 = c0 + 495; c1 <= min(c0 + 989, 999); c1 += 1) {
      if (c0 + 988 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-495+c0] + S[-c0+c1-495+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][494+c0] + S[494+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 504; c0 += 1)
    S[c0][c0+495] = MAX(S[c0][c0+495], S[c0+1][c0+495-1] + can_pair(RNA, c0, c0+495));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 503; c0 += 1)
    for (c1 = c0 + 496; c1 <= min(c0 + 991, 999); c1 += 1) {
      if (c0 + 990 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-496+c0] + S[-c0+c1-496+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][495+c0] + S[495+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 503; c0 += 1)
    S[c0][c0+496] = MAX(S[c0][c0+496], S[c0+1][c0+496-1] + can_pair(RNA, c0, c0+496));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 502; c0 += 1)
    for (c1 = c0 + 497; c1 <= min(c0 + 993, 999); c1 += 1) {
      if (c0 + 992 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-497+c0] + S[-c0+c1-497+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][496+c0] + S[496+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 502; c0 += 1)
    S[c0][c0+497] = MAX(S[c0][c0+497], S[c0+1][c0+497-1] + can_pair(RNA, c0, c0+497));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 501; c0 += 1)
    for (c1 = c0 + 498; c1 <= min(c0 + 995, 999); c1 += 1) {
      if (c0 + 994 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-498+c0] + S[-c0+c1-498+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][497+c0] + S[497+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 501; c0 += 1)
    S[c0][c0+498] = MAX(S[c0][c0+498], S[c0+1][c0+498-1] + can_pair(RNA, c0, c0+498));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 500; c0 += 1)
    for (c1 = c0 + 499; c1 <= min(c0 + 997, 999); c1 += 1) {
      if (c0 + 996 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-499+c0] + S[-c0+c1-499+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][498+c0] + S[498+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 500; c0 += 1)
    S[c0][c0+499] = MAX(S[c0][c0+499], S[c0+1][c0+499-1] + can_pair(RNA, c0, c0+499));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 499; c0 += 1)
    for (c1 = c0 + 500; c1 <= 999; c1 += 1) {
      if (c0 + 998 >= c1)
        S[c0][c1] = MAX(S[c0][-c0+c1-500+c0] + S[-c0+c1-500+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][499+c0] + S[499+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 499; c0 += 1)
    S[c0][c0+500] = MAX(S[c0][c0+500], S[c0+1][c0+500-1] + can_pair(RNA, c0, c0+500));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 498; c0 += 1)
    for (c1 = c0 + 501; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-501+c0] + S[-c0+c1-501+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][500+c0] + S[500+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 498; c0 += 1)
    S[c0][c0+501] = MAX(S[c0][c0+501], S[c0+1][c0+501-1] + can_pair(RNA, c0, c0+501));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 497; c0 += 1)
    for (c1 = c0 + 502; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-502+c0] + S[-c0+c1-502+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][501+c0] + S[501+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 497; c0 += 1)
    S[c0][c0+502] = MAX(S[c0][c0+502], S[c0+1][c0+502-1] + can_pair(RNA, c0, c0+502));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 496; c0 += 1)
    for (c1 = c0 + 503; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-503+c0] + S[-c0+c1-503+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][502+c0] + S[502+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 496; c0 += 1)
    S[c0][c0+503] = MAX(S[c0][c0+503], S[c0+1][c0+503-1] + can_pair(RNA, c0, c0+503));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 495; c0 += 1)
    for (c1 = c0 + 504; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-504+c0] + S[-c0+c1-504+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][503+c0] + S[503+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 495; c0 += 1)
    S[c0][c0+504] = MAX(S[c0][c0+504], S[c0+1][c0+504-1] + can_pair(RNA, c0, c0+504));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 494; c0 += 1)
    for (c1 = c0 + 505; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-505+c0] + S[-c0+c1-505+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][504+c0] + S[504+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 494; c0 += 1)
    S[c0][c0+505] = MAX(S[c0][c0+505], S[c0+1][c0+505-1] + can_pair(RNA, c0, c0+505));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 493; c0 += 1)
    for (c1 = c0 + 506; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-506+c0] + S[-c0+c1-506+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][505+c0] + S[505+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 493; c0 += 1)
    S[c0][c0+506] = MAX(S[c0][c0+506], S[c0+1][c0+506-1] + can_pair(RNA, c0, c0+506));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 492; c0 += 1)
    for (c1 = c0 + 507; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-507+c0] + S[-c0+c1-507+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][506+c0] + S[506+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 492; c0 += 1)
    S[c0][c0+507] = MAX(S[c0][c0+507], S[c0+1][c0+507-1] + can_pair(RNA, c0, c0+507));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 491; c0 += 1)
    for (c1 = c0 + 508; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-508+c0] + S[-c0+c1-508+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][507+c0] + S[507+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 491; c0 += 1)
    S[c0][c0+508] = MAX(S[c0][c0+508], S[c0+1][c0+508-1] + can_pair(RNA, c0, c0+508));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 490; c0 += 1)
    for (c1 = c0 + 509; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-509+c0] + S[-c0+c1-509+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][508+c0] + S[508+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 490; c0 += 1)
    S[c0][c0+509] = MAX(S[c0][c0+509], S[c0+1][c0+509-1] + can_pair(RNA, c0, c0+509));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 489; c0 += 1)
    for (c1 = c0 + 510; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-510+c0] + S[-c0+c1-510+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][509+c0] + S[509+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 489; c0 += 1)
    S[c0][c0+510] = MAX(S[c0][c0+510], S[c0+1][c0+510-1] + can_pair(RNA, c0, c0+510));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 488; c0 += 1)
    for (c1 = c0 + 511; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-511+c0] + S[-c0+c1-511+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][510+c0] + S[510+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 488; c0 += 1)
    S[c0][c0+511] = MAX(S[c0][c0+511], S[c0+1][c0+511-1] + can_pair(RNA, c0, c0+511));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 487; c0 += 1)
    for (c1 = c0 + 512; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-512+c0] + S[-c0+c1-512+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][511+c0] + S[511+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 487; c0 += 1)
    S[c0][c0+512] = MAX(S[c0][c0+512], S[c0+1][c0+512-1] + can_pair(RNA, c0, c0+512));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 486; c0 += 1)
    for (c1 = c0 + 513; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-513+c0] + S[-c0+c1-513+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][512+c0] + S[512+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 486; c0 += 1)
    S[c0][c0+513] = MAX(S[c0][c0+513], S[c0+1][c0+513-1] + can_pair(RNA, c0, c0+513));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 485; c0 += 1)
    for (c1 = c0 + 514; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-514+c0] + S[-c0+c1-514+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][513+c0] + S[513+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 485; c0 += 1)
    S[c0][c0+514] = MAX(S[c0][c0+514], S[c0+1][c0+514-1] + can_pair(RNA, c0, c0+514));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 484; c0 += 1)
    for (c1 = c0 + 515; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-515+c0] + S[-c0+c1-515+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][514+c0] + S[514+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 484; c0 += 1)
    S[c0][c0+515] = MAX(S[c0][c0+515], S[c0+1][c0+515-1] + can_pair(RNA, c0, c0+515));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 483; c0 += 1)
    for (c1 = c0 + 516; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-516+c0] + S[-c0+c1-516+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][515+c0] + S[515+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 483; c0 += 1)
    S[c0][c0+516] = MAX(S[c0][c0+516], S[c0+1][c0+516-1] + can_pair(RNA, c0, c0+516));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 482; c0 += 1)
    for (c1 = c0 + 517; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-517+c0] + S[-c0+c1-517+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][516+c0] + S[516+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 482; c0 += 1)
    S[c0][c0+517] = MAX(S[c0][c0+517], S[c0+1][c0+517-1] + can_pair(RNA, c0, c0+517));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 481; c0 += 1)
    for (c1 = c0 + 518; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-518+c0] + S[-c0+c1-518+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][517+c0] + S[517+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 481; c0 += 1)
    S[c0][c0+518] = MAX(S[c0][c0+518], S[c0+1][c0+518-1] + can_pair(RNA, c0, c0+518));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 480; c0 += 1)
    for (c1 = c0 + 519; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-519+c0] + S[-c0+c1-519+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][518+c0] + S[518+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 480; c0 += 1)
    S[c0][c0+519] = MAX(S[c0][c0+519], S[c0+1][c0+519-1] + can_pair(RNA, c0, c0+519));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 479; c0 += 1)
    for (c1 = c0 + 520; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-520+c0] + S[-c0+c1-520+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][519+c0] + S[519+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 479; c0 += 1)
    S[c0][c0+520] = MAX(S[c0][c0+520], S[c0+1][c0+520-1] + can_pair(RNA, c0, c0+520));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 478; c0 += 1)
    for (c1 = c0 + 521; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-521+c0] + S[-c0+c1-521+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][520+c0] + S[520+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 478; c0 += 1)
    S[c0][c0+521] = MAX(S[c0][c0+521], S[c0+1][c0+521-1] + can_pair(RNA, c0, c0+521));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 477; c0 += 1)
    for (c1 = c0 + 522; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-522+c0] + S[-c0+c1-522+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][521+c0] + S[521+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 477; c0 += 1)
    S[c0][c0+522] = MAX(S[c0][c0+522], S[c0+1][c0+522-1] + can_pair(RNA, c0, c0+522));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 476; c0 += 1)
    for (c1 = c0 + 523; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-523+c0] + S[-c0+c1-523+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][522+c0] + S[522+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 476; c0 += 1)
    S[c0][c0+523] = MAX(S[c0][c0+523], S[c0+1][c0+523-1] + can_pair(RNA, c0, c0+523));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 475; c0 += 1)
    for (c1 = c0 + 524; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-524+c0] + S[-c0+c1-524+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][523+c0] + S[523+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 475; c0 += 1)
    S[c0][c0+524] = MAX(S[c0][c0+524], S[c0+1][c0+524-1] + can_pair(RNA, c0, c0+524));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 474; c0 += 1)
    for (c1 = c0 + 525; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-525+c0] + S[-c0+c1-525+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][524+c0] + S[524+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 474; c0 += 1)
    S[c0][c0+525] = MAX(S[c0][c0+525], S[c0+1][c0+525-1] + can_pair(RNA, c0, c0+525));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 473; c0 += 1)
    for (c1 = c0 + 526; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-526+c0] + S[-c0+c1-526+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][525+c0] + S[525+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 473; c0 += 1)
    S[c0][c0+526] = MAX(S[c0][c0+526], S[c0+1][c0+526-1] + can_pair(RNA, c0, c0+526));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 472; c0 += 1)
    for (c1 = c0 + 527; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-527+c0] + S[-c0+c1-527+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][526+c0] + S[526+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 472; c0 += 1)
    S[c0][c0+527] = MAX(S[c0][c0+527], S[c0+1][c0+527-1] + can_pair(RNA, c0, c0+527));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 471; c0 += 1)
    for (c1 = c0 + 528; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-528+c0] + S[-c0+c1-528+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][527+c0] + S[527+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 471; c0 += 1)
    S[c0][c0+528] = MAX(S[c0][c0+528], S[c0+1][c0+528-1] + can_pair(RNA, c0, c0+528));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 470; c0 += 1)
    for (c1 = c0 + 529; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-529+c0] + S[-c0+c1-529+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][528+c0] + S[528+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 470; c0 += 1)
    S[c0][c0+529] = MAX(S[c0][c0+529], S[c0+1][c0+529-1] + can_pair(RNA, c0, c0+529));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 469; c0 += 1)
    for (c1 = c0 + 530; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-530+c0] + S[-c0+c1-530+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][529+c0] + S[529+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 469; c0 += 1)
    S[c0][c0+530] = MAX(S[c0][c0+530], S[c0+1][c0+530-1] + can_pair(RNA, c0, c0+530));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 468; c0 += 1)
    for (c1 = c0 + 531; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-531+c0] + S[-c0+c1-531+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][530+c0] + S[530+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 468; c0 += 1)
    S[c0][c0+531] = MAX(S[c0][c0+531], S[c0+1][c0+531-1] + can_pair(RNA, c0, c0+531));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 467; c0 += 1)
    for (c1 = c0 + 532; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-532+c0] + S[-c0+c1-532+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][531+c0] + S[531+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 467; c0 += 1)
    S[c0][c0+532] = MAX(S[c0][c0+532], S[c0+1][c0+532-1] + can_pair(RNA, c0, c0+532));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 466; c0 += 1)
    for (c1 = c0 + 533; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-533+c0] + S[-c0+c1-533+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][532+c0] + S[532+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 466; c0 += 1)
    S[c0][c0+533] = MAX(S[c0][c0+533], S[c0+1][c0+533-1] + can_pair(RNA, c0, c0+533));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 465; c0 += 1)
    for (c1 = c0 + 534; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-534+c0] + S[-c0+c1-534+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][533+c0] + S[533+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 465; c0 += 1)
    S[c0][c0+534] = MAX(S[c0][c0+534], S[c0+1][c0+534-1] + can_pair(RNA, c0, c0+534));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 464; c0 += 1)
    for (c1 = c0 + 535; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-535+c0] + S[-c0+c1-535+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][534+c0] + S[534+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 464; c0 += 1)
    S[c0][c0+535] = MAX(S[c0][c0+535], S[c0+1][c0+535-1] + can_pair(RNA, c0, c0+535));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 463; c0 += 1)
    for (c1 = c0 + 536; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-536+c0] + S[-c0+c1-536+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][535+c0] + S[535+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 463; c0 += 1)
    S[c0][c0+536] = MAX(S[c0][c0+536], S[c0+1][c0+536-1] + can_pair(RNA, c0, c0+536));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 462; c0 += 1)
    for (c1 = c0 + 537; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-537+c0] + S[-c0+c1-537+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][536+c0] + S[536+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 462; c0 += 1)
    S[c0][c0+537] = MAX(S[c0][c0+537], S[c0+1][c0+537-1] + can_pair(RNA, c0, c0+537));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 461; c0 += 1)
    for (c1 = c0 + 538; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-538+c0] + S[-c0+c1-538+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][537+c0] + S[537+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 461; c0 += 1)
    S[c0][c0+538] = MAX(S[c0][c0+538], S[c0+1][c0+538-1] + can_pair(RNA, c0, c0+538));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 460; c0 += 1)
    for (c1 = c0 + 539; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-539+c0] + S[-c0+c1-539+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][538+c0] + S[538+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 460; c0 += 1)
    S[c0][c0+539] = MAX(S[c0][c0+539], S[c0+1][c0+539-1] + can_pair(RNA, c0, c0+539));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 459; c0 += 1)
    for (c1 = c0 + 540; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-540+c0] + S[-c0+c1-540+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][539+c0] + S[539+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 459; c0 += 1)
    S[c0][c0+540] = MAX(S[c0][c0+540], S[c0+1][c0+540-1] + can_pair(RNA, c0, c0+540));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 458; c0 += 1)
    for (c1 = c0 + 541; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-541+c0] + S[-c0+c1-541+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][540+c0] + S[540+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 458; c0 += 1)
    S[c0][c0+541] = MAX(S[c0][c0+541], S[c0+1][c0+541-1] + can_pair(RNA, c0, c0+541));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 457; c0 += 1)
    for (c1 = c0 + 542; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-542+c0] + S[-c0+c1-542+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][541+c0] + S[541+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 457; c0 += 1)
    S[c0][c0+542] = MAX(S[c0][c0+542], S[c0+1][c0+542-1] + can_pair(RNA, c0, c0+542));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 456; c0 += 1)
    for (c1 = c0 + 543; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-543+c0] + S[-c0+c1-543+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][542+c0] + S[542+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 456; c0 += 1)
    S[c0][c0+543] = MAX(S[c0][c0+543], S[c0+1][c0+543-1] + can_pair(RNA, c0, c0+543));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 455; c0 += 1)
    for (c1 = c0 + 544; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-544+c0] + S[-c0+c1-544+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][543+c0] + S[543+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 455; c0 += 1)
    S[c0][c0+544] = MAX(S[c0][c0+544], S[c0+1][c0+544-1] + can_pair(RNA, c0, c0+544));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 454; c0 += 1)
    for (c1 = c0 + 545; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-545+c0] + S[-c0+c1-545+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][544+c0] + S[544+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 454; c0 += 1)
    S[c0][c0+545] = MAX(S[c0][c0+545], S[c0+1][c0+545-1] + can_pair(RNA, c0, c0+545));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 453; c0 += 1)
    for (c1 = c0 + 546; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-546+c0] + S[-c0+c1-546+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][545+c0] + S[545+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 453; c0 += 1)
    S[c0][c0+546] = MAX(S[c0][c0+546], S[c0+1][c0+546-1] + can_pair(RNA, c0, c0+546));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 452; c0 += 1)
    for (c1 = c0 + 547; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-547+c0] + S[-c0+c1-547+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][546+c0] + S[546+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 452; c0 += 1)
    S[c0][c0+547] = MAX(S[c0][c0+547], S[c0+1][c0+547-1] + can_pair(RNA, c0, c0+547));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 451; c0 += 1)
    for (c1 = c0 + 548; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-548+c0] + S[-c0+c1-548+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][547+c0] + S[547+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 451; c0 += 1)
    S[c0][c0+548] = MAX(S[c0][c0+548], S[c0+1][c0+548-1] + can_pair(RNA, c0, c0+548));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 450; c0 += 1)
    for (c1 = c0 + 549; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-549+c0] + S[-c0+c1-549+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][548+c0] + S[548+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 450; c0 += 1)
    S[c0][c0+549] = MAX(S[c0][c0+549], S[c0+1][c0+549-1] + can_pair(RNA, c0, c0+549));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 449; c0 += 1)
    for (c1 = c0 + 550; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-550+c0] + S[-c0+c1-550+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][549+c0] + S[549+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 449; c0 += 1)
    S[c0][c0+550] = MAX(S[c0][c0+550], S[c0+1][c0+550-1] + can_pair(RNA, c0, c0+550));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 448; c0 += 1)
    for (c1 = c0 + 551; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-551+c0] + S[-c0+c1-551+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][550+c0] + S[550+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 448; c0 += 1)
    S[c0][c0+551] = MAX(S[c0][c0+551], S[c0+1][c0+551-1] + can_pair(RNA, c0, c0+551));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 447; c0 += 1)
    for (c1 = c0 + 552; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-552+c0] + S[-c0+c1-552+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][551+c0] + S[551+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 447; c0 += 1)
    S[c0][c0+552] = MAX(S[c0][c0+552], S[c0+1][c0+552-1] + can_pair(RNA, c0, c0+552));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 446; c0 += 1)
    for (c1 = c0 + 553; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-553+c0] + S[-c0+c1-553+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][552+c0] + S[552+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 446; c0 += 1)
    S[c0][c0+553] = MAX(S[c0][c0+553], S[c0+1][c0+553-1] + can_pair(RNA, c0, c0+553));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 445; c0 += 1)
    for (c1 = c0 + 554; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-554+c0] + S[-c0+c1-554+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][553+c0] + S[553+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 445; c0 += 1)
    S[c0][c0+554] = MAX(S[c0][c0+554], S[c0+1][c0+554-1] + can_pair(RNA, c0, c0+554));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 444; c0 += 1)
    for (c1 = c0 + 555; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-555+c0] + S[-c0+c1-555+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][554+c0] + S[554+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 444; c0 += 1)
    S[c0][c0+555] = MAX(S[c0][c0+555], S[c0+1][c0+555-1] + can_pair(RNA, c0, c0+555));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 443; c0 += 1)
    for (c1 = c0 + 556; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-556+c0] + S[-c0+c1-556+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][555+c0] + S[555+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 443; c0 += 1)
    S[c0][c0+556] = MAX(S[c0][c0+556], S[c0+1][c0+556-1] + can_pair(RNA, c0, c0+556));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 442; c0 += 1)
    for (c1 = c0 + 557; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-557+c0] + S[-c0+c1-557+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][556+c0] + S[556+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 442; c0 += 1)
    S[c0][c0+557] = MAX(S[c0][c0+557], S[c0+1][c0+557-1] + can_pair(RNA, c0, c0+557));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 441; c0 += 1)
    for (c1 = c0 + 558; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-558+c0] + S[-c0+c1-558+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][557+c0] + S[557+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 441; c0 += 1)
    S[c0][c0+558] = MAX(S[c0][c0+558], S[c0+1][c0+558-1] + can_pair(RNA, c0, c0+558));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 440; c0 += 1)
    for (c1 = c0 + 559; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-559+c0] + S[-c0+c1-559+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][558+c0] + S[558+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 440; c0 += 1)
    S[c0][c0+559] = MAX(S[c0][c0+559], S[c0+1][c0+559-1] + can_pair(RNA, c0, c0+559));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 439; c0 += 1)
    for (c1 = c0 + 560; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-560+c0] + S[-c0+c1-560+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][559+c0] + S[559+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 439; c0 += 1)
    S[c0][c0+560] = MAX(S[c0][c0+560], S[c0+1][c0+560-1] + can_pair(RNA, c0, c0+560));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 438; c0 += 1)
    for (c1 = c0 + 561; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-561+c0] + S[-c0+c1-561+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][560+c0] + S[560+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 438; c0 += 1)
    S[c0][c0+561] = MAX(S[c0][c0+561], S[c0+1][c0+561-1] + can_pair(RNA, c0, c0+561));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 437; c0 += 1)
    for (c1 = c0 + 562; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-562+c0] + S[-c0+c1-562+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][561+c0] + S[561+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 437; c0 += 1)
    S[c0][c0+562] = MAX(S[c0][c0+562], S[c0+1][c0+562-1] + can_pair(RNA, c0, c0+562));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 436; c0 += 1)
    for (c1 = c0 + 563; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-563+c0] + S[-c0+c1-563+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][562+c0] + S[562+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 436; c0 += 1)
    S[c0][c0+563] = MAX(S[c0][c0+563], S[c0+1][c0+563-1] + can_pair(RNA, c0, c0+563));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 435; c0 += 1)
    for (c1 = c0 + 564; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-564+c0] + S[-c0+c1-564+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][563+c0] + S[563+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 435; c0 += 1)
    S[c0][c0+564] = MAX(S[c0][c0+564], S[c0+1][c0+564-1] + can_pair(RNA, c0, c0+564));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 434; c0 += 1)
    for (c1 = c0 + 565; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-565+c0] + S[-c0+c1-565+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][564+c0] + S[564+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 434; c0 += 1)
    S[c0][c0+565] = MAX(S[c0][c0+565], S[c0+1][c0+565-1] + can_pair(RNA, c0, c0+565));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 433; c0 += 1)
    for (c1 = c0 + 566; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-566+c0] + S[-c0+c1-566+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][565+c0] + S[565+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 433; c0 += 1)
    S[c0][c0+566] = MAX(S[c0][c0+566], S[c0+1][c0+566-1] + can_pair(RNA, c0, c0+566));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 432; c0 += 1)
    for (c1 = c0 + 567; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-567+c0] + S[-c0+c1-567+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][566+c0] + S[566+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 432; c0 += 1)
    S[c0][c0+567] = MAX(S[c0][c0+567], S[c0+1][c0+567-1] + can_pair(RNA, c0, c0+567));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 431; c0 += 1)
    for (c1 = c0 + 568; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-568+c0] + S[-c0+c1-568+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][567+c0] + S[567+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 431; c0 += 1)
    S[c0][c0+568] = MAX(S[c0][c0+568], S[c0+1][c0+568-1] + can_pair(RNA, c0, c0+568));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 430; c0 += 1)
    for (c1 = c0 + 569; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-569+c0] + S[-c0+c1-569+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][568+c0] + S[568+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 430; c0 += 1)
    S[c0][c0+569] = MAX(S[c0][c0+569], S[c0+1][c0+569-1] + can_pair(RNA, c0, c0+569));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 429; c0 += 1)
    for (c1 = c0 + 570; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-570+c0] + S[-c0+c1-570+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][569+c0] + S[569+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 429; c0 += 1)
    S[c0][c0+570] = MAX(S[c0][c0+570], S[c0+1][c0+570-1] + can_pair(RNA, c0, c0+570));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 428; c0 += 1)
    for (c1 = c0 + 571; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-571+c0] + S[-c0+c1-571+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][570+c0] + S[570+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 428; c0 += 1)
    S[c0][c0+571] = MAX(S[c0][c0+571], S[c0+1][c0+571-1] + can_pair(RNA, c0, c0+571));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 427; c0 += 1)
    for (c1 = c0 + 572; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-572+c0] + S[-c0+c1-572+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][571+c0] + S[571+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 427; c0 += 1)
    S[c0][c0+572] = MAX(S[c0][c0+572], S[c0+1][c0+572-1] + can_pair(RNA, c0, c0+572));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 426; c0 += 1)
    for (c1 = c0 + 573; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-573+c0] + S[-c0+c1-573+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][572+c0] + S[572+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 426; c0 += 1)
    S[c0][c0+573] = MAX(S[c0][c0+573], S[c0+1][c0+573-1] + can_pair(RNA, c0, c0+573));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 425; c0 += 1)
    for (c1 = c0 + 574; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-574+c0] + S[-c0+c1-574+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][573+c0] + S[573+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 425; c0 += 1)
    S[c0][c0+574] = MAX(S[c0][c0+574], S[c0+1][c0+574-1] + can_pair(RNA, c0, c0+574));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 424; c0 += 1)
    for (c1 = c0 + 575; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-575+c0] + S[-c0+c1-575+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][574+c0] + S[574+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 424; c0 += 1)
    S[c0][c0+575] = MAX(S[c0][c0+575], S[c0+1][c0+575-1] + can_pair(RNA, c0, c0+575));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 423; c0 += 1)
    for (c1 = c0 + 576; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-576+c0] + S[-c0+c1-576+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][575+c0] + S[575+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 423; c0 += 1)
    S[c0][c0+576] = MAX(S[c0][c0+576], S[c0+1][c0+576-1] + can_pair(RNA, c0, c0+576));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 422; c0 += 1)
    for (c1 = c0 + 577; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-577+c0] + S[-c0+c1-577+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][576+c0] + S[576+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 422; c0 += 1)
    S[c0][c0+577] = MAX(S[c0][c0+577], S[c0+1][c0+577-1] + can_pair(RNA, c0, c0+577));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 421; c0 += 1)
    for (c1 = c0 + 578; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-578+c0] + S[-c0+c1-578+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][577+c0] + S[577+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 421; c0 += 1)
    S[c0][c0+578] = MAX(S[c0][c0+578], S[c0+1][c0+578-1] + can_pair(RNA, c0, c0+578));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 420; c0 += 1)
    for (c1 = c0 + 579; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-579+c0] + S[-c0+c1-579+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][578+c0] + S[578+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 420; c0 += 1)
    S[c0][c0+579] = MAX(S[c0][c0+579], S[c0+1][c0+579-1] + can_pair(RNA, c0, c0+579));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 419; c0 += 1)
    for (c1 = c0 + 580; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-580+c0] + S[-c0+c1-580+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][579+c0] + S[579+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 419; c0 += 1)
    S[c0][c0+580] = MAX(S[c0][c0+580], S[c0+1][c0+580-1] + can_pair(RNA, c0, c0+580));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 418; c0 += 1)
    for (c1 = c0 + 581; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-581+c0] + S[-c0+c1-581+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][580+c0] + S[580+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 418; c0 += 1)
    S[c0][c0+581] = MAX(S[c0][c0+581], S[c0+1][c0+581-1] + can_pair(RNA, c0, c0+581));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 417; c0 += 1)
    for (c1 = c0 + 582; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-582+c0] + S[-c0+c1-582+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][581+c0] + S[581+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 417; c0 += 1)
    S[c0][c0+582] = MAX(S[c0][c0+582], S[c0+1][c0+582-1] + can_pair(RNA, c0, c0+582));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 416; c0 += 1)
    for (c1 = c0 + 583; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-583+c0] + S[-c0+c1-583+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][582+c0] + S[582+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 416; c0 += 1)
    S[c0][c0+583] = MAX(S[c0][c0+583], S[c0+1][c0+583-1] + can_pair(RNA, c0, c0+583));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 415; c0 += 1)
    for (c1 = c0 + 584; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-584+c0] + S[-c0+c1-584+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][583+c0] + S[583+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 415; c0 += 1)
    S[c0][c0+584] = MAX(S[c0][c0+584], S[c0+1][c0+584-1] + can_pair(RNA, c0, c0+584));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 414; c0 += 1)
    for (c1 = c0 + 585; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-585+c0] + S[-c0+c1-585+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][584+c0] + S[584+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 414; c0 += 1)
    S[c0][c0+585] = MAX(S[c0][c0+585], S[c0+1][c0+585-1] + can_pair(RNA, c0, c0+585));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 413; c0 += 1)
    for (c1 = c0 + 586; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-586+c0] + S[-c0+c1-586+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][585+c0] + S[585+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 413; c0 += 1)
    S[c0][c0+586] = MAX(S[c0][c0+586], S[c0+1][c0+586-1] + can_pair(RNA, c0, c0+586));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 412; c0 += 1)
    for (c1 = c0 + 587; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-587+c0] + S[-c0+c1-587+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][586+c0] + S[586+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 412; c0 += 1)
    S[c0][c0+587] = MAX(S[c0][c0+587], S[c0+1][c0+587-1] + can_pair(RNA, c0, c0+587));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 411; c0 += 1)
    for (c1 = c0 + 588; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-588+c0] + S[-c0+c1-588+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][587+c0] + S[587+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 411; c0 += 1)
    S[c0][c0+588] = MAX(S[c0][c0+588], S[c0+1][c0+588-1] + can_pair(RNA, c0, c0+588));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 410; c0 += 1)
    for (c1 = c0 + 589; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-589+c0] + S[-c0+c1-589+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][588+c0] + S[588+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 410; c0 += 1)
    S[c0][c0+589] = MAX(S[c0][c0+589], S[c0+1][c0+589-1] + can_pair(RNA, c0, c0+589));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 409; c0 += 1)
    for (c1 = c0 + 590; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-590+c0] + S[-c0+c1-590+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][589+c0] + S[589+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 409; c0 += 1)
    S[c0][c0+590] = MAX(S[c0][c0+590], S[c0+1][c0+590-1] + can_pair(RNA, c0, c0+590));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 408; c0 += 1)
    for (c1 = c0 + 591; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-591+c0] + S[-c0+c1-591+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][590+c0] + S[590+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 408; c0 += 1)
    S[c0][c0+591] = MAX(S[c0][c0+591], S[c0+1][c0+591-1] + can_pair(RNA, c0, c0+591));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 407; c0 += 1)
    for (c1 = c0 + 592; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-592+c0] + S[-c0+c1-592+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][591+c0] + S[591+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 407; c0 += 1)
    S[c0][c0+592] = MAX(S[c0][c0+592], S[c0+1][c0+592-1] + can_pair(RNA, c0, c0+592));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 406; c0 += 1)
    for (c1 = c0 + 593; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-593+c0] + S[-c0+c1-593+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][592+c0] + S[592+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 406; c0 += 1)
    S[c0][c0+593] = MAX(S[c0][c0+593], S[c0+1][c0+593-1] + can_pair(RNA, c0, c0+593));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 405; c0 += 1)
    for (c1 = c0 + 594; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-594+c0] + S[-c0+c1-594+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][593+c0] + S[593+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 405; c0 += 1)
    S[c0][c0+594] = MAX(S[c0][c0+594], S[c0+1][c0+594-1] + can_pair(RNA, c0, c0+594));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 404; c0 += 1)
    for (c1 = c0 + 595; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-595+c0] + S[-c0+c1-595+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][594+c0] + S[594+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 404; c0 += 1)
    S[c0][c0+595] = MAX(S[c0][c0+595], S[c0+1][c0+595-1] + can_pair(RNA, c0, c0+595));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 403; c0 += 1)
    for (c1 = c0 + 596; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-596+c0] + S[-c0+c1-596+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][595+c0] + S[595+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 403; c0 += 1)
    S[c0][c0+596] = MAX(S[c0][c0+596], S[c0+1][c0+596-1] + can_pair(RNA, c0, c0+596));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 402; c0 += 1)
    for (c1 = c0 + 597; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-597+c0] + S[-c0+c1-597+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][596+c0] + S[596+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 402; c0 += 1)
    S[c0][c0+597] = MAX(S[c0][c0+597], S[c0+1][c0+597-1] + can_pair(RNA, c0, c0+597));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 401; c0 += 1)
    for (c1 = c0 + 598; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-598+c0] + S[-c0+c1-598+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][597+c0] + S[597+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 401; c0 += 1)
    S[c0][c0+598] = MAX(S[c0][c0+598], S[c0+1][c0+598-1] + can_pair(RNA, c0, c0+598));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 400; c0 += 1)
    for (c1 = c0 + 599; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-599+c0] + S[-c0+c1-599+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][598+c0] + S[598+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 400; c0 += 1)
    S[c0][c0+599] = MAX(S[c0][c0+599], S[c0+1][c0+599-1] + can_pair(RNA, c0, c0+599));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 399; c0 += 1)
    for (c1 = c0 + 600; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-600+c0] + S[-c0+c1-600+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][599+c0] + S[599+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 399; c0 += 1)
    S[c0][c0+600] = MAX(S[c0][c0+600], S[c0+1][c0+600-1] + can_pair(RNA, c0, c0+600));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 398; c0 += 1)
    for (c1 = c0 + 601; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-601+c0] + S[-c0+c1-601+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][600+c0] + S[600+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 398; c0 += 1)
    S[c0][c0+601] = MAX(S[c0][c0+601], S[c0+1][c0+601-1] + can_pair(RNA, c0, c0+601));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 397; c0 += 1)
    for (c1 = c0 + 602; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-602+c0] + S[-c0+c1-602+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][601+c0] + S[601+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 397; c0 += 1)
    S[c0][c0+602] = MAX(S[c0][c0+602], S[c0+1][c0+602-1] + can_pair(RNA, c0, c0+602));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 396; c0 += 1)
    for (c1 = c0 + 603; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-603+c0] + S[-c0+c1-603+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][602+c0] + S[602+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 396; c0 += 1)
    S[c0][c0+603] = MAX(S[c0][c0+603], S[c0+1][c0+603-1] + can_pair(RNA, c0, c0+603));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 395; c0 += 1)
    for (c1 = c0 + 604; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-604+c0] + S[-c0+c1-604+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][603+c0] + S[603+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 395; c0 += 1)
    S[c0][c0+604] = MAX(S[c0][c0+604], S[c0+1][c0+604-1] + can_pair(RNA, c0, c0+604));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 394; c0 += 1)
    for (c1 = c0 + 605; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-605+c0] + S[-c0+c1-605+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][604+c0] + S[604+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 394; c0 += 1)
    S[c0][c0+605] = MAX(S[c0][c0+605], S[c0+1][c0+605-1] + can_pair(RNA, c0, c0+605));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 393; c0 += 1)
    for (c1 = c0 + 606; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-606+c0] + S[-c0+c1-606+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][605+c0] + S[605+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 393; c0 += 1)
    S[c0][c0+606] = MAX(S[c0][c0+606], S[c0+1][c0+606-1] + can_pair(RNA, c0, c0+606));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 392; c0 += 1)
    for (c1 = c0 + 607; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-607+c0] + S[-c0+c1-607+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][606+c0] + S[606+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 392; c0 += 1)
    S[c0][c0+607] = MAX(S[c0][c0+607], S[c0+1][c0+607-1] + can_pair(RNA, c0, c0+607));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 391; c0 += 1)
    for (c1 = c0 + 608; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-608+c0] + S[-c0+c1-608+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][607+c0] + S[607+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 391; c0 += 1)
    S[c0][c0+608] = MAX(S[c0][c0+608], S[c0+1][c0+608-1] + can_pair(RNA, c0, c0+608));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 390; c0 += 1)
    for (c1 = c0 + 609; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-609+c0] + S[-c0+c1-609+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][608+c0] + S[608+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 390; c0 += 1)
    S[c0][c0+609] = MAX(S[c0][c0+609], S[c0+1][c0+609-1] + can_pair(RNA, c0, c0+609));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 389; c0 += 1)
    for (c1 = c0 + 610; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-610+c0] + S[-c0+c1-610+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][609+c0] + S[609+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 389; c0 += 1)
    S[c0][c0+610] = MAX(S[c0][c0+610], S[c0+1][c0+610-1] + can_pair(RNA, c0, c0+610));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 388; c0 += 1)
    for (c1 = c0 + 611; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-611+c0] + S[-c0+c1-611+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][610+c0] + S[610+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 388; c0 += 1)
    S[c0][c0+611] = MAX(S[c0][c0+611], S[c0+1][c0+611-1] + can_pair(RNA, c0, c0+611));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 387; c0 += 1)
    for (c1 = c0 + 612; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-612+c0] + S[-c0+c1-612+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][611+c0] + S[611+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 387; c0 += 1)
    S[c0][c0+612] = MAX(S[c0][c0+612], S[c0+1][c0+612-1] + can_pair(RNA, c0, c0+612));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 386; c0 += 1)
    for (c1 = c0 + 613; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-613+c0] + S[-c0+c1-613+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][612+c0] + S[612+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 386; c0 += 1)
    S[c0][c0+613] = MAX(S[c0][c0+613], S[c0+1][c0+613-1] + can_pair(RNA, c0, c0+613));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 385; c0 += 1)
    for (c1 = c0 + 614; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-614+c0] + S[-c0+c1-614+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][613+c0] + S[613+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 385; c0 += 1)
    S[c0][c0+614] = MAX(S[c0][c0+614], S[c0+1][c0+614-1] + can_pair(RNA, c0, c0+614));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 384; c0 += 1)
    for (c1 = c0 + 615; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-615+c0] + S[-c0+c1-615+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][614+c0] + S[614+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 384; c0 += 1)
    S[c0][c0+615] = MAX(S[c0][c0+615], S[c0+1][c0+615-1] + can_pair(RNA, c0, c0+615));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 383; c0 += 1)
    for (c1 = c0 + 616; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-616+c0] + S[-c0+c1-616+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][615+c0] + S[615+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 383; c0 += 1)
    S[c0][c0+616] = MAX(S[c0][c0+616], S[c0+1][c0+616-1] + can_pair(RNA, c0, c0+616));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 382; c0 += 1)
    for (c1 = c0 + 617; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-617+c0] + S[-c0+c1-617+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][616+c0] + S[616+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 382; c0 += 1)
    S[c0][c0+617] = MAX(S[c0][c0+617], S[c0+1][c0+617-1] + can_pair(RNA, c0, c0+617));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 381; c0 += 1)
    for (c1 = c0 + 618; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-618+c0] + S[-c0+c1-618+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][617+c0] + S[617+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 381; c0 += 1)
    S[c0][c0+618] = MAX(S[c0][c0+618], S[c0+1][c0+618-1] + can_pair(RNA, c0, c0+618));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 380; c0 += 1)
    for (c1 = c0 + 619; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-619+c0] + S[-c0+c1-619+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][618+c0] + S[618+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 380; c0 += 1)
    S[c0][c0+619] = MAX(S[c0][c0+619], S[c0+1][c0+619-1] + can_pair(RNA, c0, c0+619));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 379; c0 += 1)
    for (c1 = c0 + 620; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-620+c0] + S[-c0+c1-620+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][619+c0] + S[619+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 379; c0 += 1)
    S[c0][c0+620] = MAX(S[c0][c0+620], S[c0+1][c0+620-1] + can_pair(RNA, c0, c0+620));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 378; c0 += 1)
    for (c1 = c0 + 621; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-621+c0] + S[-c0+c1-621+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][620+c0] + S[620+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 378; c0 += 1)
    S[c0][c0+621] = MAX(S[c0][c0+621], S[c0+1][c0+621-1] + can_pair(RNA, c0, c0+621));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 377; c0 += 1)
    for (c1 = c0 + 622; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-622+c0] + S[-c0+c1-622+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][621+c0] + S[621+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 377; c0 += 1)
    S[c0][c0+622] = MAX(S[c0][c0+622], S[c0+1][c0+622-1] + can_pair(RNA, c0, c0+622));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 376; c0 += 1)
    for (c1 = c0 + 623; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-623+c0] + S[-c0+c1-623+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][622+c0] + S[622+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 376; c0 += 1)
    S[c0][c0+623] = MAX(S[c0][c0+623], S[c0+1][c0+623-1] + can_pair(RNA, c0, c0+623));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 375; c0 += 1)
    for (c1 = c0 + 624; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-624+c0] + S[-c0+c1-624+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][623+c0] + S[623+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 375; c0 += 1)
    S[c0][c0+624] = MAX(S[c0][c0+624], S[c0+1][c0+624-1] + can_pair(RNA, c0, c0+624));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 374; c0 += 1)
    for (c1 = c0 + 625; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-625+c0] + S[-c0+c1-625+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][624+c0] + S[624+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 374; c0 += 1)
    S[c0][c0+625] = MAX(S[c0][c0+625], S[c0+1][c0+625-1] + can_pair(RNA, c0, c0+625));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 373; c0 += 1)
    for (c1 = c0 + 626; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-626+c0] + S[-c0+c1-626+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][625+c0] + S[625+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 373; c0 += 1)
    S[c0][c0+626] = MAX(S[c0][c0+626], S[c0+1][c0+626-1] + can_pair(RNA, c0, c0+626));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 372; c0 += 1)
    for (c1 = c0 + 627; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-627+c0] + S[-c0+c1-627+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][626+c0] + S[626+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 372; c0 += 1)
    S[c0][c0+627] = MAX(S[c0][c0+627], S[c0+1][c0+627-1] + can_pair(RNA, c0, c0+627));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 371; c0 += 1)
    for (c1 = c0 + 628; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-628+c0] + S[-c0+c1-628+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][627+c0] + S[627+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 371; c0 += 1)
    S[c0][c0+628] = MAX(S[c0][c0+628], S[c0+1][c0+628-1] + can_pair(RNA, c0, c0+628));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 370; c0 += 1)
    for (c1 = c0 + 629; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-629+c0] + S[-c0+c1-629+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][628+c0] + S[628+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 370; c0 += 1)
    S[c0][c0+629] = MAX(S[c0][c0+629], S[c0+1][c0+629-1] + can_pair(RNA, c0, c0+629));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 369; c0 += 1)
    for (c1 = c0 + 630; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-630+c0] + S[-c0+c1-630+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][629+c0] + S[629+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 369; c0 += 1)
    S[c0][c0+630] = MAX(S[c0][c0+630], S[c0+1][c0+630-1] + can_pair(RNA, c0, c0+630));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 368; c0 += 1)
    for (c1 = c0 + 631; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-631+c0] + S[-c0+c1-631+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][630+c0] + S[630+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 368; c0 += 1)
    S[c0][c0+631] = MAX(S[c0][c0+631], S[c0+1][c0+631-1] + can_pair(RNA, c0, c0+631));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 367; c0 += 1)
    for (c1 = c0 + 632; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-632+c0] + S[-c0+c1-632+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][631+c0] + S[631+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 367; c0 += 1)
    S[c0][c0+632] = MAX(S[c0][c0+632], S[c0+1][c0+632-1] + can_pair(RNA, c0, c0+632));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 366; c0 += 1)
    for (c1 = c0 + 633; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-633+c0] + S[-c0+c1-633+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][632+c0] + S[632+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 366; c0 += 1)
    S[c0][c0+633] = MAX(S[c0][c0+633], S[c0+1][c0+633-1] + can_pair(RNA, c0, c0+633));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 365; c0 += 1)
    for (c1 = c0 + 634; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-634+c0] + S[-c0+c1-634+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][633+c0] + S[633+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 365; c0 += 1)
    S[c0][c0+634] = MAX(S[c0][c0+634], S[c0+1][c0+634-1] + can_pair(RNA, c0, c0+634));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 364; c0 += 1)
    for (c1 = c0 + 635; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-635+c0] + S[-c0+c1-635+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][634+c0] + S[634+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 364; c0 += 1)
    S[c0][c0+635] = MAX(S[c0][c0+635], S[c0+1][c0+635-1] + can_pair(RNA, c0, c0+635));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 363; c0 += 1)
    for (c1 = c0 + 636; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-636+c0] + S[-c0+c1-636+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][635+c0] + S[635+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 363; c0 += 1)
    S[c0][c0+636] = MAX(S[c0][c0+636], S[c0+1][c0+636-1] + can_pair(RNA, c0, c0+636));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 362; c0 += 1)
    for (c1 = c0 + 637; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-637+c0] + S[-c0+c1-637+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][636+c0] + S[636+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 362; c0 += 1)
    S[c0][c0+637] = MAX(S[c0][c0+637], S[c0+1][c0+637-1] + can_pair(RNA, c0, c0+637));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 361; c0 += 1)
    for (c1 = c0 + 638; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-638+c0] + S[-c0+c1-638+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][637+c0] + S[637+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 361; c0 += 1)
    S[c0][c0+638] = MAX(S[c0][c0+638], S[c0+1][c0+638-1] + can_pair(RNA, c0, c0+638));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 360; c0 += 1)
    for (c1 = c0 + 639; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-639+c0] + S[-c0+c1-639+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][638+c0] + S[638+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 360; c0 += 1)
    S[c0][c0+639] = MAX(S[c0][c0+639], S[c0+1][c0+639-1] + can_pair(RNA, c0, c0+639));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 359; c0 += 1)
    for (c1 = c0 + 640; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-640+c0] + S[-c0+c1-640+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][639+c0] + S[639+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 359; c0 += 1)
    S[c0][c0+640] = MAX(S[c0][c0+640], S[c0+1][c0+640-1] + can_pair(RNA, c0, c0+640));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 358; c0 += 1)
    for (c1 = c0 + 641; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-641+c0] + S[-c0+c1-641+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][640+c0] + S[640+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 358; c0 += 1)
    S[c0][c0+641] = MAX(S[c0][c0+641], S[c0+1][c0+641-1] + can_pair(RNA, c0, c0+641));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 357; c0 += 1)
    for (c1 = c0 + 642; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-642+c0] + S[-c0+c1-642+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][641+c0] + S[641+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 357; c0 += 1)
    S[c0][c0+642] = MAX(S[c0][c0+642], S[c0+1][c0+642-1] + can_pair(RNA, c0, c0+642));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 356; c0 += 1)
    for (c1 = c0 + 643; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-643+c0] + S[-c0+c1-643+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][642+c0] + S[642+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 356; c0 += 1)
    S[c0][c0+643] = MAX(S[c0][c0+643], S[c0+1][c0+643-1] + can_pair(RNA, c0, c0+643));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 355; c0 += 1)
    for (c1 = c0 + 644; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-644+c0] + S[-c0+c1-644+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][643+c0] + S[643+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 355; c0 += 1)
    S[c0][c0+644] = MAX(S[c0][c0+644], S[c0+1][c0+644-1] + can_pair(RNA, c0, c0+644));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 354; c0 += 1)
    for (c1 = c0 + 645; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-645+c0] + S[-c0+c1-645+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][644+c0] + S[644+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 354; c0 += 1)
    S[c0][c0+645] = MAX(S[c0][c0+645], S[c0+1][c0+645-1] + can_pair(RNA, c0, c0+645));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 353; c0 += 1)
    for (c1 = c0 + 646; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-646+c0] + S[-c0+c1-646+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][645+c0] + S[645+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 353; c0 += 1)
    S[c0][c0+646] = MAX(S[c0][c0+646], S[c0+1][c0+646-1] + can_pair(RNA, c0, c0+646));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 352; c0 += 1)
    for (c1 = c0 + 647; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-647+c0] + S[-c0+c1-647+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][646+c0] + S[646+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 352; c0 += 1)
    S[c0][c0+647] = MAX(S[c0][c0+647], S[c0+1][c0+647-1] + can_pair(RNA, c0, c0+647));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 351; c0 += 1)
    for (c1 = c0 + 648; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-648+c0] + S[-c0+c1-648+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][647+c0] + S[647+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 351; c0 += 1)
    S[c0][c0+648] = MAX(S[c0][c0+648], S[c0+1][c0+648-1] + can_pair(RNA, c0, c0+648));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 350; c0 += 1)
    for (c1 = c0 + 649; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-649+c0] + S[-c0+c1-649+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][648+c0] + S[648+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 350; c0 += 1)
    S[c0][c0+649] = MAX(S[c0][c0+649], S[c0+1][c0+649-1] + can_pair(RNA, c0, c0+649));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 349; c0 += 1)
    for (c1 = c0 + 650; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-650+c0] + S[-c0+c1-650+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][649+c0] + S[649+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 349; c0 += 1)
    S[c0][c0+650] = MAX(S[c0][c0+650], S[c0+1][c0+650-1] + can_pair(RNA, c0, c0+650));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 348; c0 += 1)
    for (c1 = c0 + 651; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-651+c0] + S[-c0+c1-651+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][650+c0] + S[650+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 348; c0 += 1)
    S[c0][c0+651] = MAX(S[c0][c0+651], S[c0+1][c0+651-1] + can_pair(RNA, c0, c0+651));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 347; c0 += 1)
    for (c1 = c0 + 652; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-652+c0] + S[-c0+c1-652+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][651+c0] + S[651+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 347; c0 += 1)
    S[c0][c0+652] = MAX(S[c0][c0+652], S[c0+1][c0+652-1] + can_pair(RNA, c0, c0+652));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 346; c0 += 1)
    for (c1 = c0 + 653; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-653+c0] + S[-c0+c1-653+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][652+c0] + S[652+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 346; c0 += 1)
    S[c0][c0+653] = MAX(S[c0][c0+653], S[c0+1][c0+653-1] + can_pair(RNA, c0, c0+653));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 345; c0 += 1)
    for (c1 = c0 + 654; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-654+c0] + S[-c0+c1-654+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][653+c0] + S[653+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 345; c0 += 1)
    S[c0][c0+654] = MAX(S[c0][c0+654], S[c0+1][c0+654-1] + can_pair(RNA, c0, c0+654));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 344; c0 += 1)
    for (c1 = c0 + 655; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-655+c0] + S[-c0+c1-655+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][654+c0] + S[654+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 344; c0 += 1)
    S[c0][c0+655] = MAX(S[c0][c0+655], S[c0+1][c0+655-1] + can_pair(RNA, c0, c0+655));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 343; c0 += 1)
    for (c1 = c0 + 656; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-656+c0] + S[-c0+c1-656+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][655+c0] + S[655+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 343; c0 += 1)
    S[c0][c0+656] = MAX(S[c0][c0+656], S[c0+1][c0+656-1] + can_pair(RNA, c0, c0+656));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 342; c0 += 1)
    for (c1 = c0 + 657; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-657+c0] + S[-c0+c1-657+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][656+c0] + S[656+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 342; c0 += 1)
    S[c0][c0+657] = MAX(S[c0][c0+657], S[c0+1][c0+657-1] + can_pair(RNA, c0, c0+657));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 341; c0 += 1)
    for (c1 = c0 + 658; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-658+c0] + S[-c0+c1-658+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][657+c0] + S[657+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 341; c0 += 1)
    S[c0][c0+658] = MAX(S[c0][c0+658], S[c0+1][c0+658-1] + can_pair(RNA, c0, c0+658));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 340; c0 += 1)
    for (c1 = c0 + 659; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-659+c0] + S[-c0+c1-659+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][658+c0] + S[658+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 340; c0 += 1)
    S[c0][c0+659] = MAX(S[c0][c0+659], S[c0+1][c0+659-1] + can_pair(RNA, c0, c0+659));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 339; c0 += 1)
    for (c1 = c0 + 660; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-660+c0] + S[-c0+c1-660+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][659+c0] + S[659+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 339; c0 += 1)
    S[c0][c0+660] = MAX(S[c0][c0+660], S[c0+1][c0+660-1] + can_pair(RNA, c0, c0+660));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 338; c0 += 1)
    for (c1 = c0 + 661; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-661+c0] + S[-c0+c1-661+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][660+c0] + S[660+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 338; c0 += 1)
    S[c0][c0+661] = MAX(S[c0][c0+661], S[c0+1][c0+661-1] + can_pair(RNA, c0, c0+661));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 337; c0 += 1)
    for (c1 = c0 + 662; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-662+c0] + S[-c0+c1-662+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][661+c0] + S[661+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 337; c0 += 1)
    S[c0][c0+662] = MAX(S[c0][c0+662], S[c0+1][c0+662-1] + can_pair(RNA, c0, c0+662));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 336; c0 += 1)
    for (c1 = c0 + 663; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-663+c0] + S[-c0+c1-663+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][662+c0] + S[662+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 336; c0 += 1)
    S[c0][c0+663] = MAX(S[c0][c0+663], S[c0+1][c0+663-1] + can_pair(RNA, c0, c0+663));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 335; c0 += 1)
    for (c1 = c0 + 664; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-664+c0] + S[-c0+c1-664+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][663+c0] + S[663+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 335; c0 += 1)
    S[c0][c0+664] = MAX(S[c0][c0+664], S[c0+1][c0+664-1] + can_pair(RNA, c0, c0+664));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 334; c0 += 1)
    for (c1 = c0 + 665; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-665+c0] + S[-c0+c1-665+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][664+c0] + S[664+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 334; c0 += 1)
    S[c0][c0+665] = MAX(S[c0][c0+665], S[c0+1][c0+665-1] + can_pair(RNA, c0, c0+665));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 333; c0 += 1)
    for (c1 = c0 + 666; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-666+c0] + S[-c0+c1-666+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][665+c0] + S[665+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 333; c0 += 1)
    S[c0][c0+666] = MAX(S[c0][c0+666], S[c0+1][c0+666-1] + can_pair(RNA, c0, c0+666));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 332; c0 += 1)
    for (c1 = c0 + 667; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-667+c0] + S[-c0+c1-667+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][666+c0] + S[666+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 332; c0 += 1)
    S[c0][c0+667] = MAX(S[c0][c0+667], S[c0+1][c0+667-1] + can_pair(RNA, c0, c0+667));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 331; c0 += 1)
    for (c1 = c0 + 668; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-668+c0] + S[-c0+c1-668+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][667+c0] + S[667+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 331; c0 += 1)
    S[c0][c0+668] = MAX(S[c0][c0+668], S[c0+1][c0+668-1] + can_pair(RNA, c0, c0+668));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 330; c0 += 1)
    for (c1 = c0 + 669; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-669+c0] + S[-c0+c1-669+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][668+c0] + S[668+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 330; c0 += 1)
    S[c0][c0+669] = MAX(S[c0][c0+669], S[c0+1][c0+669-1] + can_pair(RNA, c0, c0+669));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 329; c0 += 1)
    for (c1 = c0 + 670; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-670+c0] + S[-c0+c1-670+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][669+c0] + S[669+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 329; c0 += 1)
    S[c0][c0+670] = MAX(S[c0][c0+670], S[c0+1][c0+670-1] + can_pair(RNA, c0, c0+670));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 328; c0 += 1)
    for (c1 = c0 + 671; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-671+c0] + S[-c0+c1-671+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][670+c0] + S[670+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 328; c0 += 1)
    S[c0][c0+671] = MAX(S[c0][c0+671], S[c0+1][c0+671-1] + can_pair(RNA, c0, c0+671));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 327; c0 += 1)
    for (c1 = c0 + 672; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-672+c0] + S[-c0+c1-672+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][671+c0] + S[671+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 327; c0 += 1)
    S[c0][c0+672] = MAX(S[c0][c0+672], S[c0+1][c0+672-1] + can_pair(RNA, c0, c0+672));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 326; c0 += 1)
    for (c1 = c0 + 673; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-673+c0] + S[-c0+c1-673+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][672+c0] + S[672+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 326; c0 += 1)
    S[c0][c0+673] = MAX(S[c0][c0+673], S[c0+1][c0+673-1] + can_pair(RNA, c0, c0+673));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 325; c0 += 1)
    for (c1 = c0 + 674; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-674+c0] + S[-c0+c1-674+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][673+c0] + S[673+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 325; c0 += 1)
    S[c0][c0+674] = MAX(S[c0][c0+674], S[c0+1][c0+674-1] + can_pair(RNA, c0, c0+674));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 324; c0 += 1)
    for (c1 = c0 + 675; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-675+c0] + S[-c0+c1-675+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][674+c0] + S[674+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 324; c0 += 1)
    S[c0][c0+675] = MAX(S[c0][c0+675], S[c0+1][c0+675-1] + can_pair(RNA, c0, c0+675));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 323; c0 += 1)
    for (c1 = c0 + 676; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-676+c0] + S[-c0+c1-676+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][675+c0] + S[675+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 323; c0 += 1)
    S[c0][c0+676] = MAX(S[c0][c0+676], S[c0+1][c0+676-1] + can_pair(RNA, c0, c0+676));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 322; c0 += 1)
    for (c1 = c0 + 677; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-677+c0] + S[-c0+c1-677+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][676+c0] + S[676+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 322; c0 += 1)
    S[c0][c0+677] = MAX(S[c0][c0+677], S[c0+1][c0+677-1] + can_pair(RNA, c0, c0+677));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 321; c0 += 1)
    for (c1 = c0 + 678; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-678+c0] + S[-c0+c1-678+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][677+c0] + S[677+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 321; c0 += 1)
    S[c0][c0+678] = MAX(S[c0][c0+678], S[c0+1][c0+678-1] + can_pair(RNA, c0, c0+678));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 320; c0 += 1)
    for (c1 = c0 + 679; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-679+c0] + S[-c0+c1-679+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][678+c0] + S[678+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 320; c0 += 1)
    S[c0][c0+679] = MAX(S[c0][c0+679], S[c0+1][c0+679-1] + can_pair(RNA, c0, c0+679));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 319; c0 += 1)
    for (c1 = c0 + 680; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-680+c0] + S[-c0+c1-680+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][679+c0] + S[679+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 319; c0 += 1)
    S[c0][c0+680] = MAX(S[c0][c0+680], S[c0+1][c0+680-1] + can_pair(RNA, c0, c0+680));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 318; c0 += 1)
    for (c1 = c0 + 681; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-681+c0] + S[-c0+c1-681+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][680+c0] + S[680+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 318; c0 += 1)
    S[c0][c0+681] = MAX(S[c0][c0+681], S[c0+1][c0+681-1] + can_pair(RNA, c0, c0+681));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 317; c0 += 1)
    for (c1 = c0 + 682; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-682+c0] + S[-c0+c1-682+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][681+c0] + S[681+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 317; c0 += 1)
    S[c0][c0+682] = MAX(S[c0][c0+682], S[c0+1][c0+682-1] + can_pair(RNA, c0, c0+682));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 316; c0 += 1)
    for (c1 = c0 + 683; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-683+c0] + S[-c0+c1-683+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][682+c0] + S[682+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 316; c0 += 1)
    S[c0][c0+683] = MAX(S[c0][c0+683], S[c0+1][c0+683-1] + can_pair(RNA, c0, c0+683));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 315; c0 += 1)
    for (c1 = c0 + 684; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-684+c0] + S[-c0+c1-684+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][683+c0] + S[683+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 315; c0 += 1)
    S[c0][c0+684] = MAX(S[c0][c0+684], S[c0+1][c0+684-1] + can_pair(RNA, c0, c0+684));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 314; c0 += 1)
    for (c1 = c0 + 685; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-685+c0] + S[-c0+c1-685+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][684+c0] + S[684+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 314; c0 += 1)
    S[c0][c0+685] = MAX(S[c0][c0+685], S[c0+1][c0+685-1] + can_pair(RNA, c0, c0+685));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 313; c0 += 1)
    for (c1 = c0 + 686; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-686+c0] + S[-c0+c1-686+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][685+c0] + S[685+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 313; c0 += 1)
    S[c0][c0+686] = MAX(S[c0][c0+686], S[c0+1][c0+686-1] + can_pair(RNA, c0, c0+686));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 312; c0 += 1)
    for (c1 = c0 + 687; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-687+c0] + S[-c0+c1-687+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][686+c0] + S[686+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 312; c0 += 1)
    S[c0][c0+687] = MAX(S[c0][c0+687], S[c0+1][c0+687-1] + can_pair(RNA, c0, c0+687));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 311; c0 += 1)
    for (c1 = c0 + 688; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-688+c0] + S[-c0+c1-688+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][687+c0] + S[687+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 311; c0 += 1)
    S[c0][c0+688] = MAX(S[c0][c0+688], S[c0+1][c0+688-1] + can_pair(RNA, c0, c0+688));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 310; c0 += 1)
    for (c1 = c0 + 689; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-689+c0] + S[-c0+c1-689+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][688+c0] + S[688+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 310; c0 += 1)
    S[c0][c0+689] = MAX(S[c0][c0+689], S[c0+1][c0+689-1] + can_pair(RNA, c0, c0+689));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 309; c0 += 1)
    for (c1 = c0 + 690; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-690+c0] + S[-c0+c1-690+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][689+c0] + S[689+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 309; c0 += 1)
    S[c0][c0+690] = MAX(S[c0][c0+690], S[c0+1][c0+690-1] + can_pair(RNA, c0, c0+690));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 308; c0 += 1)
    for (c1 = c0 + 691; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-691+c0] + S[-c0+c1-691+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][690+c0] + S[690+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 308; c0 += 1)
    S[c0][c0+691] = MAX(S[c0][c0+691], S[c0+1][c0+691-1] + can_pair(RNA, c0, c0+691));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 307; c0 += 1)
    for (c1 = c0 + 692; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-692+c0] + S[-c0+c1-692+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][691+c0] + S[691+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 307; c0 += 1)
    S[c0][c0+692] = MAX(S[c0][c0+692], S[c0+1][c0+692-1] + can_pair(RNA, c0, c0+692));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 306; c0 += 1)
    for (c1 = c0 + 693; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-693+c0] + S[-c0+c1-693+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][692+c0] + S[692+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 306; c0 += 1)
    S[c0][c0+693] = MAX(S[c0][c0+693], S[c0+1][c0+693-1] + can_pair(RNA, c0, c0+693));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 305; c0 += 1)
    for (c1 = c0 + 694; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-694+c0] + S[-c0+c1-694+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][693+c0] + S[693+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 305; c0 += 1)
    S[c0][c0+694] = MAX(S[c0][c0+694], S[c0+1][c0+694-1] + can_pair(RNA, c0, c0+694));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 304; c0 += 1)
    for (c1 = c0 + 695; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-695+c0] + S[-c0+c1-695+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][694+c0] + S[694+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 304; c0 += 1)
    S[c0][c0+695] = MAX(S[c0][c0+695], S[c0+1][c0+695-1] + can_pair(RNA, c0, c0+695));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 303; c0 += 1)
    for (c1 = c0 + 696; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-696+c0] + S[-c0+c1-696+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][695+c0] + S[695+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 303; c0 += 1)
    S[c0][c0+696] = MAX(S[c0][c0+696], S[c0+1][c0+696-1] + can_pair(RNA, c0, c0+696));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 302; c0 += 1)
    for (c1 = c0 + 697; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-697+c0] + S[-c0+c1-697+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][696+c0] + S[696+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 302; c0 += 1)
    S[c0][c0+697] = MAX(S[c0][c0+697], S[c0+1][c0+697-1] + can_pair(RNA, c0, c0+697));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 301; c0 += 1)
    for (c1 = c0 + 698; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-698+c0] + S[-c0+c1-698+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][697+c0] + S[697+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 301; c0 += 1)
    S[c0][c0+698] = MAX(S[c0][c0+698], S[c0+1][c0+698-1] + can_pair(RNA, c0, c0+698));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 300; c0 += 1)
    for (c1 = c0 + 699; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-699+c0] + S[-c0+c1-699+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][698+c0] + S[698+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 300; c0 += 1)
    S[c0][c0+699] = MAX(S[c0][c0+699], S[c0+1][c0+699-1] + can_pair(RNA, c0, c0+699));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 299; c0 += 1)
    for (c1 = c0 + 700; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-700+c0] + S[-c0+c1-700+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][699+c0] + S[699+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 299; c0 += 1)
    S[c0][c0+700] = MAX(S[c0][c0+700], S[c0+1][c0+700-1] + can_pair(RNA, c0, c0+700));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 298; c0 += 1)
    for (c1 = c0 + 701; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-701+c0] + S[-c0+c1-701+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][700+c0] + S[700+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 298; c0 += 1)
    S[c0][c0+701] = MAX(S[c0][c0+701], S[c0+1][c0+701-1] + can_pair(RNA, c0, c0+701));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 297; c0 += 1)
    for (c1 = c0 + 702; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-702+c0] + S[-c0+c1-702+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][701+c0] + S[701+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 297; c0 += 1)
    S[c0][c0+702] = MAX(S[c0][c0+702], S[c0+1][c0+702-1] + can_pair(RNA, c0, c0+702));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 296; c0 += 1)
    for (c1 = c0 + 703; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-703+c0] + S[-c0+c1-703+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][702+c0] + S[702+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 296; c0 += 1)
    S[c0][c0+703] = MAX(S[c0][c0+703], S[c0+1][c0+703-1] + can_pair(RNA, c0, c0+703));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 295; c0 += 1)
    for (c1 = c0 + 704; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-704+c0] + S[-c0+c1-704+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][703+c0] + S[703+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 295; c0 += 1)
    S[c0][c0+704] = MAX(S[c0][c0+704], S[c0+1][c0+704-1] + can_pair(RNA, c0, c0+704));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 294; c0 += 1)
    for (c1 = c0 + 705; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-705+c0] + S[-c0+c1-705+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][704+c0] + S[704+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 294; c0 += 1)
    S[c0][c0+705] = MAX(S[c0][c0+705], S[c0+1][c0+705-1] + can_pair(RNA, c0, c0+705));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 293; c0 += 1)
    for (c1 = c0 + 706; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-706+c0] + S[-c0+c1-706+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][705+c0] + S[705+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 293; c0 += 1)
    S[c0][c0+706] = MAX(S[c0][c0+706], S[c0+1][c0+706-1] + can_pair(RNA, c0, c0+706));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 292; c0 += 1)
    for (c1 = c0 + 707; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-707+c0] + S[-c0+c1-707+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][706+c0] + S[706+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 292; c0 += 1)
    S[c0][c0+707] = MAX(S[c0][c0+707], S[c0+1][c0+707-1] + can_pair(RNA, c0, c0+707));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 291; c0 += 1)
    for (c1 = c0 + 708; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-708+c0] + S[-c0+c1-708+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][707+c0] + S[707+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 291; c0 += 1)
    S[c0][c0+708] = MAX(S[c0][c0+708], S[c0+1][c0+708-1] + can_pair(RNA, c0, c0+708));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 290; c0 += 1)
    for (c1 = c0 + 709; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-709+c0] + S[-c0+c1-709+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][708+c0] + S[708+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 290; c0 += 1)
    S[c0][c0+709] = MAX(S[c0][c0+709], S[c0+1][c0+709-1] + can_pair(RNA, c0, c0+709));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 289; c0 += 1)
    for (c1 = c0 + 710; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-710+c0] + S[-c0+c1-710+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][709+c0] + S[709+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 289; c0 += 1)
    S[c0][c0+710] = MAX(S[c0][c0+710], S[c0+1][c0+710-1] + can_pair(RNA, c0, c0+710));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 288; c0 += 1)
    for (c1 = c0 + 711; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-711+c0] + S[-c0+c1-711+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][710+c0] + S[710+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 288; c0 += 1)
    S[c0][c0+711] = MAX(S[c0][c0+711], S[c0+1][c0+711-1] + can_pair(RNA, c0, c0+711));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 287; c0 += 1)
    for (c1 = c0 + 712; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-712+c0] + S[-c0+c1-712+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][711+c0] + S[711+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 287; c0 += 1)
    S[c0][c0+712] = MAX(S[c0][c0+712], S[c0+1][c0+712-1] + can_pair(RNA, c0, c0+712));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 286; c0 += 1)
    for (c1 = c0 + 713; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-713+c0] + S[-c0+c1-713+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][712+c0] + S[712+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 286; c0 += 1)
    S[c0][c0+713] = MAX(S[c0][c0+713], S[c0+1][c0+713-1] + can_pair(RNA, c0, c0+713));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 285; c0 += 1)
    for (c1 = c0 + 714; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-714+c0] + S[-c0+c1-714+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][713+c0] + S[713+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 285; c0 += 1)
    S[c0][c0+714] = MAX(S[c0][c0+714], S[c0+1][c0+714-1] + can_pair(RNA, c0, c0+714));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 284; c0 += 1)
    for (c1 = c0 + 715; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-715+c0] + S[-c0+c1-715+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][714+c0] + S[714+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 284; c0 += 1)
    S[c0][c0+715] = MAX(S[c0][c0+715], S[c0+1][c0+715-1] + can_pair(RNA, c0, c0+715));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 283; c0 += 1)
    for (c1 = c0 + 716; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-716+c0] + S[-c0+c1-716+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][715+c0] + S[715+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 283; c0 += 1)
    S[c0][c0+716] = MAX(S[c0][c0+716], S[c0+1][c0+716-1] + can_pair(RNA, c0, c0+716));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 282; c0 += 1)
    for (c1 = c0 + 717; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-717+c0] + S[-c0+c1-717+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][716+c0] + S[716+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 282; c0 += 1)
    S[c0][c0+717] = MAX(S[c0][c0+717], S[c0+1][c0+717-1] + can_pair(RNA, c0, c0+717));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 281; c0 += 1)
    for (c1 = c0 + 718; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-718+c0] + S[-c0+c1-718+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][717+c0] + S[717+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 281; c0 += 1)
    S[c0][c0+718] = MAX(S[c0][c0+718], S[c0+1][c0+718-1] + can_pair(RNA, c0, c0+718));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 280; c0 += 1)
    for (c1 = c0 + 719; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-719+c0] + S[-c0+c1-719+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][718+c0] + S[718+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 280; c0 += 1)
    S[c0][c0+719] = MAX(S[c0][c0+719], S[c0+1][c0+719-1] + can_pair(RNA, c0, c0+719));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 279; c0 += 1)
    for (c1 = c0 + 720; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-720+c0] + S[-c0+c1-720+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][719+c0] + S[719+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 279; c0 += 1)
    S[c0][c0+720] = MAX(S[c0][c0+720], S[c0+1][c0+720-1] + can_pair(RNA, c0, c0+720));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 278; c0 += 1)
    for (c1 = c0 + 721; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-721+c0] + S[-c0+c1-721+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][720+c0] + S[720+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 278; c0 += 1)
    S[c0][c0+721] = MAX(S[c0][c0+721], S[c0+1][c0+721-1] + can_pair(RNA, c0, c0+721));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 277; c0 += 1)
    for (c1 = c0 + 722; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-722+c0] + S[-c0+c1-722+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][721+c0] + S[721+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 277; c0 += 1)
    S[c0][c0+722] = MAX(S[c0][c0+722], S[c0+1][c0+722-1] + can_pair(RNA, c0, c0+722));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 276; c0 += 1)
    for (c1 = c0 + 723; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-723+c0] + S[-c0+c1-723+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][722+c0] + S[722+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 276; c0 += 1)
    S[c0][c0+723] = MAX(S[c0][c0+723], S[c0+1][c0+723-1] + can_pair(RNA, c0, c0+723));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 275; c0 += 1)
    for (c1 = c0 + 724; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-724+c0] + S[-c0+c1-724+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][723+c0] + S[723+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 275; c0 += 1)
    S[c0][c0+724] = MAX(S[c0][c0+724], S[c0+1][c0+724-1] + can_pair(RNA, c0, c0+724));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 274; c0 += 1)
    for (c1 = c0 + 725; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-725+c0] + S[-c0+c1-725+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][724+c0] + S[724+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 274; c0 += 1)
    S[c0][c0+725] = MAX(S[c0][c0+725], S[c0+1][c0+725-1] + can_pair(RNA, c0, c0+725));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 273; c0 += 1)
    for (c1 = c0 + 726; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-726+c0] + S[-c0+c1-726+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][725+c0] + S[725+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 273; c0 += 1)
    S[c0][c0+726] = MAX(S[c0][c0+726], S[c0+1][c0+726-1] + can_pair(RNA, c0, c0+726));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 272; c0 += 1)
    for (c1 = c0 + 727; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-727+c0] + S[-c0+c1-727+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][726+c0] + S[726+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 272; c0 += 1)
    S[c0][c0+727] = MAX(S[c0][c0+727], S[c0+1][c0+727-1] + can_pair(RNA, c0, c0+727));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 271; c0 += 1)
    for (c1 = c0 + 728; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-728+c0] + S[-c0+c1-728+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][727+c0] + S[727+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 271; c0 += 1)
    S[c0][c0+728] = MAX(S[c0][c0+728], S[c0+1][c0+728-1] + can_pair(RNA, c0, c0+728));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 270; c0 += 1)
    for (c1 = c0 + 729; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-729+c0] + S[-c0+c1-729+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][728+c0] + S[728+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 270; c0 += 1)
    S[c0][c0+729] = MAX(S[c0][c0+729], S[c0+1][c0+729-1] + can_pair(RNA, c0, c0+729));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 269; c0 += 1)
    for (c1 = c0 + 730; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-730+c0] + S[-c0+c1-730+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][729+c0] + S[729+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 269; c0 += 1)
    S[c0][c0+730] = MAX(S[c0][c0+730], S[c0+1][c0+730-1] + can_pair(RNA, c0, c0+730));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 268; c0 += 1)
    for (c1 = c0 + 731; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-731+c0] + S[-c0+c1-731+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][730+c0] + S[730+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 268; c0 += 1)
    S[c0][c0+731] = MAX(S[c0][c0+731], S[c0+1][c0+731-1] + can_pair(RNA, c0, c0+731));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 267; c0 += 1)
    for (c1 = c0 + 732; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-732+c0] + S[-c0+c1-732+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][731+c0] + S[731+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 267; c0 += 1)
    S[c0][c0+732] = MAX(S[c0][c0+732], S[c0+1][c0+732-1] + can_pair(RNA, c0, c0+732));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 266; c0 += 1)
    for (c1 = c0 + 733; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-733+c0] + S[-c0+c1-733+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][732+c0] + S[732+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 266; c0 += 1)
    S[c0][c0+733] = MAX(S[c0][c0+733], S[c0+1][c0+733-1] + can_pair(RNA, c0, c0+733));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 265; c0 += 1)
    for (c1 = c0 + 734; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-734+c0] + S[-c0+c1-734+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][733+c0] + S[733+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 265; c0 += 1)
    S[c0][c0+734] = MAX(S[c0][c0+734], S[c0+1][c0+734-1] + can_pair(RNA, c0, c0+734));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 264; c0 += 1)
    for (c1 = c0 + 735; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-735+c0] + S[-c0+c1-735+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][734+c0] + S[734+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 264; c0 += 1)
    S[c0][c0+735] = MAX(S[c0][c0+735], S[c0+1][c0+735-1] + can_pair(RNA, c0, c0+735));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 263; c0 += 1)
    for (c1 = c0 + 736; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-736+c0] + S[-c0+c1-736+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][735+c0] + S[735+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 263; c0 += 1)
    S[c0][c0+736] = MAX(S[c0][c0+736], S[c0+1][c0+736-1] + can_pair(RNA, c0, c0+736));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 262; c0 += 1)
    for (c1 = c0 + 737; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-737+c0] + S[-c0+c1-737+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][736+c0] + S[736+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 262; c0 += 1)
    S[c0][c0+737] = MAX(S[c0][c0+737], S[c0+1][c0+737-1] + can_pair(RNA, c0, c0+737));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 261; c0 += 1)
    for (c1 = c0 + 738; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-738+c0] + S[-c0+c1-738+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][737+c0] + S[737+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 261; c0 += 1)
    S[c0][c0+738] = MAX(S[c0][c0+738], S[c0+1][c0+738-1] + can_pair(RNA, c0, c0+738));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 260; c0 += 1)
    for (c1 = c0 + 739; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-739+c0] + S[-c0+c1-739+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][738+c0] + S[738+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 260; c0 += 1)
    S[c0][c0+739] = MAX(S[c0][c0+739], S[c0+1][c0+739-1] + can_pair(RNA, c0, c0+739));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 259; c0 += 1)
    for (c1 = c0 + 740; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-740+c0] + S[-c0+c1-740+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][739+c0] + S[739+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 259; c0 += 1)
    S[c0][c0+740] = MAX(S[c0][c0+740], S[c0+1][c0+740-1] + can_pair(RNA, c0, c0+740));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 258; c0 += 1)
    for (c1 = c0 + 741; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-741+c0] + S[-c0+c1-741+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][740+c0] + S[740+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 258; c0 += 1)
    S[c0][c0+741] = MAX(S[c0][c0+741], S[c0+1][c0+741-1] + can_pair(RNA, c0, c0+741));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 257; c0 += 1)
    for (c1 = c0 + 742; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-742+c0] + S[-c0+c1-742+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][741+c0] + S[741+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 257; c0 += 1)
    S[c0][c0+742] = MAX(S[c0][c0+742], S[c0+1][c0+742-1] + can_pair(RNA, c0, c0+742));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 256; c0 += 1)
    for (c1 = c0 + 743; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-743+c0] + S[-c0+c1-743+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][742+c0] + S[742+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 256; c0 += 1)
    S[c0][c0+743] = MAX(S[c0][c0+743], S[c0+1][c0+743-1] + can_pair(RNA, c0, c0+743));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 255; c0 += 1)
    for (c1 = c0 + 744; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-744+c0] + S[-c0+c1-744+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][743+c0] + S[743+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 255; c0 += 1)
    S[c0][c0+744] = MAX(S[c0][c0+744], S[c0+1][c0+744-1] + can_pair(RNA, c0, c0+744));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 254; c0 += 1)
    for (c1 = c0 + 745; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-745+c0] + S[-c0+c1-745+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][744+c0] + S[744+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 254; c0 += 1)
    S[c0][c0+745] = MAX(S[c0][c0+745], S[c0+1][c0+745-1] + can_pair(RNA, c0, c0+745));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 253; c0 += 1)
    for (c1 = c0 + 746; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-746+c0] + S[-c0+c1-746+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][745+c0] + S[745+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 253; c0 += 1)
    S[c0][c0+746] = MAX(S[c0][c0+746], S[c0+1][c0+746-1] + can_pair(RNA, c0, c0+746));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 252; c0 += 1)
    for (c1 = c0 + 747; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-747+c0] + S[-c0+c1-747+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][746+c0] + S[746+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 252; c0 += 1)
    S[c0][c0+747] = MAX(S[c0][c0+747], S[c0+1][c0+747-1] + can_pair(RNA, c0, c0+747));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 251; c0 += 1)
    for (c1 = c0 + 748; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-748+c0] + S[-c0+c1-748+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][747+c0] + S[747+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 251; c0 += 1)
    S[c0][c0+748] = MAX(S[c0][c0+748], S[c0+1][c0+748-1] + can_pair(RNA, c0, c0+748));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 250; c0 += 1)
    for (c1 = c0 + 749; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-749+c0] + S[-c0+c1-749+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][748+c0] + S[748+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 250; c0 += 1)
    S[c0][c0+749] = MAX(S[c0][c0+749], S[c0+1][c0+749-1] + can_pair(RNA, c0, c0+749));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 249; c0 += 1)
    for (c1 = c0 + 750; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-750+c0] + S[-c0+c1-750+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][749+c0] + S[749+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 249; c0 += 1)
    S[c0][c0+750] = MAX(S[c0][c0+750], S[c0+1][c0+750-1] + can_pair(RNA, c0, c0+750));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 248; c0 += 1)
    for (c1 = c0 + 751; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-751+c0] + S[-c0+c1-751+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][750+c0] + S[750+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 248; c0 += 1)
    S[c0][c0+751] = MAX(S[c0][c0+751], S[c0+1][c0+751-1] + can_pair(RNA, c0, c0+751));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 247; c0 += 1)
    for (c1 = c0 + 752; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-752+c0] + S[-c0+c1-752+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][751+c0] + S[751+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 247; c0 += 1)
    S[c0][c0+752] = MAX(S[c0][c0+752], S[c0+1][c0+752-1] + can_pair(RNA, c0, c0+752));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 246; c0 += 1)
    for (c1 = c0 + 753; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-753+c0] + S[-c0+c1-753+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][752+c0] + S[752+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 246; c0 += 1)
    S[c0][c0+753] = MAX(S[c0][c0+753], S[c0+1][c0+753-1] + can_pair(RNA, c0, c0+753));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 245; c0 += 1)
    for (c1 = c0 + 754; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-754+c0] + S[-c0+c1-754+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][753+c0] + S[753+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 245; c0 += 1)
    S[c0][c0+754] = MAX(S[c0][c0+754], S[c0+1][c0+754-1] + can_pair(RNA, c0, c0+754));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 244; c0 += 1)
    for (c1 = c0 + 755; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-755+c0] + S[-c0+c1-755+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][754+c0] + S[754+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 244; c0 += 1)
    S[c0][c0+755] = MAX(S[c0][c0+755], S[c0+1][c0+755-1] + can_pair(RNA, c0, c0+755));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 243; c0 += 1)
    for (c1 = c0 + 756; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-756+c0] + S[-c0+c1-756+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][755+c0] + S[755+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 243; c0 += 1)
    S[c0][c0+756] = MAX(S[c0][c0+756], S[c0+1][c0+756-1] + can_pair(RNA, c0, c0+756));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 242; c0 += 1)
    for (c1 = c0 + 757; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-757+c0] + S[-c0+c1-757+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][756+c0] + S[756+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 242; c0 += 1)
    S[c0][c0+757] = MAX(S[c0][c0+757], S[c0+1][c0+757-1] + can_pair(RNA, c0, c0+757));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 241; c0 += 1)
    for (c1 = c0 + 758; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-758+c0] + S[-c0+c1-758+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][757+c0] + S[757+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 241; c0 += 1)
    S[c0][c0+758] = MAX(S[c0][c0+758], S[c0+1][c0+758-1] + can_pair(RNA, c0, c0+758));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 240; c0 += 1)
    for (c1 = c0 + 759; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-759+c0] + S[-c0+c1-759+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][758+c0] + S[758+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 240; c0 += 1)
    S[c0][c0+759] = MAX(S[c0][c0+759], S[c0+1][c0+759-1] + can_pair(RNA, c0, c0+759));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 239; c0 += 1)
    for (c1 = c0 + 760; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-760+c0] + S[-c0+c1-760+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][759+c0] + S[759+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 239; c0 += 1)
    S[c0][c0+760] = MAX(S[c0][c0+760], S[c0+1][c0+760-1] + can_pair(RNA, c0, c0+760));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 238; c0 += 1)
    for (c1 = c0 + 761; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-761+c0] + S[-c0+c1-761+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][760+c0] + S[760+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 238; c0 += 1)
    S[c0][c0+761] = MAX(S[c0][c0+761], S[c0+1][c0+761-1] + can_pair(RNA, c0, c0+761));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 237; c0 += 1)
    for (c1 = c0 + 762; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-762+c0] + S[-c0+c1-762+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][761+c0] + S[761+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 237; c0 += 1)
    S[c0][c0+762] = MAX(S[c0][c0+762], S[c0+1][c0+762-1] + can_pair(RNA, c0, c0+762));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 236; c0 += 1)
    for (c1 = c0 + 763; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-763+c0] + S[-c0+c1-763+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][762+c0] + S[762+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 236; c0 += 1)
    S[c0][c0+763] = MAX(S[c0][c0+763], S[c0+1][c0+763-1] + can_pair(RNA, c0, c0+763));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 235; c0 += 1)
    for (c1 = c0 + 764; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-764+c0] + S[-c0+c1-764+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][763+c0] + S[763+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 235; c0 += 1)
    S[c0][c0+764] = MAX(S[c0][c0+764], S[c0+1][c0+764-1] + can_pair(RNA, c0, c0+764));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 234; c0 += 1)
    for (c1 = c0 + 765; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-765+c0] + S[-c0+c1-765+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][764+c0] + S[764+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 234; c0 += 1)
    S[c0][c0+765] = MAX(S[c0][c0+765], S[c0+1][c0+765-1] + can_pair(RNA, c0, c0+765));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 233; c0 += 1)
    for (c1 = c0 + 766; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-766+c0] + S[-c0+c1-766+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][765+c0] + S[765+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 233; c0 += 1)
    S[c0][c0+766] = MAX(S[c0][c0+766], S[c0+1][c0+766-1] + can_pair(RNA, c0, c0+766));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 232; c0 += 1)
    for (c1 = c0 + 767; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-767+c0] + S[-c0+c1-767+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][766+c0] + S[766+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 232; c0 += 1)
    S[c0][c0+767] = MAX(S[c0][c0+767], S[c0+1][c0+767-1] + can_pair(RNA, c0, c0+767));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 231; c0 += 1)
    for (c1 = c0 + 768; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-768+c0] + S[-c0+c1-768+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][767+c0] + S[767+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 231; c0 += 1)
    S[c0][c0+768] = MAX(S[c0][c0+768], S[c0+1][c0+768-1] + can_pair(RNA, c0, c0+768));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 230; c0 += 1)
    for (c1 = c0 + 769; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-769+c0] + S[-c0+c1-769+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][768+c0] + S[768+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 230; c0 += 1)
    S[c0][c0+769] = MAX(S[c0][c0+769], S[c0+1][c0+769-1] + can_pair(RNA, c0, c0+769));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 229; c0 += 1)
    for (c1 = c0 + 770; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-770+c0] + S[-c0+c1-770+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][769+c0] + S[769+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 229; c0 += 1)
    S[c0][c0+770] = MAX(S[c0][c0+770], S[c0+1][c0+770-1] + can_pair(RNA, c0, c0+770));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 228; c0 += 1)
    for (c1 = c0 + 771; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-771+c0] + S[-c0+c1-771+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][770+c0] + S[770+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 228; c0 += 1)
    S[c0][c0+771] = MAX(S[c0][c0+771], S[c0+1][c0+771-1] + can_pair(RNA, c0, c0+771));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 227; c0 += 1)
    for (c1 = c0 + 772; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-772+c0] + S[-c0+c1-772+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][771+c0] + S[771+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 227; c0 += 1)
    S[c0][c0+772] = MAX(S[c0][c0+772], S[c0+1][c0+772-1] + can_pair(RNA, c0, c0+772));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 226; c0 += 1)
    for (c1 = c0 + 773; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-773+c0] + S[-c0+c1-773+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][772+c0] + S[772+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 226; c0 += 1)
    S[c0][c0+773] = MAX(S[c0][c0+773], S[c0+1][c0+773-1] + can_pair(RNA, c0, c0+773));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 225; c0 += 1)
    for (c1 = c0 + 774; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-774+c0] + S[-c0+c1-774+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][773+c0] + S[773+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 225; c0 += 1)
    S[c0][c0+774] = MAX(S[c0][c0+774], S[c0+1][c0+774-1] + can_pair(RNA, c0, c0+774));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 224; c0 += 1)
    for (c1 = c0 + 775; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-775+c0] + S[-c0+c1-775+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][774+c0] + S[774+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 224; c0 += 1)
    S[c0][c0+775] = MAX(S[c0][c0+775], S[c0+1][c0+775-1] + can_pair(RNA, c0, c0+775));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 223; c0 += 1)
    for (c1 = c0 + 776; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-776+c0] + S[-c0+c1-776+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][775+c0] + S[775+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 223; c0 += 1)
    S[c0][c0+776] = MAX(S[c0][c0+776], S[c0+1][c0+776-1] + can_pair(RNA, c0, c0+776));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 222; c0 += 1)
    for (c1 = c0 + 777; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-777+c0] + S[-c0+c1-777+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][776+c0] + S[776+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 222; c0 += 1)
    S[c0][c0+777] = MAX(S[c0][c0+777], S[c0+1][c0+777-1] + can_pair(RNA, c0, c0+777));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 221; c0 += 1)
    for (c1 = c0 + 778; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-778+c0] + S[-c0+c1-778+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][777+c0] + S[777+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 221; c0 += 1)
    S[c0][c0+778] = MAX(S[c0][c0+778], S[c0+1][c0+778-1] + can_pair(RNA, c0, c0+778));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 220; c0 += 1)
    for (c1 = c0 + 779; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-779+c0] + S[-c0+c1-779+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][778+c0] + S[778+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 220; c0 += 1)
    S[c0][c0+779] = MAX(S[c0][c0+779], S[c0+1][c0+779-1] + can_pair(RNA, c0, c0+779));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 219; c0 += 1)
    for (c1 = c0 + 780; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-780+c0] + S[-c0+c1-780+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][779+c0] + S[779+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 219; c0 += 1)
    S[c0][c0+780] = MAX(S[c0][c0+780], S[c0+1][c0+780-1] + can_pair(RNA, c0, c0+780));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 218; c0 += 1)
    for (c1 = c0 + 781; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-781+c0] + S[-c0+c1-781+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][780+c0] + S[780+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 218; c0 += 1)
    S[c0][c0+781] = MAX(S[c0][c0+781], S[c0+1][c0+781-1] + can_pair(RNA, c0, c0+781));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 217; c0 += 1)
    for (c1 = c0 + 782; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-782+c0] + S[-c0+c1-782+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][781+c0] + S[781+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 217; c0 += 1)
    S[c0][c0+782] = MAX(S[c0][c0+782], S[c0+1][c0+782-1] + can_pair(RNA, c0, c0+782));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 216; c0 += 1)
    for (c1 = c0 + 783; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-783+c0] + S[-c0+c1-783+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][782+c0] + S[782+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 216; c0 += 1)
    S[c0][c0+783] = MAX(S[c0][c0+783], S[c0+1][c0+783-1] + can_pair(RNA, c0, c0+783));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 215; c0 += 1)
    for (c1 = c0 + 784; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-784+c0] + S[-c0+c1-784+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][783+c0] + S[783+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 215; c0 += 1)
    S[c0][c0+784] = MAX(S[c0][c0+784], S[c0+1][c0+784-1] + can_pair(RNA, c0, c0+784));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 214; c0 += 1)
    for (c1 = c0 + 785; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-785+c0] + S[-c0+c1-785+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][784+c0] + S[784+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 214; c0 += 1)
    S[c0][c0+785] = MAX(S[c0][c0+785], S[c0+1][c0+785-1] + can_pair(RNA, c0, c0+785));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 213; c0 += 1)
    for (c1 = c0 + 786; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-786+c0] + S[-c0+c1-786+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][785+c0] + S[785+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 213; c0 += 1)
    S[c0][c0+786] = MAX(S[c0][c0+786], S[c0+1][c0+786-1] + can_pair(RNA, c0, c0+786));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 212; c0 += 1)
    for (c1 = c0 + 787; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-787+c0] + S[-c0+c1-787+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][786+c0] + S[786+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 212; c0 += 1)
    S[c0][c0+787] = MAX(S[c0][c0+787], S[c0+1][c0+787-1] + can_pair(RNA, c0, c0+787));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 211; c0 += 1)
    for (c1 = c0 + 788; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-788+c0] + S[-c0+c1-788+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][787+c0] + S[787+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 211; c0 += 1)
    S[c0][c0+788] = MAX(S[c0][c0+788], S[c0+1][c0+788-1] + can_pair(RNA, c0, c0+788));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 210; c0 += 1)
    for (c1 = c0 + 789; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-789+c0] + S[-c0+c1-789+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][788+c0] + S[788+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 210; c0 += 1)
    S[c0][c0+789] = MAX(S[c0][c0+789], S[c0+1][c0+789-1] + can_pair(RNA, c0, c0+789));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 209; c0 += 1)
    for (c1 = c0 + 790; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-790+c0] + S[-c0+c1-790+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][789+c0] + S[789+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 209; c0 += 1)
    S[c0][c0+790] = MAX(S[c0][c0+790], S[c0+1][c0+790-1] + can_pair(RNA, c0, c0+790));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 208; c0 += 1)
    for (c1 = c0 + 791; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-791+c0] + S[-c0+c1-791+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][790+c0] + S[790+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 208; c0 += 1)
    S[c0][c0+791] = MAX(S[c0][c0+791], S[c0+1][c0+791-1] + can_pair(RNA, c0, c0+791));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 207; c0 += 1)
    for (c1 = c0 + 792; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-792+c0] + S[-c0+c1-792+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][791+c0] + S[791+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 207; c0 += 1)
    S[c0][c0+792] = MAX(S[c0][c0+792], S[c0+1][c0+792-1] + can_pair(RNA, c0, c0+792));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 206; c0 += 1)
    for (c1 = c0 + 793; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-793+c0] + S[-c0+c1-793+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][792+c0] + S[792+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 206; c0 += 1)
    S[c0][c0+793] = MAX(S[c0][c0+793], S[c0+1][c0+793-1] + can_pair(RNA, c0, c0+793));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 205; c0 += 1)
    for (c1 = c0 + 794; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-794+c0] + S[-c0+c1-794+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][793+c0] + S[793+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 205; c0 += 1)
    S[c0][c0+794] = MAX(S[c0][c0+794], S[c0+1][c0+794-1] + can_pair(RNA, c0, c0+794));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 204; c0 += 1)
    for (c1 = c0 + 795; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-795+c0] + S[-c0+c1-795+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][794+c0] + S[794+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 204; c0 += 1)
    S[c0][c0+795] = MAX(S[c0][c0+795], S[c0+1][c0+795-1] + can_pair(RNA, c0, c0+795));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 203; c0 += 1)
    for (c1 = c0 + 796; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-796+c0] + S[-c0+c1-796+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][795+c0] + S[795+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 203; c0 += 1)
    S[c0][c0+796] = MAX(S[c0][c0+796], S[c0+1][c0+796-1] + can_pair(RNA, c0, c0+796));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 202; c0 += 1)
    for (c1 = c0 + 797; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-797+c0] + S[-c0+c1-797+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][796+c0] + S[796+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 202; c0 += 1)
    S[c0][c0+797] = MAX(S[c0][c0+797], S[c0+1][c0+797-1] + can_pair(RNA, c0, c0+797));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 201; c0 += 1)
    for (c1 = c0 + 798; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-798+c0] + S[-c0+c1-798+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][797+c0] + S[797+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 201; c0 += 1)
    S[c0][c0+798] = MAX(S[c0][c0+798], S[c0+1][c0+798-1] + can_pair(RNA, c0, c0+798));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 200; c0 += 1)
    for (c1 = c0 + 799; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-799+c0] + S[-c0+c1-799+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][798+c0] + S[798+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 200; c0 += 1)
    S[c0][c0+799] = MAX(S[c0][c0+799], S[c0+1][c0+799-1] + can_pair(RNA, c0, c0+799));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 199; c0 += 1)
    for (c1 = c0 + 800; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-800+c0] + S[-c0+c1-800+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][799+c0] + S[799+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 199; c0 += 1)
    S[c0][c0+800] = MAX(S[c0][c0+800], S[c0+1][c0+800-1] + can_pair(RNA, c0, c0+800));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 198; c0 += 1)
    for (c1 = c0 + 801; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-801+c0] + S[-c0+c1-801+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][800+c0] + S[800+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 198; c0 += 1)
    S[c0][c0+801] = MAX(S[c0][c0+801], S[c0+1][c0+801-1] + can_pair(RNA, c0, c0+801));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 197; c0 += 1)
    for (c1 = c0 + 802; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-802+c0] + S[-c0+c1-802+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][801+c0] + S[801+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 197; c0 += 1)
    S[c0][c0+802] = MAX(S[c0][c0+802], S[c0+1][c0+802-1] + can_pair(RNA, c0, c0+802));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 196; c0 += 1)
    for (c1 = c0 + 803; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-803+c0] + S[-c0+c1-803+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][802+c0] + S[802+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 196; c0 += 1)
    S[c0][c0+803] = MAX(S[c0][c0+803], S[c0+1][c0+803-1] + can_pair(RNA, c0, c0+803));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 195; c0 += 1)
    for (c1 = c0 + 804; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-804+c0] + S[-c0+c1-804+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][803+c0] + S[803+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 195; c0 += 1)
    S[c0][c0+804] = MAX(S[c0][c0+804], S[c0+1][c0+804-1] + can_pair(RNA, c0, c0+804));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 194; c0 += 1)
    for (c1 = c0 + 805; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-805+c0] + S[-c0+c1-805+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][804+c0] + S[804+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 194; c0 += 1)
    S[c0][c0+805] = MAX(S[c0][c0+805], S[c0+1][c0+805-1] + can_pair(RNA, c0, c0+805));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 193; c0 += 1)
    for (c1 = c0 + 806; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-806+c0] + S[-c0+c1-806+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][805+c0] + S[805+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 193; c0 += 1)
    S[c0][c0+806] = MAX(S[c0][c0+806], S[c0+1][c0+806-1] + can_pair(RNA, c0, c0+806));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 192; c0 += 1)
    for (c1 = c0 + 807; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-807+c0] + S[-c0+c1-807+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][806+c0] + S[806+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 192; c0 += 1)
    S[c0][c0+807] = MAX(S[c0][c0+807], S[c0+1][c0+807-1] + can_pair(RNA, c0, c0+807));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 191; c0 += 1)
    for (c1 = c0 + 808; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-808+c0] + S[-c0+c1-808+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][807+c0] + S[807+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 191; c0 += 1)
    S[c0][c0+808] = MAX(S[c0][c0+808], S[c0+1][c0+808-1] + can_pair(RNA, c0, c0+808));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 190; c0 += 1)
    for (c1 = c0 + 809; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-809+c0] + S[-c0+c1-809+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][808+c0] + S[808+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 190; c0 += 1)
    S[c0][c0+809] = MAX(S[c0][c0+809], S[c0+1][c0+809-1] + can_pair(RNA, c0, c0+809));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 189; c0 += 1)
    for (c1 = c0 + 810; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-810+c0] + S[-c0+c1-810+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][809+c0] + S[809+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 189; c0 += 1)
    S[c0][c0+810] = MAX(S[c0][c0+810], S[c0+1][c0+810-1] + can_pair(RNA, c0, c0+810));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 188; c0 += 1)
    for (c1 = c0 + 811; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-811+c0] + S[-c0+c1-811+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][810+c0] + S[810+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 188; c0 += 1)
    S[c0][c0+811] = MAX(S[c0][c0+811], S[c0+1][c0+811-1] + can_pair(RNA, c0, c0+811));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 187; c0 += 1)
    for (c1 = c0 + 812; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-812+c0] + S[-c0+c1-812+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][811+c0] + S[811+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 187; c0 += 1)
    S[c0][c0+812] = MAX(S[c0][c0+812], S[c0+1][c0+812-1] + can_pair(RNA, c0, c0+812));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 186; c0 += 1)
    for (c1 = c0 + 813; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-813+c0] + S[-c0+c1-813+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][812+c0] + S[812+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 186; c0 += 1)
    S[c0][c0+813] = MAX(S[c0][c0+813], S[c0+1][c0+813-1] + can_pair(RNA, c0, c0+813));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 185; c0 += 1)
    for (c1 = c0 + 814; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-814+c0] + S[-c0+c1-814+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][813+c0] + S[813+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 185; c0 += 1)
    S[c0][c0+814] = MAX(S[c0][c0+814], S[c0+1][c0+814-1] + can_pair(RNA, c0, c0+814));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 184; c0 += 1)
    for (c1 = c0 + 815; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-815+c0] + S[-c0+c1-815+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][814+c0] + S[814+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 184; c0 += 1)
    S[c0][c0+815] = MAX(S[c0][c0+815], S[c0+1][c0+815-1] + can_pair(RNA, c0, c0+815));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 183; c0 += 1)
    for (c1 = c0 + 816; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-816+c0] + S[-c0+c1-816+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][815+c0] + S[815+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 183; c0 += 1)
    S[c0][c0+816] = MAX(S[c0][c0+816], S[c0+1][c0+816-1] + can_pair(RNA, c0, c0+816));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 182; c0 += 1)
    for (c1 = c0 + 817; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-817+c0] + S[-c0+c1-817+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][816+c0] + S[816+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 182; c0 += 1)
    S[c0][c0+817] = MAX(S[c0][c0+817], S[c0+1][c0+817-1] + can_pair(RNA, c0, c0+817));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 181; c0 += 1)
    for (c1 = c0 + 818; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-818+c0] + S[-c0+c1-818+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][817+c0] + S[817+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 181; c0 += 1)
    S[c0][c0+818] = MAX(S[c0][c0+818], S[c0+1][c0+818-1] + can_pair(RNA, c0, c0+818));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 180; c0 += 1)
    for (c1 = c0 + 819; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-819+c0] + S[-c0+c1-819+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][818+c0] + S[818+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 180; c0 += 1)
    S[c0][c0+819] = MAX(S[c0][c0+819], S[c0+1][c0+819-1] + can_pair(RNA, c0, c0+819));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 179; c0 += 1)
    for (c1 = c0 + 820; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-820+c0] + S[-c0+c1-820+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][819+c0] + S[819+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 179; c0 += 1)
    S[c0][c0+820] = MAX(S[c0][c0+820], S[c0+1][c0+820-1] + can_pair(RNA, c0, c0+820));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 178; c0 += 1)
    for (c1 = c0 + 821; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-821+c0] + S[-c0+c1-821+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][820+c0] + S[820+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 178; c0 += 1)
    S[c0][c0+821] = MAX(S[c0][c0+821], S[c0+1][c0+821-1] + can_pair(RNA, c0, c0+821));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 177; c0 += 1)
    for (c1 = c0 + 822; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-822+c0] + S[-c0+c1-822+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][821+c0] + S[821+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 177; c0 += 1)
    S[c0][c0+822] = MAX(S[c0][c0+822], S[c0+1][c0+822-1] + can_pair(RNA, c0, c0+822));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 176; c0 += 1)
    for (c1 = c0 + 823; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-823+c0] + S[-c0+c1-823+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][822+c0] + S[822+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 176; c0 += 1)
    S[c0][c0+823] = MAX(S[c0][c0+823], S[c0+1][c0+823-1] + can_pair(RNA, c0, c0+823));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 175; c0 += 1)
    for (c1 = c0 + 824; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-824+c0] + S[-c0+c1-824+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][823+c0] + S[823+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 175; c0 += 1)
    S[c0][c0+824] = MAX(S[c0][c0+824], S[c0+1][c0+824-1] + can_pair(RNA, c0, c0+824));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 174; c0 += 1)
    for (c1 = c0 + 825; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-825+c0] + S[-c0+c1-825+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][824+c0] + S[824+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 174; c0 += 1)
    S[c0][c0+825] = MAX(S[c0][c0+825], S[c0+1][c0+825-1] + can_pair(RNA, c0, c0+825));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 173; c0 += 1)
    for (c1 = c0 + 826; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-826+c0] + S[-c0+c1-826+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][825+c0] + S[825+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 173; c0 += 1)
    S[c0][c0+826] = MAX(S[c0][c0+826], S[c0+1][c0+826-1] + can_pair(RNA, c0, c0+826));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 172; c0 += 1)
    for (c1 = c0 + 827; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-827+c0] + S[-c0+c1-827+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][826+c0] + S[826+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 172; c0 += 1)
    S[c0][c0+827] = MAX(S[c0][c0+827], S[c0+1][c0+827-1] + can_pair(RNA, c0, c0+827));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 171; c0 += 1)
    for (c1 = c0 + 828; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-828+c0] + S[-c0+c1-828+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][827+c0] + S[827+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 171; c0 += 1)
    S[c0][c0+828] = MAX(S[c0][c0+828], S[c0+1][c0+828-1] + can_pair(RNA, c0, c0+828));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 170; c0 += 1)
    for (c1 = c0 + 829; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-829+c0] + S[-c0+c1-829+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][828+c0] + S[828+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 170; c0 += 1)
    S[c0][c0+829] = MAX(S[c0][c0+829], S[c0+1][c0+829-1] + can_pair(RNA, c0, c0+829));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 169; c0 += 1)
    for (c1 = c0 + 830; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-830+c0] + S[-c0+c1-830+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][829+c0] + S[829+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 169; c0 += 1)
    S[c0][c0+830] = MAX(S[c0][c0+830], S[c0+1][c0+830-1] + can_pair(RNA, c0, c0+830));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 168; c0 += 1)
    for (c1 = c0 + 831; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-831+c0] + S[-c0+c1-831+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][830+c0] + S[830+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 168; c0 += 1)
    S[c0][c0+831] = MAX(S[c0][c0+831], S[c0+1][c0+831-1] + can_pair(RNA, c0, c0+831));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 167; c0 += 1)
    for (c1 = c0 + 832; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-832+c0] + S[-c0+c1-832+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][831+c0] + S[831+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 167; c0 += 1)
    S[c0][c0+832] = MAX(S[c0][c0+832], S[c0+1][c0+832-1] + can_pair(RNA, c0, c0+832));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 166; c0 += 1)
    for (c1 = c0 + 833; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-833+c0] + S[-c0+c1-833+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][832+c0] + S[832+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 166; c0 += 1)
    S[c0][c0+833] = MAX(S[c0][c0+833], S[c0+1][c0+833-1] + can_pair(RNA, c0, c0+833));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 165; c0 += 1)
    for (c1 = c0 + 834; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-834+c0] + S[-c0+c1-834+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][833+c0] + S[833+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 165; c0 += 1)
    S[c0][c0+834] = MAX(S[c0][c0+834], S[c0+1][c0+834-1] + can_pair(RNA, c0, c0+834));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 164; c0 += 1)
    for (c1 = c0 + 835; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-835+c0] + S[-c0+c1-835+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][834+c0] + S[834+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 164; c0 += 1)
    S[c0][c0+835] = MAX(S[c0][c0+835], S[c0+1][c0+835-1] + can_pair(RNA, c0, c0+835));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 163; c0 += 1)
    for (c1 = c0 + 836; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-836+c0] + S[-c0+c1-836+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][835+c0] + S[835+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 163; c0 += 1)
    S[c0][c0+836] = MAX(S[c0][c0+836], S[c0+1][c0+836-1] + can_pair(RNA, c0, c0+836));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 162; c0 += 1)
    for (c1 = c0 + 837; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-837+c0] + S[-c0+c1-837+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][836+c0] + S[836+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 162; c0 += 1)
    S[c0][c0+837] = MAX(S[c0][c0+837], S[c0+1][c0+837-1] + can_pair(RNA, c0, c0+837));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 161; c0 += 1)
    for (c1 = c0 + 838; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-838+c0] + S[-c0+c1-838+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][837+c0] + S[837+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 161; c0 += 1)
    S[c0][c0+838] = MAX(S[c0][c0+838], S[c0+1][c0+838-1] + can_pair(RNA, c0, c0+838));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 160; c0 += 1)
    for (c1 = c0 + 839; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-839+c0] + S[-c0+c1-839+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][838+c0] + S[838+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 160; c0 += 1)
    S[c0][c0+839] = MAX(S[c0][c0+839], S[c0+1][c0+839-1] + can_pair(RNA, c0, c0+839));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 159; c0 += 1)
    for (c1 = c0 + 840; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-840+c0] + S[-c0+c1-840+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][839+c0] + S[839+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 159; c0 += 1)
    S[c0][c0+840] = MAX(S[c0][c0+840], S[c0+1][c0+840-1] + can_pair(RNA, c0, c0+840));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 158; c0 += 1)
    for (c1 = c0 + 841; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-841+c0] + S[-c0+c1-841+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][840+c0] + S[840+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 158; c0 += 1)
    S[c0][c0+841] = MAX(S[c0][c0+841], S[c0+1][c0+841-1] + can_pair(RNA, c0, c0+841));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 157; c0 += 1)
    for (c1 = c0 + 842; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-842+c0] + S[-c0+c1-842+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][841+c0] + S[841+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 157; c0 += 1)
    S[c0][c0+842] = MAX(S[c0][c0+842], S[c0+1][c0+842-1] + can_pair(RNA, c0, c0+842));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 156; c0 += 1)
    for (c1 = c0 + 843; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-843+c0] + S[-c0+c1-843+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][842+c0] + S[842+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 156; c0 += 1)
    S[c0][c0+843] = MAX(S[c0][c0+843], S[c0+1][c0+843-1] + can_pair(RNA, c0, c0+843));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 155; c0 += 1)
    for (c1 = c0 + 844; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-844+c0] + S[-c0+c1-844+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][843+c0] + S[843+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 155; c0 += 1)
    S[c0][c0+844] = MAX(S[c0][c0+844], S[c0+1][c0+844-1] + can_pair(RNA, c0, c0+844));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 154; c0 += 1)
    for (c1 = c0 + 845; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-845+c0] + S[-c0+c1-845+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][844+c0] + S[844+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 154; c0 += 1)
    S[c0][c0+845] = MAX(S[c0][c0+845], S[c0+1][c0+845-1] + can_pair(RNA, c0, c0+845));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 153; c0 += 1)
    for (c1 = c0 + 846; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-846+c0] + S[-c0+c1-846+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][845+c0] + S[845+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 153; c0 += 1)
    S[c0][c0+846] = MAX(S[c0][c0+846], S[c0+1][c0+846-1] + can_pair(RNA, c0, c0+846));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 152; c0 += 1)
    for (c1 = c0 + 847; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-847+c0] + S[-c0+c1-847+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][846+c0] + S[846+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 152; c0 += 1)
    S[c0][c0+847] = MAX(S[c0][c0+847], S[c0+1][c0+847-1] + can_pair(RNA, c0, c0+847));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 151; c0 += 1)
    for (c1 = c0 + 848; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-848+c0] + S[-c0+c1-848+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][847+c0] + S[847+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 151; c0 += 1)
    S[c0][c0+848] = MAX(S[c0][c0+848], S[c0+1][c0+848-1] + can_pair(RNA, c0, c0+848));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 150; c0 += 1)
    for (c1 = c0 + 849; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-849+c0] + S[-c0+c1-849+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][848+c0] + S[848+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 150; c0 += 1)
    S[c0][c0+849] = MAX(S[c0][c0+849], S[c0+1][c0+849-1] + can_pair(RNA, c0, c0+849));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 149; c0 += 1)
    for (c1 = c0 + 850; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-850+c0] + S[-c0+c1-850+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][849+c0] + S[849+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 149; c0 += 1)
    S[c0][c0+850] = MAX(S[c0][c0+850], S[c0+1][c0+850-1] + can_pair(RNA, c0, c0+850));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 148; c0 += 1)
    for (c1 = c0 + 851; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-851+c0] + S[-c0+c1-851+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][850+c0] + S[850+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 148; c0 += 1)
    S[c0][c0+851] = MAX(S[c0][c0+851], S[c0+1][c0+851-1] + can_pair(RNA, c0, c0+851));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 147; c0 += 1)
    for (c1 = c0 + 852; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-852+c0] + S[-c0+c1-852+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][851+c0] + S[851+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 147; c0 += 1)
    S[c0][c0+852] = MAX(S[c0][c0+852], S[c0+1][c0+852-1] + can_pair(RNA, c0, c0+852));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 146; c0 += 1)
    for (c1 = c0 + 853; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-853+c0] + S[-c0+c1-853+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][852+c0] + S[852+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 146; c0 += 1)
    S[c0][c0+853] = MAX(S[c0][c0+853], S[c0+1][c0+853-1] + can_pair(RNA, c0, c0+853));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 145; c0 += 1)
    for (c1 = c0 + 854; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-854+c0] + S[-c0+c1-854+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][853+c0] + S[853+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 145; c0 += 1)
    S[c0][c0+854] = MAX(S[c0][c0+854], S[c0+1][c0+854-1] + can_pair(RNA, c0, c0+854));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 144; c0 += 1)
    for (c1 = c0 + 855; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-855+c0] + S[-c0+c1-855+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][854+c0] + S[854+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 144; c0 += 1)
    S[c0][c0+855] = MAX(S[c0][c0+855], S[c0+1][c0+855-1] + can_pair(RNA, c0, c0+855));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 143; c0 += 1)
    for (c1 = c0 + 856; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-856+c0] + S[-c0+c1-856+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][855+c0] + S[855+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 143; c0 += 1)
    S[c0][c0+856] = MAX(S[c0][c0+856], S[c0+1][c0+856-1] + can_pair(RNA, c0, c0+856));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 142; c0 += 1)
    for (c1 = c0 + 857; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-857+c0] + S[-c0+c1-857+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][856+c0] + S[856+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 142; c0 += 1)
    S[c0][c0+857] = MAX(S[c0][c0+857], S[c0+1][c0+857-1] + can_pair(RNA, c0, c0+857));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 141; c0 += 1)
    for (c1 = c0 + 858; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-858+c0] + S[-c0+c1-858+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][857+c0] + S[857+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 141; c0 += 1)
    S[c0][c0+858] = MAX(S[c0][c0+858], S[c0+1][c0+858-1] + can_pair(RNA, c0, c0+858));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 140; c0 += 1)
    for (c1 = c0 + 859; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-859+c0] + S[-c0+c1-859+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][858+c0] + S[858+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 140; c0 += 1)
    S[c0][c0+859] = MAX(S[c0][c0+859], S[c0+1][c0+859-1] + can_pair(RNA, c0, c0+859));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 139; c0 += 1)
    for (c1 = c0 + 860; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-860+c0] + S[-c0+c1-860+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][859+c0] + S[859+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 139; c0 += 1)
    S[c0][c0+860] = MAX(S[c0][c0+860], S[c0+1][c0+860-1] + can_pair(RNA, c0, c0+860));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 138; c0 += 1)
    for (c1 = c0 + 861; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-861+c0] + S[-c0+c1-861+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][860+c0] + S[860+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 138; c0 += 1)
    S[c0][c0+861] = MAX(S[c0][c0+861], S[c0+1][c0+861-1] + can_pair(RNA, c0, c0+861));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 137; c0 += 1)
    for (c1 = c0 + 862; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-862+c0] + S[-c0+c1-862+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][861+c0] + S[861+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 137; c0 += 1)
    S[c0][c0+862] = MAX(S[c0][c0+862], S[c0+1][c0+862-1] + can_pair(RNA, c0, c0+862));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 136; c0 += 1)
    for (c1 = c0 + 863; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-863+c0] + S[-c0+c1-863+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][862+c0] + S[862+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 136; c0 += 1)
    S[c0][c0+863] = MAX(S[c0][c0+863], S[c0+1][c0+863-1] + can_pair(RNA, c0, c0+863));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 135; c0 += 1)
    for (c1 = c0 + 864; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-864+c0] + S[-c0+c1-864+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][863+c0] + S[863+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 135; c0 += 1)
    S[c0][c0+864] = MAX(S[c0][c0+864], S[c0+1][c0+864-1] + can_pair(RNA, c0, c0+864));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 134; c0 += 1)
    for (c1 = c0 + 865; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-865+c0] + S[-c0+c1-865+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][864+c0] + S[864+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 134; c0 += 1)
    S[c0][c0+865] = MAX(S[c0][c0+865], S[c0+1][c0+865-1] + can_pair(RNA, c0, c0+865));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 133; c0 += 1)
    for (c1 = c0 + 866; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-866+c0] + S[-c0+c1-866+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][865+c0] + S[865+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 133; c0 += 1)
    S[c0][c0+866] = MAX(S[c0][c0+866], S[c0+1][c0+866-1] + can_pair(RNA, c0, c0+866));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 132; c0 += 1)
    for (c1 = c0 + 867; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-867+c0] + S[-c0+c1-867+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][866+c0] + S[866+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 132; c0 += 1)
    S[c0][c0+867] = MAX(S[c0][c0+867], S[c0+1][c0+867-1] + can_pair(RNA, c0, c0+867));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 131; c0 += 1)
    for (c1 = c0 + 868; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-868+c0] + S[-c0+c1-868+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][867+c0] + S[867+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 131; c0 += 1)
    S[c0][c0+868] = MAX(S[c0][c0+868], S[c0+1][c0+868-1] + can_pair(RNA, c0, c0+868));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 130; c0 += 1)
    for (c1 = c0 + 869; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-869+c0] + S[-c0+c1-869+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][868+c0] + S[868+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 130; c0 += 1)
    S[c0][c0+869] = MAX(S[c0][c0+869], S[c0+1][c0+869-1] + can_pair(RNA, c0, c0+869));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 129; c0 += 1)
    for (c1 = c0 + 870; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-870+c0] + S[-c0+c1-870+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][869+c0] + S[869+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 129; c0 += 1)
    S[c0][c0+870] = MAX(S[c0][c0+870], S[c0+1][c0+870-1] + can_pair(RNA, c0, c0+870));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 128; c0 += 1)
    for (c1 = c0 + 871; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-871+c0] + S[-c0+c1-871+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][870+c0] + S[870+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 128; c0 += 1)
    S[c0][c0+871] = MAX(S[c0][c0+871], S[c0+1][c0+871-1] + can_pair(RNA, c0, c0+871));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 127; c0 += 1)
    for (c1 = c0 + 872; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-872+c0] + S[-c0+c1-872+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][871+c0] + S[871+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 127; c0 += 1)
    S[c0][c0+872] = MAX(S[c0][c0+872], S[c0+1][c0+872-1] + can_pair(RNA, c0, c0+872));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 126; c0 += 1)
    for (c1 = c0 + 873; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-873+c0] + S[-c0+c1-873+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][872+c0] + S[872+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 126; c0 += 1)
    S[c0][c0+873] = MAX(S[c0][c0+873], S[c0+1][c0+873-1] + can_pair(RNA, c0, c0+873));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 125; c0 += 1)
    for (c1 = c0 + 874; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-874+c0] + S[-c0+c1-874+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][873+c0] + S[873+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 125; c0 += 1)
    S[c0][c0+874] = MAX(S[c0][c0+874], S[c0+1][c0+874-1] + can_pair(RNA, c0, c0+874));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 124; c0 += 1)
    for (c1 = c0 + 875; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-875+c0] + S[-c0+c1-875+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][874+c0] + S[874+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 124; c0 += 1)
    S[c0][c0+875] = MAX(S[c0][c0+875], S[c0+1][c0+875-1] + can_pair(RNA, c0, c0+875));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 123; c0 += 1)
    for (c1 = c0 + 876; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-876+c0] + S[-c0+c1-876+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][875+c0] + S[875+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 123; c0 += 1)
    S[c0][c0+876] = MAX(S[c0][c0+876], S[c0+1][c0+876-1] + can_pair(RNA, c0, c0+876));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 122; c0 += 1)
    for (c1 = c0 + 877; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-877+c0] + S[-c0+c1-877+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][876+c0] + S[876+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 122; c0 += 1)
    S[c0][c0+877] = MAX(S[c0][c0+877], S[c0+1][c0+877-1] + can_pair(RNA, c0, c0+877));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 121; c0 += 1)
    for (c1 = c0 + 878; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-878+c0] + S[-c0+c1-878+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][877+c0] + S[877+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 121; c0 += 1)
    S[c0][c0+878] = MAX(S[c0][c0+878], S[c0+1][c0+878-1] + can_pair(RNA, c0, c0+878));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 120; c0 += 1)
    for (c1 = c0 + 879; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-879+c0] + S[-c0+c1-879+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][878+c0] + S[878+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 120; c0 += 1)
    S[c0][c0+879] = MAX(S[c0][c0+879], S[c0+1][c0+879-1] + can_pair(RNA, c0, c0+879));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 119; c0 += 1)
    for (c1 = c0 + 880; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-880+c0] + S[-c0+c1-880+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][879+c0] + S[879+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 119; c0 += 1)
    S[c0][c0+880] = MAX(S[c0][c0+880], S[c0+1][c0+880-1] + can_pair(RNA, c0, c0+880));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 118; c0 += 1)
    for (c1 = c0 + 881; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-881+c0] + S[-c0+c1-881+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][880+c0] + S[880+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 118; c0 += 1)
    S[c0][c0+881] = MAX(S[c0][c0+881], S[c0+1][c0+881-1] + can_pair(RNA, c0, c0+881));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 117; c0 += 1)
    for (c1 = c0 + 882; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-882+c0] + S[-c0+c1-882+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][881+c0] + S[881+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 117; c0 += 1)
    S[c0][c0+882] = MAX(S[c0][c0+882], S[c0+1][c0+882-1] + can_pair(RNA, c0, c0+882));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 116; c0 += 1)
    for (c1 = c0 + 883; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-883+c0] + S[-c0+c1-883+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][882+c0] + S[882+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 116; c0 += 1)
    S[c0][c0+883] = MAX(S[c0][c0+883], S[c0+1][c0+883-1] + can_pair(RNA, c0, c0+883));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 115; c0 += 1)
    for (c1 = c0 + 884; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-884+c0] + S[-c0+c1-884+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][883+c0] + S[883+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 115; c0 += 1)
    S[c0][c0+884] = MAX(S[c0][c0+884], S[c0+1][c0+884-1] + can_pair(RNA, c0, c0+884));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 114; c0 += 1)
    for (c1 = c0 + 885; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-885+c0] + S[-c0+c1-885+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][884+c0] + S[884+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 114; c0 += 1)
    S[c0][c0+885] = MAX(S[c0][c0+885], S[c0+1][c0+885-1] + can_pair(RNA, c0, c0+885));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 113; c0 += 1)
    for (c1 = c0 + 886; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-886+c0] + S[-c0+c1-886+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][885+c0] + S[885+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 113; c0 += 1)
    S[c0][c0+886] = MAX(S[c0][c0+886], S[c0+1][c0+886-1] + can_pair(RNA, c0, c0+886));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 112; c0 += 1)
    for (c1 = c0 + 887; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-887+c0] + S[-c0+c1-887+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][886+c0] + S[886+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 112; c0 += 1)
    S[c0][c0+887] = MAX(S[c0][c0+887], S[c0+1][c0+887-1] + can_pair(RNA, c0, c0+887));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 111; c0 += 1)
    for (c1 = c0 + 888; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-888+c0] + S[-c0+c1-888+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][887+c0] + S[887+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 111; c0 += 1)
    S[c0][c0+888] = MAX(S[c0][c0+888], S[c0+1][c0+888-1] + can_pair(RNA, c0, c0+888));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 110; c0 += 1)
    for (c1 = c0 + 889; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-889+c0] + S[-c0+c1-889+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][888+c0] + S[888+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 110; c0 += 1)
    S[c0][c0+889] = MAX(S[c0][c0+889], S[c0+1][c0+889-1] + can_pair(RNA, c0, c0+889));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 109; c0 += 1)
    for (c1 = c0 + 890; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-890+c0] + S[-c0+c1-890+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][889+c0] + S[889+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 109; c0 += 1)
    S[c0][c0+890] = MAX(S[c0][c0+890], S[c0+1][c0+890-1] + can_pair(RNA, c0, c0+890));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 108; c0 += 1)
    for (c1 = c0 + 891; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-891+c0] + S[-c0+c1-891+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][890+c0] + S[890+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 108; c0 += 1)
    S[c0][c0+891] = MAX(S[c0][c0+891], S[c0+1][c0+891-1] + can_pair(RNA, c0, c0+891));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 107; c0 += 1)
    for (c1 = c0 + 892; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-892+c0] + S[-c0+c1-892+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][891+c0] + S[891+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 107; c0 += 1)
    S[c0][c0+892] = MAX(S[c0][c0+892], S[c0+1][c0+892-1] + can_pair(RNA, c0, c0+892));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 106; c0 += 1)
    for (c1 = c0 + 893; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-893+c0] + S[-c0+c1-893+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][892+c0] + S[892+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 106; c0 += 1)
    S[c0][c0+893] = MAX(S[c0][c0+893], S[c0+1][c0+893-1] + can_pair(RNA, c0, c0+893));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 105; c0 += 1)
    for (c1 = c0 + 894; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-894+c0] + S[-c0+c1-894+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][893+c0] + S[893+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 105; c0 += 1)
    S[c0][c0+894] = MAX(S[c0][c0+894], S[c0+1][c0+894-1] + can_pair(RNA, c0, c0+894));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 104; c0 += 1)
    for (c1 = c0 + 895; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-895+c0] + S[-c0+c1-895+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][894+c0] + S[894+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 104; c0 += 1)
    S[c0][c0+895] = MAX(S[c0][c0+895], S[c0+1][c0+895-1] + can_pair(RNA, c0, c0+895));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 103; c0 += 1)
    for (c1 = c0 + 896; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-896+c0] + S[-c0+c1-896+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][895+c0] + S[895+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 103; c0 += 1)
    S[c0][c0+896] = MAX(S[c0][c0+896], S[c0+1][c0+896-1] + can_pair(RNA, c0, c0+896));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 102; c0 += 1)
    for (c1 = c0 + 897; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-897+c0] + S[-c0+c1-897+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][896+c0] + S[896+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 102; c0 += 1)
    S[c0][c0+897] = MAX(S[c0][c0+897], S[c0+1][c0+897-1] + can_pair(RNA, c0, c0+897));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 101; c0 += 1)
    for (c1 = c0 + 898; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-898+c0] + S[-c0+c1-898+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][897+c0] + S[897+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 101; c0 += 1)
    S[c0][c0+898] = MAX(S[c0][c0+898], S[c0+1][c0+898-1] + can_pair(RNA, c0, c0+898));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 100; c0 += 1)
    for (c1 = c0 + 899; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-899+c0] + S[-c0+c1-899+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][898+c0] + S[898+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 100; c0 += 1)
    S[c0][c0+899] = MAX(S[c0][c0+899], S[c0+1][c0+899-1] + can_pair(RNA, c0, c0+899));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 99; c0 += 1)
    for (c1 = c0 + 900; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-900+c0] + S[-c0+c1-900+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][899+c0] + S[899+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 99; c0 += 1)
    S[c0][c0+900] = MAX(S[c0][c0+900], S[c0+1][c0+900-1] + can_pair(RNA, c0, c0+900));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 98; c0 += 1)
    for (c1 = c0 + 901; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-901+c0] + S[-c0+c1-901+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][900+c0] + S[900+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 98; c0 += 1)
    S[c0][c0+901] = MAX(S[c0][c0+901], S[c0+1][c0+901-1] + can_pair(RNA, c0, c0+901));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 97; c0 += 1)
    for (c1 = c0 + 902; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-902+c0] + S[-c0+c1-902+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][901+c0] + S[901+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 97; c0 += 1)
    S[c0][c0+902] = MAX(S[c0][c0+902], S[c0+1][c0+902-1] + can_pair(RNA, c0, c0+902));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 96; c0 += 1)
    for (c1 = c0 + 903; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-903+c0] + S[-c0+c1-903+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][902+c0] + S[902+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 96; c0 += 1)
    S[c0][c0+903] = MAX(S[c0][c0+903], S[c0+1][c0+903-1] + can_pair(RNA, c0, c0+903));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 95; c0 += 1)
    for (c1 = c0 + 904; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-904+c0] + S[-c0+c1-904+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][903+c0] + S[903+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 95; c0 += 1)
    S[c0][c0+904] = MAX(S[c0][c0+904], S[c0+1][c0+904-1] + can_pair(RNA, c0, c0+904));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 94; c0 += 1)
    for (c1 = c0 + 905; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-905+c0] + S[-c0+c1-905+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][904+c0] + S[904+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 94; c0 += 1)
    S[c0][c0+905] = MAX(S[c0][c0+905], S[c0+1][c0+905-1] + can_pair(RNA, c0, c0+905));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 93; c0 += 1)
    for (c1 = c0 + 906; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-906+c0] + S[-c0+c1-906+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][905+c0] + S[905+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 93; c0 += 1)
    S[c0][c0+906] = MAX(S[c0][c0+906], S[c0+1][c0+906-1] + can_pair(RNA, c0, c0+906));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 92; c0 += 1)
    for (c1 = c0 + 907; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-907+c0] + S[-c0+c1-907+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][906+c0] + S[906+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 92; c0 += 1)
    S[c0][c0+907] = MAX(S[c0][c0+907], S[c0+1][c0+907-1] + can_pair(RNA, c0, c0+907));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 91; c0 += 1)
    for (c1 = c0 + 908; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-908+c0] + S[-c0+c1-908+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][907+c0] + S[907+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 91; c0 += 1)
    S[c0][c0+908] = MAX(S[c0][c0+908], S[c0+1][c0+908-1] + can_pair(RNA, c0, c0+908));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 90; c0 += 1)
    for (c1 = c0 + 909; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-909+c0] + S[-c0+c1-909+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][908+c0] + S[908+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 90; c0 += 1)
    S[c0][c0+909] = MAX(S[c0][c0+909], S[c0+1][c0+909-1] + can_pair(RNA, c0, c0+909));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 89; c0 += 1)
    for (c1 = c0 + 910; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-910+c0] + S[-c0+c1-910+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][909+c0] + S[909+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 89; c0 += 1)
    S[c0][c0+910] = MAX(S[c0][c0+910], S[c0+1][c0+910-1] + can_pair(RNA, c0, c0+910));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 88; c0 += 1)
    for (c1 = c0 + 911; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-911+c0] + S[-c0+c1-911+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][910+c0] + S[910+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 88; c0 += 1)
    S[c0][c0+911] = MAX(S[c0][c0+911], S[c0+1][c0+911-1] + can_pair(RNA, c0, c0+911));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 87; c0 += 1)
    for (c1 = c0 + 912; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-912+c0] + S[-c0+c1-912+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][911+c0] + S[911+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 87; c0 += 1)
    S[c0][c0+912] = MAX(S[c0][c0+912], S[c0+1][c0+912-1] + can_pair(RNA, c0, c0+912));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 86; c0 += 1)
    for (c1 = c0 + 913; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-913+c0] + S[-c0+c1-913+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][912+c0] + S[912+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 86; c0 += 1)
    S[c0][c0+913] = MAX(S[c0][c0+913], S[c0+1][c0+913-1] + can_pair(RNA, c0, c0+913));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 85; c0 += 1)
    for (c1 = c0 + 914; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-914+c0] + S[-c0+c1-914+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][913+c0] + S[913+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 85; c0 += 1)
    S[c0][c0+914] = MAX(S[c0][c0+914], S[c0+1][c0+914-1] + can_pair(RNA, c0, c0+914));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 84; c0 += 1)
    for (c1 = c0 + 915; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-915+c0] + S[-c0+c1-915+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][914+c0] + S[914+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 84; c0 += 1)
    S[c0][c0+915] = MAX(S[c0][c0+915], S[c0+1][c0+915-1] + can_pair(RNA, c0, c0+915));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 83; c0 += 1)
    for (c1 = c0 + 916; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-916+c0] + S[-c0+c1-916+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][915+c0] + S[915+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 83; c0 += 1)
    S[c0][c0+916] = MAX(S[c0][c0+916], S[c0+1][c0+916-1] + can_pair(RNA, c0, c0+916));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 82; c0 += 1)
    for (c1 = c0 + 917; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-917+c0] + S[-c0+c1-917+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][916+c0] + S[916+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 82; c0 += 1)
    S[c0][c0+917] = MAX(S[c0][c0+917], S[c0+1][c0+917-1] + can_pair(RNA, c0, c0+917));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 81; c0 += 1)
    for (c1 = c0 + 918; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-918+c0] + S[-c0+c1-918+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][917+c0] + S[917+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 81; c0 += 1)
    S[c0][c0+918] = MAX(S[c0][c0+918], S[c0+1][c0+918-1] + can_pair(RNA, c0, c0+918));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 80; c0 += 1)
    for (c1 = c0 + 919; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-919+c0] + S[-c0+c1-919+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][918+c0] + S[918+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 80; c0 += 1)
    S[c0][c0+919] = MAX(S[c0][c0+919], S[c0+1][c0+919-1] + can_pair(RNA, c0, c0+919));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 79; c0 += 1)
    for (c1 = c0 + 920; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-920+c0] + S[-c0+c1-920+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][919+c0] + S[919+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 79; c0 += 1)
    S[c0][c0+920] = MAX(S[c0][c0+920], S[c0+1][c0+920-1] + can_pair(RNA, c0, c0+920));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 78; c0 += 1)
    for (c1 = c0 + 921; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-921+c0] + S[-c0+c1-921+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][920+c0] + S[920+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 78; c0 += 1)
    S[c0][c0+921] = MAX(S[c0][c0+921], S[c0+1][c0+921-1] + can_pair(RNA, c0, c0+921));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 77; c0 += 1)
    for (c1 = c0 + 922; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-922+c0] + S[-c0+c1-922+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][921+c0] + S[921+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 77; c0 += 1)
    S[c0][c0+922] = MAX(S[c0][c0+922], S[c0+1][c0+922-1] + can_pair(RNA, c0, c0+922));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 76; c0 += 1)
    for (c1 = c0 + 923; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-923+c0] + S[-c0+c1-923+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][922+c0] + S[922+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 76; c0 += 1)
    S[c0][c0+923] = MAX(S[c0][c0+923], S[c0+1][c0+923-1] + can_pair(RNA, c0, c0+923));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 75; c0 += 1)
    for (c1 = c0 + 924; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-924+c0] + S[-c0+c1-924+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][923+c0] + S[923+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 75; c0 += 1)
    S[c0][c0+924] = MAX(S[c0][c0+924], S[c0+1][c0+924-1] + can_pair(RNA, c0, c0+924));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 74; c0 += 1)
    for (c1 = c0 + 925; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-925+c0] + S[-c0+c1-925+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][924+c0] + S[924+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 74; c0 += 1)
    S[c0][c0+925] = MAX(S[c0][c0+925], S[c0+1][c0+925-1] + can_pair(RNA, c0, c0+925));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 73; c0 += 1)
    for (c1 = c0 + 926; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-926+c0] + S[-c0+c1-926+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][925+c0] + S[925+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 73; c0 += 1)
    S[c0][c0+926] = MAX(S[c0][c0+926], S[c0+1][c0+926-1] + can_pair(RNA, c0, c0+926));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 72; c0 += 1)
    for (c1 = c0 + 927; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-927+c0] + S[-c0+c1-927+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][926+c0] + S[926+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 72; c0 += 1)
    S[c0][c0+927] = MAX(S[c0][c0+927], S[c0+1][c0+927-1] + can_pair(RNA, c0, c0+927));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 71; c0 += 1)
    for (c1 = c0 + 928; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-928+c0] + S[-c0+c1-928+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][927+c0] + S[927+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 71; c0 += 1)
    S[c0][c0+928] = MAX(S[c0][c0+928], S[c0+1][c0+928-1] + can_pair(RNA, c0, c0+928));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 70; c0 += 1)
    for (c1 = c0 + 929; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-929+c0] + S[-c0+c1-929+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][928+c0] + S[928+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 70; c0 += 1)
    S[c0][c0+929] = MAX(S[c0][c0+929], S[c0+1][c0+929-1] + can_pair(RNA, c0, c0+929));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 69; c0 += 1)
    for (c1 = c0 + 930; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-930+c0] + S[-c0+c1-930+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][929+c0] + S[929+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 69; c0 += 1)
    S[c0][c0+930] = MAX(S[c0][c0+930], S[c0+1][c0+930-1] + can_pair(RNA, c0, c0+930));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 68; c0 += 1)
    for (c1 = c0 + 931; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-931+c0] + S[-c0+c1-931+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][930+c0] + S[930+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 68; c0 += 1)
    S[c0][c0+931] = MAX(S[c0][c0+931], S[c0+1][c0+931-1] + can_pair(RNA, c0, c0+931));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 67; c0 += 1)
    for (c1 = c0 + 932; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-932+c0] + S[-c0+c1-932+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][931+c0] + S[931+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 67; c0 += 1)
    S[c0][c0+932] = MAX(S[c0][c0+932], S[c0+1][c0+932-1] + can_pair(RNA, c0, c0+932));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 66; c0 += 1)
    for (c1 = c0 + 933; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-933+c0] + S[-c0+c1-933+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][932+c0] + S[932+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 66; c0 += 1)
    S[c0][c0+933] = MAX(S[c0][c0+933], S[c0+1][c0+933-1] + can_pair(RNA, c0, c0+933));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 65; c0 += 1)
    for (c1 = c0 + 934; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-934+c0] + S[-c0+c1-934+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][933+c0] + S[933+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 65; c0 += 1)
    S[c0][c0+934] = MAX(S[c0][c0+934], S[c0+1][c0+934-1] + can_pair(RNA, c0, c0+934));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 64; c0 += 1)
    for (c1 = c0 + 935; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-935+c0] + S[-c0+c1-935+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][934+c0] + S[934+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 64; c0 += 1)
    S[c0][c0+935] = MAX(S[c0][c0+935], S[c0+1][c0+935-1] + can_pair(RNA, c0, c0+935));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 63; c0 += 1)
    for (c1 = c0 + 936; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-936+c0] + S[-c0+c1-936+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][935+c0] + S[935+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 63; c0 += 1)
    S[c0][c0+936] = MAX(S[c0][c0+936], S[c0+1][c0+936-1] + can_pair(RNA, c0, c0+936));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 62; c0 += 1)
    for (c1 = c0 + 937; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-937+c0] + S[-c0+c1-937+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][936+c0] + S[936+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 62; c0 += 1)
    S[c0][c0+937] = MAX(S[c0][c0+937], S[c0+1][c0+937-1] + can_pair(RNA, c0, c0+937));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 61; c0 += 1)
    for (c1 = c0 + 938; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-938+c0] + S[-c0+c1-938+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][937+c0] + S[937+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 61; c0 += 1)
    S[c0][c0+938] = MAX(S[c0][c0+938], S[c0+1][c0+938-1] + can_pair(RNA, c0, c0+938));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 60; c0 += 1)
    for (c1 = c0 + 939; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-939+c0] + S[-c0+c1-939+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][938+c0] + S[938+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 60; c0 += 1)
    S[c0][c0+939] = MAX(S[c0][c0+939], S[c0+1][c0+939-1] + can_pair(RNA, c0, c0+939));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 59; c0 += 1)
    for (c1 = c0 + 940; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-940+c0] + S[-c0+c1-940+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][939+c0] + S[939+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 59; c0 += 1)
    S[c0][c0+940] = MAX(S[c0][c0+940], S[c0+1][c0+940-1] + can_pair(RNA, c0, c0+940));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 58; c0 += 1)
    for (c1 = c0 + 941; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-941+c0] + S[-c0+c1-941+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][940+c0] + S[940+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 58; c0 += 1)
    S[c0][c0+941] = MAX(S[c0][c0+941], S[c0+1][c0+941-1] + can_pair(RNA, c0, c0+941));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 57; c0 += 1)
    for (c1 = c0 + 942; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-942+c0] + S[-c0+c1-942+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][941+c0] + S[941+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 57; c0 += 1)
    S[c0][c0+942] = MAX(S[c0][c0+942], S[c0+1][c0+942-1] + can_pair(RNA, c0, c0+942));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 56; c0 += 1)
    for (c1 = c0 + 943; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-943+c0] + S[-c0+c1-943+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][942+c0] + S[942+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 56; c0 += 1)
    S[c0][c0+943] = MAX(S[c0][c0+943], S[c0+1][c0+943-1] + can_pair(RNA, c0, c0+943));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 55; c0 += 1)
    for (c1 = c0 + 944; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-944+c0] + S[-c0+c1-944+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][943+c0] + S[943+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 55; c0 += 1)
    S[c0][c0+944] = MAX(S[c0][c0+944], S[c0+1][c0+944-1] + can_pair(RNA, c0, c0+944));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 54; c0 += 1)
    for (c1 = c0 + 945; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-945+c0] + S[-c0+c1-945+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][944+c0] + S[944+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 54; c0 += 1)
    S[c0][c0+945] = MAX(S[c0][c0+945], S[c0+1][c0+945-1] + can_pair(RNA, c0, c0+945));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 53; c0 += 1)
    for (c1 = c0 + 946; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-946+c0] + S[-c0+c1-946+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][945+c0] + S[945+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 53; c0 += 1)
    S[c0][c0+946] = MAX(S[c0][c0+946], S[c0+1][c0+946-1] + can_pair(RNA, c0, c0+946));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 52; c0 += 1)
    for (c1 = c0 + 947; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-947+c0] + S[-c0+c1-947+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][946+c0] + S[946+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 52; c0 += 1)
    S[c0][c0+947] = MAX(S[c0][c0+947], S[c0+1][c0+947-1] + can_pair(RNA, c0, c0+947));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 51; c0 += 1)
    for (c1 = c0 + 948; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-948+c0] + S[-c0+c1-948+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][947+c0] + S[947+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 51; c0 += 1)
    S[c0][c0+948] = MAX(S[c0][c0+948], S[c0+1][c0+948-1] + can_pair(RNA, c0, c0+948));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 50; c0 += 1)
    for (c1 = c0 + 949; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-949+c0] + S[-c0+c1-949+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][948+c0] + S[948+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 50; c0 += 1)
    S[c0][c0+949] = MAX(S[c0][c0+949], S[c0+1][c0+949-1] + can_pair(RNA, c0, c0+949));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 49; c0 += 1)
    for (c1 = c0 + 950; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-950+c0] + S[-c0+c1-950+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][949+c0] + S[949+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 49; c0 += 1)
    S[c0][c0+950] = MAX(S[c0][c0+950], S[c0+1][c0+950-1] + can_pair(RNA, c0, c0+950));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 48; c0 += 1)
    for (c1 = c0 + 951; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-951+c0] + S[-c0+c1-951+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][950+c0] + S[950+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 48; c0 += 1)
    S[c0][c0+951] = MAX(S[c0][c0+951], S[c0+1][c0+951-1] + can_pair(RNA, c0, c0+951));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 47; c0 += 1)
    for (c1 = c0 + 952; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-952+c0] + S[-c0+c1-952+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][951+c0] + S[951+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 47; c0 += 1)
    S[c0][c0+952] = MAX(S[c0][c0+952], S[c0+1][c0+952-1] + can_pair(RNA, c0, c0+952));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 46; c0 += 1)
    for (c1 = c0 + 953; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-953+c0] + S[-c0+c1-953+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][952+c0] + S[952+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 46; c0 += 1)
    S[c0][c0+953] = MAX(S[c0][c0+953], S[c0+1][c0+953-1] + can_pair(RNA, c0, c0+953));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 45; c0 += 1)
    for (c1 = c0 + 954; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-954+c0] + S[-c0+c1-954+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][953+c0] + S[953+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 45; c0 += 1)
    S[c0][c0+954] = MAX(S[c0][c0+954], S[c0+1][c0+954-1] + can_pair(RNA, c0, c0+954));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 44; c0 += 1)
    for (c1 = c0 + 955; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-955+c0] + S[-c0+c1-955+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][954+c0] + S[954+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 44; c0 += 1)
    S[c0][c0+955] = MAX(S[c0][c0+955], S[c0+1][c0+955-1] + can_pair(RNA, c0, c0+955));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 43; c0 += 1)
    for (c1 = c0 + 956; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-956+c0] + S[-c0+c1-956+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][955+c0] + S[955+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 43; c0 += 1)
    S[c0][c0+956] = MAX(S[c0][c0+956], S[c0+1][c0+956-1] + can_pair(RNA, c0, c0+956));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 42; c0 += 1)
    for (c1 = c0 + 957; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-957+c0] + S[-c0+c1-957+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][956+c0] + S[956+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 42; c0 += 1)
    S[c0][c0+957] = MAX(S[c0][c0+957], S[c0+1][c0+957-1] + can_pair(RNA, c0, c0+957));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 41; c0 += 1)
    for (c1 = c0 + 958; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-958+c0] + S[-c0+c1-958+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][957+c0] + S[957+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 41; c0 += 1)
    S[c0][c0+958] = MAX(S[c0][c0+958], S[c0+1][c0+958-1] + can_pair(RNA, c0, c0+958));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 40; c0 += 1)
    for (c1 = c0 + 959; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-959+c0] + S[-c0+c1-959+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][958+c0] + S[958+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 40; c0 += 1)
    S[c0][c0+959] = MAX(S[c0][c0+959], S[c0+1][c0+959-1] + can_pair(RNA, c0, c0+959));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 39; c0 += 1)
    for (c1 = c0 + 960; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-960+c0] + S[-c0+c1-960+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][959+c0] + S[959+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 39; c0 += 1)
    S[c0][c0+960] = MAX(S[c0][c0+960], S[c0+1][c0+960-1] + can_pair(RNA, c0, c0+960));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 38; c0 += 1)
    for (c1 = c0 + 961; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-961+c0] + S[-c0+c1-961+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][960+c0] + S[960+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 38; c0 += 1)
    S[c0][c0+961] = MAX(S[c0][c0+961], S[c0+1][c0+961-1] + can_pair(RNA, c0, c0+961));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 37; c0 += 1)
    for (c1 = c0 + 962; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-962+c0] + S[-c0+c1-962+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][961+c0] + S[961+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 37; c0 += 1)
    S[c0][c0+962] = MAX(S[c0][c0+962], S[c0+1][c0+962-1] + can_pair(RNA, c0, c0+962));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 36; c0 += 1)
    for (c1 = c0 + 963; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-963+c0] + S[-c0+c1-963+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][962+c0] + S[962+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 36; c0 += 1)
    S[c0][c0+963] = MAX(S[c0][c0+963], S[c0+1][c0+963-1] + can_pair(RNA, c0, c0+963));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 35; c0 += 1)
    for (c1 = c0 + 964; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-964+c0] + S[-c0+c1-964+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][963+c0] + S[963+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 35; c0 += 1)
    S[c0][c0+964] = MAX(S[c0][c0+964], S[c0+1][c0+964-1] + can_pair(RNA, c0, c0+964));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 34; c0 += 1)
    for (c1 = c0 + 965; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-965+c0] + S[-c0+c1-965+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][964+c0] + S[964+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 34; c0 += 1)
    S[c0][c0+965] = MAX(S[c0][c0+965], S[c0+1][c0+965-1] + can_pair(RNA, c0, c0+965));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 33; c0 += 1)
    for (c1 = c0 + 966; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-966+c0] + S[-c0+c1-966+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][965+c0] + S[965+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 33; c0 += 1)
    S[c0][c0+966] = MAX(S[c0][c0+966], S[c0+1][c0+966-1] + can_pair(RNA, c0, c0+966));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 32; c0 += 1)
    for (c1 = c0 + 967; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-967+c0] + S[-c0+c1-967+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][966+c0] + S[966+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 32; c0 += 1)
    S[c0][c0+967] = MAX(S[c0][c0+967], S[c0+1][c0+967-1] + can_pair(RNA, c0, c0+967));
}
// parallel -----
#pragma omp for
  for (c0 = 0; c0 <= 31; c0 += 1)
    for (c1 = c0 + 968; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-968+c0] + S[-c0+c1-968+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][967+c0] + S[967+c0+1][c1], S[c0][c1]);
    }
// --------------
#pragma omp single
{
  for (c0 = 0; c0 <= 31; c0 += 1)
    S[c0][c0+968] = MAX(S[c0][c0+968], S[c0+1][c0+968-1] + can_pair(RNA, c0, c0+968));
// --------------
  for (c0 = 0; c0 <= 30; c0 += 1)
    for (c1 = c0 + 969; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-969+c0] + S[-c0+c1-969+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][968+c0] + S[968+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 30; c0 += 1)
    S[c0][c0+969] = MAX(S[c0][c0+969], S[c0+1][c0+969-1] + can_pair(RNA, c0, c0+969));
// --------------
  for (c0 = 0; c0 <= 29; c0 += 1)
    for (c1 = c0 + 970; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-970+c0] + S[-c0+c1-970+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][969+c0] + S[969+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 29; c0 += 1)
    S[c0][c0+970] = MAX(S[c0][c0+970], S[c0+1][c0+970-1] + can_pair(RNA, c0, c0+970));
// --------------
  for (c0 = 0; c0 <= 28; c0 += 1)
    for (c1 = c0 + 971; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-971+c0] + S[-c0+c1-971+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][970+c0] + S[970+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 28; c0 += 1)
    S[c0][c0+971] = MAX(S[c0][c0+971], S[c0+1][c0+971-1] + can_pair(RNA, c0, c0+971));
// --------------
  for (c0 = 0; c0 <= 27; c0 += 1)
    for (c1 = c0 + 972; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-972+c0] + S[-c0+c1-972+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][971+c0] + S[971+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 27; c0 += 1)
    S[c0][c0+972] = MAX(S[c0][c0+972], S[c0+1][c0+972-1] + can_pair(RNA, c0, c0+972));
// --------------
  for (c0 = 0; c0 <= 26; c0 += 1)
    for (c1 = c0 + 973; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-973+c0] + S[-c0+c1-973+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][972+c0] + S[972+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 26; c0 += 1)
    S[c0][c0+973] = MAX(S[c0][c0+973], S[c0+1][c0+973-1] + can_pair(RNA, c0, c0+973));
// --------------
  for (c0 = 0; c0 <= 25; c0 += 1)
    for (c1 = c0 + 974; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-974+c0] + S[-c0+c1-974+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][973+c0] + S[973+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 25; c0 += 1)
    S[c0][c0+974] = MAX(S[c0][c0+974], S[c0+1][c0+974-1] + can_pair(RNA, c0, c0+974));
// --------------
  for (c0 = 0; c0 <= 24; c0 += 1)
    for (c1 = c0 + 975; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-975+c0] + S[-c0+c1-975+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][974+c0] + S[974+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 24; c0 += 1)
    S[c0][c0+975] = MAX(S[c0][c0+975], S[c0+1][c0+975-1] + can_pair(RNA, c0, c0+975));
// --------------
  for (c0 = 0; c0 <= 23; c0 += 1)
    for (c1 = c0 + 976; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-976+c0] + S[-c0+c1-976+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][975+c0] + S[975+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 23; c0 += 1)
    S[c0][c0+976] = MAX(S[c0][c0+976], S[c0+1][c0+976-1] + can_pair(RNA, c0, c0+976));
// --------------
  for (c0 = 0; c0 <= 22; c0 += 1)
    for (c1 = c0 + 977; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-977+c0] + S[-c0+c1-977+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][976+c0] + S[976+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 22; c0 += 1)
    S[c0][c0+977] = MAX(S[c0][c0+977], S[c0+1][c0+977-1] + can_pair(RNA, c0, c0+977));
// --------------
  for (c0 = 0; c0 <= 21; c0 += 1)
    for (c1 = c0 + 978; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-978+c0] + S[-c0+c1-978+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][977+c0] + S[977+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 21; c0 += 1)
    S[c0][c0+978] = MAX(S[c0][c0+978], S[c0+1][c0+978-1] + can_pair(RNA, c0, c0+978));
// --------------
  for (c0 = 0; c0 <= 20; c0 += 1)
    for (c1 = c0 + 979; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-979+c0] + S[-c0+c1-979+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][978+c0] + S[978+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 20; c0 += 1)
    S[c0][c0+979] = MAX(S[c0][c0+979], S[c0+1][c0+979-1] + can_pair(RNA, c0, c0+979));
// --------------
  for (c0 = 0; c0 <= 19; c0 += 1)
    for (c1 = c0 + 980; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-980+c0] + S[-c0+c1-980+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][979+c0] + S[979+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 19; c0 += 1)
    S[c0][c0+980] = MAX(S[c0][c0+980], S[c0+1][c0+980-1] + can_pair(RNA, c0, c0+980));
// --------------
  for (c0 = 0; c0 <= 18; c0 += 1)
    for (c1 = c0 + 981; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-981+c0] + S[-c0+c1-981+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][980+c0] + S[980+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 18; c0 += 1)
    S[c0][c0+981] = MAX(S[c0][c0+981], S[c0+1][c0+981-1] + can_pair(RNA, c0, c0+981));
// --------------
  for (c0 = 0; c0 <= 17; c0 += 1)
    for (c1 = c0 + 982; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-982+c0] + S[-c0+c1-982+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][981+c0] + S[981+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 17; c0 += 1)
    S[c0][c0+982] = MAX(S[c0][c0+982], S[c0+1][c0+982-1] + can_pair(RNA, c0, c0+982));
// --------------
  for (c0 = 0; c0 <= 16; c0 += 1)
    for (c1 = c0 + 983; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-983+c0] + S[-c0+c1-983+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][982+c0] + S[982+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 16; c0 += 1)
    S[c0][c0+983] = MAX(S[c0][c0+983], S[c0+1][c0+983-1] + can_pair(RNA, c0, c0+983));
// --------------
  for (c0 = 0; c0 <= 15; c0 += 1)
    for (c1 = c0 + 984; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-984+c0] + S[-c0+c1-984+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][983+c0] + S[983+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 15; c0 += 1)
    S[c0][c0+984] = MAX(S[c0][c0+984], S[c0+1][c0+984-1] + can_pair(RNA, c0, c0+984));
// --------------
  for (c0 = 0; c0 <= 14; c0 += 1)
    for (c1 = c0 + 985; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-985+c0] + S[-c0+c1-985+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][984+c0] + S[984+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 14; c0 += 1)
    S[c0][c0+985] = MAX(S[c0][c0+985], S[c0+1][c0+985-1] + can_pair(RNA, c0, c0+985));
// --------------
  for (c0 = 0; c0 <= 13; c0 += 1)
    for (c1 = c0 + 986; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-986+c0] + S[-c0+c1-986+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][985+c0] + S[985+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 13; c0 += 1)
    S[c0][c0+986] = MAX(S[c0][c0+986], S[c0+1][c0+986-1] + can_pair(RNA, c0, c0+986));
// --------------
  for (c0 = 0; c0 <= 12; c0 += 1)
    for (c1 = c0 + 987; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-987+c0] + S[-c0+c1-987+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][986+c0] + S[986+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 12; c0 += 1)
    S[c0][c0+987] = MAX(S[c0][c0+987], S[c0+1][c0+987-1] + can_pair(RNA, c0, c0+987));
// --------------
  for (c0 = 0; c0 <= 11; c0 += 1)
    for (c1 = c0 + 988; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-988+c0] + S[-c0+c1-988+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][987+c0] + S[987+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 11; c0 += 1)
    S[c0][c0+988] = MAX(S[c0][c0+988], S[c0+1][c0+988-1] + can_pair(RNA, c0, c0+988));
// --------------
  for (c0 = 0; c0 <= 10; c0 += 1)
    for (c1 = c0 + 989; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-989+c0] + S[-c0+c1-989+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][988+c0] + S[988+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 10; c0 += 1)
    S[c0][c0+989] = MAX(S[c0][c0+989], S[c0+1][c0+989-1] + can_pair(RNA, c0, c0+989));
// --------------
  for (c0 = 0; c0 <= 9; c0 += 1)
    for (c1 = c0 + 990; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-990+c0] + S[-c0+c1-990+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][989+c0] + S[989+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 9; c0 += 1)
    S[c0][c0+990] = MAX(S[c0][c0+990], S[c0+1][c0+990-1] + can_pair(RNA, c0, c0+990));
// --------------
  for (c0 = 0; c0 <= 8; c0 += 1)
    for (c1 = c0 + 991; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-991+c0] + S[-c0+c1-991+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][990+c0] + S[990+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 8; c0 += 1)
    S[c0][c0+991] = MAX(S[c0][c0+991], S[c0+1][c0+991-1] + can_pair(RNA, c0, c0+991));
// --------------
  for (c0 = 0; c0 <= 7; c0 += 1)
    for (c1 = c0 + 992; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-992+c0] + S[-c0+c1-992+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][991+c0] + S[991+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 7; c0 += 1)
    S[c0][c0+992] = MAX(S[c0][c0+992], S[c0+1][c0+992-1] + can_pair(RNA, c0, c0+992));
// --------------
  for (c0 = 0; c0 <= 6; c0 += 1)
    for (c1 = c0 + 993; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-993+c0] + S[-c0+c1-993+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][992+c0] + S[992+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 6; c0 += 1)
    S[c0][c0+993] = MAX(S[c0][c0+993], S[c0+1][c0+993-1] + can_pair(RNA, c0, c0+993));
// --------------
  for (c0 = 0; c0 <= 5; c0 += 1)
    for (c1 = c0 + 994; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-994+c0] + S[-c0+c1-994+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][993+c0] + S[993+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 5; c0 += 1)
    S[c0][c0+994] = MAX(S[c0][c0+994], S[c0+1][c0+994-1] + can_pair(RNA, c0, c0+994));
// --------------
  for (c0 = 0; c0 <= 4; c0 += 1)
    for (c1 = c0 + 995; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-995+c0] + S[-c0+c1-995+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][994+c0] + S[994+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 4; c0 += 1)
    S[c0][c0+995] = MAX(S[c0][c0+995], S[c0+1][c0+995-1] + can_pair(RNA, c0, c0+995));
// --------------
  for (c0 = 0; c0 <= 3; c0 += 1)
    for (c1 = c0 + 996; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-996+c0] + S[-c0+c1-996+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][995+c0] + S[995+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 3; c0 += 1)
    S[c0][c0+996] = MAX(S[c0][c0+996], S[c0+1][c0+996-1] + can_pair(RNA, c0, c0+996));
// --------------
  for (c0 = 0; c0 <= 2; c0 += 1)
    for (c1 = c0 + 997; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-997+c0] + S[-c0+c1-997+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][996+c0] + S[996+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 2; c0 += 1)
    S[c0][c0+997] = MAX(S[c0][c0+997], S[c0+1][c0+997-1] + can_pair(RNA, c0, c0+997));
// --------------
  for (c0 = 0; c0 <= 1; c0 += 1)
    for (c1 = c0 + 998; c1 <= 999; c1 += 1) {
      S[c0][c1] = MAX(S[c0][-c0+c1-998+c0] + S[-c0+c1-998+c0+1][c1], S[c0][c1]);
      S[c0][c1] = MAX(S[c0][997+c0] + S[997+c0+1][c1], S[c0][c1]);
    }
// --------------
  for (c0 = 0; c0 <= 1; c0 += 1)
    S[c0][c0+998] = MAX(S[c0][c0+998], S[c0+1][c0+998-1] + can_pair(RNA, c0, c0+998));
// --------------
if (N == 1000) {
  S[0][999] = MAX(S[0][0+0] + S[0+0+1][999], S[0][999]);
  S[0][999] = MAX(S[0][998+0] + S[998+0+1][999], S[0][999]);
}
// --------------
  S[0][999] = MAX(S[0][999], S[0+1][999-1] + can_pair(RNA, 0, 999));

}
}






    end = omp_get_wtime();
	printf("%.6f\n", end - start);

    return 0;


}

