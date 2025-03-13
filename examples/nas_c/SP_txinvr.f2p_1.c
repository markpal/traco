int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      ;
      ru1 = rho_i[i][j][k];
      uu = us[i][j][k];
      vv = vs[i][j][k];
      ww = ws[i][j][k];
      ac = speed[i][j][k];
      ac2inv = 1.0 / ( ac*ac );
      ;
      r1 = rhs[1][i][j][k];
      r2 = rhs[2][i][j][k];
      r3 = rhs[3][i][j][k];
      r4 = rhs[4][i][j][k];
      r5 = rhs[5][i][j][k];
      ;
      t1 = c2 * ac2inv * ( qs[i][j][k]*r1 - uu*r2  - vv*r3 - ww*r4 + r5 );
      t2 = bt * ru1 * ( uu * r1 - r2 );
      t3 = ( bt * ru1 * ac ) * t1;
      ;
      rhs[1][i][j][k] = r1 - t1;
      rhs[2][i][j][k] = - ru1 * ( ww*r1 - r4 );
      rhs[3][i][j][k] =   ru1 * ( vv*r1 - r3 );
      rhs[4][i][j][k] = - t2 + t3;
      rhs[5][i][j][k] =   t2 + t3;
      ;
    }
  }
}


#pragma endscop
}