int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      ;
      xvel = us[i][j][k];
      yvel = vs[i][j][k];
      zvel = ws[i][j][k];
      ac   = speed[i][j][k];
      ;
      ac2u = ac*ac;
      ;
      r1 = rhs[1][i][j][k];
      r2 = rhs[2][i][j][k];
      r3 = rhs[3][i][j][k];
      r4 = rhs[4][i][j][k];
      r5 = rhs[5][i][j][k];
      ;
      uzik1 = u[1][i][j][k];
      btuz  = bt * uzik1;
      ;
      t1 = btuz/ac * (r4 + r5);
      t2 = r3 + t1;
      t3 = btuz * (r4 - r5);
      ;
      rhs[1][i][j][k] = t2;
      rhs[2][i][j][k] = -uzik1*r2 + xvel*t2;
      rhs[3][i][j][k] =  uzik1*r1 + yvel*t2;
      rhs[4][i][j][k] =  zvel*t2  + t3;
      rhs[5][i][j][k] =  uzik1*(-xvel*r2 + yvel*r1) + qs[i][j][k]*t2 + c2iv*ac2u*t1 + zvel*t3;
      ;
    }
  }
}


#pragma endscop
}