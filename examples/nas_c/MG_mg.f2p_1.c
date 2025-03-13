for(ax = 1; ax <= 3; ax++){
  for(l = N1; l <= N2; l++){
    ng[ax][l] = ng[ax][l+1]/2;
  }
}

