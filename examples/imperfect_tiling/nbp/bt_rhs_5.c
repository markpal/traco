#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 200;
int N1, N2, N3, N4, DIM;
int DIM1;
int DIM2;
int DIM3;






void seq(float rhs[6][DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3],
         float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3]) {
int i,j,k,wijk,wp1,wm1,dz1tz1=1,dz2tz1=1,dz3tz1=1,dz4tz1=1,dz5tz1=1,tz2=1,zzcon2=1,zzcon3=1,zzcon43=1,zzcon4=1,cc2=1,con43=1,zzcon5=1,c1=1;

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      wijk = ws[i][j][k];
      wp1  = ws[i][j][k+1];
      wm1  = ws[i][j][k-1];

      rhs[1][i][j][k] = rhs[1][i][j][k] + dz1tz1 * (u[1][i][j][k+1] - 2.0*u[1][i][j][k] + u[1][i][j][k-1]) - tz2 * (u[4][i][j][k+1] - u[4][i][j][k-1]);
      rhs[2][i][j][k] = rhs[2][i][j][k] + dz2tz1 * (u[2][i][j][k+1] - 2.0*u[2][i][j][k] + u[2][i][j][k-1]) + zzcon2 * (us[i][j][k+1] - 2.0*us[i][j][k] + us[i][j][k-1]) - tz2 * (u[2][i][j][k+1]*wp1 - u[2][i][j][k-1]*wm1);
      rhs[3][i][j][k] = rhs[3][i][j][k] + dz3tz1 * (u[3][i][j][k+1] - 2.0*u[3][i][j][k] + u[3][i][j][k-1]) + zzcon2 * (vs[i][j][k+1] - 2.0*vs[i][j][k] + vs[i][j][k-1]) - tz2 * (u[3][i][j][k+1]*wp1 - u[3][i][j][k-1]*wm1);
      rhs[4][i][j][k] = rhs[4][i][j][k] + dz4tz1 * (u[4][i][j][k+1] - 2.0*u[4][i][j][k] + u[4][i][j][k-1]) + zzcon2*con43 * (wp1 - 2.0*wijk + wm1) - tz2 * (u[4][i][j][k+1]*wp1 - u[4][i][j][k-1]*wm1 + (u[5][i][j][k+1] - square[i][j][k+1] - u[5][i][j][k-1] + square[i][j][k-1]) *cc2);
      rhs[5][i][j][k] = rhs[5][i][j][k] + dz5tz1 * (u[5][i][j][k+1] - 2.0*u[5][i][j][k] + u[5][i][j][k-1]) + zzcon3 * (qs[i][j][k+1] - 2.0*qs[i][j][k] + qs[i][j][k-1]) + zzcon4 * (wp1*wp1 - 2.0*wijk*wijk + wm1*wm1) + zzcon5 * (u[5][i][j][k+1]*rho_i[i][j][k+1] - 2.0*u[5][i][j][k]*rho_i[i][j][k] + u[5][i][j][k-1]*rho_i[i][j][k-1]) - tz2 * ( (c1*u[5][i][j][k+1] - cc2*square[i][j][k+1])*wp1 - (c1*u[5][i][j][k-1] - cc2*square[i][j][k-1])*wm1);
    }
  }
}


}


void comp(float rhs[6][DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3],
         float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3]) {
int i,j,k,wijk,wp1,wm1,dz1tz1=1,dz2tz1=1,dz3tz1=1,dz4tz1=1,dz5tz1=1,tz2=1,zzcon2=1,zzcon3=1,zzcon43=1,zzcon4=1,cc2=1,con43=1,zzcon5=1;
int c0, c2, c4, c6, c8, c10,c1=1;

/*
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          for (c10 = 16 * c4 + 1; c10 <= min(N3, 16 * c4 + 16); c10 += 1) {
            wijk=ws[c10][c8][c6];
            wp1=ws[c10][c8][c6+1];
            wm1=ws[c10][c8][c6-1];
            rhs[1][c10][c8][c6]=rhs[1][c10][c8][c6]+dz1tz1*(u[1][c10][c8][c6+1]-2.0*u[1][c10][c8][c6]+u[1][c10][c8][c6-1])-tz2*(u[4][c10][c8][c6+1]-u[4][c10][c8][c6-1]);
            rhs[2][c10][c8][c6]=rhs[2][c10][c8][c6]+dz2tz1*(u[2][c10][c8][c6+1]-2.0*u[2][c10][c8][c6]+u[2][c10][c8][c6-1])+zzcon2*(us[c10][c8][c6+1]-2.0*us[c10][c8][c6]+us[c10][c8][c6-1])-tz2*(u[2][c10][c8][c6+1]*wp1-u[2][c10][c8][c6-1]*wm1);
            rhs[3][c10][c8][c6]=rhs[3][c10][c8][c6]+dz3tz1*(u[3][c10][c8][c6+1]-2.0*u[3][c10][c8][c6]+u[3][c10][c8][c6-1])+zzcon2*(vs[c10][c8][c6+1]-2.0*vs[c10][c8][c6]+vs[c10][c8][c6-1])-tz2*(u[3][c10][c8][c6+1]*wp1-u[3][c10][c8][c6-1]*wm1);
            rhs[4][c10][c8][c6]=rhs[4][c10][c8][c6]+dz4tz1*(u[4][c10][c8][c6+1]-2.0*u[4][c10][c8][c6]+u[4][c10][c8][c6-1])+zzcon2*con43*(wp1-2.0*wijk+wm1)-tz2*(u[4][c10][c8][c6+1]*wp1-u[4][c10][c8][c6-1]*wm1+(u[5][c10][c8][c6+1]-square[c10][c8][c6+1]-u[5][c10][c8][c6-1]+square[c10][c8][c6-1])*cc2);
            rhs[5][c10][c8][c6]=rhs[5][c10][c8][c6]+dz5tz1*(u[5][c10][c8][c6+1]-2.0*u[5][c10][c8][c6]+u[5][c10][c8][c6-1])+zzcon3*(qs[c10][c8][c6+1]-2.0*qs[c10][c8][c6]+qs[c10][c8][c6-1])+zzcon4*(wp1*wp1-2.0*wijk*wijk+wm1*wm1)+zzcon5*(u[5][c10][c8][c6+1]*rho_i[c10][c8][c6+1]-2.0*u[5][c10][c8][c6]*rho_i[c10][c8][c6]+u[5][c10][c8][c6-1]*rho_i[c10][c8][c6-1])-tz2*((c1*u[5][c10][c8][c6+1]-cc2*square[c10][c8][c6+1])*wp1-(c1*u[5][c10][c8][c6-1]-cc2*square[c10][c8][c6-1])*wm1);
          }


*/
#pragma omp parallel for private(wijk, wp1, wm1)
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
      if (c0 >= 0 && c2 >= 0 && c1 >= 0)
        for (c3 = 16 * c0 + 1; c3 <= min(N1, 16 * c0 + 16); c3 += 1)
          for (c4 = 16 * c1 + 1; c4 <= min(N2, 16 * c1 + 16); c4 += 1)
            for (c5 = 16 * c2 + 1; c5 <= min(N3, 16 * c2 + 16); c5 += 1) {
              wijk=ws[c5][c4][c3];
              wp1=ws[c5][c4][c3+1];
              wm1=ws[c5][c4][c3-1];
              rhs[1][c5][c4][c3]=rhs[1][c5][c4][c3]+dz1tz1*(u[1][c5][c4][c3+1]-2.0*u[1][c5][c4][c3]+u[1][c5][c4][c3-1])-tz2*(u[4][c5][c4][c3+1]-u[4][c5][c4][c3-1]);
              rhs[2][c5][c4][c3]=rhs[2][c5][c4][c3]+dz2tz1*(u[2][c5][c4][c3+1]-2.0*u[2][c5][c4][c3]+u[2][c5][c4][c3-1])+zzcon2*(us[c5][c4][c3+1]-2.0*us[c5][c4][c3]+us[c5][c4][c3-1])-tz2*(u[2][c5][c4][c3+1]*wp1-u[2][c5][c4][c3-1]*wm1];
              rhs[3][c5][c4][c3]=rhs[3][c5][c4][c3]+dz3tz1*(u[3][c5][c4][c3+1]-2.0*u[3][c5][c4][c3]+u[3][c5][c4][c3-1])+zzcon2*(vs[c5][c4][c3+1]-2.0*vs[c5][c4][c3]+vs[c5][c4][c3-1])-tz2*(u[3][c5][c4][c3+1]*wp1-u[3][c5][c4][c3-1]*wm1];
              rhs[4][c5][c4][c3]=rhs[4][c5][c4][c3]+dz4tz1*(u[4][c5][c4][c3+1]-2.0*u[4][c5][c4][c3]+u[4][c5][c4][c3-1])+zzcon2*con43*(wp1-2.0*wijk+wm1]-tz2*(u[4][c5][c4][c3+1]*wp1-u[4][c5][c4][c3-1]*wm1+(u[5][c5][c4][c3+1]-square[c5][c4][c3+1]-u[5][c5][c4][c3-1]+square[c5][c4][c3-1])*cc2];
              rhs[5][c5][c4][c3]=rhs[5][c5][c4][c3]+dz5tz1*(u[5][c5][c4][c3+1]-2.0*u[5][c5][c4][c3]+u[5][c5][c4][c3-1])+zzcon3*(qs[c5][c4][c3+1]-2.0*qs[c5][c4][c3]+qs[c5][c4][c3-1])+zzcon4*(wp1*wp1-2.0*wijk*wijk+wm1*wm1]+zzcon5*(u[5][c5][c4][c3+1]*rho_i[c5][c4][c3+1]-2.0*u[5][c5][c4][c3]*rho_i[c5][c4][c3]+u[5][c5][c4][c3-1]*rho_i[c5][c4][c3-1])-tz2*((c1*u[5][c5][c4][c3+1]-cc2*square[c5][c4][c3+1])*wp1-(c1*u[5][c5][c4][c3-1]-cc2*square[c5][c4][c3-1])*wm1];
            }


}

void comp4(float rhs[6][DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3],
         float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3]) {
int i,j,k,wijk,wp1,wm1,dz1tz1=1,dz2tz1=1,dz3tz1=1,dz4tz1=1,dz5tz1=1,tz2=1,zzcon2=1,zzcon3=1,zzcon43=1,zzcon4=1,cc2=1,con43=1,zzcon5=1;
int c0, c2, c4, c6, c8, c10,c1=1;

for (c0 = 0; c0 <= floord(N1 - 1, 4); c0 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 4); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 4); c4 += 1)
      for (c6 = 4 * c0 + 1; c6 <= min(N1, 4 * c0 + 4); c6 += 1)
        for (c8 = 4 * c2 + 1; c8 <= min(N2, 4 * c2 + 4); c8 += 1)
          for (c10 = 4 * c4 + 1; c10 <= min(N3, 4 * c4 + 4); c10 += 1) {
            wijk=ws[c10][c8][c6];
            wp1=ws[c10][c8][c6+1];
            wm1=ws[c10][c8][c6-1];
            rhs[1][c10][c8][c6]=rhs[1][c10][c8][c6]+dz1tz1*(u[1][c10][c8][c6+1]-2.0*u[1][c10][c8][c6]+u[1][c10][c8][c6-1])-tz2*(u[4][c10][c8][c6+1]-u[4][c10][c8][c6-1]);
            rhs[2][c10][c8][c6]=rhs[2][c10][c8][c6]+dz2tz1*(u[2][c10][c8][c6+1]-2.0*u[2][c10][c8][c6]+u[2][c10][c8][c6-1])+zzcon2*(us[c10][c8][c6+1]-2.0*us[c10][c8][c6]+us[c10][c8][c6-1])-tz2*(u[2][c10][c8][c6+1]*wp1-u[2][c10][c8][c6-1]*wm1);
            rhs[3][c10][c8][c6]=rhs[3][c10][c8][c6]+dz3tz1*(u[3][c10][c8][c6+1]-2.0*u[3][c10][c8][c6]+u[3][c10][c8][c6-1])+zzcon2*(vs[c10][c8][c6+1]-2.0*vs[c10][c8][c6]+vs[c10][c8][c6-1])-tz2*(u[3][c10][c8][c6+1]*wp1-u[3][c10][c8][c6-1]*wm1);
            rhs[4][c10][c8][c6]=rhs[4][c10][c8][c6]+dz4tz1*(u[4][c10][c8][c6+1]-2.0*u[4][c10][c8][c6]+u[4][c10][c8][c6-1])+zzcon2*con43*(wp1-2.0*wijk+wm1)-tz2*(u[4][c10][c8][c6+1]*wp1-u[4][c10][c8][c6-1]*wm1+(u[5][c10][c8][c6+1]-square[c10][c8][c6+1]-u[5][c10][c8][c6-1]+square[c10][c8][c6-1])*cc2);
            rhs[5][c10][c8][c6]=rhs[5][c10][c8][c6]+dz5tz1*(u[5][c10][c8][c6+1]-2.0*u[5][c10][c8][c6]+u[5][c10][c8][c6-1])+zzcon3*(qs[c10][c8][c6+1]-2.0*qs[c10][c8][c6]+qs[c10][c8][c6-1])+zzcon4*(wp1*wp1-2.0*wijk*wijk+wm1*wm1)+zzcon5*(u[5][c10][c8][c6+1]*rho_i[c10][c8][c6+1]-2.0*u[5][c10][c8][c6]*rho_i[c10][c8][c6]+u[5][c10][c8][c6-1]*rho_i[c10][c8][c6-1])-tz2*((c1*u[5][c10][c8][c6+1]-cc2*square[c10][c8][c6+1])*wp1-(c1*u[5][c10][c8][c6-1]-cc2*square[c10][c8][c6-1])*wm1);
          }


}

void comp32(float rhs[6][DIM1][DIM2][DIM3], float frct[6][DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3],
         float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3]) {
int i,j,k,wijk,wp1,wm1,dz1tz1=1,dz2tz1=1,dz3tz1=1,dz4tz1=1,dz5tz1=1,tz2=1,zzcon2=1,zzcon3=1,zzcon43=1,zzcon4=1,cc2=1,con43=1,zzcon5=1;
int c0, c2, c4, c6, c8, c10,c1=1;

for (c0 = 0; c0 <= floord(N1 - 1, 32); c0 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 32); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 32); c4 += 1)
      for (c6 = 32 * c0 + 1; c6 <= min(N1, 32 * c0 + 32); c6 += 1)
        for (c8 = 32 * c2 + 1; c8 <= min(N2, 32 * c2 + 32); c8 += 1)
          for (c10 = 32 * c4 + 1; c10 <= min(N3, 32 * c4 + 32); c10 += 1) {
            wijk=ws[c10][c8][c6];
            wp1=ws[c10][c8][c6+1];
            wm1=ws[c10][c8][c6-1];
            rhs[1][c10][c8][c6]=rhs[1][c10][c8][c6]+dz1tz1*(u[1][c10][c8][c6+1]-2.0*u[1][c10][c8][c6]+u[1][c10][c8][c6-1])-tz2*(u[4][c10][c8][c6+1]-u[4][c10][c8][c6-1]);
            rhs[2][c10][c8][c6]=rhs[2][c10][c8][c6]+dz2tz1*(u[2][c10][c8][c6+1]-2.0*u[2][c10][c8][c6]+u[2][c10][c8][c6-1])+zzcon2*(us[c10][c8][c6+1]-2.0*us[c10][c8][c6]+us[c10][c8][c6-1])-tz2*(u[2][c10][c8][c6+1]*wp1-u[2][c10][c8][c6-1]*wm1);
            rhs[3][c10][c8][c6]=rhs[3][c10][c8][c6]+dz3tz1*(u[3][c10][c8][c6+1]-2.0*u[3][c10][c8][c6]+u[3][c10][c8][c6-1])+zzcon2*(vs[c10][c8][c6+1]-2.0*vs[c10][c8][c6]+vs[c10][c8][c6-1])-tz2*(u[3][c10][c8][c6+1]*wp1-u[3][c10][c8][c6-1]*wm1);
            rhs[4][c10][c8][c6]=rhs[4][c10][c8][c6]+dz4tz1*(u[4][c10][c8][c6+1]-2.0*u[4][c10][c8][c6]+u[4][c10][c8][c6-1])+zzcon2*con43*(wp1-2.0*wijk+wm1)-tz2*(u[4][c10][c8][c6+1]*wp1-u[4][c10][c8][c6-1]*wm1+(u[5][c10][c8][c6+1]-square[c10][c8][c6+1]-u[5][c10][c8][c6-1]+square[c10][c8][c6-1])*cc2);
            rhs[5][c10][c8][c6]=rhs[5][c10][c8][c6]+dz5tz1*(u[5][c10][c8][c6+1]-2.0*u[5][c10][c8][c6]+u[5][c10][c8][c6-1])+zzcon3*(qs[c10][c8][c6+1]-2.0*qs[c10][c8][c6]+qs[c10][c8][c6-1])+zzcon4*(wp1*wp1-2.0*wijk*wijk+wm1*wm1)+zzcon5*(u[5][c10][c8][c6+1]*rho_i[c10][c8][c6+1]-2.0*u[5][c10][c8][c6]*rho_i[c10][c8][c6]+u[5][c10][c8][c6-1]*rho_i[c10][c8][c6-1])-tz2*((c1*u[5][c10][c8][c6+1]-cc2*square[c10][c8][c6+1])*wp1-(c1*u[5][c10][c8][c6-1]-cc2*square[c10][c8][c6-1])*wm1);
          }


}




void comp_pluto() {




}




int main(int argc, char *argv[]) {

  // number of processors
  int tile_kind=1;
  tile_kind = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N2 = N3 = N4 = N;
  DIM = DIM1 = DIM2 = DIM3 = N+2;

  float (*rhs)[DIM1][DIM2][DIM3], (*frct)[DIM1][DIM2][DIM3], (*u)[DIM1][DIM2][DIM3], (*vs)[DIM2][DIM3], (*us)[DIM2][DIM3], (*rho_i)[DIM2][DIM3],
  (*qs)[DIM2][DIM3], (*square)[DIM2][DIM3], (*ws)[DIM2][DIM3];


  rhs = (float (*)[DIM1][DIM2][DIM3])malloc(6 * DIM1 * DIM2 * DIM3 * sizeof(float));
  frct = (float (*)[DIM1][DIM2][DIM3])malloc(6 * DIM1 * DIM2 * DIM3 * sizeof(float));
  u = (float (*)[DIM1][DIM2][DIM3])malloc(6 * DIM1 * DIM2 * DIM3 * sizeof(float));
  rho_i = (float (*)[DIM2][DIM3])malloc( DIM1 * DIM2 * DIM3 * sizeof(float));
  qs = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  us = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  vs = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  square = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));
  ws = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));

  printf("Ilosc procesorow: %i \n\n", tile_kind);
  omp_set_num_threads(tile_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tile_kind == 1)
    seq(rhs, frct, u, rho_i, qs, us, vs, square, ws);
  else if (tile_kind == 2)
         comp(rhs, frct, u, rho_i, qs, us, vs, square, ws);
       else
          comp_pluto();


   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}

