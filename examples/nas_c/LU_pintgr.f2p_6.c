int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  for(i = N3; i <= N4; i++){
    phi2[i][k] = c2*(  u[5][i][jfin][k] - 0.50 * (  u[2][i][jfin][k] ** 2 + u[3][i][jfin][k] ** 2 + u[4][i][jfin][k] ** 2 ) / u[1][i][jfin][k] );
  }
}


#pragma endscop
}