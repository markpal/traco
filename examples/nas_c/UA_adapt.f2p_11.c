int main(){
#pragma scop

for(iz = 1; iz <= N1; iz++){
  for(iy = 1; iy <= N2; iy++){
    y[1][iy][iz]=x1[1][iy][iz];

    y[2][iy][iz]=0;
    for(ip = 1; ip <= N3; ip++){
      y[2][iy][iz]=y[2][iy][iz]+map2[ip]*x1[ip][iy][iz];
    }

    y[3][iy][iz]=x1[lx1][iy][iz];

    y[4][iy][iz]=0;
    for(ip = 1; ip <= N4; ip++){
      y[4][iy][iz]=y[4][iy][iz]+map4[ip]*x2[ip][iy][iz];
    }

    y[lx1][iy][iz]=x2[lx1][iy][iz];
  }
}


#pragma endscop
}