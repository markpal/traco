int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  for(i = N3; i <= N4; i++){
    phi1[i][k] = c2*(  u[5][i][jbeg][k] - 0.50 * (  u[2][i][jbeg][k] ** 2 + u[3][i][jbeg][k] ** 2 + u[4][i][jbeg][k] ** 2 ) / u[1][i][jbeg][k] );
  }
}


#pragma endscop
}