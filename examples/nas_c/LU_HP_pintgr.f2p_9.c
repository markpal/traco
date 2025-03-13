int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  for(j = N3; j <= N4; j++){
    phi1[j][k] = c2*(  u[5][ibeg][j][k] - 0.50 * (  u[2][ibeg][j][k] ** 2 + u[3][ibeg][j][k] ** 2 + u[4][ibeg][j][k] ** 2 ) / u[1][ibeg][j][k] );
  }
}


#pragma endscop
}