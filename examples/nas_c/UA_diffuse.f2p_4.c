for(iz = 1; iz <= N1; iz++){
  for(ppp = 1; ppp <= N2; ppp++){
    for(j = 1; j <= N3; j++){
      for(i = 1; i <= N4; i++){
        tm2[i][j][iz] = tm2[i][j][iz]+u[i][ppp][iz]*wdtdr[ppp][j];
      }
    }
  }
}

