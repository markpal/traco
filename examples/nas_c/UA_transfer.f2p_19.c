for(col = 2; col <= N1; col++){
  tmor[1][col]=tmor[1][col]+temp[1][col];
  for(j = 1; j <= N2; j++){
    for(i = 2; i <= N3; i++){
      tmor[j][col] = tmor[j][col] + qbnew[i-1][j][1] *temp[i][col];
    }
  }
}

