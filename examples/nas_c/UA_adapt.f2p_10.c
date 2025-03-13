for(iz = 1; iz <= N1; iz++){
  for(ix = 1; ix <= N2; ix++){
    y[ix][1][iz]=x1[ix][1][iz];

    y[ix][2][iz]=0;
    for(ip = 1; ip <= N3; ip++){
      y[ix][2][iz]=y[ix][2][iz]+map2[ip]*x1[ix][ip][iz];
    }

    y[ix][3][iz]=x1[ix][lx1][iz];

    y[ix][4][iz]=0;
    for(ip = 1; ip <= N4; ip++){
      y[ix][4][iz]=y[ix][4][iz]+map4[ip]*x2[ix][ip][iz];
    }
 
    y[ix][lx1][iz]=x2[ix][lx1][iz];
  }
}

