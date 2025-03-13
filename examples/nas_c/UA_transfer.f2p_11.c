for(col = 1; col <= N1; col++){
  i = 1;
  tmp[i][col]=tmor[i][col];
  for(i = 2; i <= N2; i++){
    for(j = 1; j <= N3; j++){
      tmp[i][col] = tmp[i][col] + qbnew[i-1][j][1]*tmor[j][col];
    }
  }
}

