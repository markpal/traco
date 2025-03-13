int main(){
int k,i,j,N1,N2,N3;

int rho_inv, u[6][100][100][100], rho_i[100][100][100];
int us[100][100][100], ws[100][100][100], vs[100][100][100];
int qs[100][100][100], square[100][100][100];

#pragma scop
for(k = 0; k <= N1; k++){
  for(j = 0; j <= N2; j++){
    for(i = 0; i <= N3; i++){
      rho_inv = 1.0/u[1][i][j][k];
      rho_i[i][j][k] = rho_inv;
      us[i][j][k] = u[2][i][j][k] * rho_inv;
      vs[i][j][k] = u[3][i][j][k] * rho_inv;
      ws[i][j][k] = u[4][i][j][k] * rho_inv;
      square[i][j][k]     = 0.5* ( u[2][i][j][k]*u[2][i][j][k] + u[3][i][j][k]*u[3][i][j][k] + u[4][i][j][k]*u[4][i][j][k] ) * rho_inv;
      qs[i][j][k] = square[i][j][k] * rho_inv;
    }
  }
}
#pragma endscop

return 0;

}
