for(j = 1; j <= N1; j++){
  for(i = 2; i <= N2; i++){
    tmor[j][col]=tmor[j][col] + qbnew[i-1][j][1] *bottom[i] + qbnew[i-1][j][1] *temp[i][col];
  }
}

