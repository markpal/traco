int main(){
#pragma scop

for(j = N1; j <= N2; j++){
  for(i = N3; i <= N4; i++){
    k = ki1;
    phi1[i][j] = c2*(  u[5][i][j][k] - 0.50 * (  u[2][i][j][k] ** 2 + u[3][i][j][k] ** 2 + u[4][i][j][k] ** 2 ) / u[1][i][j][k] );
    k = ki2;
    phi2[i][j] = c2*(  u[5][i][j][k] - 0.50 * (  u[2][i][j][k] ** 2 + u[3][i][j][k] ** 2 + u[4][i][j][k] ** 2 ) / u[1][i][j][k] );
  }
}


#pragma endscop
}