for(iz = 1; iz <= N1; iz++){
  for(p = 1; p <= N2; p++){
    for(j = 1; j <= N3; j++){
      for(i = 1; i <= N4; i++){
        tm1[i][j][iz] = tm1[i][j][iz]+wdtdr[i][p]*u[p][j][iz];
      }
    }
  }
}

