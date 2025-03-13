int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      ;
      r1 = rhs[1][i][j][k];
      r2 = rhs[2][i][j][k];
      r3 = rhs[3][i][j][k];
      r4 = rhs[4][i][j][k];
      r5 = rhs[5][i][j][k];
      ;
      t1 = bt * r3;
      t2 = 0.5 * ( r4 + r5 );
      ;
      rhs[1][i][j][k] = -r2;
      rhs[2][i][j][k] =  r1;
      rhs[3][i][j][k] = bt * ( r4 - r5 );
      rhs[4][i][j][k] = -t1 + t2;
      rhs[5][i][j][k] =  t1 + t2;
    }
  }
}


#pragma endscop
}