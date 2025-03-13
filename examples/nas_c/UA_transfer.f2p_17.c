for(col = 1; col <= N1; col++){
  temp[col][1]=tx[col][1];
  j = 1;
  bottom[col]= 0.;
  for(i = 2; i <= N2; i++){
    bottom[col]=bottom[col] + qbnew[i-1][j][1]*tx[col][i];
  }
  
  for(i = 2; i <= N3; i++){
    for(j = 2; j <= N4; j++){
      temp[col][i] = temp[col][i] + qbnew[j-1][i][1]*tx[col][j];
    }
    
  }
}

