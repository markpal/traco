for(pp = 1; pp <= N1; pp++){
  for(iz = 1; iz <= N2; iz++){
    for(j = 1; j <= N3; j++){
      for(i = 1; i <= N4; i++){
        r[i][j][iz] = r[i][j][iz]+u[i][j][pp]*wdtdr[pp][iz];
      }
    }
  }
}

