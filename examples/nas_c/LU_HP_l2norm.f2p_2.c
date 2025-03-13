for(l = 2; l <= N1; l++){
  for(j = N2; j <= N3; j++){
    for(i = N4; i <= N5; i++){
      for(z = 1; z <= 5; z++){
        sum[z] = sum[z] + v[z][i][j][l] * v[z][i][j][l];
      }
    }
  }
}

