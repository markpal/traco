for(iy = 1; iy <= N1; iy++){
  for(ix = 1; ix <= N2; ix++){
    y[ix][iy][1]=x1[ix][iy][1];

    y[ix][iy][2]=0;
    for(ip = 1; ip <= N3; ip++){
      y[ix][iy][2]=y[ix][iy][2]+map2[ip]*x1[ix][iy][ip];
    }

    y[ix][iy][3]=x1[ix][iy][lx1];

    y[ix][iy][4]=0;
    for(ip = 1; ip <= N4; ip++){
      y[ix][iy][4]=y[ix][iy][4]+map4[ip]*x2[ix][iy][ip];
    }

    y[ix][iy][lx1]=x2[ix][iy][lx1];
  }
}

