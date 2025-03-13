int main(){
#pragma scop

for(k = 2; k <= N1; k++){
  for(j = N2; j <= N3; j++){
    for(i = N4; i <= N5; i++){
      for(m = 1; m <= 5; m++){
        sum[m] = sum[m] + v[m][i][j][k] * v[m][i][j][k];
      }
    }
  }
}


#pragma endscop
}