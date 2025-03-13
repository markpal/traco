int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  for(j = N3; j <= N4; j++){
    phi2[j][k] = c2*(  u[5][ifin][j][k] - 0.50 * (  u[2][ifin][j][k] ** 2 + u[3][ifin][j][k] ** 2 + u[4][ifin][j][k] ** 2 ) / u[1][ifin][j][k] );
  }
}


#pragma endscop
}