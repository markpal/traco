int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= N2; i++){
    for(n = 1; n <= 5; n++){
      for(m = 1; m <= 5; m++){
        a[m][n][i][j] = 0.;
        b[m][n][i][j] = 0.;
        c[m][n][i][j] = 0.;
        d[m][n][i][j] = 0.;
      }
    }
  }
}


#pragma endscop
}