for(p = 1; p <= N1; p++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      for(m = 1; m <= 5; m++){
        add = rhs[m][i][j][p];
        rms[m] = rms[m] + add*add;
      }
    }
  }
}

