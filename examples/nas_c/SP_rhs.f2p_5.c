int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      wijk = ws[i][j][k];
      wp1  = ws[i][j][k+1];
      wm1  = ws[i][j][k-1];
      
      rhs[1][i][j][k] = rhs[1][i][j][k] + dz1tz1 * (u[1][i][j][k+1] - 2.0*u[1][i][j][k] + u[1][i][j][k-1]) - tz2 * (u[4][i][j][k+1] - u[4][i][j][k-1]);
      rhs[2][i][j][k] = rhs[2][i][j][k] + dz2tz1 * (u[2][i][j][k+1] - 2.0*u[2][i][j][k] + u[2][i][j][k-1]) + zzcon2 * (us[i][j][k+1] - 2.0*us[i][j][k] + us[i][j][k-1]) - tz2 * (u[2][i][j][k+1]*wp1 - u[2][i][j][k-1]*wm1);
      rhs[3][i][j][k] = rhs[3][i][j][k] + dz3tz1 * (u[3][i][j][k+1] - 2.0*u[3][i][j][k] + u[3][i][j][k-1]) + zzcon2 * (vs[i][j][k+1] - 2.0*vs[i][j][k] + vs[i][j][k-1]) - tz2 * (u[3][i][j][k+1]*wp1 - u[3][i][j][k-1]*wm1);
      rhs[4][i][j][k] = rhs[4][i][j][k] + dz4tz1 * (u[4][i][j][k+1] - 2.0*u[4][i][j][k] + u[4][i][j][k-1]) + zzcon2*con43 * (wp1 - 2.0*wijk + wm1) - tz2 * (u[4][i][j][k+1]*wp1 - u[4][i][j][k-1]*wm1 + (u[5][i][j][k+1] - square[i][j][k+1] - u[5][i][j][k-1] + square[i][j][k-1]) *c2);
      rhs[5][i][j][k] = rhs[5][i][j][k] + dz5tz1 * (u[5][i][j][k+1] - 2.0*u[5][i][j][k] + u[5][i][j][k-1]) + zzcon3 * (qs[i][j][k+1] - 2.0*qs[i][j][k] + qs[i][j][k-1]) + zzcon4 * (wp1*wp1 - 2.0*wijk*wijk + wm1*wm1) + zzcon5 * (u[5][i][j][k+1]*rho_i[i][j][k+1] - 2.0*u[5][i][j][k]*rho_i[i][j][k] + u[5][i][j][k-1]*rho_i[i][j][k-1]) - tz2 * ( (c1*u[5][i][j][k+1] - c2*square[i][j][k+1])*wp1 - (c1*u[5][i][j][k-1] - c2*square[i][j][k-1])*wm1);
    }
  }
}


#pragma endscop
}