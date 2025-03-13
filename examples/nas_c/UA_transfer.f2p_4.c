for(col = 1; col <= N1; col++){
  temp[col]=tx[col][1][1];
  for(i = 2; i <= N2; i++){
    temp[col] = temp[col] + qbnew[i-1][1][1]*tx[col][i][1];
  }
}

