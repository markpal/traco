int main(){
#pragma scop

for(k = 0; k <= N1; k++){
  for(j = 0; j <= N2; j++){
    for(i = 0; i <= N3; i++){
      u[1][i][j][k] = 1.0;
      u[2][i][j][k] = 0.0;
      u[3][i][j][k] = 0.0;
      u[4][i][j][k] = 0.0;
      u[5][i][j][k] = 1.0;
    }
  }
}


#pragma endscop
}