for(i = 1; i <= N1; i++){
  for(l = 1; l <= N2; l++){
    for(j = 1; j <= N3; j++){
      y[j][l][i]=y[j][l][i]*twiddle[j][l][i];
      x[j][l][i]=y[j][l][i];
    }
  }
}
