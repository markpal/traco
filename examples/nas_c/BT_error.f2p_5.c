for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      for(m = 1; m <= 5; m++){
        add = rhs[m][i][j][k];
        rms[m] = rms[m] + add*add;
      }
    }
  }
}

