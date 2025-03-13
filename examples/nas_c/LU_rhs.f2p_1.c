int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      for(z = 1; z <= 5; z++){
        rsd[z][i][j][k] = - frct[z][i][j][k];
      }
      tmp = 1.0 / u[1][i][j][k];
      rho_i[i][j][k] = tmp;
      qs[i][j][k] = 0.50 * (  u[2][i][j][k] * u[2][i][j][k] + u[3][i][j][k] * u[3][i][j][k] + u[4][i][j][k] * u[4][i][j][k] ) * tmp;
    }
  }
}


#pragma endscop
}